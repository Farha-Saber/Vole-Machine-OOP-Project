#include "MainWindow.h"
#include "InstructionValidator.h"
#include "ProgramLoader.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QStringList>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

static QString hex2(int v) {
    return QString("%1").arg(v, 2, 16, QChar('0')).toUpper();
}

static QString reg(int n) {
    return "R" + QString::number(n, 16).toUpper();
}

// Human-readable description of one 16-bit instruction word.
static QString describe(int w) {
    int op = (w >> 12) & 0xF;
    int r = (w >> 8) & 0xF;
    int x = (w >> 4) & 0xF;
    int y = w & 0xF;
    int xy = w & 0xFF;

    InstructionFields f{
        static_cast<uint8_t>(op), static_cast<uint8_t>(r),
        static_cast<uint8_t>(x), static_cast<uint8_t>(y)
    };
    if (!InstructionValidator::validate(f)) {
        return "-- invalid / data --";
    }

    switch (op) {
    case 0x1: return "LOAD " + reg(r) + " <- memory[" + hex2(xy) + "]";
    case 0x2: return "LOAD " + reg(r) + " <- value " + hex2(xy);
    case 0x3:
        if (xy == 0xFF) return "STORE " + reg(r) + " -> SCREEN (FF)";
        return "STORE " + reg(r) + " -> memory[" + hex2(xy) + "]";
    case 0x4: return "MOVE " + reg(x) + " -> " + reg(y);
    case 0x5: return "ADD " + reg(r) + " = " + reg(x) + " + " + reg(y);
    case 0x6: return "ADD(float) " + reg(r) + " = " + reg(x) + " + " + reg(y);
    case 0x7: return "OR " + reg(r) + " = " + reg(x) + " | " + reg(y);
    case 0x8: return "AND " + reg(r) + " = " + reg(x) + " & " + reg(y);
    case 0x9: return "XOR " + reg(r) + " = " + reg(x) + " ^ " + reg(y);
    case 0xA: return "ROTATE " + reg(r) + " right " + QString::number(y) + "x";
    case 0xB: return "JUMP to " + hex2(xy) + " if " + reg(r) + " == R0";
    case 0xC: return "HALT";
    default:  return "???";
    }
}

static QString makeStyle(int theme) {
    QString bg, field, border, text, muted, accent, btn, btnH, header, primary, primaryText, danger, font;
    if (theme == 0) {          // dark
        bg = "#1b1d23"; field = "#14161a"; border = "#343845"; text = "#e6e6e6";
        muted = "#9aa0a6"; accent = "#8ab4f8"; btn = "#2b2f3a"; btnH = "#383d4c";
        header = "#23262e"; primary = "#3b82f6"; primaryText = "#ffffff"; danger = "#ef5350";
    } else if (theme == 1) {   // light
        bg = "#f3f4f6"; field = "#ffffff"; border = "#c9ccd3"; text = "#1f2328";
        muted = "#5f6368"; accent = "#1a56c4"; btn = "#e4e7ec"; btnH = "#d3d8e0";
        header = "#e9ecf1"; primary = "#2563eb"; primaryText = "#ffffff"; danger = "#c62828";
    } else {                   // CRT
        bg = "#000000"; field = "#020a02"; border = "#1f6f1f"; text = "#39ff14";
        muted = "#1fa31f"; accent = "#7dff7d"; btn = "#031a03"; btnH = "#0a330a";
        header = "#052005"; primary = "#0f5f0f"; primaryText = "#b6ffb6"; danger = "#ff5555";
        font = "font-family:'Consolas','Courier New',monospace;";
    }

    QString css =
        "QMainWindow, QWidget { background:%BG%; color:%TEXT%; font-size:13px; %FONT% }"
        "QGroupBox { border:1px solid %BORDER%; border-radius:8px; margin-top:14px; padding:10px; font-weight:bold; }"
        "QGroupBox::title { subcontrol-origin: margin; left:12px; padding:0 6px; color:%ACCENT%; }"
        "QLineEdit, QPlainTextEdit, QTableWidget, QListWidget { background:%FIELD%; border:1px solid %BORDER%; border-radius:5px; gridline-color:%BORDER%; }"
        "QLineEdit { padding:5px; font: 14px 'Consolas','Courier New',monospace; }"
        "QListWidget { font: 13px 'Consolas','Courier New',monospace; }"
        "QListWidget::item { padding:3px; }"
        "QHeaderView::section { background:%HEADER%; color:%MUTED%; border:0; padding:3px; font-weight:bold; }"
        "QTableWidget { font: 13px 'Consolas','Courier New',monospace; }"
        "QPushButton { background:%BTN%; border:1px solid %BORDER%; border-radius:6px; padding:7px 14px; }"
        "QPushButton:hover { background:%BTNH%; }"
        "QPushButton#primary { background:%PRIMARY%; border:0; color:%PRIMARYTEXT%; font-weight:bold; }"
        "QPushButton#danger { color:%DANGER%; }"
        "QLabel#caption { color:%MUTED%; font-weight:bold; }"
        "QLabel#valueBox { background:%FIELD%; border:1px solid %BORDER%; border-radius:5px; padding:8px; font: bold 17px 'Consolas','Courier New',monospace; }";

    css.replace("%BG%", bg).replace("%FIELD%", field).replace("%BORDER%", border)
       .replace("%TEXT%", text).replace("%MUTED%", muted).replace("%ACCENT%", accent)
       .replace("%BTNH%", btnH).replace("%BTN%", btn).replace("%HEADER%", header)
       .replace("%PRIMARYTEXT%", primaryText).replace("%PRIMARY%", primary)
       .replace("%DANGER%", danger).replace("%FONT%", font);
    return css;
}

MainWindow::MainWindow() {
    setWindowTitle("Vole Machine Simulator");
    resize(1420, 780);

    // ======================= LEFT COLUMN =======================
    addrEdit = new QLineEdit("00");
    addrEdit->setMaxLength(2);
    addrEdit->setMaximumWidth(60);
    addrEdit->setToolTip("Start address in hex (even number, 00 to FE)");

    instrEdit = new QLineEdit;
    instrEdit->setMaxLength(4);
    instrEdit->setPlaceholderText("e.g. 2005");
    instrEdit->setValidator(new QRegularExpressionValidator(
        QRegularExpression("[0-9A-Fa-f]{0,4}"), this));
    auto* storeBtn = new QPushButton("STORE");
    storeBtn->setObjectName("primary");

    pathEdit = new QLineEdit;
    pathEdit->setPlaceholderText("program file (.txt)");
    auto* browseBtn = new QPushButton("Browse");
    auto* loadBtn = new QPushButton("Load Program");
    loadBtn->setObjectName("primary");

    auto* progBox = new QGroupBox("Program");
    auto* pg = new QGridLayout(progBox);
    pg->addWidget(new QLabel("Address (hex)"), 0, 0);
    pg->addWidget(addrEdit, 0, 1);
    pg->addWidget(new QLabel("Instruction"), 1, 0);
    pg->addWidget(instrEdit, 1, 1);
    pg->addWidget(storeBtn, 1, 2);
    pg->addWidget(new QLabel("File"), 2, 0);
    pg->addWidget(pathEdit, 2, 1);
    pg->addWidget(browseBtn, 2, 2);
    pg->addWidget(loadBtn, 3, 0, 1, 3);

    regTable = new QTableWidget(8, 2);
    regTable->horizontalHeader()->setVisible(false);
    regTable->verticalHeader()->setVisible(false);
    regTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    regTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    regTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    regTable->setSelectionMode(QAbstractItemView::NoSelection);
    regTable->setToolTip("Double-click a register to edit it");
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 2; ++col) {
            auto* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            regTable->setItem(row, col, item);
        }
    }
    regTable->setMinimumHeight(230);

    pcLabel = new QLabel("00");
    pcLabel->setObjectName("valueBox");
    irLabel = new QLabel("0000");
    irLabel->setObjectName("valueBox");
    auto* pcCap = new QLabel("PC");
    pcCap->setObjectName("caption");
    auto* irCap = new QLabel("IR");
    irCap->setObjectName("caption");

    auto* cpuBox = new QGroupBox("CPU Registers");
    auto* cg = new QGridLayout(cpuBox);
    cg->addWidget(regTable, 0, 0, 1, 2);
    cg->addWidget(pcCap, 1, 0);
    cg->addWidget(irCap, 1, 1);
    cg->addWidget(pcLabel, 2, 0);
    cg->addWidget(irLabel, 2, 1);

    auto* left = new QVBoxLayout;
    left->addWidget(progBox);
    left->addWidget(cpuBox, 1);

    // ======================= CENTER: memory + listing =======================
    memTable = new QTableWidget(16, 16);
    QStringList heads;
    for (int i = 0; i < 16; ++i) heads << QString::number(i, 16).toUpper();
    memTable->setHorizontalHeaderLabels(heads);
    memTable->setVerticalHeaderLabels(heads);
    memTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    memTable->setSelectionMode(QAbstractItemView::NoSelection);
    memTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->setMinimumHeight(360);
    memTable->setToolTip("Double-click a cell to edit. Orange = instruction at PC, green = just changed.");
    for (int r = 0; r < 16; ++r) {
        for (int c = 0; c < 16; ++c) {
            auto* item = new QTableWidgetItem("00");
            item->setTextAlignment(Qt::AlignCenter);
            memTable->setItem(r, c, item);
        }
    }
    heatCheck = new QCheckBox("Heatmap (brighter = larger value)");
    auto* memBox = new QGroupBox("Memory   (row digit + column digit = address)");
    auto* mg = new QVBoxLayout(memBox);
    mg->addWidget(heatCheck);
    mg->addWidget(memTable, 1);

    listView = new QListWidget;
    listView->setSelectionMode(QAbstractItemView::NoSelection);
    listView->setToolTip("Readable view of the program. > marks the next instruction.");
    auto* listBox = new QGroupBox("Program Listing");
    auto* lg = new QVBoxLayout(listBox);
    lg->addWidget(listView);
    listBox->setFixedWidth(340);

    auto* centerRow = new QHBoxLayout;
    centerRow->addWidget(memBox, 1);
    centerRow->addWidget(listBox);

    // ======================= SCREEN + BUTTONS =======================
    screenView = new QPlainTextEdit;
    screenView->setReadOnly(true);
    screenView->setMaximumHeight(110);
    screenView->setStyleSheet(
        "background:#0d0f12; color:#39ff14; border:1px solid #343845;"
        "font: 14px 'Consolas','Courier New',monospace;");
    auto* screenBox = new QGroupBox("Screen  (values stored to FF)");
    auto* sg = new QVBoxLayout(screenBox);
    sg->addWidget(screenView);

    auto* runBtn = new QPushButton("Run  (F5)");
    runBtn->setObjectName("primary");
    runBtn->setShortcut(QKeySequence(Qt::Key_F5));
    auto* stepBtn = new QPushButton("Step  (F10)");
    stepBtn->setShortcut(QKeySequence(Qt::Key_F10));
    auto* resetCpuBtn = new QPushButton("Reset CPU");
    auto* resetMemBtn = new QPushButton("Reset Memory");
    resetMemBtn->setObjectName("danger");
    themeBtn = new QPushButton("Theme: Dark");
    auto* helpBtn = new QPushButton("Help");

    auto* buttons = new QHBoxLayout;
    buttons->addWidget(runBtn, 2);
    buttons->addWidget(stepBtn, 2);
    buttons->addWidget(resetCpuBtn, 2);
    buttons->addWidget(resetMemBtn, 2);
    buttons->addWidget(themeBtn, 2);
    buttons->addWidget(helpBtn, 1);

    auto* right = new QVBoxLayout;
    right->addLayout(centerRow, 1);
    right->addWidget(screenBox);
    right->addLayout(buttons);

    // ======================= WINDOW =======================
    statusLabel = new QLabel("Type an instruction and press STORE, or load a program file.");

    auto* columns = new QHBoxLayout;
    auto* leftWidget = new QWidget;
    leftWidget->setLayout(left);
    leftWidget->setFixedWidth(360);
    columns->addWidget(leftWidget);
    columns->addLayout(right, 1);

    auto* root = new QVBoxLayout;
    root->addLayout(columns, 1);
    root->addWidget(statusLabel);
    auto* central = new QWidget;
    central->setLayout(root);
    setCentralWidget(central);

    applyTheme();

    // ======================= CONNECTIONS =======================
    connect(browseBtn, &QPushButton::clicked, this, &MainWindow::browse);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadProgram);
    connect(storeBtn, &QPushButton::clicked, this, &MainWindow::storeInstruction);
    connect(instrEdit, &QLineEdit::returnPressed, this, &MainWindow::storeInstruction);
    connect(runBtn, &QPushButton::clicked, this, &MainWindow::runAll);
    connect(stepBtn, &QPushButton::clicked, this, &MainWindow::stepOnce);
    connect(resetCpuBtn, &QPushButton::clicked, this, &MainWindow::resetCpu);
    connect(resetMemBtn, &QPushButton::clicked, this, &MainWindow::resetMemory);
    connect(themeBtn, &QPushButton::clicked, this, &MainWindow::cycleTheme);
    connect(heatCheck, &QCheckBox::toggled, this, [this]() { refresh(false); });
    connect(helpBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Help",
            "Option A - type instructions:\n"
            "  Write 4 hex digits (e.g. 2005) and press STORE or Enter.\n"
            "  Each instruction goes to the address box, then the address moves to the next one.\n\n"
            "Option B - load a file:\n"
            "  Browse, choose an even start address, press Load Program.\n\n"
            "Then press Step (one instruction) or Run (all).\n"
            "Double-click any register or memory cell to edit it.\n\n"
            "Colors: orange = next instruction (PC), green = value that just changed.\n"
            "Program Listing shows each instruction in plain words.\n"
            "Heatmap colors memory cells by their value.\n"
            "Theme cycles Dark / Light / CRT.\n"
            "Reset CPU keeps memory and goes back to the program start.");
    });
    connect(regTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::editRegister);
    connect(memTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::editMemory);

    refresh(false);
}

void MainWindow::applyTheme() {
    setStyleSheet(makeStyle(theme));
    static const char* names[] = {"Dark", "Light", "CRT"};
    themeBtn->setText(QString("Theme: ") + names[theme]);
}

void MainWindow::cycleTheme() {
    theme = (theme + 1) % 3;
    applyTheme();
    refresh(false);
}

void MainWindow::setStatus(const QString& text, bool ok) {
    statusLabel->setText(text);
    statusLabel->setStyleSheet(ok ? "color:#4caf50; font-weight:bold;"
                                  : "color:#ef5350; font-weight:bold;");
}

void MainWindow::refresh(bool markChanges) {
    const QBrush pcBrush(QColor("#ffb74d"));
    const QBrush changedBrush(QColor("#66bb6a"));
    const QBrush black(Qt::black);
    const bool heat = heatCheck->isChecked();
    const QColor heatBase = (theme == 2) ? QColor(57, 255, 20) : QColor(59, 130, 246);

    int pc = machine.getCpu().getPC();
    pcLabel->setText(hex2(pc));
    irLabel->setText(QString::fromStdString(machine.getCpu().getIRRaw()));

    // registers: index = column * 8 + row
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 2; ++col) {
            int index = col * 8 + row;
            int v = machine.getRegisters().getRegister(index);
            auto* item = regTable->item(row, col);
            item->setText(QString("R%1   %2").arg(index, 0, 16).toUpper().arg(hex2(v)));
            bool changed = markChanges && prevRegs[index] != v;
            item->setBackground(changed ? changedBrush : QBrush());
            item->setForeground(changed ? black : QBrush());
            prevRegs[index] = v;
        }
    }

    // memory
    for (int r = 0; r < 16; ++r) {
        for (int c = 0; c < 16; ++c) {
            int address = r * 16 + c;
            int v = machine.getMemory().read(address);
            auto* item = memTable->item(r, c);
            item->setText(hex2(v));
            bool atPc = loaded && (address == pc || address == pc + 1);
            bool changed = markChanges && prevMem[address] != v;
            if (atPc) {
                item->setBackground(pcBrush);
                item->setForeground(black);
            } else if (changed) {
                item->setBackground(changedBrush);
                item->setForeground(black);
            } else if (heat && v != 0) {
                QColor hc = heatBase;
                hc.setAlpha(50 + (v * 170) / 255);
                item->setBackground(QBrush(hc));
                item->setForeground(QBrush());
            } else {
                item->setBackground(QBrush());
                item->setForeground(QBrush());
            }
            prevMem[address] = v;
        }
    }

    // screen: backend log holds decimal values, one per line
    QString text;
    const QStringList lines = QString::fromStdString(machine.getScreen().getOutputLog())
                                  .split('\n', Qt::SkipEmptyParts);
    for (const QString& line : lines) {
        int v = line.toInt();
        text += hex2(v) + "   (" + QString::number(v) + ")\n";
    }
    screenView->setPlainText(text);

    rebuildListing();
}

void MainWindow::rebuildListing() {
    listView->clear();
    if (programStart < 0) {
        listView->addItem("No program yet.");
        return;
    }

    // show only the instructions that were stored or loaded
    int end = (programEnd >= programStart) ? programEnd : programStart;

    int pc = machine.getCpu().getPC();
    bool halted = machine.getCpu().isExecutionHalted();
    QListWidgetItem* current = nullptr;

    for (int a = programStart; a <= end; a += 2) {
        int w = (machine.getMemory().read(a) << 8) | machine.getMemory().read(a + 1);
        bool isNext = !halted && a == pc;
        QString line = QString(isNext ? "> " : "  ") + hex2(a) + ":  "
                     + hex2(w >> 8) + hex2(w & 0xFF) + "   " + describe(w);
        auto* item = new QListWidgetItem(line);
        if (isNext) {
            item->setBackground(QBrush(QColor("#ffb74d")));
            item->setForeground(QBrush(Qt::black));
            current = item;
        } else if (a == lastExec) {
            item->setBackground(QBrush(QColor("#66bb6a")));
            item->setForeground(QBrush(Qt::black));
        }
        listView->addItem(item);
    }
    if (current) listView->scrollToItem(current);
}

void MainWindow::browse() {
    QString file = QFileDialog::getOpenFileName(this, "Open Vole program", QString(),
                                                "Text files (*.txt);;All files (*)");
    if (!file.isEmpty()) pathEdit->setText(file);
}

void MainWindow::loadProgram() {
    bool ok = false;
    int start = addrEdit->text().trimmed().toInt(&ok, 16);
    if (!ok || start < 0 || start > 0xFE || start % 2 != 0) {
        setStatus("Address must be an even hex number from 00 to FE.", false);
        return;
    }
    if (pathEdit->text().trimmed().isEmpty()) {
        setStatus("Choose a program file first.", false);
        return;
    }
    loaded = machine.loadProgram(pathEdit->text().trimmed().toStdString(), start);
    if (loaded) {
        programStart = start;
        std::vector<uint16_t> tmp;
        ProgramLoader::readProgram(pathEdit->text().trimmed().toStdString(), tmp);
        programEnd = start + 2 * static_cast<int>(tmp.size()) - 2;
    }
    lastExec = -1;
    refresh(false);
    if (loaded) {
        setStatus("Program loaded at " + hex2(start) + ". PC = " + hex2(start) + ".");
    } else {
        setStatus("Rejected: file not found, empty, or has an invalid instruction.", false);
    }
}

void MainWindow::storeInstruction() {
    QString text = instrEdit->text().trimmed();
    if (text.size() != 4) {
        setStatus("An instruction must be exactly 4 hex digits.", false);
        return;
    }
    bool ok = false;
    int start = addrEdit->text().trimmed().toInt(&ok, 16);
    if (!ok || start < 0 || start > 0xFE || start % 2 != 0) {
        setStatus("Address must be an even hex number from 00 to FE.", false);
        return;
    }
    int value = text.toInt(&ok, 16);
    InstructionFields f{
        static_cast<uint8_t>((value >> 12) & 0xF),
        static_cast<uint8_t>((value >> 8) & 0xF),
        static_cast<uint8_t>((value >> 4) & 0xF),
        static_cast<uint8_t>(value & 0xF)
    };
    if (!InstructionValidator::validate(f)) {
        setStatus("Rejected: " + text.toUpper() + " is not a valid instruction.", false);
        return;
    }

    machine.getMemory().write(start, static_cast<uint8_t>((value >> 8) & 0xFF));
    machine.getMemory().write(start + 1, static_cast<uint8_t>(value & 0xFF));
    if (programStart < 0) programStart = start;
    if (start > programEnd) programEnd = start;
    machine.getCpu().reset();
    machine.getCpu().setPC(programStart);
    loaded = true;
    lastExec = -1;

    int next = start + 2;
    if (next <= 0xFE) {
        addrEdit->setText(hex2(next));
        setStatus("Stored " + text.toUpper() + " at " + hex2(start) + ". Next address: " + hex2(next) + ".");
    } else {
        setStatus("Stored " + text.toUpper() + " at " + hex2(start) + ". Memory is full.");
    }
    instrEdit->clear();
    refresh(true);
}

void MainWindow::runAll() {
    if (!loaded) {
        setStatus("Load or store a program first.", false);
        return;
    }
    // Step limit so an endless loop in a Vole program cannot freeze the window.
    const int maxSteps = 10000;
    int steps = 0;
    while (!machine.getCpu().isExecutionHalted() && steps < maxSteps) {
        lastExec = machine.getCpu().getPC();
        machine.step();
        ++steps;
    }
    refresh(true);
    if (machine.getCpu().isExecutionHalted()) {
        setStatus("Finished (halted) after " + QString::number(steps) + " steps.");
    } else {
        setStatus("Stopped after 10000 steps (possible infinite loop).", false);
    }
}

void MainWindow::stepOnce() {
    if (!loaded) {
        setStatus("Load or store a program first.", false);
        return;
    }
    if (machine.getCpu().isExecutionHalted()) {
        setStatus("Program already halted. Press Reset CPU to run again.", false);
        return;
    }
    lastExec = machine.getCpu().getPC();
    machine.step();
    refresh(true);
    if (machine.getCpu().isExecutionHalted()) {
        setStatus("Program halted.");
    } else {
        setStatus("Executed one instruction.");
    }
}

void MainWindow::resetCpu() {
    machine.getRegisters().clear();
    machine.getScreen().clear();
    machine.getCpu().reset();
    machine.getCpu().setPC(programStart >= 0 ? programStart : 0);
    lastExec = -1;
    refresh(false);
    setStatus("CPU reset. Memory kept, PC back to program start.");
}

void MainWindow::resetMemory() {
    machine.getMemory().clear();
    programStart = -1;
    programEnd = -1;
    lastExec = -1;
    loaded = false;
    addrEdit->setText("00");
    refresh(false);
    setStatus("Memory cleared.");
}

void MainWindow::editRegister(int row, int column) {
    int index = column * 8 + row;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Edit register",
        "New value for R" + QString::number(index, 16).toUpper() + " (hex 00-FF):",
        QLineEdit::Normal, hex2(machine.getRegisters().getRegister(index)), &ok);
    if (!ok) return;
    int v = text.trimmed().toInt(&ok, 16);
    if (!ok || v < 0 || v > 255) {
        setStatus("Invalid value. Use hex from 00 to FF.", false);
        return;
    }
    machine.getRegisters().setRegister(index, static_cast<uint8_t>(v));
    refresh(true);
    setStatus("Register updated.");
}

void MainWindow::editMemory(int row, int column) {
    int address = row * 16 + column;
    bool ok = false;
    QString text = QInputDialog::getText(this, "Edit memory cell",
        "New value for cell " + hex2(address) + " (hex 00-FF):",
        QLineEdit::Normal, hex2(machine.getMemory().read(address)), &ok);
    if (!ok) return;
    int v = text.trimmed().toInt(&ok, 16);
    if (!ok || v < 0 || v > 255) {
        setStatus("Invalid value. Use hex from 00 to FF.", false);
        return;
    }
    machine.getMemory().write(address, static_cast<uint8_t>(v));
    refresh(true);
    setStatus("Memory cell updated.");
}

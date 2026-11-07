#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <QMainWindow>
#include <QString>
#include "Machine.h"

class QTableWidget;
class QListWidget;
class QCheckBox;
class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void browse();
    void loadProgram();
    void storeInstruction();
    void runAll();
    void stepOnce();
    void resetCpu();
    void resetMemory();
    void cycleTheme();
    void editRegister(int row, int column);
    void editMemory(int row, int column);

private:
    void refresh(bool markChanges = true);
    void rebuildListing();
    void applyTheme();
    void setStatus(const QString& text, bool ok = true);

    Machine machine;
    bool loaded = false;
    int programStart = -1;
    int programEnd = -1;   // address of the last stored/loaded instruction
    int lastExec = -1;   // address of the last executed instruction
    int theme = 0;       // 0 = dark, 1 = light, 2 = CRT

    std::array<int, 16> prevRegs{};
    std::array<int, 256> prevMem{};

    QLineEdit* pathEdit;
    QLineEdit* addrEdit;
    QLineEdit* instrEdit;
    QTableWidget* memTable;
    QTableWidget* regTable;
    QListWidget* listView;
    QCheckBox* heatCheck;
    QLabel* pcLabel;
    QLabel* irLabel;
    QLabel* statusLabel;
    QPlainTextEdit* screenView;
    QPushButton* themeBtn;
};

#endif

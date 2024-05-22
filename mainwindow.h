#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NimGame.h"
#include <QMainWindow>
#include <QVector> // Include QVector header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateVisibleMatchsticks(); // Declaration of the function
    void updateVectorInfoLabel();
    NimGame *nimGame; // Declare NimGame instance

private:
    Ui::MainWindow *ui;
    QVector<int> visibleMatchsticks; // Declare the QVector to store counts of visible matchsticks

    int findNonEmptyRow(const QVector<int>& matchstickCounts);
     // Declaration of the function to find the first non-empty row

public slots:
    void removeMatchstickFromRow1(); // Declaration of function to remove matchstick from row 1
    void removeMatchstickFromRow2(); // Declaration of function to remove matchstick from row 2
    void removeMatchstickFromRow3(); // Declaration of function to remove matchstick from row 3
    void removeMatchstickFromRow4(); // Declaration of function to remove matchstick from row 4
    void updateNimSumLabel(int nimSum);
    void calculateNimSumAndUpdateLabel();
    void pcMove();
    void removeMatchstickForPcRow1(int count); // Declaration of function to remove matchsticks for PC from row 1
    void removeMatchstickForPcRow2(int count); // Declaration of function to remove matchsticks for PC from row 2
    void removeMatchstickForPcRow3(int count); // Declaration of function to remove matchsticks for PC from row 3
    void removeMatchstickForPcRow4(int count); // Declaration of function to remove matchsticks for PC from row 4
    void makeMove(int row, int numMatchsticksToRemove);
    void optimalMove(const QString& vectorInfo);
    void onPcMoveButtonClicked();
    void checkWinner(int lastMove);
    void resetWindow();

};

#endif // MAINWINDOW_H

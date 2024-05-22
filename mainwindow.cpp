#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NimGame.h"
#include "QDebug"
#include <QRegularExpression>
#include <QMessageBox>
#include <QRandomGenerator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nimGame = new NimGame(this);

    connect(ui->vectorButton, &QPushButton::clicked, this, &MainWindow::updateVectorInfoLabel);


    // Connect the signal from NimGame to the slot for updating nim sum label
    connect(nimGame, &NimGame::nimSumCalculated, this, &MainWindow::updateNimSumLabel);
    // Connect the clicked signal of nimsumButton to a slot in MainWindow
    connect(ui->nimsumButton, &QPushButton::clicked, this, &MainWindow::calculateNimSumAndUpdateLabel);







    // Set up connections for row buttons
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::removeMatchstickFromRow1);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::removeMatchstickFromRow2);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::removeMatchstickFromRow3);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::removeMatchstickFromRow4);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onPcMoveButtonClicked);

    // Connect the reset button
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::resetWindow);






    // Set the pixmap for all labels to the matchstick image
    ui->label->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_2->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_3->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_4->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_5->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_6->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_7->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_8->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_9->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_10->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_11->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_12->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_13->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_14->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_15->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_16->setPixmap(QPixmap(":/rec/matchstick2.png"));



    // Disable and hide vectorButton
    ui->vectorButton->setEnabled(false);
    ui->vectorButton->hide();

    // Disable and hide nimsumButton
    ui->nimsumButton->setEnabled(false);
    ui->nimsumButton->hide();

    // Hide vectorinfo label
    ui->vectorinfo->hide();
    ui->label_17->hide();




}

MainWindow::~MainWindow()
{
    delete ui;
}




#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::resetWindow() {


    // Set the pixmap for all labels to the matchstick image
    ui->label->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_2->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_3->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_4->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_5->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_6->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_7->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_8->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_9->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_10->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_11->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_12->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_13->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_14->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_15->setPixmap(QPixmap(":/rec/matchstick2.png"));
    ui->label_16->setPixmap(QPixmap(":/rec/matchstick2.png"));




    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);

    updateVectorInfoLabel();

}



void MainWindow::onPcMoveButtonClicked() {

    // Call updateVectorInfoLabel() to update vector information
    updateVectorInfoLabel();

    // Call pcMove() to handle PC's move
    pcMove();
}

void MainWindow::pcMove() {
    // Disable the button for PC move
    ui->pushButton_5->setEnabled(false);

    // Call optimalMove() to determine the PC's move
    optimalMove(ui->vectorinfo->text());

    // Enable the row buttons after PC move is done
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);

    checkWinner(0);
}




void MainWindow::optimalMove(const QString& vectorInfo) {
    // Use static regular expression to match numbers in the string
    static QRegularExpression regex("\\[(\\d+(?:,\\s*\\d+)*)\\]");
    QRegularExpressionMatch match = regex.match(vectorInfo);

    if (!match.hasMatch()) {
        qDebug() << "Invalid vector information format";
        return;
    }

    QString numbersString = match.captured(1);

    // Use static regular expression for splitting
    static QRegularExpression splitRegex(",\\s*");
    QStringList parts = numbersString.split(splitRegex, Qt::SkipEmptyParts);

    // Convert matched numbers to integers and store them in a QVector
    QVector<int> matchstickCounts;
    for (const QString &part : parts) {
        matchstickCounts.push_back(part.toInt());
    }

    // Check if the conditions for nim sum 1 move are met
    int conditionsMet = 0;
    if (matchstickCounts.size() >= 4) {
        if (matchstickCounts[0] == 0) {
            conditionsMet++;
        }
        if (matchstickCounts[1] <= 1) {
            conditionsMet++;
        }
        if (matchstickCounts[2] <= 2) {
            conditionsMet++;
        }
        if (matchstickCounts[3] <= 3) {
            conditionsMet++;
        }
    }

    // If at least two conditions are met, find the row where the nim sum 1 move can be made
    if (conditionsMet >= 2) {
        for (int row = 0; row < matchstickCounts.size(); ++row) {
            int numMatchsticks = matchstickCounts[row];
            if (numMatchsticks > 0) {
                for (int numToRemove = 1; numToRemove <= numMatchsticks; ++numToRemove) {
                    QVector<int> newVectorInfo = matchstickCounts;
                    newVectorInfo[row] -= numToRemove;
                    int nimSum = 0;
                    for (int i = 0; i < newVectorInfo.size(); ++i) {
                        nimSum ^= newVectorInfo[i];
                    }
                    if (nimSum == 1) {
                        makeMove(row + 1, numToRemove);
                        qDebug() << "PC Move: Row" << (row + 1) << ", Matchsticks" << numToRemove << "(Nim sum is 1)";
                        return;
                    }
                }
            }
        }
    }

    // If Nim sum 1 move is not possible, perform Nim sum 0 move
    for (int row = 0; row < matchstickCounts.size(); ++row) {
        int numMatchsticks = matchstickCounts[row];
        if (numMatchsticks > 0) {
            for (int numToRemove = 1; numToRemove <= numMatchsticks; ++numToRemove) {
                QVector<int> newVectorInfo = matchstickCounts;
                newVectorInfo[row] -= numToRemove;
                int nimSum = 0;
                for (int i = 0; i < newVectorInfo.size(); ++i) {
                    nimSum ^= newVectorInfo[i];
                }
                if (nimSum == 0) {
                    makeMove(row + 1, numToRemove);
                    qDebug() << "PC Move: Row" << (row + 1) << ", Matchsticks" << numToRemove << "(Nim sum is 0)";
                    return;
                }
            }
        }
    }


    // If no optimal move is found, make any move from a non-empty row
    for (int row = 0; row < matchstickCounts.size(); ++row) {
        if (matchstickCounts[row] > 0) {
            makeMove(row + 1, 1);
            qDebug() << "PC Move: Row" << (row + 1) << ", Matchsticks 1 (No optimal move, Nim sum is non-zero)";
            return;
        }
    }
}

























void MainWindow::makeMove(int row, int numMatchsticksToRemove) {
    switch (row) {
    case 1:
        removeMatchstickForPcRow1(numMatchsticksToRemove);
        break;
    case 2:
        removeMatchstickForPcRow2(numMatchsticksToRemove);
        break;
    case 3:
        removeMatchstickForPcRow3(numMatchsticksToRemove);
        break;
    case 4:
        removeMatchstickForPcRow4(numMatchsticksToRemove);
        break;
    default:
        // Invalid row, do nothing
        break;
    }
}


void MainWindow::removeMatchstickForPcRow1(int numMatchsticksToRemove) {
    // Check if there are still matchsticks in row 1
    if (!ui->label->pixmap().isNull()) {
        // Remove matchsticks one by one
        for (int i = 0; i < numMatchsticksToRemove; ++i) {
            if (!ui->label->pixmap().isNull()) {
                ui->label->clear();
            }
        }
        // Enable buttons for rows 2, 3, and 4
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        // Update the vector information label
        updateVectorInfoLabel();
    }
}

void MainWindow::removeMatchstickForPcRow2(int numMatchsticksToRemove) {
    // Check if there are still matchsticks in row 2
    if (!ui->label_2->pixmap().isNull() || !ui->label_3->pixmap().isNull() || !ui->label_4->pixmap().isNull()) {
        // Remove matchsticks one by one
        for (int i = 0; i < numMatchsticksToRemove; ++i) {
            if (!ui->label_4->pixmap().isNull()) {
                ui->label_4->clear();
            } else if (!ui->label_3->pixmap().isNull()) {
                ui->label_3->clear();
            } else if (!ui->label_2->pixmap().isNull()) {
                ui->label_2->clear();
            }
        }
        // Enable buttons for rows 1, 3, and 4
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        // Update the vector information label
        updateVectorInfoLabel();
    }
}

void MainWindow::removeMatchstickForPcRow3(int numMatchsticksToRemove) {
    // Check if there are still matchsticks in row 3
    if (!ui->label_5->pixmap().isNull() || !ui->label_6->pixmap().isNull() || !ui->label_7->pixmap().isNull() ||
        !ui->label_8->pixmap().isNull() || !ui->label_9->pixmap().isNull()) {
        // Remove matchsticks one by one
        for (int i = 0; i < numMatchsticksToRemove; ++i) {
            if (!ui->label_9->pixmap().isNull()) {
                ui->label_9->clear();
            } else if (!ui->label_8->pixmap().isNull()) {
                ui->label_8->clear();
            } else if (!ui->label_7->pixmap().isNull()) {
                ui->label_7->clear();
            } else if (!ui->label_6->pixmap().isNull()) {
                ui->label_6->clear();
            } else if (!ui->label_5->pixmap().isNull()) {
                ui->label_5->clear();
            }
        }
        // Enable buttons for rows 1, 2, and 4
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        // Update the vector information label
        updateVectorInfoLabel();
    }
}

void MainWindow::removeMatchstickForPcRow4(int numMatchsticksToRemove) {
    // Check if there are still matchsticks in row 4
    if (!ui->label_10->pixmap().isNull() || !ui->label_11->pixmap().isNull() || !ui->label_12->pixmap().isNull() ||
        !ui->label_13->pixmap().isNull() || !ui->label_14->pixmap().isNull() || !ui->label_15->pixmap().isNull() ||
        !ui->label_16->pixmap().isNull()) {
        // Remove matchsticks one by one
        for (int i = 0; i < numMatchsticksToRemove; ++i) {
            if (!ui->label_16->pixmap().isNull()) {
                ui->label_16->clear();
            } else if (!ui->label_15->pixmap().isNull()) {
                ui->label_15->clear();
            } else if (!ui->label_14->pixmap().isNull()) {
                ui->label_14->clear();
            } else if (!ui->label_13->pixmap().isNull()) {
                ui->label_13->clear();
            } else if (!ui->label_12->pixmap().isNull()) {
                ui->label_12->clear();
            } else if (!ui->label_11->pixmap().isNull()) {
                ui->label_11->clear();
            } else if (!ui->label_10->pixmap().isNull()) {
                ui->label_10->clear();
            }
        }
        // Enable buttons for rows 1, 2, and 3
        ui->pushButton_1->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        // Update the vector information label
        updateVectorInfoLabel();
    }
}








void MainWindow::updateNimSumLabel(int nimSum)
{
    // Update the label with the calculated nim sum
    ui->label_17->setText(QString("Nim Sum: %1").arg(nimSum));
}

void MainWindow::calculateNimSumAndUpdateLabel()
{
    // Get the vector information from the main window
    QString vectorInfoText = ui->vectorinfo->text();

    // Calculate the nim sum using NimGame with the obtained vector information
    int nimSum = nimGame->calculateNimSum(vectorInfoText);

    // Update the label with the calculated nim sum
    updateNimSumLabel(nimSum);
}






void MainWindow::updateVisibleMatchsticks() {
    // Clear the existing vector
    visibleMatchsticks.clear();

    // Check each row and count the visible matchsticks
    int visibleCount = 0;
    if (!ui->label->pixmap().isNull()) {
        ++visibleCount;
    }
    visibleMatchsticks.push_back(visibleCount);

    visibleCount = 0;
    for (int i = 2; i <= 4; ++i) {
        QLabel *label = findChild<QLabel *>("label_" + QString::number(i));
        if (label && !label->pixmap().isNull()) {
            ++visibleCount;
        }
    }
    visibleMatchsticks.push_back(visibleCount);

    visibleCount = 0;
    for (int i = 5; i <= 9; ++i) {
        QLabel *label = findChild<QLabel *>("label_" + QString::number(i));
        if (label && !label->pixmap().isNull()) {
            ++visibleCount;
        }
    }
    visibleMatchsticks.push_back(visibleCount);

    visibleCount = 0;
    for (int i = 10; i <= 16; ++i) {
        QLabel *label = findChild<QLabel *>("label_" + QString::number(i));
        if (label && !label->pixmap().isNull()) {
            ++visibleCount;
        }
    }
    visibleMatchsticks.push_back(visibleCount);
}

void MainWindow::removeMatchstickFromRow1()
{

        // Check if there is still a matchstick in row 1
        if (!ui->label->pixmap().isNull()) {
            // Remove the matchstick
            ui->label->clear();

            // Disable buttons for rows 2, 3, and 4
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(true);

            // Update the vector information label
            updateVectorInfoLabel();

            checkWinner(1);

        }

}

void MainWindow::removeMatchstickFromRow2()
{

        // Check if there are still matchsticks in row 2
        if (!ui->label_2->pixmap().isNull() || !ui->label_3->pixmap().isNull() || !ui->label_4->pixmap().isNull()) {
            // Remove one matchstick at a time, starting from label_4 and moving left
            if (!ui->label_4->pixmap().isNull()) {
                ui->label_4->clear();
            } else if (!ui->label_3->pixmap().isNull()) {
                ui->label_3->clear();
            } else if (!ui->label_2->pixmap().isNull()) {
                ui->label_2->clear();
            }


            // Disable buttons for rows 1, 3, and 4
            ui->pushButton_1->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(true);

            // Update the vector information label
            updateVectorInfoLabel();

            checkWinner(2);

        }

}

void MainWindow::removeMatchstickFromRow3()
{

        // Check if there are still matchsticks in row 3
        if (!ui->label_5->pixmap().isNull() || !ui->label_6->pixmap().isNull() || !ui->label_7->pixmap().isNull() ||
            !ui->label_8->pixmap().isNull() || !ui->label_9->pixmap().isNull()) {
            // Remove one matchstick at a time, starting from label_9 and moving left
            if (!ui->label_9->pixmap().isNull()) {
                ui->label_9->clear();
            } else if (!ui->label_8->pixmap().isNull()) {
                ui->label_8->clear();
            } else if (!ui->label_7->pixmap().isNull()) {
                ui->label_7->clear();
            } else if (!ui->label_6->pixmap().isNull()) {
                ui->label_6->clear();
            } else if (!ui->label_5->pixmap().isNull()) {
                ui->label_5->clear();
            }

            // Disable buttons for rows 1, 2, and 4
            ui->pushButton_1->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(true);

            // Update the vector information label
            updateVectorInfoLabel();

            checkWinner(3);
        }

}

void MainWindow::removeMatchstickFromRow4()
{

        // Check if there are still matchsticks in row 4
        if (!ui->label_10->pixmap().isNull() || !ui->label_11->pixmap().isNull() || !ui->label_12->pixmap().isNull() ||
            !ui->label_13->pixmap().isNull() || !ui->label_14->pixmap().isNull() || !ui->label_15->pixmap().isNull() ||
            !ui->label_16->pixmap().isNull()) {
            // Remove one matchstick at a time, starting from label_16 and moving left
            if (!ui->label_16->pixmap().isNull()) {
                ui->label_16->clear();
            } else if (!ui->label_15->pixmap().isNull()) {
                ui->label_15->clear();
            } else if (!ui->label_14->pixmap().isNull()) {
                ui->label_14->clear();
            } else if (!ui->label_13->pixmap().isNull()) {
                ui->label_13->clear();
            } else if (!ui->label_12->pixmap().isNull()) {
                ui->label_12->clear();
            } else if (!ui->label_11->pixmap().isNull()) {
                ui->label_11->clear();
            } else if (!ui->label_10->pixmap().isNull()) {
                ui->label_10->clear();
            }

            // Disable buttons for rows 1, 2, and 3
            ui->pushButton_1->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_5->setEnabled(true);
            // Update the vector information label
            updateVectorInfoLabel();

            checkWinner(4);

        }

}



void MainWindow::checkWinner(int lastMove) {
    // Get the current vector information from the label
    QString vectorInfo = ui->vectorinfo->text();

    // Use regular expression to extract the numbers from the vector information
    static QRegularExpression regex("\\[(\\d+(?:,\\s*\\d+)*)\\]");
    QRegularExpressionMatch match = regex.match(vectorInfo);

    if (match.hasMatch()) {
        QString numbersString = match.captured(1);

        // Use regular expression for splitting
        static QRegularExpression splitRegex(",\\s*");
        QStringList parts = numbersString.split(splitRegex, Qt::SkipEmptyParts);

        // Convert the matched numbers to integers and store them in a QVector
        QVector<int> visibleMatchsticks;
        for (const QString &part : parts) {
            visibleMatchsticks.push_back(part.toInt());
        }

        // Check if the current vector information matches any winning condition
        if (visibleMatchsticks == QVector<int>({1, 0, 0, 0}) ||
            visibleMatchsticks == QVector<int>({0, 1, 0, 0}) ||
            visibleMatchsticks == QVector<int>({0, 0, 1, 0}) ||
            visibleMatchsticks == QVector<int>({0, 0, 0, 1})) {
            // Determine the winner based on the last move

            QString winnerMessage;
                if (lastMove == 0) {
                winnerMessage = "PC Wins!";
            } else {
                winnerMessage = "User Wins!";
            }

            QMessageBox::information(this, "Game Over", winnerMessage);
        }
    }
}





void MainWindow::updateVectorInfoLabel() {

    updateVisibleMatchsticks();

    // Construct a QString to display the vector information
    QString vectorInfoText = "Vector Information: [";
    for (int i = 0; i < visibleMatchsticks.size(); ++i) {
        vectorInfoText += QString::number(visibleMatchsticks[i]);
        if (i < visibleMatchsticks.size() - 1) {
            vectorInfoText += ", ";
        }
    }
    vectorInfoText += "]";

    // Set the text of the vectorinfo label
    ui->vectorinfo->setText(vectorInfoText);
}

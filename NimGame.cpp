#include "NimGame.h"
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>
#include <iostream>

NimGame::NimGame(QObject *parent) : QObject(parent)
{
    // Constructor implementation
}

NimGame::~NimGame()
{
    // Destructor implementation
}

int NimGame::calculateNimSum(const QString &vectorInfoText)
{
    // Use static regular expression to match numbers in the string
    static QRegularExpression regex("\\[(\\d+(?:,\\s*\\d+)*)\\]");
    QRegularExpressionMatch match = regex.match(vectorInfoText);

    if (match.hasMatch()) {
        QString numbersString = match.captured(1);

        // Use static regular expression for splitting
        static QRegularExpression splitRegex(",\\s*");
        QStringList parts = numbersString.split(splitRegex, Qt::SkipEmptyParts);

        // Convert matched numbers to integers and store them in a QVector
        QVector<int> visibleMatchsticks;
        for (const QString &part : parts) {
            visibleMatchsticks.push_back(part.toInt());
        }

        // Calculate the Nim Sum
        int nimSum = 0;
        for (int i = 0; i < visibleMatchsticks.size(); ++i) {
            nimSum ^= visibleMatchsticks[i];
        }

        // Emit the signal with the calculated nim sum
        emit nimSumCalculated(nimSum);

        return nimSum;
    } else {
        return -1; // Or handle the error condition accordingly
    }
}









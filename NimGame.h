#ifndef NIMGAME_H
#define NIMGAME_H

#include <QObject>
#include <QString>

class NimGame : public QObject
{
    Q_OBJECT

public:
    explicit NimGame(QObject *parent = nullptr);
    ~NimGame();

    int calculateNimSum(const QString &vectorInfoText);

signals:
    void nimSumCalculated(int nimSum);





private:
};

#endif // NIMGAME_H

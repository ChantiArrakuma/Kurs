#ifndef ROFL_H
#define ROFL_H

#include <QObject>
#include <QtSql>
#include <QFile>

class rofl : public QObject
{
    Q_OBJECT

public:
    explicit rofl(QObject *parent = nullptr);
    Q_INVOKABLE void cute(int thr, int n);
signals:

};

#endif // ROFL_H

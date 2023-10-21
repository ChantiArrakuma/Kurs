#ifndef TABSE_H
#define TABSE_H

#include <QAbstractTableModel>
#include <QObject>
#include <QFile>
#include <QtSql>
#include <QVector>

class TabSe : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles
    {
        Place
    };
    explicit TabSe(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void readTxt(int threads);
    QVector<QVector<QString>> poo;



    int countLine = 0;
    int maxLine = 0;
    int n = 0;
    Q_INVOKABLE void setN(int newN);
    Q_INVOKABLE int getMaxLine();
    Q_INVOKABLE void setNewLine(int line);

protected:
    QHash<int, QByteArray> roleNames() const;




public slots:
    void updateModel();
    int getId(int row, int column);


};

#endif // TABSE_H

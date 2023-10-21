#include "tabse.h"

TabSe::TabSe(QObject *parent)
    : QAbstractTableModel(parent)
{
    readTxt(n);
}

void TabSe::readTxt(int threads)
{
    this->maxLine = 0;

    QString path("./out/");
    QString nameOfFile = "rofloKek_" + QString::number(threads) + ".txt";
    QFile file(path + nameOfFile);
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    QVector<QString> alla;

    alla = out.readAll().split("\r\n").toVector();

    for(int i = 0; i != alla.size(); i++)
    {
        poo.append(alla[i].split(" ").toVector());
        maxLine += 1;
    }
    return;
}

void TabSe::setN(int newN)
{
    QString path("./out/");
    QString nameOfFile = "rofloKek_" + QString::number(newN) + ".txt";
    QFile file(path + nameOfFile);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
        return;
    else
        file.close();

    this->n = newN;
    this->countLine = 0;
    this->poo.clear();
    readTxt(n);
    updateModel();
    return;
}

int TabSe::rowCount(const QModelIndex & /*parent*/) const
{
    return n;
}

int TabSe::columnCount(const QModelIndex & /*parent*/) const
{
    return n;
}

QHash<int, QByteArray> TabSe::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[Place] = "place";
    return roles;
}

QVariant TabSe::data(const QModelIndex &index, int role) const
{
    if(role == Place)
    {
        if(index.row() == poo[countLine][index.column()].toInt())
        {
            return "♕";
        }
        return "•";
    }

    //qDebug() << arr;
    if (role == Qt::DisplayRole)
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);
    return QVariant();
}

int TabSe::getId(int row, int column)
{
    return this->data(this->index(row, column), Place).toInt();
}

void TabSe::updateModel()
{
    beginResetModel();
    endResetModel();
    return;
}

void TabSe::setNewLine(int line)
{
    countLine = line;
    this->updateModel();
    return;
}

int TabSe::getMaxLine()
{
    return this->maxLine;
}

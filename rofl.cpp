#include "rofl.h"
#include <QDebug>
#include <QFuture>
#include <cmath>
#include <iostream>
#include <QTableView>

//Вывод массива (положений ферзей)
std::mutex m;
void out_kex(int* a, int n)
{
//    std::lock_guard<std::mutex> lg(m);
//    QString st = "";
//    for (int i = 0; i < n; i++)
//    {
//        st += QString::number(a[i])+" ";
//    }


//    QSqlQuery query;
//    query.prepare("INSERT INTO threads (thr, queen)"
//               " VALUES (:thr, :queen)");
//    query.bindValue(":thr", n);
//    query.bindValue(":queen", st);
//    query.exec();
    std::lock_guard<std::mutex> lg(m);

    QString path("./out/");
    QDir dir;

    QString nameOfFile = "rofloKek_" + QString::number(n) + ".txt";

    QFile file(path + nameOfFile);
    file.open(QIODevice::Append | QFile::Text);
    QTextStream out(&file);
    for (int i = 0; i < n-1; i++)
    {
        out << a[i] << " ";
    }
    out << a[n-1];

    out << Qt::endl;

}

bool has_intersec(int x1, int y1, int x2, int y2)
{
    return (x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1));
}

bool valid_place(int* a, int step, int column)
{
    for (int i = 0; i < step; i++)
    {
        if (has_intersec(i, a[i], step, column))
            return 0;
    }
    return 1;
}

//Рекурсивный способ решения
void queen_set(int* a, int n, int step, int offset)
{
    if ((step == 0 && offset == n) || step == -1)
    {
        return;
    }
    if (step == n)
    {
        //out_kex(a, n);
        return;
    }
    //int max = 0;
    int i = offset;
    for (; i < n; i++)
    {
        if (valid_place(a, step, i))
        {
            a[step] = i;

            queen_set(a, n, step + 1, 0);
            break;

        }
    }
    queen_set(a, n, step - 1, a[step - 1] + 1);
}


int found_place(int* a, int n, int step, int offset)
{
    for (int i = offset; i < n; i++)
    {
        if (valid_place(a, step, i))
        {
            return i;
        }
    }
    return -1;
}


//не рекурсивный способ решения, принимает левую границу и правую (по первой строке)
int no_stack_queen_set(int* a, int n, int left, int right , int i)
{
    int step = 1;
    int offset = 0;
    int count_set = 0;
    a[0] = left;
    while (1)
    {
        while (step < n)
        {
            a[step] = found_place(a, n, step, offset);
            if ((a[step] == -1 || a[step] >= right) && step == 0)
            {
                return count_set;
            }
            if (a[step] == -1)
            {
                step--;
                offset = a[step] + 1;
            }
            else
            {
                step++;
                offset = 0;
            }

        }
        step = n - 2;
        offset = a[step] + 1;

        out_kex(a, n);                  // Раскомментировать для вывода, не доделано для многопоточности, "лепит" значения друг к другу, работает на 1 потоке.

        count_set++;
    }
}

//
int  func(int* a, int n, int thread_num)
{
    int res = 0;
    std::future<int>* results = new std::future<int>[thread_num];
    int last_paths = n;
    int last_threads = thread_num;

    int left = 0;

    for (int i = 0; i < thread_num; i++) {
        int right = left + std::ceil(last_paths / last_threads);
        last_paths = n - right;
        last_threads--;

        int* arr = new int[n];
//
        results[i] = std::async(no_stack_queen_set, arr, n, left, right, i);
        left = right;
    }
    for (int i = 0; i < thread_num; i++) {
        res += results[i].get();
    }
    return res;
}

rofl::rofl(QObject *parent)
    : QObject{parent}
{

}

void rofl::cute(int thr, int n)
{


    //int* a = new int[n];
    //qDebug() << func(a, n, thr);

    int* a = new int[n];

    QString path("./out/");
    QDir dir;
    QString nameOfFile = "rofloKek_" + QString::number(n) + ".txt";

    QFile file(path + nameOfFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        if (!dir.exists(path))
            dir.mkpath(path); // You can check the success if needed
        QFile file(path + nameOfFile);
        file.open(QIODevice::WriteOnly);
    }

    QTextStream out(&file);


    func(a, n, thr);
    qDebug() << "it's ok bro";



}



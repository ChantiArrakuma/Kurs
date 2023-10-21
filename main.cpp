#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QDebug"
#include <QQmlContext>

#include "rofl.h"
#include "tabse.h"

#include <QEvent>

#include <iostream>
#include <QFuture>
#include <cmath>

//#include "par.cpp"

//Делай через текстовый файл.



int main(int argc, char *argv[])
{


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    rofl art;

    QQmlContext* cont = engine.rootContext();
    cont->setContextProperty("art", &art);


    TabSe* tableModel = new TabSe();

    cont->setContextProperty("myModel", tableModel);
    //cont->setContextProperties()

    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    return app.exec();
}

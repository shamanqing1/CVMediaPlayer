#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "grayfilter.h"
#include "cvmediaplayer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    qmlRegisterType<GrayFilter>("my.video.filter", 1, 0, "GrayFilter");
    qmlRegisterType<CVMediaPlayer>("my.video.cvmedia", 1, 0, "CVMediaPlayer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

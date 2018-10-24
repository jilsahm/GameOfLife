#include <QGuiApplication>
#include <QQuickView>
//#include <QQmlApplicationEngine>

#include "gameboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<GameBoard>("game", 1, 0, "GameBoard");

    /*QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/views/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;*/

    QQuickView view(QUrl("qrc:/views/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.showFullScreen();

    return app.exec();
}

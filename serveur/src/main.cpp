#include <QApplication>
#include "gameserverlauncher.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    gameServerLauncher launch;
    launch.start();
    launch.show();

    return app.exec();
}


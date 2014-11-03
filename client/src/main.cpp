#include <QApplication>
#include <iostream>
#include <QtGui>
#include "Launcher.h"

using namespace std;

int main(int argc,char * argv[])
{
    QApplication app(argc , argv);

    Launcher launcher;
    launcher.show();

    return app.exec();
    return 0;
}


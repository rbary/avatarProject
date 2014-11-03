#include "Launcher.h"
Launcher::Launcher()
{
    p_management = new Management;
    setCentralWidget(p_management);

    QMenu * p_gameMenu = menuBar()->addMenu("&Menu");
    p_gameMenu->addAction("&Connection",this,SLOT(slot_seConnecterServeur()),Qt::Key_F1);
    p_gameMenu->addAction("&Quitter",this,SLOT(close()),Qt::CTRL + Qt::Key_Q);
    setFixedSquareSize((p_management->initSize()));
    setWindowTitle("Avatar Battle 2D");
    id=-1;
}

void Launcher::setFixedSquareSize(int size){
    centralWidget()->setFixedSize(size,size);
    setFixedSize(sizeHint());
}

void Launcher::slot_seConnecterServeur(){
    p_management->clientnetwork.show();
    p_management->clientnetwork.autoFillBackground();
    p_management->clientnetwork.activateWindow();
}


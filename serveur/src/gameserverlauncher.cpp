#include "gameserverlauncher.h"

gameServerLauncher::gameServerLauncher()
{
}

void gameServerLauncher::start()
{
    etatServeur = new QLabel;
    QString Serv;
    Serv = manag.getEtatServer();
    etatServeur->setText(Serv);
    boutonQuitter = new QPushButton(tr("Quitter"));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(etatServeur);
    layout->addWidget(boutonQuitter);
    setLayout(layout);

    setWindowTitle(tr("Game - Serveur"));

}

void gameServerLauncher::end()
{
    this->close();
}

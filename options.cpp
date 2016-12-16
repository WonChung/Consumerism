#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::lightGray);
    this->setPalette(palette);
}

options::~options()
{
    delete ui;
}

void options::openMain()
{
    uiMain = new MainWindow();
    // uiMain->adjustSize();
    uiMain->move(QApplication::desktop()->screen()->rect().center()-uiMain->rect().center());
    uiMain->show();
    this->close();
}

void options::pushButton2_clicked()
{
    gameMode = 0; // Singleplayer
    openMain();
}

void options::pushButton3_clicked()
{
    gameMode = 1; // Sandbox
    openMain();
}

void options::pushButton4_clicked()
{
    gameMode = 2; // AI FFA
    openMain();
}

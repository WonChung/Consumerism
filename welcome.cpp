#include "welcome.h"
#include "ui_welcome.h"

welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::darkGray);
    this->setPalette(palette);
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openOptions()));
}

welcome::~welcome()
{
    delete ui;
}

void welcome::openOptions()
{
    uiOptions = new options();

    uiOptions->show();
    this->close();
}

void welcome::openMain()
{
    uiMain = new MainWindow();
    uiMain->move(QApplication::desktop()->screen()->rect().center()-uiMain->rect().center());
    uiMain->show();
    uiMain->show();
    this->close();
}

void welcome::pushButton_clicked()
{
    openOptions();
}

void welcome::pushButton3_clicked()
{
    openMain();
}

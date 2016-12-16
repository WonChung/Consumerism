#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(openOptions()));
    // QPixmap backGround("door.png");
    // backGround = backGround.scaled(this->size(), Qt::IgnoreAspectRatio);
    // QPalette palette;
    // palette.setBrush(QPalette::Background, backGround);
    // this->setPalette(palette);
    // this->setStyleSheet("door.png");

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::darkGreen);
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//
// void MainWindow::openOptions()
// {
//     uiOptions = new options();
//
//     uiOptions->show();
//     this->close();
// }
//
// void MainWindow::pushButton5_clicked()
// {
//     openOptions();
// }

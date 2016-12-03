#include "options.h"
#include "ui_options.h"

options::options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::options)
{
    ui->setupUi(this);
}

options::~options()
{
    delete ui;
}

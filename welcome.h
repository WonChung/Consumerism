#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include "options.h"
#include "ui_options.h"

namespace Ui {
class welcome;
}

class welcome : public QDialog
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();
public slots:
    void openOptions();
    void openMain();
private:
    Ui::welcome *ui;
    options *uiOptions;
    MainWindow *uiMain;
    //void pushButton_clicked();
private slots:
    void pushButton_clicked();
    void pushButton3_clicked();
};

#endif // WELCOME_H

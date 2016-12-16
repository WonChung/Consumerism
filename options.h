#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class options;
}

class options : public QDialog
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = 0);
    ~options();
    int gameMode;
    inline int getmode() const {return gameMode; } 
public slots:
    void openMain();
private:
    Ui::options *ui;
    MainWindow *uiMain;

private slots:
    void pushButton2_clicked();
    void pushButton3_clicked();
    void pushButton4_clicked();
};

#endif // OPTIONS_H

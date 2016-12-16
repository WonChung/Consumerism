#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
// public slots:
//     void openOptions();

private:
    Ui::MainWindow *ui;
    // Ui::options *uiOptions;
// private slots:
//     void pushButton5_clicked();
};

#endif // MAINWINDOW_H

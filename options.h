#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
class options;
}

class options : public QDialog
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = 0);
    ~options();

private:
    Ui::options *ui;
};

#endif // OPTIONS_H

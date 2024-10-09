#ifndef REGISTER_H
#define REGISTER_H
#include <QDialog>

namespace Ui {
class signUp;
}

class signUp : public QDialog
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);
    ~signUp();

private slots:

private:
    Ui::signUp *ui;
};

#endif // REGISTER_H

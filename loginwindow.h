#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class loginWindow;
}
QT_END_NAMESPACE

class loginWindow : public QMainWindow
{
    Q_OBJECT

public:
    loginWindow(QWidget *parent = nullptr);
    ~loginWindow();

private slots:
    void on_login_button_clicked();

    void on_signup_button_clicked();

private:
    Ui::loginWindow *ui;
};
#endif // LOGINWINDOW_H

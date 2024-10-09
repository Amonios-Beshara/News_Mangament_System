#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "data.h"
#include "registration.h"
#include "adminview.h"
#include "user.h"
using namespace std;
loginWindow::loginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    ui->username_error->hide();
    ui->password_error->hide();
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_login_button_clicked()

{
    ui->username_error->hide();
    ui->password_error->hide();
    auto i=usernames.find(ui->username_lineedit->text());
    if (i==usernames.end()){
        ui->username_error->show();
        return;
    }
    adminView *V = new adminView(this);
    if(get<0>(i->second)== ui->password_lineedit->text()){
        if (get<1>(i->second)==true){
            //Go to admin
            qDebug()<<"admin";
            V->show();


        }
        else{
            interests inter = std::get<2>(i->second);
            user* theuser = new user(inter);
            theuser->show();
        }
    }
    else{
        ui->password_error->show();
    }

}


void loginWindow::on_signup_button_clicked()
{
    registration* reg = new registration(this);
    reg->show();

}



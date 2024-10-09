#include "registration.h"
#include "ui_registration.h"
#include "data.h"
#include "adminview.h"
#include "user.h"
registration::registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);
    ui->username_error->hide();
    ui->check_error->hide();
}

registration::~registration()
{
    delete ui;
}

void registration::on_pushButton_clicked()

{
    ui->username_error->hide();
    ui->check_error->hide();
    auto i = usernames.find(ui->username_lineedit->text());
    if (!ui->admin_button->isChecked()&&!ui->user_button->isChecked()){
        ui->check_error->show();
        return;
    }
    if(i==usernames.end()){
        interests inter(ui->politics->isChecked(), ui->business->isChecked(), ui->technology->isChecked(),
                        ui->healthcare->isChecked(), ui->science->isChecked(), ui->entertainment->isChecked(), ui->sports->isChecked());
        usernames.insert({ui->username_lineedit->text(), std::tuple<QString, bool, interests>(ui->password_lineedit->text(), ui->admin_button->isChecked(), inter)});
        if (ui->admin_button->isChecked()){
            adminView *V = new adminView(this);
            V->isAdmin = true;

            V->show();
        }
        else{
            user* theuser = new user(inter);
            this->hide();
            theuser->show();
        }
    }
    else{
        ui->username_error->show();
        return;
    }

}









void registration::on_pushButton_2_clicked()
{
    this->hide();
}


#ifndef USER_H
#define USER_H
#include <QLabel>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QVector>
#include "post.h"
#include "data.h"

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(interests inInter,QWidget *parent = nullptr);
    ~user();
    interests inter;
    void viewPost(Post* p);
    QVector <Post*> vec;
    QVector<QWidget* > vector;
    QVBoxLayout *postLayout;
    static QVector<QWidget* >postwidgett;
    QWidget* postWidget;
    static int count;
    void loadPosts();
public slots:
    //void on_pushButton_2_clicked();

private slots:
    void on_pushButton_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public:
    Ui::user *ui;
};

#endif // USER_H

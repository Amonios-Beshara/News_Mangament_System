#ifndef ADMINVIEW_H
#define ADMINVIEW_H
#include <QLabel>
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QVBoxLayout>
#include "ui_user.h"
#include "user.h"
#include "postview.h"
class Post;

namespace Ui {
class adminView;
}

class adminView : public QDialog
{
    Q_OBJECT

public:
    explicit adminView(QWidget *parent = nullptr);
    ~adminView();
    bool isAdmin = false;
    QVBoxLayout *postLayout;
    QWidget *postWidget;
    user* us;
    int postAddingCount;
    static int count;



private:
    Ui::adminView *ui;

public slots:
    void addPost(Post *p);
    void on_pushButton_clicked();
    void loadPosts();
    //void updatePost(QString title, QString description);

private slots:
    void on_title_search_button_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // ADMINVIEW_H

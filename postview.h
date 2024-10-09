#ifndef POSTVIEW_H
#define POSTVIEW_H

#include <QDialog>
class Post;

namespace Ui {
class PostView;
}

class PostView : public QDialog
{
    Q_OBJECT

public:
    explicit PostView(Post *inP,QWidget *parent = nullptr);
    Post *p;
    ~PostView();

signals:
    void postPublished(Post *outp);

private slots:
    void on_pushButton_clicked();

private:
    Ui::PostView *ui;
};

#endif // POSTVIEW_H

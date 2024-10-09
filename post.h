#ifndef POST_H
#define POST_H

#include <QString>
#include <QDate>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <vector>
using namespace std;



class Post : public QWidget
{
    Q_OBJECT

public:
    bool operator < (Post* p);
    static int count;
    int UserRatingTotal;
    int UserRatings;
    static vector<Post*> all_posts;
    vector<QString> keywords;
    QString title;
    QString description;
    QDate date;
    int rating;
    QString category;
    QPushButton* deleteButton;
    QPushButton* editButton;
    QHBoxLayout* layout;

    Post();
    ~Post();
    void setInfo(QString t, QString d, QDate indate, int r, QString categ);

public slots:
    void deletePost();
    void editPost();

};

#endif // POST_H

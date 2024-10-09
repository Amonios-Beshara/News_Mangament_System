#ifndef EDITPOST_H
#define EDITPOST_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>

class EditPostDialog : public QDialog
{
    Q_OBJECT

public:
    EditPostDialog(QWidget *parent = nullptr);

    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QDateEdit *dateEdit;
    QComboBox *ratingComboBox;
    QComboBox *categoryComboBox;

private slots:
    void savePost();

signals:
    void postEdited(const QString& title, const QString& description, const QDate& date, const QString& rating, const QString& category);
};



#endif // EDITPOST_H

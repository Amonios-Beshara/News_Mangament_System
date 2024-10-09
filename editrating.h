#ifndef EDITRATING_H
#define EDITRATING_H

#include <QAbstractItemModel>
#include <QPushButton>
#include <QComboBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class editrating : public QDialog
{
    Q_OBJECT

public:
    editrating(QWidget *parent = nullptr);
    QComboBox *ratingComboBox;

private slots:
    void savePost();

signals:
    void postEdited(const QString& rating);

};

#endif // EDITRATING_H

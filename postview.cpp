#include "postview.h"
#include "ui_postview.h"
#include "adminview.h"
#include "post.h"
#include "data.h"



PostView::PostView(Post *inP,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PostView)
{
    p = inP;
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true); // Enable calendar popup

    for(int i=0; i<CategoryNames.size(); i++)
    {
        ui->comboBox_2->addItem(CategoryNames[i]);

    }
}

PostView::~PostView()
{
    delete ui;
}

void PostView::on_pushButton_clicked()
{
    // QString title = ui->lineEdit->text();
    // QString Description = ui->textEdit->toPlainText();
    // int rating = ui->comboBox->currentText().toInt();
    // QString Category = ui->comboBox_2->currentText();
    // QDate Date = ui->dateEdit->date();

    // p->setInfo(title,Description,Date,rating,Category);
    // emit postPublished(p);
    // this->hide();

    QString title = ui->lineEdit->text();
    QString Description = ui->textEdit->toPlainText();
    int rating = ui->comboBox->currentText().toInt();
    QString Category = ui->comboBox_2->currentText();
    QDate Date = ui->dateEdit->date();

    p->setInfo(title,Description,Date,rating,Category);

    //for (int i = 0 ; i < Post::all_posts.size() ; i++){
      //  qDebug()<<Post::all_posts[i]->date;
    //}
    QString text=ui->textEdit_keywords->toPlainText();
    QTextStream stream(&text , QIODevice::ReadOnly);
    QString word;
    while(!stream.atEnd())
    {
        stream>>word;
        p->keywords.push_back(word);

    }
    for (int i = 0 ; i < p->keywords.size() ; i++){
        qDebug()<<p->keywords[i];
    }

    // Update UI with edited post information
    //title->setText(p->title);

    adminView* ad = new adminView();
    close();
    ad->show();
    emit postPublished(p);
    this->hide();
}




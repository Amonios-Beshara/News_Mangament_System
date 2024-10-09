 #include "user.h"
#include "ui_user.h"
#include <QDialog>
#include "postview.h"
#include "editrating.h"
#include "postview.h"
#include <QTextStream>
#include <QDebug>
#include "data.h"
#include <vector>
int user::count = 0;
QVector<QWidget*> user::postwidgett={};

user::user(interests inInter,QWidget *parent)
    : QDialog(parent), inter(inInter)
    , ui(new Ui::user)
{

    ui->setupUi(this);
    ui->verticalLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);


    count++;
    if(Post::all_posts.size() == 0)
        loadPosts();
    else
        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            if((Post::all_posts[i]->rating)>=2)
            {
                std::sort(Post::all_posts.begin(), Post::all_posts.end(), [](Post* l, Post* r) { return l->date>r->date; });
            viewPost(Post::all_posts[i]);
            }
        }
    for(int i=0; i<CategoryNames.size(); i++)
    {
        ui->filter->addItem(CategoryNames[i]);
    }



}

user::~user()
{
    delete ui;
}


void user::on_pushButton_clicked()
{
   /* for (int count = 0; count < postwidgett.size(); count++) {
        // adding all postwidgets again
        ui->verticalLayout->addWidget(postwidgett.at(count));
        postwidgett.at(count)->show();
    }
*/
    if (ui->title->isChecked())
    {

        if (ui->verticalLayout) {
            QLayoutItem *child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }

        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            if(Post::all_posts[i]->title==ui->Searchbar->text())
            {
                viewPost(Post::all_posts[i]);
            }

        }




    }
    else if (ui->date->isChecked())
    {
        if (ui->verticalLayout) {
            QLayoutItem *child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }

        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            if (Post::all_posts[i]->date.toString()==ui->Searchbar->text()){
                viewPost(Post::all_posts[i]);
            }
        }
    }
    else if (ui->keyword->isChecked())
    {
        if (ui->verticalLayout) {
            QLayoutItem *child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }

        for (int i = 0 ; i < Post::all_posts.size() ; i++){
                auto it = std::find(Post::all_posts[i]->keywords.begin(), Post::all_posts[i]->keywords.end(), ui->Searchbar->text());
                if (it!=Post::all_posts[i]->keywords.end()){
                    viewPost(Post::all_posts[i]);

            }
        }
}
}


//void user::on_pushButton_2_clicked()
//{
    //postWidget = new QWidget(ui->scrollAreaWidgetContents);
    //postLayout = new QVBoxLayout(postWidget);
   // Post *NEWP = new Post();
    //PostView *p = new PostView(NEWP, this);
    //connect(p, &PostView::postPublished, this, &user::viewPost);
    //p->show();
    //vec.push_back(NEWP);
//}


void user::on_pushButton_3_clicked()
{

    if(ui->filter->currentText()== "None")
    {
        if (ui->verticalLayout) {
            QLayoutItem *child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }

        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            if(!Post::all_posts[i]->title.isEmpty())
            {
                viewPost(Post::all_posts[i]);
            }

        }
        return;
    }
    if(ui->filter->currentText()== "Interests")
    {
        qDebug()<<"SIZE ";
        if (ui->verticalLayout) {
            QLayoutItem *child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }
        }
        qDebug()<<"SIZE ";

        std::vector<QString> outputV = inter.TrueInterests();
        qDebug()<<"SIZE ";
        qDebug()<<"SIZE "<<outputV.size();

        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            for(int j=0; j<outputV.size();j++)
            {
            if (Post::all_posts[i]->category==outputV[j]){
                viewPost(Post::all_posts[i]);
            }
            }
        }
        return;
    }
    if (ui->verticalLayout) {
        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    }

    for (int i = 0 ; i < Post::all_posts.size() ; i++){
        if (Post::all_posts[i]->category==ui->filter->currentText()){
                viewPost(Post::all_posts[i]);
            }
        }


}



void user::viewPost(Post *p) {
    postWidget = new QWidget(ui->scrollAreaWidgetContents);
    postLayout = new QVBoxLayout(postWidget);
    qDebug() << "it entered here";
    postwidgett.push_back(postWidget);

    QLabel *title = new QLabel(p->title);
    QLabel *description = new QLabel(p->description);
    QLabel *date = new QLabel(p->date.toString());
    QLabel *rating = new QLabel("Rating: "+QString::number(p->rating)+ " Stars");
    QLabel *category = new QLabel(p->category);

    description->setWordWrap(true);
    postLayout->addWidget(title);
    postLayout->addWidget(description);
    postLayout->addWidget(rating);
    postLayout->addWidget(category);
    postLayout->addWidget(date);
    QPushButton *Addrating = new QPushButton("Rate");

    postLayout->addWidget(Addrating);



    connect(Addrating, &QPushButton::clicked, [=]() {
        editrating dialog(this);
        dialog.ratingComboBox->setCurrentText(QString::number(p->rating) + " Stars"); // Set selected rating in combo box

        if (dialog.exec() == QDialog::Accepted) {
            // Update the post information if the dialog was accepted
            QString selectedRating = dialog.ratingComboBox->currentText();
            int NewRating = selectedRating.split(" ")[0].toInt(); // Retrieve rating from combo box

            p->UserRatingTotal+=NewRating;
            p->UserRatings++;

            // Update UI with edited post information
            rating->setText("Rating: "+QString::number(NewRating)+ " Stars");


        }
    });
    ui->verticalLayout->addWidget(postWidget);
}

void user::loadPosts()
{
    QFile inFile("/Users/kareem/Desktop/postsFile.txt");

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file for reading.";
    }

    QTextStream inStream(&inFile);

    while(!inStream.atEnd())
    {
        for(int i=0; i<5; i++)
        {
            Post *newP = new Post;
            newP->title = inStream.readLine();
            newP->description = inStream.readLine();
            newP->date = QDate::fromString(inStream.readLine().trimmed(), "ddd MMM d yyyy");
            newP->rating = inStream.readLine().toInt();
            newP->UserRatings = inStream.readLine().toInt();
            newP->UserRatingTotal = inStream.readLine().toInt();
            newP->category = inStream.readLine();
            if(newP->rating>=2)
                viewPost(newP);
        }
    }
}





void user::on_pushButton_4_clicked()
{
    QFile postsFile("/Users/kareem/Desktop/postsFile.txt");
    if (!postsFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Failed to open file for writing: " << postsFile.errorString();
        return;
    }
    QTextStream outFile(&postsFile);

    for(int i=0; i<Post::all_posts.size(); i++)
    {
        outFile << Post::all_posts[i]->title << Qt::endl;
        outFile << Post::all_posts[i]->description << Qt::endl;
        outFile << Post::all_posts[i]->date.toString() <<Qt::endl;
        qDebug() << "Post number " <<i<< "date" <<Post::all_posts[i]->date.toString();
        outFile << Post::all_posts[i]->rating << Qt::endl;
        outFile << Post::all_posts[i]->UserRatings <<Qt::endl;
        outFile << Post::all_posts[i]->UserRatingTotal <<Qt::endl;
        outFile << Post::all_posts[i]->category <<Qt::endl;



    }
    postsFile.flush();
    postsFile.close();
    exit(0);

}


void user::on_pushButton_5_clicked()
{
    this->hide();
}


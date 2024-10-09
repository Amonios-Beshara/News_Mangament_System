#include "adminview.h"
#include "ui_adminview.h"
#include "postview.h"
#include "editpost.h"
#include "post.h"
#include <QTextStream>
#include <QDebug>
#include "data.h"

int adminView::count = 0;
adminView::adminView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminView)
{


    ui->setupUi(this);
    ui->verticalLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    isAdmin = true;
    std::sort(Post::all_posts.begin(), Post::all_posts.end(), [](Post* l, Post* r) { return l->date>r->date; });

    for(int i=0; i<CategoryNames.size(); i++)
    {
        ui->category_combo_box->addItem(CategoryNames[i]);
    }

    qDebug() << "this is a counter " << count;
    count++;
    qDebug()<<Post::all_posts.size();
    if(Post::all_posts.size() == 0)
        loadPosts();
    else
        for (int i = 0 ; i < Post::all_posts.size() ; i++){
            qDebug()<<"ddd";
            addPost(Post::all_posts[i]);
        }
    qDebug()<<Post::all_posts.size();
}

adminView::~adminView()
{
    delete ui;
}

void adminView::on_pushButton_clicked()
{

    qDebug()<<Post::all_posts.size();

    Post *NEWP = new Post();
    PostView *p = new PostView(NEWP, this);
    connect(p, &PostView::postPublished, this, &adminView::addPost);

    p->show();
    this->hide();
}

void adminView::addPost(Post *p) {
    postWidget = new QWidget(ui->scrollAreaWidgetContents);
    postLayout = new QVBoxLayout(postWidget);
    QLabel *title = new QLabel(p->title);
    QLabel *description = new QLabel(p->description);
    QLabel *date = new QLabel(p->date.toString());
    QLabel *rating = new QLabel("Rating: "+QString::number(p->rating)+ " Stars");
    float average = (p->UserRatingTotal)/(p->UserRatings);
    QLabel *Average = new QLabel ("Average Rating: "+ QString::number(average)+ " Stars");
    QLabel *category
        = new QLabel(p->category);

    description->setWordWrap(true);
    postLayout->addWidget(title);
    postLayout->addWidget(description);
    postLayout->addWidget(rating);
    postLayout->addWidget(Average);
    postLayout->addWidget(category);
    postLayout->addWidget(date);


    if (isAdmin) {

        QPushButton *deleteButton = new QPushButton("Delete");
        QPushButton *editButton = new QPushButton("Edit");

        postLayout->addWidget(deleteButton);
        postLayout->addWidget(editButton);

        connect(deleteButton, &QPushButton::clicked, [=]() {
            //ui->verticalLayout->removeWidget(postWidget);
            if (ui->verticalLayout) {
                QLayoutItem *child;
                while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                    delete child->widget();
                    delete child;
                }

            }

            //delete postWidget;
            for(int i=0; i<Post::all_posts.size(); i++)
            {
                if(Post::all_posts[i] == p)
                {
                    qDebug()<<p->title;
                    Post::all_posts.erase(Post::all_posts.begin()+i);
                }
            }
            for (int i = 0 ; i < Post::all_posts.size() ; i++){
                qDebug()<<"ddd";
                addPost(Post::all_posts[i]);
            }

        });


        connect(editButton, &QPushButton::clicked, [=]() {
            EditPostDialog dialog(this);
            dialog.titleEdit->setText(p->title);
            dialog.descriptionEdit->setText(p->description);
            dialog.dateEdit->setDate(p->date); // Set date using QDate
            dialog.ratingComboBox->setCurrentText(QString::number(p->rating) + " Stars"); // Set selected rating in combo box
            dialog.categoryComboBox->setCurrentText(p->category); // Set selected category in combo box

            if (dialog.exec() == QDialog::Accepted) {
                // Update the post information if the dialog was accepted
                p->title = dialog.titleEdit->text();
                p->description = dialog.descriptionEdit->toPlainText();
                p->date = dialog.dateEdit->date(); // Retrieve date from QDateEdit
                QString selectedRating = dialog.ratingComboBox->currentText();
                p->rating = selectedRating.split(" ")[0].toInt(); // Retrieve rating from combo box
                p->category = dialog.categoryComboBox->currentText(); // Retrieve category from combo box

                description->setText(p->description);
                date->setText(p->date.toString());
                rating->setText("Rating: "+QString::number(p->rating)+ " Stars");
                category->setText(p->category);
            }
        });
    }


    ui->verticalLayout->addWidget(postWidget);
}

void adminView::on_title_search_button_clicked()
{
    if (ui->verticalLayout) {
        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    }

    for (int i = 0 ; i < Post::all_posts.size() ; i++){
        if (Post::all_posts[i]->title==ui->search_bar_line_edit->text() && Post::all_posts[i]->category==ui->category_combo_box->currentText() && Post::all_posts[i]->rating==(ui->rating_combo_box->currentText()).toInt()){
            auto it = std::find(Post::all_posts[i]->keywords.begin(), Post::all_posts[i]->keywords.end(), ui->keywords->text());
            if (it!=Post::all_posts[i]->keywords.end()){
                addPost(Post::all_posts[i]);
            }
        }
    }
}


void adminView::on_pushButton_2_clicked()
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
void adminView::loadPosts()
{
    isAdmin = true;
    QFile inFile("/Users/kareem/Desktop/postsFile.txt");

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file for reading.";
    }

    QTextStream inStream(&inFile);

    while(!inStream.atEnd())
    {

        for(int i=0; i<7; i++)
        {
            QString t = inStream.readLine();
            if(t==""&&i==0)
            {
                qDebug()<<"Break";
                break;
            }
            Post *newP = new Post;
            newP->title = t;
            newP->description = inStream.readLine();
            newP->date = QDate::fromString(inStream.readLine().trimmed(), "ddd MMM d yyyy");
            newP->rating = inStream.readLine().toInt();
            newP->UserRatings = inStream.readLine().toInt();
            newP->UserRatingTotal = inStream.readLine().toInt();
            newP->category = inStream.readLine();
            if(newP->rating!=0)
            {
                qDebug()<<"Added";
                addPost(newP);
            }
            else
            {
                for(int i=0; i<Post::all_posts.size(); i++)
                {
                    if(Post::all_posts[i]==newP)
                    {
                        Post::all_posts.erase(Post::all_posts.begin()+i);
                        delete newP;
                    }
                }
            }
        }
    }
}


void adminView::on_pushButton_3_clicked()
{
    this->hide();

}


void adminView::on_pushButton_4_clicked()
{
    QString newcateg = ui->CategoryLine->text();
    ui->category_combo_box->addItem(newcateg);

    CategoryNames.push_back(newcateg);


}


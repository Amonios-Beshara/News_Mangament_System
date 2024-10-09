#include "post.h"
#include "editpost.h"
#include "QtAlgorithms"

int Post::count = 0;
vector<Post*> Post::all_posts={};

bool Post::operator < (Post*p){
    if (this->date<p->date){
        return true;
    }
    else{
        return false;
    }
}
Post::Post() : QWidget()
{
    layout = new QHBoxLayout();
    deleteButton = new QPushButton("Delete");
    editButton = new QPushButton("Edit");

    connect(deleteButton, &QPushButton::clicked, this, &Post::deletePost);
    connect(editButton, &QPushButton::clicked, this, &Post::editPost);

    layout->addWidget(deleteButton);
    layout->addWidget(editButton);

    setLayout(layout);

    count++;
    UserRatings = 0;
    UserRatingTotal = 0;

    all_posts.push_back(this);
    //sort(all_posts.begin(), all_posts.end());

}

Post::~Post()
{

    delete layout;
}

void Post::setInfo(QString t, QString d, QDate indate, int r, QString categ)
{
    title = t;
    description = d;
    date = indate;
    rating = r;
    category = categ;
}

void Post::deletePost()
{
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Delete Post", "Are you sure you want to delete this post?",
                                         QMessageBox::Yes | QMessageBox::No);
    if (confirmation == QMessageBox::Yes) {
        // Post deletion logic here
        // For example:
        // emit deleteSignal(); // Emit a signal to notify parent to delete this post
    } else {
        // Do nothing, user canceled deletion
    }
}

void Post::editPost()
{
    EditPostDialog dialog;
    dialog.titleEdit->setText(title);
    dialog.descriptionEdit->setText(description);

    // Set date using QDate
    dialog.dateEdit->setDate(date);
    dialog.dateEdit->setCalendarPopup(true); // Enable calendar popup


    // Set selected rating and category in the combo boxes
    dialog.ratingComboBox->setCurrentText(QString::number(rating) + " Stars");
    dialog.categoryComboBox->setCurrentText(category);

    if (dialog.exec() == QDialog::Accepted) {
        title = dialog.titleEdit->text();
        description = dialog.descriptionEdit->toPlainText();

        // Retrieve date from QDateEdit
        date = dialog.dateEdit->date();

        // Retrieve rating from the selected text in QComboBox
        QString selectedRating = dialog.ratingComboBox->currentText();
        rating = selectedRating.split(" ")[0].toInt(); // Extract the numeric part

        // Retrieve category from the selected text in QComboBox
        category = dialog.categoryComboBox->currentText();

        // Post editing logic here
        // For example:
        // emit editSignal(); // Emit a signal to notify parent to edit this post
    }


}

//Add after meeting:
//sort(all_posts.begin(), all_posts.end());
//QString text=dialog.textEdit_keywords->toPlainText();
//QTextStream stream(&text , QIODevice::ReadOnly);
//QString word;
//while()
//{
    //p->keywords.push_back(word);

//}
// Update UI with edited post information
//title->setText(p->title);

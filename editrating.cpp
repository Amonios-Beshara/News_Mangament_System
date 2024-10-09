#include "editrating.h"

editrating::editrating(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();

    ratingComboBox = new QComboBox(); // Change to QComboBox
    ratingComboBox->addItem("1 Star");
    ratingComboBox->addItem("2 Stars");
    ratingComboBox->addItem("3 Stars");
    ratingComboBox->addItem("4 Stars");
    ratingComboBox->addItem("5 Stars");

    layout->addWidget(new QLabel("Rating:"));
    layout->addWidget(ratingComboBox);

    QPushButton *saveButton = new QPushButton("Save");

    connect(saveButton, &QPushButton::clicked, this, &editrating::savePost);

    layout->addWidget(saveButton);

    setLayout(layout);
}
void editrating::savePost()
{
    QString rating = ratingComboBox->currentText(); // Retrieve selected text from QComboBox
    emit postEdited(rating);
    accept();
}




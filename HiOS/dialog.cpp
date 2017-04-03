#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->textBrowser->setText(readFrom(helpFilePath));
    QMessageBox::information(this, "help", helpFilePath);
}

Dialog::~Dialog()
{
    delete ui;
}


QString Dialog::readFrom(QString fileName)
{
    QFile mFile (fileName);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Attempt Failed", "Cannot open file for reading!! ");
        return "Err!";
    }

    QTextStream in(&mFile);             //read thru text stream and return
    QString text = in.readAll();

    mFile.close();

    return text;
}

void Dialog::on_pushButton_clicked()
{
    this->close();
}

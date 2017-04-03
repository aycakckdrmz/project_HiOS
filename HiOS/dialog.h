#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QtCore>
#include <QtWidgets>
#include "commands.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString readFrom(QString);




private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    Commands dCommand;
    QString const helpFilePath = "/Users/ayca/Downloads/HiOS/commandList.txt";
};

#endif // DIALOG_H

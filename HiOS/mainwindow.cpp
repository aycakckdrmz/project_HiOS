#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setPlainText(" Welcome to Hi! OS ");
    comboAddMenuItms();
    renameAppear(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCurrent_Version_triggered()
{
    mCommand.curVers(this);

}

void MainWindow::on_actionExit_Hi_OS_triggered()
{
    mCommand.exit(this);
}

void MainWindow::on_actionDate_triggered()
{
    mCommand.sDate(this);
}

void MainWindow::on_actionTime_triggered()
{
    //will display it in status after multi-thread stuff

}

void MainWindow::on_actionShow_Directory_triggered()
{
    ui->textBrowser->setPlainText(mCommand.sDir(this));
}


QString MainWindow::readFrom(QString fileName)
{
    QFile mFile (fileName);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Attempt Failed", "Cannot open file for reading!! ");
        return "Err~";
    }

    QTextStream in(&mFile);             //read thru text stream and return
    QString text = in.readAll();

    QMessageBox::information(this, "Success! ", "Reading successfully completed!!");

    mFile.close();

    return text;
}

void MainWindow::writeTo(QString fileName, QString text)
{
    QFile mFile (fileName);

    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Attempt Failed", "Cannot open file for writing!! ");
        return;
    }

    QTextStream out (&mFile);
    out << text;
    QMessageBox::information(this, "Success! ", "Writing successfully completed!!");

    mFile.flush();
    mFile.close();
}



void MainWindow::on_actionOpen_Help_Page_triggered()
{
    Dialog *mDialog = new Dialog();
    mDialog->setWindowTitle("Help Page");
    mDialog->setModal(true);
    mDialog->exec();

}


void MainWindow::on_actionRename_Stuff_triggered()
{
    renameAppear(true);
}

void MainWindow::on_rename_button_clicked()
{
    QString itm_name(ui->comboBox->currentText());
    if (itm_name == "Menu")
        ui->menuMenu->setTitle(ui->lineEdit_2->text());
    else if (itm_name == "Version")
        ui->menuVersion->setTitle(ui->lineEdit_2->text());
    else if (itm_name == "Date Time")
        ui->menuDate_Time->setTitle(ui->lineEdit_2->text());
    else if (itm_name == "Help")
        ui->menuHelp->setTitle(ui->lineEdit_2->text());
    else if (itm_name == "Rename")
        ui->menuRename->setTitle(ui->lineEdit_2->text());
    else if (itm_name == "Exit")
        ui->menuExit->setTitle(ui->lineEdit_2->text());

}

void MainWindow::on_rename_button_2_clicked()
{
    renameAppear(false);
}

void MainWindow::renameAppear(bool visible)
{
    ui->comboBox->setVisible(visible);
    ui->lineEdit_2->setVisible(visible);
    ui->rename_button->setVisible(visible);
    ui->rename_button_2->setVisible(visible);
}

void MainWindow::comboAddMenuItms()
{
    ui->comboBox->addItem("Select One ");
    ui->comboBox->addItem("Menu");
    ui->comboBox->addItem("Version");
    ui->comboBox->addItem("Date Time");
    ui->comboBox->addItem("Help");
    ui->comboBox->addItem("Rename");         //hard-coded for now ll be fixed soon
    ui->comboBox->addItem("Directory");
    ui->comboBox->addItem("Exit");
}

void MainWindow::on_actionGo_to_PCB_Screen_triggered()
{

    PcbDialog pDialog;
    pDialog.setWindowTitle("Process Control Block Window");
    pDialog.setModal(true);    //disables main window functionality
    pDialog.exec();

}

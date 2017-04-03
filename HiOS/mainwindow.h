#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QApplication>
#include <QtWidgets>
#include <QDateTime>
#include <QTextStream>
#include <sys/types.h>
#include "dialog.h"
#include "pcbdialog.h"
#include <QList>
#include <QSharedPointer>
#include <QtGlobal>
#include "commands.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString readFrom(QString fileName);
    void writeTo(QString fileName, QString);
    void renameAppear(bool);
    void comboAddMenuItms();

private slots:
    void on_actionCurrent_Version_triggered();

    void on_actionExit_Hi_OS_triggered();

    void on_actionDate_triggered();

    void on_actionTime_triggered();

    void on_actionShow_Directory_triggered();

    void on_actionOpen_Help_Page_triggered();

    //void on_actionWrite_triggered();

    void on_actionRename_Stuff_triggered();

    void on_rename_button_clicked();

    void on_rename_button_2_clicked();

    void on_actionGo_to_PCB_Screen_triggered();

private:
    Ui::MainWindow *ui;
    QString currentVers = "Version 1.0 beta";
    QList<QSharedPointer<QObject>> changable_items;
    bool renameFlag = false;
    Commands mCommand;


};

#endif // MAINWINDOW_H

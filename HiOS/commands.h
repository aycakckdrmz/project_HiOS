#ifndef COMMANDS_H
#define COMMANDS_H
#include <QtCore>
#include <QtWidgets>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>
#include "hilist.h"

#define HELP_PATH "/home/i-cha/Projects/HiOS/HiOS"
#define VERS "Version 1.0 beta"


class Commands
{
public:
    Commands();
    //functionality commands
    void curVers(QWidget*);
    void exit(QWidget*);
    void sDate(QWidget*);
    QString sDir(QWidget*);
    QString getFolderPath();

    HiList listKey;


private:
    QString currentVersion = VERS;
    QString folderPath = HELP_PATH;



};

#endif // COMMANDS_H

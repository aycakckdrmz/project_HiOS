#include "commands.h"

Commands::Commands()
{

}


void Commands::curVers(QWidget *parent){
    QMessageBox::information(parent, "Version","Hi! OS \n" + currentVersion);
}

void Commands::exit(QWidget *parent){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(parent, "Exit", "Do you want to exit? Really?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        parent->close();
}

void Commands::sDate(QWidget *parent){
    QDateTime *curDate = new QDateTime();
    QString current = curDate->currentDateTime().toString();
    QMessageBox::information(parent, "Date", current);
}


QString Commands::sDir(QWidget *parent){
    QDir mDir;
    QString path = " ";
    QString textDir = " ";
    mDir.setCurrent(folderPath);
    QMessageBox::information(parent, "Current Path", path);
    foreach (QFileInfo item, mDir.entryInfoList())
    {
        QString temp = item.absoluteFilePath().remove(0,folderPath.length());
        textDir = textDir + temp + '\n';
    }
    return textDir; //show it on text display
}


QString Commands::getFolderPath(){
    return folderPath;
}


#ifndef PCBDIALOG_H
#define PCBDIALOG_H
#include <QtCore>
#include <QtWidgets>
#include <QDialog>
#include "pcbcommands.h"
#include "systemmemory.h"
#include "hilist.h"


namespace Ui {
class pcbDialog;
}

class PcbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PcbDialog(QWidget *parent = 0);
    ~PcbDialog();
    //GUI handling
    void createVisible();
    void deleteVisible();
    void blockVisible();
    void unblockVisible();
    void showpcbVisible();
    void showallVisible();
    void showReadyVisible();
    void showBlockedVisible();
    void genRandomVisible();
    void executeVisible();
    void execOptionsVisible();
    void execRegularVisible();
    void exec_rr_Visible();
    void exec_mlfq_Visible();
    void saveVisible();
    void reloadVisible();
    void loadVisible();
    void memoryVisible();
    void invisibleAll();

    //file IO



private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_activated(int index);

    void on_processBt_clicked();

    void on_c0_clicked();

    void on_c1_clicked();

    void on_c2_clicked();

    void on_buttonLeftLineEdit_clicked();

private:
    Ui::pcbDialog *ui;
    HiList l;
    SystemMemory sysMemKey;
    pcbCommands mCommand;
    QString const defaultPcbPath = "/Users/ayca/Downloads/HiOS/samplePCB.txt";

};

#endif // PCBDIALOG_H

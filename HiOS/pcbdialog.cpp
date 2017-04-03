#include "pcbdialog.h"
#include "ui_pcbdialog.h"



PcbDialog::PcbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pcbDialog)
{
    ui->setupUi(this);
    invisibleAll();

}

PcbDialog::~PcbDialog()
{
    delete ui;
}

void PcbDialog::on_comboBox_activated(const QString &arg1)
{   // by combo item's current string


}

void PcbDialog::on_comboBox_activated(int index)
{   // handles GUI components appearances by combo item's index #
    if (index == 1){
        invisibleAll();
        createVisible();
    }
    else if(index == 2){
        invisibleAll();
        deleteVisible();
    }
    else if(index == 3){
        invisibleAll();
        blockVisible();
    }
    else if(index == 4){
        invisibleAll();
        unblockVisible();
    }
    else if(index == 5){
        invisibleAll();
        showpcbVisible();
    }
    else if(index == 6){
        invisibleAll();
        showallVisible();
    }
    else if(index == 7){
        invisibleAll();
        showReadyVisible();
    }
    else if(index == 8){
        invisibleAll();
        showBlockedVisible();
    }
    else if(index == 9){
        invisibleAll();
        genRandomVisible();
    }
    else if(index == 10){
        invisibleAll();
        executeVisible();
    }
    else if(index == 11){
        invisibleAll();
        saveVisible();
    }
    else if(index == 12){
        invisibleAll();
        reloadVisible();
    }
    else if(index == 13){
        invisibleAll();
        loadVisible();
    }
    else if(index == 14){
        invisibleAll();
        memoryVisible();
    }
}

void PcbDialog::createVisible(){

    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->second_line_label->setVisible(true);
    ui->secondLineBox->setVisible(true);    //vvv Memory limit check
    ui->secondLineBox->setRange(0, sysMemKey.getRemainingMem());
    ui->processBt->setText("Create");
    ui->processBt->setVisible(true);

}

void PcbDialog::deleteVisible(){
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Delete");
    ui->processBt->setVisible(true);
}

void PcbDialog::blockVisible(){
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Block");
    ui->processBt->setVisible(true);
}

void PcbDialog::unblockVisible(){
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Unblock");
    ui->processBt->setVisible(true);
}


void PcbDialog::showpcbVisible(){
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Show this PCB ");
    ui->processBt->setVisible(true);
}
void PcbDialog::showallVisible(){
    ui->processBt->setText("Show All! ");
    ui->processBt->setVisible(true);
}

void PcbDialog::showReadyVisible(){
    ui->processBt->setText("Show Ready ");
    ui->processBt->setVisible(true);
}

void PcbDialog::showBlockedVisible(){
    ui->processBt->setText("Show Blocked ");
    ui->processBt->setVisible(true);
}

void PcbDialog::genRandomVisible(){
    ui->first_line_label->setText("# of PCBs: ");
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Generate PCB ");
    ui->processBt->setVisible(true);
}

void PcbDialog::executeVisible(){
    execOptionsVisible();
    ui->c0->setChecked(true);           //default -- regular exec
}

void PcbDialog::execOptionsVisible(){
    ui->c0->setVisible(true);
    ui->c1->setVisible(true);
    ui->c2->setVisible(true);
}
void PcbDialog::execRegularVisible(){
    ui->processBt->setText("Execute! ");
    ui->processBt->setVisible(true);
}

void PcbDialog::exec_rr_Visible(){
    ui->first_line_label->setText("Time Slice:  ");
    ui->first_line_label->setVisible(true);
    ui->firstLineBox->setVisible(true);
    ui->processBt->setText("Execute! ");
    ui->processBt->setVisible(true);
}

void PcbDialog::exec_mlfq_Visible(){
    ui->mlfq_label->setText("# of Levels:  ");
    ui->mlfq_label->setVisible(true);
    ui->mlfq_spin->setVisible(true);
    ui->labelLeftLineEdit->setText("Time Quantums: ");
    ui->labelLeftLineEdit->setVisible(true);
    ui->lineEditLeft->setText("Enter each quantum with a space in between.. ");
    ui->lineEditLeft->setVisible(true);
    ui->buttonLeftLineEdit->setText("Execute!");
    ui->buttonLeftLineEdit->setVisible(true);
}

void PcbDialog::saveVisible(){
    ui->processBt->setText("Save! ");
    ui->processBt->setVisible(true);
}

void PcbDialog::reloadVisible(){
    ui->processBt->setText("Reload! ");
    ui->processBt->setVisible(true);
}

void PcbDialog::loadVisible(){
    ui->labelLeftLineEdit->setText("Load PCBs via Local File: ");
    ui->labelLeftLineEdit->setVisible(true);
    ui->lineEditLeft->setText("Enter path here.. (Leave as is for default)");
    ui->lineEditLeft->setVisible(true);
    ui->buttonLeftLineEdit->setText("Load PCBs! ");
    ui->buttonLeftLineEdit->setVisible(true);

}
void PcbDialog::memoryVisible(){
    ui->processBt->setText("Show System Memory! ");
    ui->processBt->adjustSize ();
    ui->processBt->setVisible(true);
}

void PcbDialog::invisibleAll(){
    ui->first_line_label->setVisible(false);
    ui->second_line_label->setVisible(false);
    ui->firstLineBox->setVisible(false);
    ui->secondLineBox->setVisible(false);
    ui->processBt->setText("OK");
    ui->processBt->setVisible(false);   // so we can buid healthy ifs on it
    ui->c0->setVisible(false);
    ui->c1->setVisible(false);
    ui->c2->setVisible(false);
    ui->mlfq_label->setVisible(false);
    ui->mlfq_spin->setVisible(false);
    ui->labelLeftLineEdit->setVisible(false);
    ui->lineEditLeft->setVisible(false);
    ui->buttonLeftLineEdit->setVisible(false);

}

void PcbDialog::on_processBt_clicked()
{
    if(ui->processBt->text() == "Create"){
        int pid_ = 0;
        int mem_ = 0;
        int aTime = 0;
        ui->secondLineBox->setRange(0, sysMemKey.getRemainingMem());
        pid_ = (int)ui->firstLineBox->value();
        mem_ = (int)ui->secondLineBox->value();
        if(mCommand.createPCB(pid_, mem_, aTime))
            QMessageBox::information(this, "Success!!", "PCB Added!!");
        else
            QMessageBox::warning(this, "Failure!", "This PID number is already taken!");


    }
    else if(ui->processBt->text() == "Delete"){
        QSpinBox *ptr = ui->firstLineBox;
        if(mCommand.deletePCB((int)ptr->value()))
            QMessageBox::information(this, "Success!!", "PCB Deleted!!");
        else
            QMessageBox::warning(this, "Failure!", "This PID number does not exist!");

    }
    else if(ui->processBt->text() == "Block"){
        QSpinBox *ptr = ui->firstLineBox;
        if(mCommand.blockPCB((int)ptr->value()))
            QMessageBox::information(this, "Success!!", "PCB Blocked!!");
        else
            QMessageBox::warning(this, "Failure!", "This PCB cannot be blocked!! ");

    }
    else if(ui->processBt->text() == "Unblock"){
        QSpinBox *ptr = ui->firstLineBox;
        if(mCommand.unblockPCB((int)ptr->value()))
            QMessageBox::information(this, "Success!!", "PCB Unblocked!!");
        else
            QMessageBox::warning(this, "Failure!", "This PCB cannot be unblocked!! ");
    }
    else if(ui->processBt->text() == "Show this PCB "){
        QSpinBox *ptr = ui->firstLineBox;
        QString info = mCommand.showPCB((int)ptr->value());
        ui->textBrowser->setText(info);
    }
    else if(ui->processBt->text() == "Show All! "){
        QString info = mCommand.showAll();
        ui->textBrowser->setText(info);
    }
    else if(ui->processBt->text() == "Show Ready "){
        QString info = mCommand.showReady();
        ui->textBrowser->setText(info);

    }
    else if(ui->processBt->text() == "Show Blocked "){
        QString info = mCommand.showBlocked();
        ui->textBrowser->setText(info);
    }
    else if(ui->processBt->text() == "Generate PCB "){
        QSpinBox *ptr = ui->firstLineBox;
        if(mCommand.genRandomPCB((int)ptr->value()))
            QMessageBox::information(this, "Success!!", "PCBs Generated!!");
        else
            QMessageBox::warning(this, "Failure!", "Something went wrong! Try again! ");

    }
    else if(ui->processBt->text() == "Execute! "){
        QQueue <QString> sysOut;
        QString out ("");

        if(ui->c0->isChecked())
            sysOut = mCommand.executePCB();
        else if(ui->c1->isChecked()){
            QSpinBox *ptr = ui->firstLineBox;
            sysOut = mCommand.executeRR((int)ptr->value());
        }
        else if(ui->c2->isChecked()){
            QSpinBox *ptr = ui->mlfq_spin;
            QQueue<int> test;
            sysOut = mCommand.executeMLFQ((int)ptr->value(), test);
        }


        foreach(QString s, sysOut){
            out += s;
            out += "  \n";
        }
        ui->textBrowser->setText(out);
    }
    else if(ui->processBt->text() == "Save! "){
        if(mCommand.save())
            QMessageBox::information(this, "Success!!", "PCBs Saved!!");
        else
             QMessageBox::warning(this, "Failure!", "No PCBs to save! :(  ");

    }
    else if(ui->processBt->text() == "Reload! "){
        if(mCommand.reload())
            QMessageBox::information(this, "Success!!", "PCBs Reloaded!!");
        else
             QMessageBox::warning(this, "Failure!", "No saved PCB! :(  ");

    }
    else if(ui->processBt->text() == "Show System Memory! "){
        QString info = mCommand.showMemory();
        ui->textBrowser->setText(info);

    }

}


void PcbDialog::on_c0_clicked()
{
    invisibleAll();
    execOptionsVisible();
    execRegularVisible();

}


void PcbDialog::on_c1_clicked()
{
    invisibleAll();
    execOptionsVisible();
    exec_rr_Visible();
}

void PcbDialog::on_c2_clicked()
{
    invisibleAll();
    execOptionsVisible();
    exec_mlfq_Visible();
}


void PcbDialog::on_buttonLeftLineEdit_clicked()
{
    QPushButton* but = ui->buttonLeftLineEdit;
    if (but->text() == "Load PCBs! "){
        bool loaded = mCommand.loadpcb(defaultPcbPath);
        if(!loaded)
            QMessageBox::warning(this, "Failed", "Can't read from/open the file");
        else
            QMessageBox::information(this, "Success", "File copied down successfully! ");
    }
}

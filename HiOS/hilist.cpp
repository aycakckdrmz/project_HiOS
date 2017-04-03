#include "hilist.h"

HiList::HiList()
{


}

bool HiList::addToAll(Blocks b_){
    bool added = true;
    foreach(Blocks b, allpcb){
        if(b_.get_pid() == b.get_pid())
            added = false;
    }
    if(added)
        allpcb.enqueue(b_);
    return added;
}


bool HiList::addToBlocked(Blocks b_){
    blockedpcb.enqueue(b_);
    return true;
}
bool HiList::addToReady(Blocks b_){
    readypcb.enqueue(b_);
    return true;
}

bool HiList::removeFromAll_pcb(Blocks b_){
    bool deleted = false;
    if(allpcb.removeOne(b_)){
        deleted = true;
        readypcb.removeOne(b_);//whichever b exist remove it
        blockedpcb.removeOne(b_);
    }

    return deleted;
}


bool HiList::moveReadyToBlocked(Blocks b_){
    bool moved = false;
    readypcb.removeOne(b_);
    b_.set_state('b');
    blockedpcb.enqueue(b_); // add pcb to blocked
    moved = true;
    return moved;
}

bool HiList::moveBlockedToReady(Blocks b_){
    bool moved = false;
    if(blockedpcb.removeOne(b_)){ //if b_ exists in block remove and do:
        b_.set_state('r');
        readypcb.enqueue(b_); // add pcb to ready
        qDebug()<< "b_.get_state()";
        moved = true;
    }
    return moved;
}

bool HiList::pcbExists(int pid_, char key){
    bool flag = false;
    if(key == 'r'){
        foreach (Blocks b, readypcb) {
            if(b.get_pid() == pid_)
                flag = true;
        }
    } else if(key == 'b'){
        foreach (Blocks b, blockedpcb) {
            if(b.get_pid() == pid_)
                flag = true;
        }
    } else if(key == 'a'){
        foreach (Blocks b, blockedpcb) {
            if(b.get_pid() == pid_)
                flag = true;
        } foreach (Blocks b, readypcb) {
            if(b.get_pid() == pid_)
                flag = true;
        }
    }
    return flag;
}

Blocks HiList::getBlock(int pid_){
    Blocks temp;
    foreach (Blocks b, readypcb) {
        if(b.get_pid() == pid_)
            temp = b;
    }
    foreach (Blocks b, blockedpcb) {
        if(b.get_pid() == pid_)
            temp = b;
    }
    return temp;

}

QString HiList::getPCB_Info(Blocks b_){
    QString info("");
    QString currState("");


    if(b_.get_state() == 'b')
        currState = "Blocked";
    else if(b_.get_state() == 'r')
        currState = "Ready";
    else if(b_.get_state() == 'c')
        currState = "CPU";
    else if(b_.get_state() == 'd')
        currState = "Root Process";

    info += "PID #: " + QString::number(b_.get_pid()) + " \n";
    info += "Memory Need: " + QString::number(b_.get_mem()) + " \n";
    info += "Time of Arrival: " + QString::number(b_.get_aTime()) + " \n";
    info += "CPU Usage Term: " + QString::number(b_.get_cputerm()) + " \n";
    info += "IO Request Term: " + QString::number(b_.get_ioterm()) + " \n";
    info += "Waiting Term: " + QString::number(b_.get_waiting()) + " \n";
    info += "Current State #: " + currState + " \n";


    return info;
}

QString HiList::getAllInfo(){
    QString out("");
    foreach (Blocks b, readypcb) {
        out += getPCB_Info(b);
        out += " \n";
    }
    foreach (Blocks b, blockedpcb) {
        out += getPCB_Info(b);
        out += " \n";
    }
    return out;
}

QString HiList::getBlockedInfo(){
    QString out("");
    foreach (Blocks b, blockedpcb) {
        out += getPCB_Info(b);
        out += " \n";
    }
    return out;
}

QString HiList::getReadyInfo(){
    QString out("");
    foreach (Blocks b, readypcb) {
        out += getPCB_Info(b);
        out += " \n";
    }
    return out;
}

bool HiList::generate(){
    int randPID = 0;
    int randMem = 0;
    bool noMatch = true;

    randMem = qrand() % RAND_MEM_LIMIT;

    do{
        randPID = qrand() % RAND_PID_LIMIT + 1;

    }while(pcbExists(randPID, 'a'));
    Blocks randpcb(randPID, randMem, 'r');
    addToAll(randpcb);
    addToReady(randpcb);
    return noMatch;
}

bool HiList::multiGenerate(int count){
    bool success = true;
    while(count > 0){
        generate();
        count--;
    }

    return success;
}

bool HiList::moveToCPU(){
    bool done = true;
    Blocks temp = readypcb.dequeue();
    temp.set_state('c');
    cpu = temp;

    int processTime = qrand() % PROCESS_TIME_LIMIT + 1;
    cpu.set_cputerm(processTime);
    return done;

}

void HiList::updateCycles(int pTime){
    cpu.set_cputerm(cpu.get_cputerm() + pTime); //updates cputerm

    for(int i = 0; i < readypcb.size(); i++){
        int temp = 0;
        temp = (int)readypcb[i].get_waiting() + pTime;
        readypcb[i].set_waiting(temp);
    }for(int i = 0; i < blockedpcb.size(); i++){
        int temp = 0;
        temp = (int)blockedpcb[i].get_waiting() + pTime;
        blockedpcb[i].set_waiting(temp);;
    }
}



QString HiList::finishProcess(int pTime){
    updateCycles(pTime);
    return getPCB_Info(cpu);
}

bool HiList::save(){
    bool done = true;
    foreach (Blocks b, readypcb) {
        buffer.enqueue(b);
    }
    foreach (Blocks b, blockedpcb) {
        b.set_state('r');
        buffer.enqueue(b);
    }
    foreach (Blocks b, terminated) {
        b.set_state('r');
        buffer.enqueue(b);
    }
    if(buffer.empty()) done = false;

    return done;
}

bool HiList::reload(){
    bool done = true;
    if(!buffer.empty())
        readypcb = buffer;
    else
        done = false;
    return done;
}

QString HiList::getStat(Blocks b){
    QString stat("");
    stat += "TurnAround Time:   " +
         QString::number(b.get_cputerm() + b.get_waiting() + b.get_ioterm()) + " \n";

    stat += "Response Time:   " +
         QString::number(b.get_waiting()) + " \n";

    return stat;
}
/*

bool HiList::mlfqToReady(QQueue< QQueue<Blocks>> mlfq)  {
    bool done = true;
    readypcb.clear();
    if(!mlfq.empty()){
        foreach (QQueue<Blocks> q_, mlfq) {
            foreach (Blocks b_, q_) {
                readypcb.enqueue(b_);
            }
        }
    }
    return done;

}*/

void HiList::banner(QString info){
    exec_info.enqueue("************************  \n");
    exec_info.enqueue("  "+ info +" \n");
    exec_info.enqueue("************************  \n");
}

void HiList::cpuDecision(int pTime){
    int decision = 0;
    decision = qrand() % 4;
    if(decision == 0){
        terminate( pTime);
    }else if(decision == 1){
        moveEnd(pTime);
    }else if(decision == 2){
        need_io(pTime);
    }else if(decision == 3){
        need_hd(pTime);
    }

}

void HiList::processType(int rand_cycle){
    int rand_io = 0, pKind = 0;
    pKind = qrand() % 3;
    //  0 >> mixed 1 >> interactive 2 >> CPU Bound

    for (int i = 0; i < rand_cycle; i++){
        rand_io = qrand() % 30;
        if(pKind == 0){
            rand_io %= 10;
            // -Mixed Process
            if(rand_io == 4){
                events.enqueue(Event(0,rand_cycle*10));
            }else if(rand_io % 9 == 0){ //if 9, 18 or 27 so 3/30 = 1/10
                events.enqueue(Event(1,rand_cycle*10));
            }
        }else if( pKind == 1){
            rand_io %= 10;
            // -Interactive Process
            if(rand_io == 4 || rand_io == 5 || rand_io == 6){
                events.enqueue(Event(0,rand_cycle*10));
            }else if(rand_io % 9 == 0){ //if 9, 18 or 27 so 3/30 = 1/10
                events.enqueue(Event(1,rand_cycle*10));
            }
        }else if( pKind == 2){
            // -CPU Bound Process
            if(rand_io == 4){
                events.enqueue(Event(0,rand_cycle*10));
            }else if(rand_io % 9 == 0){ //if 9, 18 or 27 so 3/30 = 1/10
                events.enqueue(Event(1,rand_cycle*10));
            }
        }
    }
}

void HiList::terminate(int processTime){
    exec_info.enqueue( "Process Terminated: ");
    exec_info.enqueue(finishProcess(processTime));
    terminated.enqueue(cpu);
    exec_info.enqueue(getStat(cpu));
    exec_info.enqueue("----------------------- \n");
    }

void HiList::moveEnd(int processTime){
    exec_info.enqueue("Process Moved to the end of the Ready Queue \n");
    updateCycles(processTime);
    readypcb.enqueue(cpu);
    exec_info.enqueue("----------------------- \n");
    }

/*void HiList::move_mlfq(int processTime){

}*/

void HiList::need_io(int processTime){
    exec_info.enqueue("Process Needs a User I/O - moved to Blocked \n");
    cpu.setUser_io(true);
    moveReadyToBlocked (cpu);
    exec_info.enqueue("----------------------- \n");
}

void HiList::need_hd(int processTime){
    exec_info.enqueue("Process Needs a Hard Drive I/O - moved to Blocked \n");
    cpu.setHard_io(true);
    cpu.set_state('b');
    updateCycles(processTime);
    blockedpcb.enqueue(cpu);
    exec_info.enqueue("----------------------- \n");
}

void HiList::eventCheck(int processTime){
    while(!events.empty()){
        Event curEvent = events.dequeue();
        for(int i = 0; i < blockedpcb.size(); i++){
            if((curEvent.getKind() == 0 && blockedpcb[i].getUser_io())
                  && (blockedpcb[i].get_waiting() > curEvent.getTime())){
                //if user io event && process is older than the event

                int temp = blockedpcb[i].get_ioterm() + processTime;
                blockedpcb[i].set_iotem(temp);
                blockedpcb[i].setUser_io(false);
                moveBlockedToReady(blockedpcb[i]);
                exec_info.enqueue("  >> Process got the User Event. Moving to Ready...");

            }
            else if((curEvent.getKind() == 1 && blockedpcb[i].getHard_io())
                  && (blockedpcb[i].get_waiting() > curEvent.getTime())){
                //if hard drive event && process is older than the event

                int temp = blockedpcb[i].get_ioterm() + processTime;
                blockedpcb[i].set_iotem(temp);
                blockedpcb[i].setHard_io(false);
                moveBlockedToReady(blockedpcb[i]);
                exec_info.enqueue("  >> Process got the Hard Drive Event. Moving to Ready...");

            }
        }
    }
}


QString HiList::readFrom(QString fileName)
{
    QFile mFile (fileName);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        return "Err!";
    }

    QTextStream in(&mFile);             //read thru text stream and return
    QString text = in.readAll();

    mFile.close();

    return text;
}

QString HiList::getTotalUsedMemory (){
    long totalMem = 0;
    QString temp("Current Memory Usage Details \n ");
    temp += "(r - Ready | b - Blocked)  \n";
    temp += "---------------------------------- \n";
    foreach (Blocks b, readypcb + blockedpcb ) {
            totalMem += b.get_mem();
            temp +=  "PID #: " + QString::number(b.get_pid ()) +
                  "  Status: " + b.get_state () +
                  "  Memory: " + QString::number(b.get_mem ()) + " \n";

    }
    temp += "---------------------------------- \n \n";

    temp += " TOTAL MEMORY USE:    " +
            QString::number(totalMem) + "  \n"
            "  \n" + " REMAINING MEMORY:    " +
            QString::number(SystemMemory().getMemory () - totalMem) + "  \n";

    return temp;
}









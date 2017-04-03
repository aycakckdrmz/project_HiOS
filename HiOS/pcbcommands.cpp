#include "pcbcommands.h"

int pcbCommands::timeCycle = 0;

pcbCommands::pcbCommands()
{

}


bool pcbCommands::createPCB(int pid_, int mem_, int aTime){
    bool added = false;
    Blocks temp(pid_, mem_,'r', aTime);
    memKey.setRemainingMem(mem_);
    if(listKey.addToAll(temp)){     //if it doesnt exist add
        added = true;
        listKey.addToReady(temp);
    }

    return added;
}


bool pcbCommands::deletePCB(int pid_){
    bool removed = false;
    Blocks temp;
    temp = listKey.getBlock(pid_);
    if(temp.get_pid()!= 0) //if that pid number exists
        removed = listKey.removeFromAll_pcb(temp);
    return removed;
}

bool pcbCommands::blockPCB(int pid_){
    bool blocked = false;
    Blocks temp;
    temp = listKey.getBlock(pid_);
    if(temp.get_pid()!= 0){
        temp.set_state('b');
        blocked = listKey.moveReadyToBlocked(temp);
    }
    return blocked;
}

bool pcbCommands::unblockPCB(int pid_){
    bool unblocked = false;
    Blocks temp;
    temp = listKey.getBlock(pid_);
    if(temp.get_pid()!= 0)
        unblocked = listKey.moveBlockedToReady(temp);
    return unblocked;
}

QString pcbCommands::showPCB(int pid_){
    QString info("");
    Blocks temp;
    temp = listKey.getBlock(pid_);
    if(temp.get_pid()!= 0){
        info = listKey.getPCB_Info(temp);
    }else
        info = "PCB does not exist!! ";
    return info;
}

QString pcbCommands::showAll(){
    QString info("");
    info = listKey.getAllInfo();
    return info;
}

QString pcbCommands::showReady(){
    QString info("");
    info = listKey.getReadyInfo();
    return info;

}

QString pcbCommands::showBlocked(){
    QString info("");
    info = listKey.getBlockedInfo();
    return info;
}

bool pcbCommands::genRandomPCB(int count){
    return listKey.multiGenerate(count);
}

QQueue <QString> pcbCommands::executePCB(){
    bool run = true;
    int rand_cycle = 0;
    int processTime = 0;
    int curTime = 0;
    QString in("");
    Blocks t(-1, -1, 'd');
    listKey.readypcb.enqueue(t); //dummy block
    listKey.banner("      Regular Exec!!  ");
    while(run){

        Blocks temp = listKey.readypcb.dequeue();
        if(temp.get_pid() == -1){   //if dummy - end of list
            listKey.banner("End of the process list!");
            run = false;
            return listKey.exec_info;
        }
        listKey.cpu = temp;
        processTime = qrand() % PROCESS_TIME_LIMIT + 1;
        listKey.cpu.set_cputerm(processTime);
        processTime += CONTEXT_SWITCH;
        curTime += processTime;
        listKey.cpu.set_aTime(curTime);  //time of arrival
        listKey.exec_info.enqueue("  >> Context Switching...   \n");

        rand_cycle = processTime / CONTEXT_SWITCH;
        curTime += rand_cycle;
        listKey.processType(rand_cycle);
        //mixed, interactive or CPU bound

        listKey.cpuDecision(processTime);
        //cpu terminated or queued

        listKey.eventCheck(processTime);
        //go thru blocked, match with events (if any)
        curTime++;
    }


    return listKey.exec_info;

}

QQueue <QString> pcbCommands::executeRR(int timeSlice){
    bool run = true;
    int rand_cycle = 0;
    int processTime = 0;
    int curTime = 0;
    QString in("");
    Blocks t(-1, -1, 'd');
    listKey.readypcb.enqueue(t); //dummy block
    listKey.banner("       Round Robin Exec!! ");
    while(run){

        Blocks temp = listKey.readypcb.dequeue();
        processTime += timeSlice;
        curTime += processTime;
        temp.set_aTime(processTime);   //setting time of arrival

        if(temp.get_pid() == -1){ //if dummy - end of list
            listKey.banner("End of the process list!");
            run = false;
            return listKey.exec_info;
        }
        listKey.cpu = temp;

        listKey.cpu.set_cputerm(processTime);
        processTime += CONTEXT_SWITCH;
        curTime += CONTEXT_SWITCH;
        listKey.exec_info.enqueue("  >> Context Switching...   \n");

        rand_cycle = processTime / CONTEXT_SWITCH;
        curTime += rand_cycle;

        listKey.processType(rand_cycle);
        //mixed, interactive || CPU bound

        listKey.cpuDecision(processTime);
        //cpu terminated || blocked || delayed

        listKey.eventCheck(processTime);
        //go thru blocked, match with events (if any)
        curTime++;
    }


    return listKey.exec_info;

}


QQueue<QString> pcbCommands::executeMLFQ(int lCount, QQueue<int> tSlices){
    if(lCount != tSlices.size()){
        listKey.exec_info.enqueue("! LEVELS AND # of TIME SLICES ARE NOT EQUAL ! \n");
        listKey.exec_info.enqueue("                                 ~ Try again  \n");
        return listKey.exec_info;
    }




    return listKey.exec_info;

}




bool pcbCommands::save(){
    return listKey.save();
}

bool pcbCommands::reload(){
    return listKey.reload();
}


bool pcbCommands::loadpcb(QString path){
    bool loaded = true;
    int pid_load = 0;
    int mem_load = 0;
    int aTime_load = 0;
    QString out = listKey.readFrom(path);
    if (out == "Err!")
        loaded = false;
    else{
       QStringList sl  = out.trimmed().replace('\n', ',').split(',');
        // clean white space, separate, then push to list
       QQueue<long> nums;
       for (int i = 0; i < sl.size(); i++){
           nums.enqueue(sl.at(i).toLong());
       }
       if(nums.size() % 3 != 0)
           return false;
       for (int i = 0; i < nums.size(); i++){
            if (i % 3 == 0)     //first col -- pid
                pid_load = nums.at(i);
            else if (i % 3 == 1)  //second col -- mem
                mem_load = nums.at(i);
            else{   //third col -- aTime
                    //PCB has all to be created now
                if(!listKey.pcbExists(pid_load, 'a')){
                    aTime_load = nums.at(i);
                    createPCB(pid_load, mem_load, aTime_load);
                }
                //check - if pid is unique create the pcb, if not then skip
                else{
                        //if pid does exist then do smt
                }

            }
       }
    }

    return loaded;
}


QString pcbCommands::showMemory (){
    return listKey.getTotalUsedMemory ();
}

//---------------


#include "blocks.h"

int Blocks::cpuUsageTerm = 0;

Blocks::Blocks()
{
    pid = 0;

    memoryNeed = qrand() % 2500 + 1;
    arrivalTime = 0;
    ioRequestTerm = 0;
    waitingTerm = 0;
    state = 'x';        //invalid (null) state
    requireUser_io = false;
    requireHard_io = false;

}

Blocks::Blocks(int p, int m, char s, int aT)
{
    pid = p;
    memoryNeed = m;
    arrivalTime = aT;
    ioRequestTerm = 0;
    waitingTerm = 0;
    state = s;
    requireUser_io = false;
    requireHard_io = false;
}

//getters
int Blocks::get_pid(){
    return pid;
}

int Blocks::get_mem(){
    return memoryNeed;
}

int Blocks::get_aTime(){
    return arrivalTime;
}

int Blocks::get_cputerm(){
    return cpuUsageTerm;
}

int Blocks::get_ioterm(){
    return ioRequestTerm;
}

int Blocks::get_waiting(){
    return waitingTerm;
}

char Blocks::get_state(){
    return state;
}
bool Blocks::getUser_io(){
    return requireUser_io;
}

bool Blocks::getHard_io(){
    return requireHard_io;
}

//setters
void Blocks::set_mem(int m){
    memoryNeed = m;
}

void Blocks::set_aTime(int aT){
    if(arrivalTime == 0)
        arrivalTime = aT;
} //only set arrival time if it has not set yet - arrTime won't change

void Blocks::set_cputerm(int c){
    cpuUsageTerm = c;
}

void Blocks::set_iotem(int io){
    ioRequestTerm = io;
}

void Blocks::set_waiting(int w){
    waitingTerm = w;
}

void Blocks::set_state(char s){
    state = s;
}

void Blocks::setUser_io(bool io){
    requireUser_io = io;
}

void Blocks::setHard_io(bool io){
    requireHard_io = io;
}

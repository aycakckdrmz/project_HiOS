#ifndef BLOCKS_H
#define BLOCKS_H

#include <QtCore>



class Blocks
{
public:
    Blocks();
    Blocks(int, int, char, int = 0);
    bool operator==(const Blocks &pcb) const {return pid == pcb.pid;}
    //overriding operators is my jam now :D !!
    //getters
    int get_pid();
    int get_mem();
    int get_aTime();
    int get_cputerm();
    int get_ioterm();
    int get_waiting();
    char get_state();
    bool getUser_io();
    bool getHard_io();
    //setters (no need setter for pid - unique & static)
    void set_mem(int);
    void set_aTime(int);
    void set_cputerm(int);
    void set_iotem(int);
    void set_waiting(int);
    void set_state(char);
    void setUser_io(bool);
    void setHard_io(bool);
private:
    int pid;
    int memoryNeed;
    int static cpuUsageTerm;
    int ioRequestTerm;
    int waitingTerm;
    int arrivalTime;
    char state;
    bool requireUser_io;
    bool requireHard_io;
};

#endif // BLOCKS_H

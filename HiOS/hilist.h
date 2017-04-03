#ifndef HILIST_H
#define HILIST_H

#include <QQueue>
#include <QtDebug>
#include <QtGlobal>
#include <QtCore>
#include "blocks.h"
#include "event.h"
#include "systemmemory.h"

#define RAND_PID_LIMIT 500
#define RAND_MEM_LIMIT 1000
#define PROCESS_TIME_LIMIT 10000
#define CONTEXT_SWITCH 10

class HiList
{
public:
    HiList();
    //Queues & CPU
    QQueue<Blocks> allpcb;
    QQueue<Blocks> readypcb;
    QQueue<Blocks> blockedpcb;
    QQueue<Event> events;
    QQueue<QString> exec_info;
    QQueue<Blocks> buffer;
    QQueue<Blocks> terminated;
    QQueue<QString> mem_info;
    Blocks cpu;


    // create, check, terminate functions
    // all return false in case of DNE || already exists
    bool addToAll(Blocks);
    bool addToBlocked(Blocks);
    bool addToReady(Blocks);
    bool removeFromAll_pcb(Blocks);
    bool moveReadyToBlocked(Blocks);
    bool moveBlockedToReady(Blocks);
    bool pcbExists(int, char);
    bool generate();
    bool multiGenerate(int);
    bool moveToCPU();
    bool save();
    bool reload();

    //exec funtions
    QString finishProcess(int);
    void updateCycles(int);
    void cpuDecision(int);
    void terminate(int processTime);
    void moveEnd(int); //reg method-> move to end of ready
    void move_mlfq(int); //mlfq method-> decrease level
    void need_io(int);
    void need_hd(int);
    void processType(int);
    void eventCheck(int);



    //status get&show functions
    QString getPCB_Info(Blocks);
    QString getAllInfo();
    QString getBlockedInfo();
    QString getReadyInfo();
    QString getStat(Blocks);
    QString getTotalUsedMemory();

    //informal
    void banner(QString);
    Blocks getBlock(int); //if exists

    //String manip., file IO
    QString readFrom(QString);
    QQueue<int> parse_stoi(QString);




};

#endif // HILIST_H

#ifndef PCBCOMMANDS_H
#define PCBCOMMANDS_H
#include "hilist.h"
#include <QtCore>
#include "systemmemory.h"



class pcbCommands
{
public:
    pcbCommands();
    //arrivalTime has default -> more flex code -> less repeatation
    bool createPCB(int, int, int = 0);
    bool deletePCB(int);
    bool blockPCB(int);
    bool unblockPCB(int);
    QString showPCB(int);
    QString showAll();
    QString showReady();
    QString showBlocked();
    bool genRandomPCB(int);
    QString showMemory();

    bool cpuDecision();

    //---exec functions
    QQueue<QString> executePCB();
    QQueue<QString> executeRR(int);
    QQueue<QString> executeMLFQ(int, QQueue<int>);

    bool save();
    bool reload();
    bool loadpcb(QString);

    HiList listKey;
    SystemMemory memKey;
    int static timeCycle;
};

#endif // PCBCOMMANDS_H

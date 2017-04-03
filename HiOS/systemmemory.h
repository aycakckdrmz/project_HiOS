#ifndef SYSTEMMEMORY_H
#define SYSTEMMEMORY_H


class SystemMemory
{

private:
    int sMem;
    int remaningMem;

public:
    SystemMemory();
    int getMemory();
    void setMemory(int);
    int getRemainingMem();
    void setRemainingMem(int);
};

#endif // SYSTEMMEMORY_H

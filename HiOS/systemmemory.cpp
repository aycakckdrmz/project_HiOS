#include "systemmemory.h"

SystemMemory::SystemMemory()
{
    sMem = 100000000; //assuming in bytes
    remaningMem = sMem;
}
int SystemMemory::getMemory(){
    return sMem;
}

void SystemMemory::setMemory(int newMem){
    sMem = newMem;
}
int SystemMemory::getRemainingMem(){
    return remaningMem;
}

void SystemMemory::setRemainingMem(int usedMem){
    remaningMem -= usedMem;
}

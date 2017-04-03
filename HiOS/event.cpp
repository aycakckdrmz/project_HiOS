#include "event.h"

Event::Event(int kind_, int pTime)
{
    kind = kind_ % 2;
    init_time = pTime;

}


int Event::getKind(){
    return kind;
}

int Event::getTime(){
    return init_time;
}

void Event::setKind(int kind_){
     kind = kind_;
}

void Event::setTime(int time){
    init_time = time;
}

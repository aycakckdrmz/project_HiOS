#ifndef EVENT_H
#define EVENT_H


class Event
{
public:
    Event(int, int);
    bool operator==(const Event &e) const {
        return (init_time == e.init_time && kind == e.kind);}
    int getKind();
    int getTime();

    void setKind(int);
    void setTime(int);

private:
    int kind; //0 for the user IO -- 1 for harddrive
    int init_time;
};

#endif // EVENT_H

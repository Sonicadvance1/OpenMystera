#ifndef _TIMING_H_
#define _TIMING_H_
#include <stdio.h>
#include <sys/time.h>

long GetTicks();

//timer class
class cTimer
{
	private:
	long start;
    bool started;

	public:
    cTimer()
    {
        started=0;
    }
    void go()
    {
        started=1;
        start=0;
    }
    bool tick(int len)
    {
        if(!started)
        {
            reset();
            started=1;
        }
        if(int(GetTicks()-start)>=len)
        {
            reset();
            return 1;
        }
        return 0;
    }
    void reset()
    {
        start = GetTicks();
    }
    long ticks()
    {
        return GetTicks()-start;
    }
};
#endif

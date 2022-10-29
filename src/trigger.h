#ifndef TRIGGER_H
#define TRIGGER_H

#include <Arduino.h>
#include <AudioStream.h>

class Trigger : public AudioStream
{
public:
	Trigger(void) : AudioStream(0, NULL)
    { 	
	}
    virtual void update(void);
    void set();
    void clear();
private:
    int16_t outputVal = 0;
};

#endif

#ifndef RANDOM_H
#define RANDOM_H

#include <Arduino.h>

typedef struct ranctx { uint32_t a; uint32_t b; uint32_t c; uint32_t d; } ranctx;

#define rot(x,k) (((x)<<(k))|((x)>>(32-(k))))


class Random
{
public:
	Random(uint32_t seed)
    { 	
        reset(seed);
	}

    uint32_t next() 
    {
        uint32_t e = this->x.a - rot(this->x.b, 27);
        this->x.a = this->x.b ^ rot(this->x.c, 17);
        this->x.b = this->x.c + this->x.d;
        this->x.c = this->x.d + e;
        this->x.d = e + this->x.a;
        return this->x.d;
    }

    void reset(uint8_t seed)
    {
        this->seed = seed;
        uint32_t i;
        this->x.a = 0xf1ea5eed;
        this->x.b = this->x.c = this->x.d = this->seed;
        for (i=0; i<20; ++i)
        {
            (void)next();
        }
    }

private:
    uint32_t seed;
    ranctx x;
};




#endif

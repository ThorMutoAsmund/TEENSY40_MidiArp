#include "trigger.h"

void Trigger::set()
{
    this->outputVal = 30000;
}

void Trigger::clear()
{
    this->outputVal = 0;
}

void Trigger::update()
{
    audio_block_t *block;
    int16_t *bp;

    block = allocate();
    if (block)
    {
        bp = block->data;

        for (uint16_t i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
        {
            bp[0] = this->outputVal;
            bp++;
        }

        // send the samples to the channel
        transmit(block, 0);
        release(block);
    }
}


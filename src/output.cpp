#include "output.h"

const char* modeNames[ARP_MODES] = {"None","AsPlayed","Up","Down","Up-Down","Down-Up","Up-Down+","Down-Up+","Chord"};
const char* repStyleNames[ARP_REPSTYLES] = {"None", "2", "3", "4", "2-1", "1-2", "3-1", "1-3", "1-0", "1-1-2", "1-2-2",
"1-1-0","1-0-1","2-3-3","3-3-2","5-1-2","2-5-1","2-1-5","1-5-2","1-2-5" };
const char* speedModeNames[ARP_SPEEDMODES] = { "Const note len, slow","Const note len, fast","Const beat len, slow","Const beat len, fast",
"BPS and tone len","Ext trig pulse","Ext trig hold" };
const char* randomModeNames[ARP_RANDOMMODES] = { "Off", "On" };

const int8_t repStyle1[2] = { 2,-1 };
const int8_t repStyle2[2] = { 3,-1 };
const int8_t repStyle3[2] = { 4,-1 };
const int8_t repStyle4[3] = { 2,1,-1 };
const int8_t repStyle5[3] = { 1,2,-1 };
const int8_t repStyle6[3] = { 3,1,-1 };
const int8_t repStyle7[3] = { 1,3,-1 };
const int8_t repStyle8[3] = { 1,0,-1 };
const int8_t repStyle9[4] = { 1,1,2,-1 };
const int8_t repStyle10[4] = { 1,2,2,-1 };
const int8_t repStyle11[4] = { 1,1,0,-1 };
const int8_t repStyle12[4] = { 1,0,1,-1 };
const int8_t repStyle13[4] = { 2,3,3,-1 };
const int8_t repStyle14[4] = { 3,3,2,-1 };
const int8_t repStyle15[4] = { 5,1,2,-1 };
const int8_t repStyle16[4] = { 2,5,1,-1 };
const int8_t repStyle17[4] = { 2,1,5,-1 };
const int8_t repStyle18[4] = { 1,5,2,-1 };
const int8_t repStyle19[4] = { 1,2,5,-1 };
const int8_t* repStyles[ARP_REPSTYLES - 1] = {repStyle1, repStyle2, repStyle3, repStyle4, repStyle5, repStyle6, repStyle7,
                                                repStyle8,repStyle9,repStyle10,repStyle11,repStyle12,repStyle13,repStyle14,repStyle15,repStyle16,
                                                repStyle17,repStyle18,repStyle19,
                                                };

// First byte represents the number of bytes coming after. 
// The rest indicate halftones

#define _Cs 1
#define _Db 1
#define _D 2
#define _Ds 3
#define _Eb 3
#define _E 4
#define _F 5
#define _Fs 6
#define _Gb 6
#define _G 7
#define _Gs 8
#define _Ab 8
#define _A 9
#define _As 10
#define _Bb 10
#define _B 11


const uint8_t chord1[13] = { 11, _Cs,_D,_Ds,_E,_F,_Fs,_G,_Gs,_A,_As,_B };
const uint8_t chord2[8]  = { 6,  _D,_Eb,_F,_G,_A,_Bb };
const uint8_t chord3[8]  = { 6,  _D,_Eb,_F,_G,_Ab,_Bb };
const uint8_t chord4[8]  = { 6,  _D,_E,_F,_G,_A,_B };
const uint8_t chord5[8]  = { 6,  _Db,_Eb,_F,_Gb,_Ab,_Bb };
const uint8_t chord6[8]  = { 6,  _D,_E,_Fs,_G,_A,_B };
const uint8_t chord7[8]  = { 6,  _Db,_Eb,_F,_G,_Ab,_Bb };
const uint8_t chord8[8]  = { 6,  _Db,_E,_Fs,_Gs,_As,_B };
const uint8_t chord9[8]  = { 6,  _D,_E,_F,_G,_A,_Bb };
const uint8_t chord10[8]  = { 6,  _D,_E,_Fs,_G,_A,_Bb };
const uint8_t chord11[8]  = { 6,  _Db,_Eb,_F,_G,_A,_B };
const uint8_t chord12[8]  = { 6,  _Db,_E,_F,_G,_Ab,_Bb };
const uint8_t chord13[8]  = { 6,  _Db,_E,_F,_Gb,_Ab,_B };
const uint8_t chord14[8]  = { 6,  _Db,_E,_F,_G,_Ab,_B };
const uint8_t chord15[8]  = { 6,  _D,_Eb,_F,_Gb,_A,_Bb };
const uint8_t chord16[8]  = { 6,  _D,_Eb,_F,_Gb,_Ab,_Bb };
const uint8_t chord17[8]  = { 6,  _D,_Eb,_Fs,_G,_Ab,_B };
const uint8_t* chords[ARP_CHORDS] = {chord1, chord2, chord3, chord4, chord5, chord6, chord7, chord8, chord9, chord10,
                                    chord11, chord12, chord13, chord14, chord15, chord16, chord17
                                    };

// First byte represents the number of bytes coming after plus one. 
// Bytes after the first represent the distance to the root note

const uint8_t trigger1[2] = { 2, _Cs };
const uint8_t trigger2[2] = { 2, _D };
const uint8_t trigger3[2] = { 2, _Eb };
const uint8_t trigger4[2] = { 2, _E };
const uint8_t trigger5[2] = { 2, _F };

const uint8_t trigger6[2] = { 2, _Fs };
const uint8_t trigger7[2] = { 2, _G };
const uint8_t trigger8[2] = { 2, _Gs };
const uint8_t trigger9[2] = { 2, _A };
const uint8_t trigger10[2] = { 2, _Bb };
const uint8_t trigger11[3] = { 3, _Db,_Eb };
const uint8_t trigger12[3] = { 3, _Db,_E };
const uint8_t trigger13[3] = { 3, _Db,_F };
const uint8_t trigger14[3] = { 3, _Db,_G };
const uint8_t trigger15[3] = { 3, _D,_Eb };
const uint8_t trigger16[3] = { 3, _D,_F };
const uint8_t trigger17[3] = { 3, _D,_Fs };
const uint8_t* chordTriggers[ARP_CHORDS] = {trigger1, trigger2, trigger3, trigger4, trigger5, trigger6, trigger7, trigger8, trigger9, trigger10,
                                            trigger11, trigger12, trigger13, trigger14, trigger15, trigger16, trigger17//, trigger8, trigger9, trigger10,
                                    };



void Output::noteOn(int8_t note)
{
    if (!isNotePlayable(note))
    {
        return;
    }

    if (this->notePtr == MAX_NOTES - 1)
    {
        return;
    }

    this->note[this->notePtr++] = note;
    sortNotes();

    if (this->arpMode == ARP_MODE_NONE)
    {
        this->playNote(note);
    }
    else
    {
        if (this->notePtr == 1)
        {
            arpReset();
        }
        else
        {
            setNoteTime();
        }
    }
}

void Output::noteOff(int8_t note)
{
    for (uint8_t i = 0; i < this->notePtr; i++)
    {
        if (this->note[i] == note)
        {
            for (uint8_t j = i + 1; j < this->notePtr; j++)
            {
                this->note[j-1] = this->note[j];
            }

            if (!--this->notePtr)
            {
                this->trigger.clear();
            }
            else
            {
                sortNotes();

                if (this->arpMode == ARP_MODE_NONE)
                {
                    this->playNote(this->note[this->notePtr - 1]);
                }
                else
                {
                    setNoteTime();
                }
            }
            break;
        }
    }
}

void Output::changeOctaveVoltage(int16_t add)
{
    this->octaveVoltage += add;
    Serial.print("Octave voltage is ");
    Serial.println(this->octaveVoltage, DEC);
}

void Output::setSpeed(uint8_t data) // 0->255
{
    // this->arpSpeed_LS8 = (((uint32_t)data * data)) + 0x0040;
    this->arpSpeed = (uint32_t)data;
    setNoteTime();
}

void Output::setNoteSpacing(uint8_t data)
{
    this->arpNoteSpacing = data;
    setNoteTime();
}

uint8_t Output::setEnumArpMode(uint8_t data)
{ 
    if (data >= ARP_MODES)
    {
        data = ARP_MODES -1;
    }

    if (data != this->arpMode)
    {
        this->arpMode = data;
        arpReset();
    }

    return this->arpMode;
}

uint8_t Output::setEnumWidth(uint8_t data)
{
    if (data > 31)
    {
        data = 31;
    }

    if (data != this->arpWidth)
    {
        this->arpWidth = data;
        arpReset();
    }

    return this->arpWidth;

    // uint8_t width = calcExtraNotes(this->arpWidth);
    // if (width != calcExtraNotes(data))
    // {
    //     this->arpWidth = data;
    //     arpReset();
    // }
}

uint8_t Output::setEnumOctaveWidth(uint8_t data)
{
    if (data > 36)
    {
        data = 36;
    }

    if (data != this->arpWidth)
    {
        this->arpOctaveWidth = data;
        sortNotes();
    }

    return this->arpOctaveWidth;

}

uint8_t Output::setEnumRepStyle(uint8_t data)
{
    if (data >= ARP_REPSTYLES)
    {
        data = ARP_REPSTYLES -1;
    }

    if (data != this->arpRepStyle)
    {
        this->arpRepStyle = data;
        arpReset();
    }

    return this->arpRepStyle;
}

uint8_t Output::setEnumRandomMode(uint8_t data)
{
    if (data >= ARP_RANDOMMODES)
    {
        data = ARP_RANDOMMODES -1;
    }

    if (data != this->arpRandomMode)
    {
        this->arpRandomMode = data;
        arpReset();
    }

    return this->arpRandomMode;
}


uint8_t Output::setEnumSpeedMode(uint8_t data)
{
    if (data >= ARP_SPEEDMODES)
    {
        data = ARP_SPEEDMODES -1;
    }

    if (data != this->arpSpeedMode)
    {
        this->arpSpeedMode = data;
        arpReset();
    }

    return this->arpSpeedMode;
}

void Output::setRandomSeed(uint8_t data)
{
    if (this->arpRandomSeed != data)
    {
        this->arpRandomSeed = data;
        sortNotes();
    }
}

void Output::playNote(int8_t note)
{
    // A skip-note
    if (!note)
    {
        this->trigger.clear();
        return;
    }
    // Get "frequency"
    int32_t freq = ((int32_t)this->octaveVoltage) * (note - this->noteAt0V) / 12;
    this->outputVal = (int16_t)freq;

    // CV out
    this->trigger.set();
}

void Output::arp()
{    
    if (arpM > this->noteRestartTime)
    {
        this->ramp = (this->ramp + 1) % this->arpNoteLen;
        this->playNote(selectNextNote());
        this->noteOnTime = arpM;
        setNoteTime();
    }
    else if (arpM > this->noteOffTime)
    {
        this->trigger.clear();
    }
}

int8_t Output::selectNextNote()
{
    return this->snote[this->ramp];
}

void Output::setNoteTime()
{    
    if (this->notePtr)
    {
        switch (this->arpSpeedMode)
        {
            case ARP_SPEEDMODE_CONSTANT_NOTE_LEN_SLOW:
            case ARP_SPEEDMODE_CONSTANT_NOTE_LEN_FAST:
                this->noteRestartTime = 0xFF - this->arpSpeed;
                
                this->noteRestartTime = this->arpSpeedMode == ARP_SPEEDMODE_CONSTANT_NOTE_LEN_SLOW ?
                    ((((uint32_t)1000 * this->noteRestartTime * this->noteRestartTime) >> 16) + 100) :
                    ((((uint32_t)100 * this->noteRestartTime * this->noteRestartTime) >> 16) + 40);
                break;
            case ARP_SPEEDMODE_CONSTANT_BEAT_LEN_SLOW:
            case ARP_SPEEDMODE_CONSTANT_BEAT_LEN_FAST:
                this->noteRestartTime = 0xFF - this->arpSpeed;
                
                this->noteRestartTime = this->arpSpeedMode == ARP_SPEEDMODE_CONSTANT_BEAT_LEN_SLOW ?
                    ((((uint32_t)4000 * this->noteRestartTime * this->noteRestartTime) >> 16) + 250) / this->arpNoteLen :
                    ((((uint32_t)450 * this->noteRestartTime * this->noteRestartTime) >> 16) + 50) / this->arpNoteLen;
                break;
        }

        this->noteOffTime = this->arpNoteSpacing ?
            this->noteRestartTime * (256 - this->arpNoteSpacing) / 256 :
            this->noteRestartTime;

        this->noteRestartTime += this->noteOnTime;
        this->noteOffTime += this->noteOnTime;
    }
}

// f = f_0 * 2^V
// f_0 is "middle C", MIDI note 60, 261.6256 Hz

void Output::update()
{
    this->arpM = millis();

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

    if (this->arpMode != ARP_MODE_NONE && this->notePtr)
    {
        this->arp();
    }
}

uint8_t Output::isNotePlayable(int8_t note)
{
    return note >= this->lowestNote && note <= this->highestNote;
}

void Output::arpReset()
{    
    if (this->notePtr)
    {
        sortNotes();
        this->ramp = 0;
        this->noteOnTime = millis();
        setNoteTime();
        this->playNote(selectNextNote());
    }
}
void Output::sortNotes()
{
    // if (this->arpMode == ARP_MODE_CHORD && this->notePtr == 1)
    // {

    //     this
    // }

    this->noteRand.reset(this->arpRandomSeed);

    this->arpNoteLen = this->notePtr;

    if (this->arpMode)
    {
        uint8_t extraNotes = this->arpWidth;

        if (this->arpMode == ARP_MODE_AS_PLAYED)
        {
            for (uint8_t j = 0; j < this->notePtr; ++j)
            {
                this->snote[j] = this->note[j];
            }
        }
        else
        {
            // Sort notes
            int8_t lastNote = 0;
            for (uint8_t j = 0; j < this->notePtr; ++j)
            {
                int8_t nextNote = 127;
                for (uint8_t i = 0; i < this->notePtr; ++i)
                {
                    if (this->note[i] < nextNote && this->note[i] > lastNote)
                    {
                        nextNote = this->note[i];
                    }
                }
                this->snote[j] = nextNote;
                lastNote = nextNote;
            }

            // Turn into chord?
            if (this->arpMode == ARP_MODE_CHORD && this->notePtr > 1 && this->notePtr < 4)
            {
                int8_t chordNo = -1;

                if (this->notePtr == 2)
                {
                    uint8_t n1_n0 = this->snote[1] - this->snote[0];

                    for (int8_t j = 0; j < ARP_CHORDS; ++j)
                    {
                        if (chordTriggers[j][0] == 2 && chordTriggers[j][1] == n1_n0)
                        {
                            chordNo = j;
                            break;
                        }
                    }
                }
                else
                {
                    uint8_t n1_n0 = this->snote[1] - this->snote[0];
                    uint8_t n2_n0 = this->snote[2] - this->snote[0];

                    for (int8_t j = 0; j < ARP_CHORDS; ++j)
                    {
                        if (chordTriggers[j][0] == 3 && chordTriggers[j][1] == n1_n0 && chordTriggers[j][2] == n2_n0)
                        {
                            chordNo = j;
                            break;
                        }
                    }
                }

                if (chordNo >= 0)
                {
                    this->arpNoteLen = 1;
                    for (uint8_t j = 1; j <= chords[chordNo][0]; ++j)
                    {
                        this->snote[j] = this->snote[0] + chords[chordNo][j];
                        this->arpNoteLen++;
                    }
                }
            }
        }

        uint8_t lenWithExtraNotes = this->arpNoteLen;

        // Add extra notes
        for (uint8_t j = 0; j < extraNotes; ++j)
        {
            int8_t extraNote = this->snote[j % lenWithExtraNotes] + this->arpOctaveWidth * (1 + j / this->notePtr);
            if (!isNotePlayable(extraNote))
            {
                break;
            }
            this->snote[lenWithExtraNotes + j] = extraNote;
            this->arpNoteLen++;
        }

        // Reverse?
        if (this->arpNoteLen > 1 && (this->arpMode == ARP_MODE_DOWN || this->arpMode == ARP_MODE_DOWN_UP || this->arpMode == ARP_MODE_DOWN_UP_PLUS))
        {
            int8_t temp;
            for (uint8_t j = 0; j < (this->arpNoteLen + 1) / 2; ++j)
            {   
                temp = this->snote[j];
                this->snote[j] = this->snote[this->arpNoteLen - 1 - j];
                this->snote[this->arpNoteLen - 1 - j] = temp;
            }
        }

        lenWithExtraNotes = this->arpNoteLen;

        // Randomize?
        if (this->arpRandomMode)
        {
            uint8_t max = lenWithExtraNotes;
            for (uint8_t j = 0; j < lenWithExtraNotes; ++j)
            {
                this->tnote[j] = this->snote[j];
            }
            for (uint8_t j = 0; j < lenWithExtraNotes; ++j)
            {
                uint8_t r = noteRand.next() % max;
                this->snote[j] = this->tnote[r];
                max--;
                if (r != max)
                {
                    this->tnote[r] = this->tnote[max];
                }
            }
        }

        // Repeat style?
        if (this->arpRepStyle)
        {
            // Create temp array
            for (uint8_t j = 0; j < lenWithExtraNotes; ++j)
            {
                this->tnote[j] = this->snote[j];
            }
            this->arpNoteLen = 0;
            uint8_t repPtr = 0;
            const int8_t* repStyle = repStyles[this->arpRepStyle-1];

            for (uint8_t j = 0; j < lenWithExtraNotes; ++j)
            {
                // Skip note
                if (!repStyle[repPtr])
                {
                    this->snote[this->arpNoteLen++] = 0;
                }
                else
                {
                    for (uint8_t i = 0; i < repStyle[repPtr]; ++i)
                    {
                        this->snote[this->arpNoteLen++] = this->tnote[j];
                    }
                }

                repPtr++;
                if (repStyle[repPtr] == -1)
                {
                    repPtr = 0;
                }
            }
        }

        // Handle up down
        if (this->notePtr > 2 && (this->arpMode == ARP_MODE_UP_DOWN || this->arpMode == ARP_MODE_DOWN_UP))
        {
            for (uint8_t j = 0; j < lenWithExtraNotes - 2; ++j)
            {
                this->snote[lenWithExtraNotes + j] = this->snote[lenWithExtraNotes - 2 - j];
                this->arpNoteLen++;
            }
        }
        else if (this->notePtr > 1 && (this->arpMode == ARP_MODE_UP_DOWN_PLUS || this->arpMode == ARP_MODE_DOWN_UP_PLUS))
        {
            for (uint8_t j = 0; j < lenWithExtraNotes; ++j)
            {
                this->snote[lenWithExtraNotes + j] = this->snote[lenWithExtraNotes - 1 - j];
                this->arpNoteLen++;
            }
        }
    }
}

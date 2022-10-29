#ifndef OUTPUT_H
#define OUTPUT_H

#include <Arduino.h>
#include <AudioStream.h>
#include "trigger.h"
#include "random.h"

#define MAX_NOTES 16

#define ARP_MODE_NONE 0
#define ARP_MODE_AS_PLAYED 1
#define ARP_MODE_UP 2
#define ARP_MODE_DOWN 3
#define ARP_MODE_UP_DOWN 4
#define ARP_MODE_DOWN_UP 5
#define ARP_MODE_UP_DOWN_PLUS 6
#define ARP_MODE_DOWN_UP_PLUS 7
#define ARP_MODE_CHORD 8
#define ARP_MODES (ARP_MODE_CHORD+1)

#define ARP_SPEEDMODE_CONSTANT_NOTE_LEN_SLOW 0
#define ARP_SPEEDMODE_CONSTANT_NOTE_LEN_FAST 1
#define ARP_SPEEDMODE_CONSTANT_BEAT_LEN_SLOW 2
#define ARP_SPEEDMODE_CONSTANT_BEAT_LEN_FAST 3
#define ARP_SPEEDMODE_BPS_AND_TONE_LEN 4
#define ARP_SPEEDMODE_EXT_TRIG_PULSE 5 // uses arpNoteSpacing to define spacing
#define ARP_SPEEDMODE_EXT_TRIG_HOLD 6  // note is released when trigger goes off
#define ARP_SPEEDMODES (ARP_SPEEDMODE_EXT_TRIG_HOLD+1)

#define ARP_RANDOMMODE_OFF 0
#define ARP_RANDOMMODE_ON 1
#define ARP_RANDOMMODES (ARP_RANDOMMODE_ON+1)

#define ARP_REPSTYLE_NONE 0
#define ARP_REPSTYLES 20

#define ARP_CHORDS 17

extern const char* modeNames[ARP_MODES];
extern const char* repStyleNames[ARP_REPSTYLES];
extern const char* speedModeNames[ARP_SPEEDMODES];
extern const char* randomModeNames[ARP_RANDOMMODES];

class Output : public AudioStream
{
public:
	Output(Trigger &trigger) : AudioStream(0, NULL), trigger(trigger)
    { 	
	}
    virtual void update(void);
    void noteOn(int8_t note);
    void noteOff(int8_t note);
    void changeOctaveVoltage(int16_t add);
    void setSpeed(uint8_t data);
    void setNoteSpacing(uint8_t data);
    uint8_t setEnumArpMode(uint8_t data);
    uint8_t setEnumWidth(uint8_t data);
    uint8_t setEnumOctaveWidth(uint8_t data);
    uint8_t setEnumRepStyle(uint8_t data);
    uint8_t setEnumRandomMode(uint8_t data);
    uint8_t setEnumSpeedMode(uint8_t data);
    void setRandomSeed(uint8_t data);
private:
    Random noteRand = Random(0);
    Trigger &trigger;
    int16_t outputVal = 0;
    int16_t octaveVoltage = 11195;
    int8_t lowestNote = 0x19;
    int8_t highestNote = 0x5F;
    int8_t noteAt0V = 60;
    uint8_t notePtr = 0;
    int8_t note[MAX_NOTES];
    int8_t tnote[MAX_NOTES*4];
    int8_t snote[MAX_NOTES*2*4*4];  // *2 because up/down   *4 beacuse we can go 4 octaves up   *4 because of repeat
    uint8_t arpNoteLen = 0;

    const uint32_t _4000 = 3000;
    const uint32_t _100 = 100;
    const uint32_t _10000 = 10000;

    uint32_t arpM;
    uint32_t noteOnTime;
    uint32_t noteOffTime;
    uint32_t noteRestartTime;
    int8_t ramp = -1;
    uint8_t arpMode = ARP_MODE_CHORD;
    uint16_t arpSpeed = 0x01;
    uint8_t arpWidth = 0;
    uint8_t arpSpeedMode = ARP_SPEEDMODE_CONSTANT_NOTE_LEN_SLOW;
    uint8_t arpNoteSpacing = 40;
    uint8_t arpOctaveWidth = 12;
    uint8_t arpRepStyle = 0;
    uint8_t arpRandomMode = 0;
    uint8_t arpRandomSeed = 0;

    void playNote(int8_t note);
    void arpReset();
    void arp();
    int8_t selectNextNote();
    void setNoteTime();
    uint8_t isNotePlayable(int8_t note);
    uint8_t calcExtraNotes(uint8_t width);
    void sortNotes();
};

#endif

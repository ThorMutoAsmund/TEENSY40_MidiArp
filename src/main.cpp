#include <Arduino.h>
#include <Audio.h>
#include <Output.h>
#include <Trigger.h>

#define SENSOR_PIN A3

#define MIDI_RX_PIN 15
#define MIDI_TX_PIN 14
#define LED_PIN 13

#define LRCK_PIN 4
#define BCK_PIN 5
#define DATA_PIN 6

#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90
#define MIDI_AFTERTOUCH 0xA0
#define MIDI_CC 0xB0
#define MIDI_PROGRAM_CHANGE 0xC0
#define MIDI_CHANNEL_PRESSURE 0xD0
#define MIDI_PB 0xE0

// Control change
#define MIDI_CC_ENUM_ARP_MODE 24
#define MIDI_CC_ENUM_REP_STYLE 25
#define MIDI_CC_ENUM_WIDTH 26
#define MIDI_CC_ENUM_OCTAVE_WIDTH 27
#define MIDI_CC_ENUM_RANDOM_MODE 28
#define MIDI_CC_ENUM_SPEED_MODE 29
#define MIDI_CC_E5 30
#define MIDI_CC_E6 31

#define MIDI_CC_NOTE_SPACING 16
#define MIDI_CC_SPEED 17
#define MIDI_CC_RANDOM_SEED 18
#define MIDI_CC_X0 19
#define MIDI_CC_X1 20
#define MIDI_CC_X2 21
#define MIDI_CC_X3 22
#define MIDI_CC_X4 23

// System Common Messages
#define MIDI_SYSEX_BEGIN 0xF0
#define MIDI_SYSEX_END 0xF7

// System realtime messages
#define MIDI_TIMING_CLOCK 0xF8
#define MIDI_START 0xFA
#define MIDI_CONTINUE 0xFB
#define MIDI_STOP 0xFC
#define MIDI_ACTIVE_SENSE 0xFE
#define MIDI_RESET 0xFF


Trigger trigger;
Output output(trigger);
AudioOutputI2S i2s1;
AudioConnection patchCord1 (output, 0, i2s1, 0);
AudioConnection patchCord2 (trigger, 0, i2s1, 1);

uint8_t printNewLine = 0;
uint8_t data;
uint8_t readData = 0, prevReadData;
uint8_t status, prevStatus = 0xFF;
uint8_t statusHigh;
uint8_t statusChannel;
uint8_t data1, data2;
uint8_t analog;
uint8_t midiChannel = 0;

// Forward declarations
uint8_t getMessageLength(uint8_t statusHigh);
void debugWrite(const char* text, const char* val);
void debugWrite(const char* text, int val);
void debugWrite(const char* text, int val, int val2);

void setup()
{
    // wait for Arduino Serial Monitor to be ready
    Serial.begin(9600);
    pinMode(MIDI_RX_PIN, INPUT);
    pinMode(MIDI_TX_PIN, OUTPUT);

    while (!Serial && millis() < 2500) { }
    // digitalWrite(LRCK_PIN, LOW);
    // digitalWrite(BCK_PIN, LOW);

    AudioMemory (2);

    // pinMode(LRCK_PIN, OUTPUT);
    // pinMode(BCK_PIN, OUTPUT);
    // pinMode(DATA_PIN, OUTPUT);

    // Set MIDI baud rate:
    // Serial.begin(9600);
    // while (!Serial) { ; }

    //     

    Serial3.begin(31250);

    Serial.println("Midi ARP is Ready!");
    Serial.print("Running at ");
    Serial.print(F_CPU / 1000000, DEC);
    Serial.println(" MHz");    
}

uint32_t cnt = 0;
uint32_t ledVal = HIGH;

void loop()
{
    if (cnt)
    {
        if (!--cnt)
        {
            digitalWrite(LED_PIN, LOW);
        }
    }
    if (Serial.available())
    {
        data = Serial.read();
    }
    if (Serial3.available())
    {
        if (data != MIDI_ACTIVE_SENSE)
        {
            if (!cnt)
            {
                digitalWrite(LED_PIN, HIGH);
            }
            cnt = 500000;
        }

        data = Serial3.read();

        if ((data & 0xF0) == 0xF0)
        {
            if (data != MIDI_ACTIVE_SENSE)
            {
                Serial.print("SYS ");
                Serial.println(data, HEX);
            }
        }
        else
        {
            if (data & 0x80)
            {
                status = data;
                statusHigh = status & 0xF0;
                readData = getMessageLength(statusHigh);
                statusChannel = data & 0xF;
                Serial.println(statusChannel, DEC);
            }
            else
            {
                if (!readData)
                {
                    readData = getMessageLength(statusHigh);
                }

                if (readData == 2)
                {
                    data1 = data;
                    readData--;
                }
                else if (readData == 1)
                {
                    data2 = data;
                    readData--;
                }
            }

            if (!readData)
            {
                if (statusChannel == midiChannel)
                {
                    if (statusHigh == MIDI_NOTE_OFF || (statusHigh == MIDI_NOTE_ON && data2 == 0 ))
                    {
                        debugWrite("NOTE OFF ", data1);
                        output.noteOff(data1);
                    }
                    else if (statusHigh == MIDI_NOTE_ON)
                    {
                        debugWrite("NOTE ON ", data1);
                        output.noteOn(data1);
                    }
                    else if (statusHigh == MIDI_CC)
                    {
                        if (data1 == MIDI_CC_NOTE_SPACING)
                        {
                            debugWrite("Note spacing ", data2);
                            output.setNoteSpacing(data2 * 2);
                        }
                        else if (data1 == MIDI_CC_SPEED)
                        {
                            debugWrite("MOD ", data2);
                            output.setSpeed(data2 * 2);
                        }
                        else if (data1 == MIDI_CC_ENUM_ARP_MODE)
                        {
                            debugWrite("Mode ", modeNames[output.setEnumArpMode(data2)]);
                        }
                        else if (data1 == MIDI_CC_ENUM_WIDTH)
                        {
                            debugWrite("Width ", output.setEnumWidth(data2));
                        }
                        else if (data1 == MIDI_CC_ENUM_OCTAVE_WIDTH)
                        {
                            debugWrite("Octave Width ", output.setEnumOctaveWidth(data2));
                        }
                        else if (data1 == MIDI_CC_ENUM_REP_STYLE)
                        {
                            debugWrite("Rep Style ", repStyleNames[output.setEnumRepStyle(data2)]);
                        }
                        else if (data1 == MIDI_CC_ENUM_RANDOM_MODE)
                        {
                            debugWrite("Random Mode ", randomModeNames[output.setEnumRandomMode(data2)]);
                        }
                        else if (data1 == MIDI_CC_ENUM_SPEED_MODE)
                        {
                            debugWrite("Speed Mode ", speedModeNames[output.setEnumSpeedMode(data2)]);
                        }
                        else if (data1 == MIDI_CC_RANDOM_SEED)
                        {
                            debugWrite("Random seed ", data2);
                            output.setRandomSeed(data2 * 2);
                        }
                        else
                        {
                            debugWrite("CC ", data1, data2);
                        }
                    }
                    else if (statusHigh == MIDI_PB)
                    {
                        debugWrite("PB ", (data2<<7)+data1);
                    }
                    else if (statusHigh == MIDI_PROGRAM_CHANGE)
                    {
                        debugWrite("Mode ", modeNames[output.setEnumArpMode(data2)]);
                    }
                }
                prevStatus = status;
                prevReadData = readData;
            }
        }
    }
}
uint8_t getMessageLength(uint8_t statusHigh)
{
    return (statusHigh == MIDI_NOTE_ON || statusHigh == MIDI_NOTE_OFF || statusHigh == MIDI_AFTERTOUCH || statusHigh == MIDI_CC || statusHigh == MIDI_PB) ? 2 :
    ((statusHigh == MIDI_PROGRAM_CHANGE || statusHigh == MIDI_CHANNEL_PRESSURE) ? 1 : 0);
}

void debugWrite(const char* text, const char* val)
{
    Serial.print(text);
    Serial.println(val);
}

void debugWrite(const char* text, int val)
{
    Serial.print(text);
    Serial.println(val, DEC);
}

void debugWrite(const char* text, int val, int val2)
{
    Serial.print(text);
    Serial.print(val, DEC);
    Serial.print(" ");
    Serial.println(val2, DEC);
}

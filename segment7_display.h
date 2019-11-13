#ifndef my_segment7_display
#define my_segment7_display

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class segment7_display
{
public:
    segment7_display(int cols, int rows, int max_loop_tdelay = 1000);

    void pinSetup();
    void clearBits();
    void number_display(char number, bool decimalSet = false);
    void dataSet(bool data);
    void selectionSet(bool select = 1);
    int rtdelay();

private:
    int cols;
    int rows;
    int max_loop_tdelay;
    int tdelay = max_loop_tdelay / (cols * rows);

    uint8_t selectionClock = 5;
    uint8_t selectionPin = 6;
    uint8_t selectionLatch = 7;

    const uint8_t clockPin = 2;
    const uint8_t dataPin = 3;
    const uint8_t latchPin = 4;

    const bool segment_map[11][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}, // 9
        {1, 0, 0, 1, 1, 1, 0}  // Error "E"
    };
};

#endif
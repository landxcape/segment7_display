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

    void pinSetup(uint8_t dPin = 2, uint8_t lPin = 3, uint8_t cPin = 4,
                  uint8_t sPin = 5, uint8_t sLatch = 6, uint8_t sClock = 7);

    void clearBits();
    void number_display(char number, bool decimalSet = false);
    void setData(bool data);
    void setSelection(bool select = 1);
    void display_num_rows(String ROWS, bool first_row = false);
    void display_values(String *ROW_VALUES);

private:
    int cols;
    int rows;
    int max_loop_tdelay;
    int tdelay = max_loop_tdelay / (cols * rows);

    uint8_t selectionClock;
    uint8_t selectionPin;
    uint8_t selectionLatch;

    uint8_t clockPin;
    uint8_t dataPin;
    uint8_t latchPin;

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
        {1, 0, 0, 1, 1, 1, 1}  // Error "E"
    };
};

#endif
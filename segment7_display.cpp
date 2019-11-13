#include "segment7_display.h"

segment7_display::segment7_display(int cols, int rows, int max_loop_tdelay = 1000) : cols(cols),
                                                                                     rows(rows),
                                                                                     max_loop_tdelay(max_loop_tdelay)
{
}

void segment7_display::pinSetup()
{
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(selectionClock, OUTPUT);
    pinMode(selectionPin, OUTPUT);
    pinMode(selectionLatch, OUTPUT);
}

int segment7_display::rtdelay()
{
    return tdelay;
}

void segment7_display::clearBits()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0B00000000);
    digitalWrite(latchPin, HIGH);
}

void segment7_display::number_display(char number, bool decimalSet = false)
{
    digitalWrite(latchPin, LOW); // Latch
    dataSet(decimalSet);
    if (number == '0')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[0][6 - i]);
    }
    else if (number == '1')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[1][6 - i]);
    }
    else if (number == '2')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[2][6 - i]);
    }
    else if (number == '3')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[3][6 - i]);
    }
    else if (number == '4')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[4][6 - i]);
    }
    else if (number == '5')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[5][6 - i]);
    }
    else if (number == '6')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[6][6 - i]);
    }
    else if (number == '7')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[7][6 - i]);
    }
    else if (number == '8')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[8][6 - i]);
    }
    else if (number == '9')
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[9][6 - i]);
    }
    else
    {
        for (uint8_t i = 0; i < 7; i++)
            dataSet(segment_map[10][6 - i]);
    }
    digitalWrite(latchPin, HIGH); // Latch
}

void segment7_display::dataSet(bool data)
{
    digitalWrite(dataPin, data);  // Data set
    digitalWrite(clockPin, HIGH); // Clock
    digitalWrite(clockPin, LOW);  // Clock end
}

void segment7_display::selectionSet(bool select = 1)
{
    digitalWrite(selectionLatch, LOW);  // Latch
    digitalWrite(selectionPin, select); // Data set
    digitalWrite(selectionClock, HIGH); // Clock
    digitalWrite(selectionClock, LOW);  // Clock end
    digitalWrite(selectionLatch, HIGH); // Latch end
}

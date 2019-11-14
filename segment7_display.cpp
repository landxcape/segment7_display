#include "segment7_display.h"

segment7_display::segment7_display(int cols, int rows, int max_loop_tdelay = 1000) : cols(cols),
                                                                                     rows(rows),
                                                                                     max_loop_tdelay(max_loop_tdelay)
{
    pinSetup();
}

void segment7_display::pinSetup(uint8_t cPin, uint8_t dPin, uint8_t lPin,
                                uint8_t sClock, uint8_t sPin, uint8_t sLatch)
{
    for (uint8_t i = cPin; i <= sLatch; i++)
        pinMode(i, OUTPUT);

    clockPin = cPin;
    dataPin = dPin;
    latchPin = lPin;
    selectionClock = sClock;
    selectionPin = sPin;
    selectionLatch = sLatch;
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
    setData(decimalSet);
    if (number == '0')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[0][6 - i]);
    }
    else if (number == '1')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[1][6 - i]);
    }
    else if (number == '2')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[2][6 - i]);
    }
    else if (number == '3')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[3][6 - i]);
    }
    else if (number == '4')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[4][6 - i]);
    }
    else if (number == '5')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[5][6 - i]);
    }
    else if (number == '6')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[6][6 - i]);
    }
    else if (number == '7')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[7][6 - i]);
    }
    else if (number == '8')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[8][6 - i]);
    }
    else if (number == '9')
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[9][6 - i]);
    }
    else
    {
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[10][6 - i]);
    }
    digitalWrite(latchPin, HIGH); // Latch
}

void segment7_display::setData(bool data)
{
    digitalWrite(dataPin, data);  // Data set
    digitalWrite(clockPin, HIGH); // Clock
    digitalWrite(clockPin, LOW);  // Clock end
}

void segment7_display::setSelection(bool select = 1)
{
    digitalWrite(selectionLatch, LOW);  // Latch
    digitalWrite(selectionPin, select); // Data set
    digitalWrite(selectionClock, HIGH); // Clock
    digitalWrite(selectionClock, LOW);  // Clock end
    digitalWrite(selectionLatch, HIGH); // Latch end
}

void segment7_display::display_num_rows(String ROWS, int decimal_pos, bool first_row)
{
    bool leading_zero;
    char num;
    int leading_cols;
    int num_shift = 0;
    leading_zero = true;
    leading_cols = (int)ROWS[0] - 48;

    for (int c = 1; c <= leading_cols; c++)
    {
        num = ROWS[c];
        clearBits();
        if (first_row && c == 1)
            setSelection(0);
        else
            setSelection(1);

        if (leading_zero && num == '0' && c != decimal_pos && c != leading_cols)
        {
        }
        else
        {
            leading_zero = false;
            if (c == decimal_pos)
                number_display(num, true);
            else
                number_display(num, false);
        }

        delayMicroseconds(tdelay);
    }
    // }
}

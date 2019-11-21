#include "segment7_display.h"

segment7_display::segment7_display()
{
    pinSetup();
}

void segment7_display::pinSetup(uint8_t dPin, uint8_t lPin, uint8_t cPin,
                                uint8_t sPin, uint8_t sLatch, uint8_t sClock)
{
    for (uint8_t i = dPin; i <= sClock; i++)
        pinMode(i, OUTPUT);

    dataPin = dPin;
    latchPin = lPin;
    clockPin = cPin;
    selectionPin = sPin;
    selectionLatch = sLatch;
    selectionClock = sClock;
}

void segment7_display::setDisplay(int cols, int rows, unsigned long max_l_tdelay, bool CC)
{
    ncols = cols;
    nrows = rows;
    max_loop_tdelay = max_l_tdelay;
    COMMON_CATHODE = CC;
    tdelay = (int)(max_loop_tdelay / ((int)cols * (int)rows));
}

void segment7_display::clearBits()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, clearBit);
    digitalWrite(latchPin, HIGH);
}

void segment7_display::number_display(char c_number, bool decimalSet = false)
{
    uint8_t number = (int)c_number - 48;

    digitalWrite(latchPin, LOW); // Latch
    setData(decimalSet);

    if (number >= 0 && number <= 9)
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[number][6 - i]);

    // else if (c_number == '1')
    //     for (uint8_t i = 0; i < 7; i++)
    //         setData(segment_map[1][6 - i]);

    else
        for (uint8_t i = 0; i < 7; i++)
            setData(segment_map[10][6 - i]);

    digitalWrite(latchPin, HIGH); // Latch
}

void segment7_display::setData(bool data)
{
    if (!COMMON_CATHODE)
        data = !data;
    digitalWrite(dataPin, data);  // Data set
    digitalWrite(clockPin, HIGH); // Clock
    digitalWrite(clockPin, LOW);  // Clock end
}

void segment7_display::setSelection(bool select = 1)
{
    if (!COMMON_CATHODE)
        select = !select;
    digitalWrite(selectionLatch, LOW);  // Latch
    digitalWrite(selectionPin, select); // Data set
    digitalWrite(selectionClock, HIGH); // Clock
    digitalWrite(selectionClock, LOW);  // Clock end
    digitalWrite(selectionLatch, HIGH); // Latch end
}

void segment7_display::display_num_rows(String ROWS, bool first_row)
{
    char num, next_num;
    bool leading_zero = true;
    uint8_t display_cols = ROWS.length();

    for (uint8_t c = 0; c < display_cols; c++)
    {
        num = ROWS[c];
        next_num = ROWS[c + 1];

        clearBits();
        if (first_row && c == 0)
            setSelection(0);
        else
            setSelection(1);

        if (leading_zero && num == '0' && next_num != '.' && c != display_cols - 1)
        {
        }
        else
        {
            leading_zero = false;
            if (next_num == '.')
            {
                number_display(num, true);
                c++;
            }
            else
                number_display(num, false);
        }

        if (tdelay < 10000) // delayMicroseconds() can handle max of 16383 accurately
            delayMicroseconds(tdelay);
        else
            delay(tdelay / 1000);
    }
}

void segment7_display::display_values(String *ROW_VALUES)
{
    display_num_rows(*(ROW_VALUES), true);

    for (uint8_t i = 1; i < nrows; i++)
        display_num_rows(*(ROW_VALUES + i));
}
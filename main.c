#include <REGX51.H>

// 7-segment codes for digits 0–9 (common cathode)
unsigned char seg_code[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Digit control pins
sbit DIG1 = P0^0;
sbit DIG2 = P0^1;
sbit DIG3 = P0^2;
sbit DIG4 = P0^3;

// Disable all digit pins
void disable_all_digits() {
    DIG1 = 1;
    DIG2 = 1;
    DIG3 = 1;
    DIG4 = 1;
}

// Short delay (approx 1 ms)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++);
}

// Display one digit at a time
void display_digits(unsigned int num) {
    unsigned char t, h, te, o;

    t = (num / 1000) % 10;
    h = (num / 100) % 10;
    te = (num / 10) % 10;
    o = num % 10;

    // Thousands place
    disable_all_digits();
    P2 = seg_code[t];
    DIG1 = 0;
    delay_ms(1);

    // Hundreds place
    disable_all_digits();
    P2 = seg_code[h];
    DIG2 = 0;
    delay_ms(1);

    // Tens place
    disable_all_digits();
    P2 = seg_code[te];
    DIG3 = 0;
    delay_ms(1);

    // Ones place
    disable_all_digits();
    P2 = seg_code[o];
    DIG4 = 0;
    delay_ms(1);
}

void main() {
    unsigned int number = 0;
    unsigned int refresh_count = 0;

    while (1) {
        // Refresh display many times before changing number
        display_digits(number);
        refresh_count++;

        if (refresh_count >= 1) {  // ~250 full refreshes (~1s)
            refresh_count = 0;
            number++;
            if (number > 9999)
                number = 0;
        }
    }
}
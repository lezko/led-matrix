#include <Arduino.h>

int ROWS = 3;
int COLS = 3;

int col_pins[3] = {A0, A1, A2};
int value = 153;
int current_time = 0;
int cycle = 15;

int matrix[3][3] {
    value, 0, 0,
    0, 0, 0,
    0, 0, 0
};

void updateMatrix() {
    current_time++;
    if (current_time < cycle) {
        return;
    }
    current_time = 0;

    bool found = false;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (matrix[r][c] == value) {
                found = true;
                matrix[r][c] = 0;
                if (r == 0) {
                    c++;
                    if (c == COLS) {
                        r = 1;
                        c = COLS - 1;
                    }
                } else if (c == COLS - 1) {
                    r++;
                    if (r == ROWS) {
                        c = COLS - 2;
                        r = ROWS - 1;
                    }
                } else if (r == ROWS - 1) {
                    c--;
                    if (c < 0) {
                        r = ROWS - 2;
                        c = 0;
                    }
                } else if (c == 0) {
                    r--;
                    if (r < 0) {
                        c = 1;
                        r = 0;
                    }
                }

                matrix[r][c] = value;
                break;
            }
        }


        if (found) {
            break;
        }
    }
};

void renderMatrix(int t) {
    for (int r = 0; r < ROWS; ++r) {
        digitalWrite(r, 1);
        for (int c = 0; c < COLS; ++c) {
            analogWrite(col_pins[c], matrix[r][c]);
        }
        delay(t);
        digitalWrite(r, 0);
    }
};

void setup() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
}

void loop() {
    updateMatrix();
    renderMatrix(1);
}

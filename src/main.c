#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "ultrasonic_distance.h"
#include "chassis.h"

int main() {
    DDRD = (1 << LEFT_MOTOR) | (1 << RIGHT_MOTOR) | (1 << ULTRASONIC_TRIGGER);

    bool run = false;
    int ir_diode = (1 << IR_DIODE);
    int run_button = (1 << RUN_BUTTON);

    ultrasonic_init();

    while (1) {
        if (run) {
            if ((PIND & ir_diode) | (ultrasonic_distance() <= 5)) {
            stopRightMotor();
            }
            else {
                startRightMotor();
            }
        }

        if (PINB & run_button) {
            if (run) {
                stopLeftMotor();
                stopRightMotor();
            }
            else {
                startLeftMotor();
                startRightMotor();
            }
            run = !run;
        }

        _delay_ms(100);
    }

    return 0;
}
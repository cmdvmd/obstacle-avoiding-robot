#include "ultrasonic_distance.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int timer;

void ultrasonic_init() {
    // Setup interrupt every 1us
    TCCR0A |= (1 << WGM01);
    OCR0A   =  20;
    TIMSK0 |= (1 << OCIE0A);

    sei();
}

void startTimer() {
    TCNT0  =  0;
    TCCR0B = (1 << CS00);
    timer  =  0;
}

void stopTimer() {
    TCCR0B = 0;
}

unsigned long ultrasonic_distance() {
    unsigned char trigger_pin = (1 << ULTRASONIC_TRIGGER);
    unsigned char echo_pin    = (1 << ULTRASONIC_ECHO);

    PORTD &= ~trigger_pin;
    _delay_us(2);
    PORTD |= trigger_pin;
    _delay_us(10);

    while (!(PIND & echo_pin));
    startTimer();
    while (PIND & echo_pin);
    stopTimer();

    return timer / 50;
}

ISR(TIMER0_COMPA_vect) {
    timer++;
}

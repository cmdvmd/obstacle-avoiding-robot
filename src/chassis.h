#ifndef CHASSIS_H
#define CHASSIS_H

#include <avr/io.h>

#define startLeftMotor()  (PORTD |=  (1 << LEFT_MOTOR))
#define stopLeftMotor()   (PORTD &= ~(1 << LEFT_MOTOR))
#define startRightMotor() (PORTD |=  (1 << RIGHT_MOTOR))
#define stopRightMotor()  (PORTD &= ~(1 << RIGHT_MOTOR))

#endif
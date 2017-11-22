//******************************************************************************
// IRremote
// Version 2.0.1 June, 2015
// Copyright 2009 Ken Shirriff
// For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html

// This file contains all board specific information. It was previously contained within
// IRremoteInt.h

// Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
//
// Interrupt code based on NECIRrcv by Joe Knapp
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
// Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
//
// JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
// Whynter A/C ARC-110WD added by Francesco Meschia
//******************************************************************************

// fixes (
#define digitalWrite(x,y) x
#define CORE_LED0_PIN 1
#define OUTPUT 1
#define pinMode(x,y) x
#include <avr/interrupt.h>
#define micros() 1
//#define boolean uint8_t
#define delay(x) x
//)


#ifndef boarddefs_h
#define boarddefs_h
#include <avr/io.h>

//------------------------------------------------------------------------------
// Defines for blinking the LED
//

#define BLINKLED        CORE_LED0_PIN
#define BLINKLED_ON()   (digitalWrite(CORE_LED0_PIN, HIGH))
#define BLINKLED_OFF()  (digitalWrite(CORE_LED0_PIN, LOW))


//------------------------------------------------------------------------------
// CPU Frequency
//
#define SYSCLOCK  16000000  // main Arduino clock

// microseconds per clock interrupt tick
#define USECPERTICK    50

#define IR_USE_TIMER1   // tx = pin 9


//---------------------------------------------------------
// Timer1 (16 bits)
//

#define TIMER_RESET  // irRecv, IRremote
#define TIMER_ENABLE_PWM   (TCCR1A |= _BV(COM1A1)) // irSend
#define TIMER_DISABLE_PWM  (TCCR1A &= ~(_BV(COM1A1)))//irSend

#define TIMER_ENABLE_INTR   (TIMSK1 = _BV(OCIE1A))  // irRecv
#define TIMER_DISABLE_INTR  (TIMSK1 = 0)           //irSend

#define TIMER_INTR_NAME       TIMER1_COMPA_vect   // IRremote

   //irSend
#define TIMER_CONFIG_KHZ(val) ({ \
	const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
	TCCR1A                = _BV(WGM11); \
	TCCR1B                = _BV(WGM13) | _BV(CS10); \
	ICR1                  = pwmval; \
	OCR1A                 = pwmval / 3; \
})

 // irRecv
#define TIMER_CONFIG_NORMAL() ({ \
	TCCR1A = 0;	 \
	TCCR1B = _BV(WGM12) | _BV(CS10); \
	OCR1A  = SYSCLOCK * USECPERTICK / 1000000; \
	TCNT1  = 0; \
})

#define TIMER_PWM_PIN  9   //irSend


#endif // ! boarddefs_h

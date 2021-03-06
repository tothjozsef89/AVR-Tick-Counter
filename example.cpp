//
// Simple and accurate tick counter on AVR microcontrollers
// https://github.com/malcom/AVR-Tick-Counter
//
// Copyright (C) 2017 Marcin 'Malcom' Malich <me@malcom.pl>
// Released under the MIT License.
//

#include <inttypes.h>

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "avr-tick-counter.h"

int main() {

	LcdInit();


	// First measurement by simple API

	Tick::ResetCounter();
	Tick::StartCounter();
	////////////////////

	__builtin_avr_delay_cycles(0xffff);

	////////////////////
	Tick::StopCounter();
	// pause counter
	// do sth...
	// resume counter
	Tick::StartCounter();
	////////////////////

	__builtin_avr_delay_cycles(100);

	////////////////////
	Tick::StopCounter();
	uint16_t m1 = Tick::Get();


	// Second measurement by RAII
	{
		Tick::AutoCounter ticks(true);
		////////////////////

		__builtin_avr_delay_cycles(200);

		////////////////////
	}
	uint16_t m2 = Tick::Get();


	char buf[16];

	LcdGoto(0, 0);
	sprintf(buf, "ticks1: %d", m1);
	LcdWriteText(buf);

	LcdGoto(0, 1);
	sprintf(buf, "ticks2: %d", m2);
	LcdWriteText(buf);

	while (true)
		;

	return 0;
}

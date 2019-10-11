//CUHK-IE did some modification for ENGG1100 (2017-2018), 2017.07.18

//  Author: avishorp@gmail.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include "TM1637DisplayClass.h"
#include <Arduino.h>

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // B
  0b00111001,    // C
  0b01011110,    // D
  0b01111001,    // E
  0b01110001     // F
  };
 
  //void TM1637DisplayClass::init( uint8_t pinClk, uint8_t pinDIO)
  void TM1637DisplayClass::init( uint8_t pinDIO,  uint8_t pinClk)  
  {	
	// Copy the pin numbers
	m_pinClk = pinClk;
	m_pinDIO = pinDIO;
	
	// Set the pin direction and default value.
	// Both pins are set as inputs, allowing the pull-up resistors to pull them up
    pinMode(m_pinClk, INPUT);
    pinMode(m_pinDIO,INPUT);
	digitalWrite(m_pinClk, LOW);
	digitalWrite(m_pinDIO, LOW);
  }
  
	void TM1637DisplayClass::setValue(int num)// leading zero = true;
  {  
  	num = abs(num);
	  showNumberDec(num, true);
  }
  
  void TM1637DisplayClass::setDigit(int num, uint8_t pos)	//num = 1 digit only
  {
	  num = abs(num%10);
    if (pos<0)  pos = 0;
    if (pos>3) pos = 3;
	  showNumberDec(num, false, 1, pos);
  }
  	
//TM1637DisplayClass::TM1637DisplayClass( uint8_t pinClk, uint8_t pinDIO)
TM1637DisplayClass::TM1637DisplayClass(  uint8_t pinDIO, uint8_t pinClk)
{
	// Copy the pin numbers
	m_pinClk = pinClk;
	m_pinDIO = pinDIO;
	
	// Set the pin direction and default value.
	// Both pins are set as inputs, allowing the pull-up resistors to pull them up
    pinMode(m_pinClk, INPUT);
    pinMode(m_pinDIO,INPUT);
	digitalWrite(m_pinClk, LOW);
	digitalWrite(m_pinDIO, LOW);
}

void TM1637DisplayClass::setBrightness(uint8_t brightness)
{
	m_brightness = brightness;
}

void TM1637DisplayClass::setColon(bool colon)
{
	m_colon = colon;
}

void TM1637DisplayClass::setSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
    // Write COMM1
	start();
	writeByte(TM1637_I2C_COMM1);
	stop();
	
	// Write COMM2 + first digit address
	start();
	writeByte(TM1637_I2C_COMM2 + (pos & 0x03));
	
	// Write the data bytes
	for (uint8_t k=0; k < length; k++) 
	  writeByte(segments[k]);
	  
	stop();

	// Write COMM3 + brightness
	start();
	writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
	stop();
}
 
void TM1637DisplayClass::showNumberDec(int num, bool leading_zero, uint8_t length, uint8_t pos)
{
	uint8_t digits[4];
	const static int divisors[] = { 1, 10, 100, 1000 };
	bool leading = true;
	
	for(int8_t k = 0; k < 4; k++) {
	    int divisor = divisors[4 - 1 - k];
		int d = num / divisor;
		
		if ( k == 1 && m_colon == true ){
		
			if (d == 0) {
			  if (leading_zero || !leading || (k == 3))
				digits[k] = 0x80 | encodeDigit(d);
			  else
				digits[k] = 0x80 | 0;
			}
			else {
				digits[k] = 0x80 | encodeDigit(d);
				num -= d * divisor;
				leading = false;
			}
			
		} else{
			if (d == 0) {
			  if (leading_zero || !leading || (k == 3))
				digits[k] = encodeDigit(d);
			  else
				digits[k] = 0;
			}
			else {
				digits[k] = encodeDigit(d);
				num -= d * divisor;
				leading = false;
			}
		}	
	}
	
	setSegments(digits + (4 - length), length, pos);
}

void TM1637DisplayClass::bitDelay()
{
	delayMicroseconds(50);
}
   
void TM1637DisplayClass::start()
{
  pinMode(m_pinDIO, OUTPUT);
  bitDelay();
}
   
void TM1637DisplayClass::stop()
{
	pinMode(m_pinDIO, OUTPUT);
	bitDelay();
	pinMode(m_pinClk, INPUT);
	bitDelay();
	pinMode(m_pinDIO, INPUT);
	bitDelay();
}
  
bool TM1637DisplayClass::writeByte(uint8_t b)
{
  uint8_t data = b;

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    pinMode(m_pinClk, OUTPUT);
    bitDelay();
    
	// Set data bit
    if (data & 0x01)
      pinMode(m_pinDIO, INPUT);
    else
      pinMode(m_pinDIO, OUTPUT);
    
    bitDelay();
	
	// CLK high
    pinMode(m_pinClk, INPUT);
    bitDelay();
    data = data >> 1;
  }
  
  // Wait for acknowledge
  // CLK to zero
  pinMode(m_pinClk, OUTPUT);
  pinMode(m_pinDIO, INPUT);
  bitDelay();
  
  // CLK to high
  pinMode(m_pinClk, INPUT);
  bitDelay();
  uint8_t ack = digitalRead(m_pinDIO);
  if (ack == 0)
    pinMode(m_pinDIO, OUTPUT);
	
	
  bitDelay();
  pinMode(m_pinClk, OUTPUT);
  bitDelay();
  
  return ack;
}

uint8_t TM1637DisplayClass::encodeDigit(uint8_t digit)
{
	return digitToSegment[digit & 0x0f];
}

   


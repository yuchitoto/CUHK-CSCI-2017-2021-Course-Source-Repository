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

#ifndef __TM1637DISPLAY__
#define __TM1637DISPLAY__

#include <inttypes.h>

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

class TM1637DisplayClass {

public:
  //! @param pinClk - The number of the digital pin connected to the clock pin of the module
  //! @param pinDIO - The number of the digital pin connected to the DIO pin of the module
  TM1637DisplayClass(uint8_t pinClk, uint8_t pinDIO);
  
  //! Sets the brightness of the display.
  //!
  //! The setting takes effect when a command is given to change the data being
  //! displayed.
  //!
  //! @param brightness A number from 0 (lowes brightness) to 7 (highest brightness)
  void setBrightness(uint8_t brightness);
 
  void setColon ( bool colon);
  void setSegments(const uint8_t segments[], uint8_t length = 4, uint8_t pos = 0);
  
  
  //! Translate a single digit into 7 segment code
  uint8_t encodeDigit(uint8_t digit);

  void init( uint8_t pinClk, uint8_t pinDIO);
  
  void setValue(int num);			// leading zero = true;
  
  void setDigit(int num, uint8_t pos = 0);	//num = 1 digit only
  
protected:
   void bitDelay();
   
   void start();
   
   void stop();
   
   bool writeByte(uint8_t b);
   
private:
	uint8_t m_pinClk;
	uint8_t m_pinDIO;
	uint8_t m_brightness;
	bool m_colon;
	
  //! Displayes a decimal number
  void showNumberDec(int num, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);
};

#endif // __TM1637DISPLAY__

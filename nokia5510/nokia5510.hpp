// ==========================================================================
//
// File      : nokia5510.hpp
// Part of   : library for a nokia5510 input interface
// Copyright : A.D. van Bergeijk(2016)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
//
// ==========================================================================

#ifndef NOKIA5510_HPP
#define NOKIA5510_HPP
#include "hwlib.hpp"
/// Nokia 5510 lcd input interface
//
/// This is a class of a nokia5510 lcd of 84x48 pixels.
/// The neccecery constructors and input functies a provided within.
/// An empty data matrix and buffer are also provided.
/// Framerate is based on the amount of pixels the screen needs change per flush.
/// Needs hwlib to function properly.
/// Pin discription:
/// din: Used to provide data to send to the screen
/// clock: Used to send the data to the screen when going from high to low.
/// reset: Can interupt the data being send to the sreen:
/// dc: decides if the data being send is a command or data to print (low = command, high = data). 
/// enable: enables the other pins (active low).
class nokia5510{
protected:
	hwlib::target::pin_out & din;
	hwlib::target::pin_out & clock;
	hwlib::target::pin_out & reset;
	hwlib::target::pin_out & dc;
	hwlib::target::pin_out & enable;
	int buffer[84][48] = {{0}};
	int data[84][48] = {{0}};
	const int sizex = 84 ;
	const int sizey = 48 ; 
public:

	nokia5510(hwlib::target::pin_out & din, hwlib::target::pin_out & clock,hwlib::target::pin_out & reset,hwlib::target::pin_out & dc,hwlib::target::pin_out & enable);
	
	void setpixel(int x, int y);
	
	void datain(int x[8]);
	int getsizex();
	int getsizey();
	void clear();
	void command(int x[8]);
	void locx(int x = 0);
	void locy(int x = 0);
	void flush();
};
;
#endif // NOKIA5510_HPP
// ==========================================================================
//
// File      : nokia5510.cpp
// Part of   : library for a nokia5510 input interface
// Copyright : A.D. van Bergeijk(2016)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
//
// ==========================================================================

#include "nokia5510.hpp"

	/// Constructor nokia5510 lcd
	//
	/// Sets the pins needed to put data on the screen.
	/// Executes commands needed to properly use the lcd.
	/// Emptys the screen.
	nokia5510::nokia5510(hwlib::target::pin_out & din, hwlib::target::pin_out & clock,hwlib::target::pin_out & reset,hwlib::target::pin_out & dc,hwlib::target::pin_out & enable):
	din(din),
	clock(clock),
	reset(reset),
	dc(dc),
	enable(enable)
	{
		clock.set(0);
		hwlib::wait_ms(10);
		enable.set(1);
		hwlib::wait_ms(10);
		reset.set(0);
		hwlib::wait_ms(10);
		reset.set(0.5);
		hwlib::wait_ms(200);
		int a[9] = {0,0,1,0,0,0,0,1};
		int b[9] = {1,1,0,0,1,0,0,0};
		int c[9] = {0,0,0,0,0,1,1,0};
		int d[9] = {0,0,1,0,0,0,0,0};
		int e[9] = {0,0,0,1,0,0,1,1};
		int f[9] = {0,0,0,0,1,1,0,0};
		command(a);
		command(b);
		command(c);
		command(d);
		command(e);
		command(f);
		clear();
		locx();
		locy();
	}
	/// Set pixel
	//
	/// Sets a pixel in the data matrix at the given x and y coordinats.
	void nokia5510::setpixel(int x, int y){
		data[x][y] = 1;
	}
	/// Put byte on screen
	//
	/// Puts a byte of data on the screen.
	/// Used by flush.
	void nokia5510::datain(int x[8]){
		dc.set(1);
		enable.set(0);
		for(int i = 7; i >= 0 ;i--){
			din.set(x[i]);
			clock.set(1);
			hwlib::wait_ms(0.3);
			clock.set(0);
		}
		enable.set(1);
	}
	/// Get size x
	//
	/// Returns the x size of the lcd.
	int nokia5510::getsizex(){
		return sizex;
	}
	/// Get size y
	//
	/// Returns the y size of the lcd.
	int nokia5510::getsizey(){
		return sizey;
	}
	/// Screen clear
	//
	/// Clears the screen of al pixels.
	/// Emptys both the buffer and data matrix.
	void nokia5510::clear(){
		int empty[8] = {0};
		for(int i = 0 ;i < 504; i++){
			datain(empty);
		}
		for(int y = 0; y < 48; y++){
			for(int x = 0; x <84; x++){
				buffer[x][y] = 0;
				data[x][y] = 0;
			}
		}
	}
	/// Give a command to screen
	//
	/// Gives a byte of data as a command to the screen.
	/// Used to change draw location.
	void nokia5510::command(int x[8]){
		dc.set(0);
		enable.set(0);
		for(int i = 0; i < 8;i++){
			din.set(x[i]);
			clock.set(1);
			hwlib::wait_ms(0.3);
			clock.set(0);
		}
		enable.set(1);
	}
	/// Change draw loction x coordinat
	//
	/// Makes a binairy byte from an integer.
	/// Adds a 1 on the appropriat spot to specify it as a new x coordinat.
	/// Executes the command.
	void nokia5510::locx(int x){
		int a[8] = {0};
		for(int i = 7;i >= 0;i--){
			a[i] = x % 2;
			x = x / 2;
		}
		a[0] = 1;
			for(int i = 0; i< 8; i++){
		}
		command(a);
	}
	/// Change draw loction y coordinat
	//
	/// Makes a binairy byte from an integer.
	/// Adds a 1 on the appropriat spot to specify it as a new y coordinat.
	/// Executes the command.
	void nokia5510::locy(int x){
		int a[8] = {0};
		for(int i = 7;i >= 0;i--){
			a[i] = x % 2;
			x = x / 2;
		}
		a[1] = 1;
			for(int i = 0; i< 8; i++){
		}
		command(a);
	}
	/// Flush set pixels
	//
	/// Compares the data matrix to the buffer matrix.
	/// Differences are copied to the buffer.
	/// Bytes with differences in them are printed on the screen.
	/// Data matrix is emptied.
	void nokia5510::flush(){
		int posx = 0;
		int posy = 0;
		int ar[8];
		for(int y = 0; y < 48; y++){
			for(int x = 0; x <84; x++){
				if (data[x][y] != buffer[x][y]){
					if ((!(x == 0 && y == 0 ))&&(!(x == posx + 1 && ((y/8)*8) == ((posy/8)*8)))){
						locx(x);
						
						locy(y/8);
						
					}
					for (int n = 0; n < 8; n++){
						ar[n] = data[x][n + ((y/8)*8)];
						buffer[x][n + ((y/8)*8)] = data[x][n+((y/8)*8)];
					}
					datain(ar);
					posx = x;
					posy = y;
				}
			}
		}
		for(int y = 0; y < 48; y++){
			for(int x = 0; x <84; x++){
				data[x][y] = 0;
			}
		}
	}
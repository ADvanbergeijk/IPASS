#include "hwlib.hpp"
#include "nokia5510.hpp"

int main(int argc, char **argv)
{
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	auto dc = hwlib::target::pin_out( hwlib::target::pins::d7 );
	auto enable = hwlib::target::pin_out( hwlib::target::pins::d10 );
	auto reset = hwlib::target::pin_out( hwlib::target::pins::d5 );
	auto din = hwlib::target::pin_out( hwlib::target::pins::d8 );
	auto clock = hwlib::target::pin_out( hwlib::target::pins::d9 );
	nokia5510 w(din,clock,reset,dc,enable);
	hwlib::wait_ms(1000);
	hwlib::cout<<"Prints a pixel that goes from left to right over every row from top to bottom.";
	hwlib::wait_ms(1000);
int i = 0;
int j = 0;
while(1){
	w.setpixel(i,j);
	w.setpixel(i+1,j);
	w.setpixel(i+2,j);
	w.flush();
	hwlib::wait_ms(60);
	i++;
	if(i >= 84){
		i = 0;
		j++;
	}
}
}

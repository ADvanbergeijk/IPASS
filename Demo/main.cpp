#include "hwlib.hpp"
#include "nokia5510.hpp"
#include "paddle.hpp"
#include "obj.hpp"

#include "sonarSensor.hpp"


int main(void){
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
//	
	HWLIB_TRACE;
	auto dc = hwlib::target::pin_out( hwlib::target::pins::d7 );
	auto enable = hwlib::target::pin_out( hwlib::target::pins::d10 );
	auto reset = hwlib::target::pin_out( hwlib::target::pins::d5 );
	auto din = hwlib::target::pin_out( hwlib::target::pins::d8 );
	auto clock = hwlib::target::pin_out( hwlib::target::pins::d9 );
	auto triggerl = hwlib::target::pin_out( hwlib::target::pins::d2 );
	auto echol = hwlib::target::pin_in( hwlib::target::pins::d3 );
	auto triggerr = hwlib::target::pin_out( hwlib::target::pins::d11 );
	auto echor = hwlib::target::pin_in( hwlib::target::pins::d12 );
	nokia5510 w(din,clock,reset,dc,enable);
	obj b(w,4,4,20,20,-2,0);
	sonarSensor left(triggerl,echol);
	sonarSensor right(triggerr,echor);
	paddle l(w,left,12,2,6,18,0,0);
	paddle r(w,right,12,2,76,18,0,0);
	
	hwlib::wait_ms(1000);
	l.update();
	r.update();
	b.update();
	w.flush();
	hwlib::wait_ms(1000);
	while(1){
		l.update();
		r.update();
		b.update();
		w.flush();
		
		hwlib::wait_ms(70);
		if(b.locy > (47 - b.lenght) || b.locy < 1){
			b.speedy *= -1;
		}
		if(b.locx >= w.getsizex() - b.width || b.locx <= 0 - b.width){
			b.locx = 42;
			b.speedy *= -1;
		}
		if(b.locx == (l.locx + l.width ) && (b.locy > l.locy && b.locy < (l.locy + l.lenght))&& (b.speedx < 0)){
			b.speedx *= -1;
			b.speedy = l.speedy;
		}
		if(b.locx == (r.locx - b.width ) && (b.locy > r.locy && b.locy < (r.locy + r.lenght))&& (b.speedx > 0)){
			b.speedx *= -1;
			b.speedy = r.speedy;
		}
	}
}
#include "obj.hpp"

obj::obj( nokia5510 & w, int lenght, int width, int locx, int locy, int speedx, int speedy):
		w(w),
		lenght(lenght),
		width(width),
		locx(locx),
		locy(locy),
		speedx(speedx),
		speedy(speedy)
	{}
	
	int obj::get_x(){
		return locx;
	}
	
void obj::update(){
	locx += speedx;
	locy += speedy;
	for(int i = 0; i < width; i++){
		for (int j = 0; j < lenght; j++){
			if((i != 0 || j != 0) &&(i != 0 || j != lenght-1) &&(i != width-1 || j != 0) &&(i != width-1 || j != lenght-1)){
				w.setpixel((i+ locx),(j+locy));
			}
		}
	}
}

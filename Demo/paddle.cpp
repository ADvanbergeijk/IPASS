#include "paddle.hpp"
paddle::paddle( nokia5510 & w,sonarSensor & sensor, int lenght, int width, int locx, int locy, int speedx, int speedy):
		w(w),
		sensor(sensor),
		lenght(lenght),
		width(width),
		locx(locx),
		locy(locy),
		speedx(speedx),
		speedy(speedy)
	{}
	
void paddle::update(){
	if (sensor.TriggerInRange(4,20,1)*0.48 > locy){
		speedy = 1;
	}
	else if (sensor.TriggerInRange(4,20,1)*0.48 < locy){
		speedy = -1;
	}
	else if(sensor.TriggerInRange(4,20,1)*0.48 == locy){
		speedy = 0;
	}
	locy  = (sensor.TriggerInRange(4,20,1)*0.48);
	for(int i = 0; i < width; i++){
		for (int j = 0; j < lenght; j++){
				w.setpixel((i+ locx),(j+locy));
		}
	}
}

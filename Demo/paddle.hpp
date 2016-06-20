#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "nokia5510.hpp"
#include "sonarSensor.hpp"
class paddle{
protected:
   nokia5510 & w;
   sonarSensor & sensor;
public:
   int lenght;
   int width;
   int locx;
   int locy;
   int speedx;
   int speedy;
	paddle( nokia5510 & w,sonarSensor & sensor, int lenght, int width, int locx, int locy, int speedx, int speedy);
	void update();
	int get_x();
};
#endif // paddle_HPP
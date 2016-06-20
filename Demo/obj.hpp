#ifndef OBJ_HPP
#define OBJ_HPP

#include "nokia5510.hpp"
class obj{
protected:
   nokia5510 & w;

public:
   int lenght;
   int width;
   int locx;
   int locy;
   int speedx;
   int speedy;
	obj( nokia5510 & w, int lenght, int width, int locx, int locy, int speedx, int speedy);
	void update();
	int get_x();
};
#endif // OBJ_HPP
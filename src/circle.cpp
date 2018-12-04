#include "circle.h"
using namespace circleSpace;
using nlohmann::json;
int circle::getTimeError(int timeClicked)
{
	int error = abs(timeClicked - milisecondTime);
	return error;
}

int circle::scoreClick(int timeError)
{
	if (timeError <= 200) {
		return 100;
	}
	else if (timeError <= 300) {
		return 50;
	}
	else {
		return 0;
	}
}

circle::circle(int time, int x, int y, int rad)
{
	milisecondTime = time;
	xCoord = x;
	yCoord = y;
	location.set(x, y);
	radius = rad;
	clicked = false;
	deleted = false;
}

void circle::deleteCircle()
{
	location.set(-300, -300);
	deleted = true;
}

//inline void circleSpace::to_json(json & j, const circle & c)
//{
//	j = json{ {"time", c.milisecondTime}, {"xCoord", c.xCoord}, {"yCoord", c.yCoord} };
//}
//
//inline void circleSpace::from_json(const json & j, circle & c)
//{
//	j.at("time").get_to(c.milisecondTime);
//	j.at("x").get_to(c.xCoord);
//	j.at("y").get_to(c.yCoord);
//}


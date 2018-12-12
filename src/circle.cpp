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
	if (timeError <= 100) {
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
	displayNum = 0;
	assignedNum = false;
}

void circle::deleteCircle()
{
	location.set(-300, -300);
	deleted = true;
}

bool circleSpace::circle::isClickable(std::vector<circle> circles, int position)
{
	if (position == 0) {
		return true;
	}
	for (int i = 0; i < position; i++) {
		if (circles[i].clicked == true || circles[i].deleted == true) {

		}
		else {
			return false;
		}
	}
	return true;
}

inline void circleSpace::to_json(json & j, const circle & c)
{
	j = json{ {"time", c.milisecondTime}, {"xCoord", c.xCoord}, {"yCoord", c.yCoord} };
}

inline void circleSpace::from_json(const json & j, circle & c)
{
	j.at("time").get<decltype(c.milisecondTime)>();
	j.at("x").get<decltype(c.xCoord)>();
	j.at("y").get<decltype(c.yCoord)>();
	//j.at("circle").get<decltype(c.circles)>();
}


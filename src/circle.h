#pragma once
#include "ofxGui.h"
class circle {
public:
	ofPoint location;
	int radius;
	int milisecondTime;
	int xCoord;
	int yCoord;
	bool clicked;
	bool deleted;
	int getTimeError(int timeClicked);
	int scoreClick(int timeError);
	circle(int time, int x, int y, int radius);
	void deleteCircle();
};
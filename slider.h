#pragma once
#include "ofxGui.h"
class slider {
public:
	ofPoint point1;
	ofPoint control;
	ofPoint point2;
	int radius;
	int startTime;
	int endTime;
	int xCoordOne;
	int yCoordOne;
	int xCoordCtr;
	int yCoordCtr;
	int xCoordTwo;
	int yCoordTwo;
	bool deleted;
	//int getTimeError(int timeClicked);
	//int scoreClick(int timeError);
	//slider(int);
	//void deleteCircle();
};
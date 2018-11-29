#pragma once
#include "ofxGui.h"
class slider {
public:
	ofPoint pointOne;
	ofPoint control;
	ofPoint pointTwo;
	int startTime;
	int endTime;
	int xCoordOne;
	int yCoordOne;
	int xCoordCtr;
	int yCoordCtr;
	int xCoordTwo;
	int yCoordTwo;
	int totalTime;
	bool deleted;
	slider(int startTime, int xOne, int yOne, int xCtr, int yCtr, int endTime, int xTwo, int yTwo);
	bool inside(float x, float y);
	void deleteSlider();
};
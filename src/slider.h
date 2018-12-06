#pragma once
#include "ofxGui.h"
class slider {
public:
	ofPoint pointOne;
	ofPoint control;
	ofPoint pointTwo;
	ofPolyline path;
	int startTime;
	int endTime;
	int xCoordOne;
	int yCoordOne;
	int xCoordCtr;
	int yCoordCtr;
	int xCoordTwo;
	int yCoordTwo;
	int totalTime;
	int pointCounter;
	int displayNum;
	bool assignedNum;
	bool deleted;
	int totalPoints;
	slider(int startTime, int xOne, int yOne, int xCtr, int yCtr, int endTime, int xTwo, int yTwo);
	void deleteSlider();
};
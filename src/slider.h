#pragma once
#include "ofxGui.h"
class slider {
public:
	//Start point of slider
	ofPoint pointOne;
	//Point for calculating curve of the slider
	ofPoint control;
	//End point of slider
	ofPoint pointTwo;
	//Path the slider will follow
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
	//Total number of combo to limit combo per slider
	int pointCounter;
	//Number to be displayed on the slider
	int displayNum;
	//Whether a number was assigned already or not
	bool assignedNum;
	bool deleted;
	//Max points for the slider
	int totalPoints;
	//Constructs the slider with 3 points and start and end time
	slider(int startTime, int xOne, int yOne, int xCtr, int yCtr, int endTime, int xTwo, int yTwo);
	void deleteSlider();
};
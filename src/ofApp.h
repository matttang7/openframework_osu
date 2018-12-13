#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "circle.h"
#include "slider.h"
#include "spinner.h"
#include <json.hpp>
#include <iostream>
#include <fstream>
using namespace circleSpace;
class ofApp : public ofBaseApp {

public:
	//Keeps track of time elapsed
	float timer;
	static const int half = 2;
	static const int lifeTotal = 10000;
	static const int positionLifeWidth = 500;
	static const int positionLifeHeight = 750;
	static const int approachTime = 1000;
	static const int marginAfter = 100;
	static const int approachCircleDivider = 20;
	static const int approachSliderDivider = 21;
	static const int positionTextX = 8;
	static const int positionTextY = 15;
	static const int circleMissLoss = 800;
	static const int cursorError = 5;
	static const int sliderLifeGain = 30;
	static const int circleHalfLifeGain = 400;
	static const int circleFullLifeGain = 600;
	static const int lifeDrain = 100;
	vector<circle> allCircles;
	vector<slider> allSliders;
	vector<spinner> allSpinners;
	int radius;
	int life;
	int totalScore;
	void setup();
	//Checks for z or x for calling mouseDragged
	void update();
	void draw();
	/*Takes in z or x for mouse clicks*/
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	/*Checks if mouse if being dragged over a slider or spinning
	Scores the points if inside a slider or spinning spinner
	*/
	void mouseDragged(int x, int y, int button);
	/*Checks if mouse clicked on a circle and gets the time error
	Then scores the click based on that error
	*/
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	float startTime;
	ofxPanel gui;
	ofTrueTypeFont text;
	ofTrueTypeFont textCombo;

	//Different sound players are for loading/playing different songs
	ofSoundPlayer unravel;
	ofSoundPlayer shelter;
	ofSoundPlayer jojo;
	ofSoundPlayer killlakill;
	ofSoundPlayer fate;
	ofImage background;
	int combo;
	int toBeAssigned;
	double accuracy;
	bool accuracyDivided;
	float angle,spinnerRadius = 350;
	glm::vec2  prevMouse, currentMouse, center;
	int revolutions;
};

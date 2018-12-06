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
	float timer;
	vector<circle> allCircles;
	vector<slider> allSliders;
	vector<spinner> allSpinners;
	//ofPoint circleButton;
	bool bCircleButton;
	ofPoint timedButton;
	ofPoint getTimeButton;
	bool clickedTimedButton;
	int radius;
	int life;
	int totalScore;
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	float startTime;
	bool timerEnd;
	ofxPanel gui;
	ofParameter<float> endTime;
	ofTrueTypeFont text;
	ofTrueTypeFont textCombo;
	ofSoundPlayer unravel;
	ofSoundPlayer shelter;
	ofImage background;
	int combo;
	int toBeAssigned;
	float angle,spinnerRadius = 350;
	glm::vec2  prevMouse, currentMouse, center;
	int revolutions;
};

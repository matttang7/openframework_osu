#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "circle.h"
#include "slider.h"
#include "json/json.h"
#include "json/include/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
class ofApp : public ofBaseApp {

public:
	float timer;
	vector<circle> allCircles;
	//ofPoint circleButton;
	bool bCircleButton;
	ofPoint timedButton;
	ofPoint getTimeButton;
	bool clickedTimedButton;
	int radius;
	int life;
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
	ofSoundPlayer unravel;
	ofSoundPlayer shelter;
	ofImage background;
	int combo;
};

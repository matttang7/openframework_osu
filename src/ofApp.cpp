#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	background.load("shelterBackground.jpg");
	text.loadFont("bebas.ttf", 50);
	gui.setup();
	gui.add(endTime.set("endTime", 2000.0, 0.0, 6000.0));
	timerEnd = false;
	startTime = ofGetElapsedTimeMillis();
	//circleButton.set(100, 100);
	radius = 50;
	life = 10000;
	combo = 0;
	bCircleButton = false;
	clickedTimedButton = false;
	shelter.load("shelter.mp3");
	shelter.play();
	allCircles.push_back(circle(3562, 600, 300, radius));
	allCircles.push_back(circle(4138, 200, 200, radius));
	allCircles.push_back(circle(4309, 500, 500, radius));
	allCircles.push_back(circle(4800, 700, 700, radius));
	allCircles.push_back(circle(6229, 600, 600, radius));
	allCircles.push_back(circle(6784, 200, 200, radius));
	allCircles.push_back(circle(6976, 500, 500, radius));
	allCircles.push_back(circle(7424, 700, 700, radius));
	allCircles.push_back(circle(8896, 400, 200, radius));
	allCircles.push_back(circle(9514, 400, 600, radius));
	allCircles.push_back(circle(10240, 200, 600, radius));
	allCircles.push_back(circle(10880, 600, 400, radius));
	allCircles.push_back(circle(11221, 100, 500, radius));
	allCircles.push_back(circle(11626, 300, 500, radius));
	allCircles.push_back(circle(14357, 550, 450, radius));
	allCircles.push_back(circle(14954, 400, 300, radius));
	allCircles.push_back(circle(15125, 350, 550, radius));
	allCircles.push_back(circle(15552, 500, 400, radius));
	allCircles.push_back(circle(16960, 300, 250, radius));
	allCircles.push_back(circle(17557, 500, 400, radius));
	allCircles.push_back(circle(17749, 700, 700, radius));
	allCircles.push_back(circle(18133, 750, 200, radius));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (bCircleButton) {
		//do something
	}
	else {
		//or do sth else
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	gui.draw();
	float barWidth = 600;
	timer = ofGetElapsedTimeMillis() - startTime;
	ofSetColor(255, 0, 0);
	text.drawString(to_string(combo) + "x", 0,ofGetHeight());
	ofSetColor(255, 255, 255);
	if (timer >= endTime) {
		timerEnd = true;
	}
	float timerBar = ofMap(life - timer, 0.0, 10000, 0.0, 1.0, true);
	ofSetColor(255);
	ofDrawRectangle(ofGetWidth() / 2 - 100, ofGetHeight() - 750, barWidth * timerBar, 30);
	if (timer >= 0) {
		getTimeButton.set(300, 600);
		ofSetColor(255, 0, 0);
		ofDrawCircle(getTimeButton, radius);
		ofSetColor(255, 255, 255);
	}
	//if (bCircleButton)
	//	ofSetColor(ofColor::sandyBrown);
	//else
	//	ofSetColor(ofColor::white);
	//ofDrawCircle(circleButton, radius);
	for (int i = 0; i < allCircles.size(); i++) {
		if (timer >= allCircles[i].milisecondTime - 1000 && timer <= allCircles[i].milisecondTime + 300) {
			ofSetColor(0, 0, 0);
			ofDrawCircle(allCircles[i].location, allCircles[i].radius);
			if (timer <= allCircles[i].milisecondTime) {
				ofNoFill();
				int outerRadius = allCircles[i].radius - ((timer - allCircles[i].milisecondTime) / 20);
				ofDrawCircle(allCircles[i].location, outerRadius);
			}
			ofSetColor(255, 255, 255);
			ofFill();
		}
		else if (timer >= allCircles[i].milisecondTime + 500 && !allCircles[i].clicked && !allCircles[i].deleted) {
			combo = 0;
			allCircles[i].deleteCircle();
		}
	}
	//ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	//ofBeginShape();
	//ofVertex(400, 135);
	//ofVertex(215, 135);
	//ofVertex(365, 25);
	//ofVertex(305, 200);
	//ofVertex(250, 25);
	//ofEndShape();
	ofPoint p1(400, 400);
	ofPoint p2(500, 300);
	ofPoint p3(600, 600);
	ofDrawCircle(p1, radius);
	ofDrawCircle(p3, radius);
	ofPolyline poly;
	poly.quadBezierTo(p1, p2, p3);
	ofSetLineWidth(600);
	poly.draw();
	/*ofPath path;
	for (int i = 0; i < poly.getVertices().size(); i++) {
		if (i == 0) {
			path.newSubPath();
			path.moveTo(poly.getVertices()[i]);
		}
		else {
			path.lineTo(poly.getVertices()[i]);
		}
	}
	path.close();
	path.simplify();
	path.draw();*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		timerEnd = false;
		startTime = ofGetElapsedTimeMillis();
		clickedTimedButton = false;
	}
	if (key == 'z') {
		mousePressed(ofGetMouseX(), ofGetMouseY(), 0);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){           

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	/*if (circleButton.distance(ofPoint(x, y)) < radius) {
		bCircleButton = !bCircleButton;
	}*/
	if (timedButton.distance(ofPoint(x, y)) < radius) {
		clickedTimedButton = !clickedTimedButton;
	}
	if (getTimeButton.distance(ofPoint(x, y)) < radius) {
		std::cout << shelter.getPositionMS() << std::endl;
	}
	for (int i = 0; i < allCircles.size(); i++) {
		if (allCircles[i].location.distance(ofPoint(x, y)) < allCircles[i].radius && !allCircles[i].clicked && timer >= allCircles[i].milisecondTime - 300 ) {
			std::cout << "clicked" << std::endl;
			std::cout<<allCircles[i].getTimeError(timer)<<std::endl;
			int score = allCircles[i].scoreClick(allCircles[i].getTimeError(timer));
			std::cout<< score <<std::endl;
			if (score > 0) {
				combo++;
				life += 800;
			}
			else {
				combo = 0;
			}
			allCircles[i].clicked = true;
			allCircles[i].deleteCircle();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

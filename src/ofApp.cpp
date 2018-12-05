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
	totalScore = 0;
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
	std::ifstream i("map.json");
	json j;
	i >> j;
	allSliders.push_back(slider(20000, 400, 400, 500, 300, 22000, 600, 600));
	allSliders.push_back(slider(25000, 300, 300, 400, 400, 27000, 500, 500));
	allSpinners.push_back(spinner(10000, 15000));
	center = { ofGetWidth() / 2, ofGetHeight() / 2 };
	ofSetCircleResolution(100);
	angle = 0;
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
	ofSetLineWidth(600);
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

	for (int i = 0; i < allSliders.size(); i++) {
		ofPolyline poly;
		poly.quadBezierTo(allSliders[i].pointOne, allSliders[i].control, allSliders[i].pointTwo);
		if (timer >= allSliders[i].startTime - 1000 && timer <= allSliders[i].endTime) {
			ofSetColor(0, 0, 0);
			ofDrawCircle(allSliders[i].pointOne, radius);
			ofDrawCircle(allSliders[i].pointTwo, radius);
			poly.draw();
			if (timer <= allSliders[i].startTime) {
				ofNoFill();
				int outerRadius = radius - ((timer - allSliders[i].startTime) / 20);
				ofDrawCircle(allSliders[i].pointOne, outerRadius);
			}
			if (timer >= allSliders[i].startTime) {
				ofDrawCircle(poly.getPointAtIndexInterpolated(((timer - allSliders[i].startTime) / allSliders[i].totalTime) * 21), radius);
			}
			ofSetColor(255, 255, 255);
			ofFill();
		}
	}


	for (int i = 0; i < allSpinners.size(); i++) {
		if (timer >= allSpinners[i].startTime && timer <= allSpinners[i].endTime) {
			ofPushMatrix();
			ofTranslate(center);
			ofRotateRad(-angle);

			ofFill();
			ofSetColor(220);
			ofDrawCircle(0, 0, spinnerRadius);

			ofSetLineWidth(3);
			ofNoFill();
			ofSetColor(150);
			ofDrawCircle(0, 0, spinnerRadius);
			ofDrawLine(0, 0, spinnerRadius, 0);


			ofPopMatrix();
			ofFill();

			stringstream s;
			s << "Angle: " << angle;

			s << "\nmouse - c: " << (currentMouse - center);
			s << "\np mouse - c: " << (prevMouse - center);
			s << "\ncurrent mouse: " << currentMouse;
			s << "\np mouse: " << prevMouse;
			s << "\nRevolutions: " << angle / glm::two_pi<float>();

			ofDrawBitmapStringHighlight(s.str(), 20, 20);
		}
	}
	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		timerEnd = false;
		startTime = ofGetElapsedTimeMillis();
		clickedTimedButton = false;
	}
	if (key == 'z' || key == 'x') {
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
	for (int i = 0; i < allSliders.size(); i++) {
		if (timer >= allSliders[i].startTime) {
			ofPoint p = allSliders[i].path.getPointAtIndexInterpolated(((timer - allSliders[i].startTime) / allSliders[i].totalTime) * allSliders[i].path.size());
			if (p.distance(ofPoint(x, y)) < radius) {
				if (allSliders[i].totalPoints > 0) {
					allSliders[i].totalPoints--;
					totalScore += combo;
				}
			}
		}
	}

	for (int i = 0; i < allSpinners.size(); i++) {
		if (!allSpinners[i].scored && timer >= allSpinners[i].startTime && timer <= allSpinners[i].endTime) {
			if (ofDist(x, y, center.x, center.y) <= spinnerRadius) {
				currentMouse = { x,y };
				if (currentMouse != prevMouse) {
					//		b = glm::acos(glm::dot(glm::normalize(m - c), glm::normalize(prevMouse - c)));
					auto d = currentMouse - center;
					auto pd = prevMouse - center;
					float diff = ofAngleDifferenceRadians(atan2(d.y, d.x), atan2(pd.y, pd.x));
					if (!isnan(diff)) {
						angle += diff;
					}
					allSpinners[i].revolutions = angle / glm::two_pi<float>();
				}
				prevMouse = currentMouse;
			}
		}
		else if (!allSpinners[i].scored && timer >= allSpinners[i].endTime) {
			if (combo == 0) {
				totalScore += allSpinners[i].scoreSpin();
			}
			else {
				totalScore += allSpinners[i].scoreSpin() * combo;
			}
			combo++;
			allSpinners[i].scored = true;
		}
	}
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
			int score = allCircles[i].scoreClick(allCircles[i].getTimeError(timer));
			std::cout << score << std::endl;
			if (combo == 0) {
				totalScore += score;
			}
			else {
				totalScore += (score * combo);
			}
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
	std::cout << totalScore << std::endl;

	prevMouse = { x,y };
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

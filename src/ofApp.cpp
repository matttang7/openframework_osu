#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	//background.load("shelterBackground.jpg");
	//background.load("giorno.jpg");
	//background.load("killlakillbackground.jpg");
	background.load("fateBackground.jpg");
	text.loadFont("bebas.ttf", 25);
	textCombo.loadFont("bebas.ttf", 50);
	startTime = ofGetElapsedTimeMillis();
	radius = 50;
	life = 10000;
	combo = 0;
	totalScore = 0;
	//shelter.load("shelter.mp3");
	//shelter.play();
	//jojo.load("jojo.mp3");
	//jojo.play();
	//killlakill.load("killlakill.mp3");
	//killlakill.play();
	fate.load("fate.mp3");
	fate.play();
	std::ifstream i("fate.json");
	json j;
	i >> j;
	double d = j["circles"][1]["time"];
	for (int i = 0; i < j["circles"].size(); i++) {
		allCircles.push_back(circle(j["circles"][i]["time"], j["circles"][i]["x"], j["circles"][i]["y"], radius));
	}
	for (int i = 0; i < j["sliders"].size(); i++) {
		allSliders.push_back(slider(j["sliders"][i]["startTime"], j["sliders"][i]["startX"], j["sliders"][i]["startY"], 
			j["sliders"][i]["controlX"], j["sliders"][i]["controlY"], j["sliders"][i]["endTime"], j["sliders"][i]["endX"], j["sliders"][i]["endY"]));
	}
	for (int i = 0; i < j["spinners"].size(); i++) {
		allSpinners.push_back(spinner(j["spinners"][i]["start"], j["spinners"][i]["end"]));
	}

	center = { ofGetWidth() /half, ofGetHeight() / half };
	ofSetCircleResolution(100);
	angle = 0;
	toBeAssigned = 1;
	accuracy = 0;
	accuracyDivided = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (life <= timer/half + lifeTotal) {
		//ofExit();
	}
	if (life > timer/half + lifeTotal) {
		life -= lifeDrain;
	}
	if(ofGetKeyPressed('z') || ofGetKeyPressed('x')) {
		mouseDragged(ofGetMouseX(), ofGetMouseY(), 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	float barWidth = 600;
	timer = ofGetElapsedTimeMillis() - startTime;
	ofSetColor(ofColor::aqua);
	textCombo.drawString(to_string(combo) + "x", 0,ofGetHeight());

	//Drawing the life bar of the player
	ofSetLineWidth(600);
	float timerBar = ofMap(life - timer/half, 0.0, lifeTotal, 0.0, 1.0, true);
	ofSetColor(ofColor::aqua);
	ofDrawRectangle(ofGetWidth() / half - positionLifeWidth, ofGetHeight() - positionLifeHeight, barWidth * timerBar, 30);

	// Draws the circles when the time to hit them is within the interval
	for (int i = 0; i < allCircles.size(); i++) {
		if (timer >= allCircles[i].milisecondTime - approachTime && timer <= allCircles[i].milisecondTime + marginAfter && !allCircles[i].clicked) {
			//Assigns numbers 1-9 to the circles
			if (!allCircles[i].assignedNum) {
				allCircles[i].displayNum = toBeAssigned;
				if (toBeAssigned < 9) {
					toBeAssigned++;
				}
				else {
					toBeAssigned = 1;
				}
				allCircles[i].assignedNum = true;
			}

			ofSetColor(ofColor::aqua);
			ofDrawCircle(allCircles[i].location, allCircles[i].radius);
			//Draws the approach circles to let player know when to hit the circle
			if (timer <= allCircles[i].milisecondTime) {
				ofNoFill();
				int outerRadius = allCircles[i].radius - ((timer - allCircles[i].milisecondTime) / approachCircleDivider);
				ofDrawCircle(allCircles[i].location, outerRadius);
			}
			ofSetColor(255, 255, 255);
			text.drawString(to_string(allCircles[i].displayNum), allCircles[i].xCoord - positionTextX, allCircles[i].yCoord + positionTextY);
			ofNoFill();
			ofSetColor(150);
			ofDrawCircle(allCircles[i].xCoord, allCircles[i].yCoord, radius);
			ofFill();
		}
		else if (timer >= allCircles[i].milisecondTime + marginAfter && !allCircles[i].clicked && !allCircles[i].deleted) {
			combo = 0;
			allCircles[i].deleteCircle();
			life -= circleMissLoss;
		}
	}

	//Draws the sliders when it is time to hit the sliders
	for (int i = 0; i < allSliders.size(); i++) {
		ofPolyline poly;
		poly.quadBezierTo(allSliders[i].pointOne, allSliders[i].control, allSliders[i].pointTwo);
		if (timer >= allSliders[i].startTime - approachTime && timer <= allSliders[i].endTime) {
			if (!allSliders[i].assignedNum) {
				allSliders[i].displayNum = toBeAssigned;
				if (toBeAssigned < 9) {
					toBeAssigned++;
				}
				else {
					toBeAssigned = 1;
				}
				allSliders[i].assignedNum = true;
			}
			ofSetColor(ofColor::aqua);
			ofDrawCircle(allSliders[i].pointOne, radius);
			ofDrawCircle(allSliders[i].pointTwo, radius);
			ofNoFill();
			ofSetColor(150);
			ofDrawCircle(allSliders[i].pointOne, radius);
			ofDrawCircle(allSliders[i].pointTwo, radius);
			ofSetColor(ofColor::aqua);
			ofFill();
			poly.draw();

			//Draws the approach circle for the slider
			if (timer <= allSliders[i].startTime) {
				ofNoFill();
				int outerRadius = radius - ((timer - allSliders[i].startTime) / approachCircleDivider);
				ofDrawCircle(allSliders[i].pointOne, outerRadius);
			}
			if (timer >= allSliders[i].startTime) {
				ofDrawCircle(poly.getPointAtIndexInterpolated(((timer - allSliders[i].startTime) / allSliders[i].totalTime) * approachSliderDivider), radius + cursorError);
			}
			ofSetColor(255, 255, 255);
			text.drawString(to_string(allSliders[i].displayNum), allSliders[i].pointOne.x - positionTextX, allSliders[i].pointOne.y + positionTextY);
			ofFill();
		}
	}

	//Draws the spinners when the time to spin is reached
	for (int i = 0; i < allSpinners.size(); i++) {
		if (timer >= allSpinners[i].startTime && timer <= allSpinners[i].endTime) {
			ofPushMatrix();
			ofTranslate(center);
			ofRotateRad(-angle);

			ofFill();
			ofSetColor(ofColor::blueSteel);
			ofDrawCircle(0, 0, spinnerRadius);

			ofSetLineWidth(3);
			ofNoFill();
			ofSetColor(150);
			ofDrawCircle(0, 0, spinnerRadius);
			ofDrawLine(0, 0, spinnerRadius, 0);


			ofPopMatrix();
			ofFill();
		}
	}
	ofSetColor(255, 255, 255);

	//Draws end screen when it reaches the end of the song
	if (!shelter.isPlaying() && !killlakill.isPlaying() && !fate.isPlaying()) {
		ofSetColor(ofColor::aqua);
		if (!accuracyDivided) {
			accuracy = accuracy / static_cast<double>(allCircles.size());
			accuracyDivided = true;
		}
		text.drawString("Final Score: " + to_string(totalScore) + "\n Accuracy: " + to_string(accuracy), ofGetWidth() / half, ofGetHeight() / half);
		ofSetColor(255, 255, 255);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
	//Checks for mouse in the circle of the slider
	for (int i = 0; i < allSliders.size(); i++) {
		if (timer >= allSliders[i].startTime && timer < allSliders[i].endTime) {
			//Moves the slider circle along the path
			ofPoint p = allSliders[i].path.getPointAtIndexInterpolated(((timer - allSliders[i].startTime) / allSliders[i].totalTime) * allSliders[i].path.size());
			if (p.distance(ofPoint(x, y)) < radius + cursorError) {
				if (life < timer/half + lifeTotal) {
					life += sliderLifeGain;
				}
				if (allSliders[i].totalPoints > 0) {
					allSliders[i].totalPoints--;
					totalScore += combo;
				}
				if (allSliders[i].pointCounter < 25) {
					allSliders[i].pointCounter++;
				}
				else {
					allSliders[i].pointCounter = 0;
					combo++;
				}
			}
			else{
				combo = 0;
			}
		}
	}

	//Counts spins for each spinner
	for (int i = 0; i < allSpinners.size(); i++) {
		if (!allSpinners[i].scored && timer >= allSpinners[i].startTime && timer <= allSpinners[i].endTime) {
			if (ofDist(x, y, center.x, center.y) <= spinnerRadius+50) {
				currentMouse = { x,y };
				if (currentMouse != prevMouse) {
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
		//Adds to life for spinner
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
		if (abs(allSpinners[i].revolutions) >= allSpinners[i].revCounter) {
			if (life < timer/half + lifeTotal) {
				life += circleHalfLifeGain;
			}
			allSpinners[i].revCounter++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//Checks for circle being clicked when time is right
	for (int i = allCircles.size()-1; i >= 0; i--) {
		if (allCircles[i].location.distance(ofPoint(x, y)) < allCircles[i].radius && !allCircles[i].clicked
			&& timer >= allCircles[i].milisecondTime - 300 && allCircles[i].isClickable(allCircles,i)) {
			std::cout << "clicked" << std::endl;
			int score = allCircles[i].scoreClick(allCircles[i].getTimeError(timer));
			std::cout << score << std::endl;
			//Changes combo/score based on the score
			if (combo == 0) {
				totalScore += score;
			}
			else {
				totalScore += (score * combo);
			}
			if (score == 100) {
				combo++;
				accuracy++;
				if (life < timer/half + lifeTotal) {
					life += circleFullLifeGain;
				}
			}
			else if (score == 50) {
				combo++;
				accuracy += 0.5;
				if (life < timer/half + lifeTotal) {
					life += circleHalfLifeGain;
				}
			}
			else {
				combo = 0;
				life -= circleMissLoss;
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

#pragma once
class spinner {
public:
	int startTime;
	int endTime;
	//Number of times spinner is spun
	int revolutions;
	//Takes the absolute value of revolutions for scoring
	int revCounter;
	bool scored;
	//Score for each revolution
	static const int scoreMultiplier = 100;
	//Constructs spinner with start and end time
	spinner(int start, int end);
	//Gives score for each 
	int scoreSpin();
};
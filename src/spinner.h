#pragma once
class spinner {
public:
	int startTime;
	int endTime;
	int revolutions;
	int revCounter;
	bool scored;
	spinner(int start, int end);
	int scoreSpin();
};
#pragma once
class spinner {
public:
	int startTime;
	int endTime;
	int revolutions;
	bool scored;
	spinner(int start, int end);
	int scoreSpin();
};
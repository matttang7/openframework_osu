#include "slider.h"

slider::slider(int start, int xOne, int yOne, int xCtr, int yCtr, int end, int xTwo, int yTwo)
{
	startTime = start;
	xCoordOne = xOne;
	yCoordOne = yOne;
	xCoordCtr = xCtr;
	yCoordCtr = yCtr;
	xCoordTwo = xTwo;
	yCoordTwo = yTwo;
	endTime = end;
	totalTime = end - start;
	pointOne.set(xOne, yOne);
	control.set(xCtr, yCtr);
	pointTwo.set(xTwo, yTwo);
	path.quadBezierTo(pointOne, control, pointTwo);
	totalPoints = (endTime - startTime);
	pointCounter = 0;
	deleted = false;
	displayNum = 0;
	assignedNum = false;
}

void slider::deleteSlider()
{
	pointOne.set(-300, -300);
	control.set(-300, -300);
	pointTwo.set(-300, -300);
	deleted = true;
}

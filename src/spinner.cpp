#include "spinner.h"

spinner::spinner(int start, int end)
{
	startTime = start;
	endTime = end;
	revolutions = 0;
	scored = false;
}

int spinner::scoreSpin()
{
	return 100 * revolutions;
}

#include "spinner.h"
#include <cmath>
spinner::spinner(int start, int end)
{
	startTime = start;
	endTime = end;
	revolutions = 0;
	revCounter = 0;
	scored = false;
}

int spinner::scoreSpin()
{
	return 100 * abs(revolutions);
}

/*
 * StepSorter.cpp
 *
 *  Created on: 18-01-2011
 *      Author: darek
 */

#include "StepSorter.h"

using namespace std;

StepSorter::StepSorter() {
}

StepSorter::~StepSorter() {
}

void StepSorter::median(Step::Iterator begin, Step::Iterator nth, Step::Iterator end, Comparator compare)
{
	--end;
	while (begin < end) {
		ParticleCoord x = *nth;
		Step::Iterator i(begin);
		Step::Iterator j(end);
		do {
			while (compare(*i, x))
				i++;
			while (compare(x, *j))
				j--;
			if (i <= j) {
				iter_swap(i, j);
				i++;
				j--;
			}
		} while (i <= j);
		if (j < nth)
			begin = i;
		if (nth < i)
			end = j;
	}
}

Step& StepSorter::sort(Step & step) {

	sort(step.begin(), step.end(), 0);

	return step;
}

inline int StepSorter::normalizeDepth(int depth) {
	return depth % Step::DIMENSION_NUMBER;
}

void StepSorter::sort(Step::Iterator left, Step::Iterator right, int depth) {
	if (right - left < 2)
		return;

	depth = normalizeDepth(depth);

	Step::Iterator middle = left + (right - left) / 2;
	median(left, middle, right, Comparator(depth));

	sort(left, middle, depth + 1);
	sort(middle, right, depth + 1);
}

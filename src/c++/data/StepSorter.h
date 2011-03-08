/*
 * StepSorter.h
 *
 *  Created on: 18-01-2011
 *      Author: Dariusz Galysa
 */

#ifndef STEPSORTER_H_
#define STEPSORTER_H_

#include "Step.h"

class StepSorter {
private:

	class Comparator {
	private:
		int _dimensionNumber;

	public:
		Comparator(int dimensionNumber) :
			_dimensionNumber(dimensionNumber) {
		}

		template<typename P>
		bool operator()(const P& a, const P& b) const {
			return a[_dimensionNumber] < b[_dimensionNumber];
		}
	};

	void median(Step::Iterator begin, Step::Iterator nth, Step::Iterator end, Comparator compare);
	void sort(Step::Iterator left, Step::Iterator right, int depth);
	int normalizeDepth(int depth);

    friend class SorterTest;
public:
	StepSorter();
	virtual ~StepSorter();
	Step& sort(Step& step);
};

#endif /* STEPSORTER_H_ */

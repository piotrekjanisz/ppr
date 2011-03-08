/*
 * Step.h
 *
 *  Created on: 10-01-2011
 *      Author: Dariusz Galysa
 */

#ifndef STEP_H_
#define STEP_H_

#include "H5Cpp.h"
#include <map>
#include <string>
#include <cstring>
#include <boost/iterator/iterator_facade.hpp>

const int DIM_NUMBER = 3;

class ParticleCoord {
private:
	float _coordinates[DIM_NUMBER];

public:
	ParticleCoord(float* coordinates) {
		memcpy(_coordinates, coordinates, sizeof(float) * DIM_NUMBER);
	}

	float operator[](int index) const {
		return _coordinates[index];
	}
};

class Step {
private:
	std::string _name;
	int _particlesNumber;
	float* _coordinates;
	std::map<std::string, float*> _additionalData;

	void copyData(const Step& other);
	void deleteData();

public:
	static const int DIMENSION_NUMBER = DIM_NUMBER;
	static const int COORDINATES_NUMBER = DIMENSION_NUMBER + 1;

	enum Dimensions {
		X = 0, Y = 1, Z = 2
	};

	Step();
	Step(std::string name, int particlesNumber, float* coordinates);
	Step(const Step& other);
	virtual ~Step();

	Step& operator=(const Step& other);

	std::map<std::string, float*>& getAdditionalData() { return _additionalData; }
	const std::map<std::string, float*>& getAdditionalData() const { return _additionalData; }

	float *getCoordinates() const;
	std::string getName() const;
	int getParticlesNumber() const;
	void setCoordinates(float *coordinates);
	void setName(std::string name);
	void setParticlesNumber(int pointsNumber);
	void setAdditionalData(std::map<std::string, float*> additionalData);
	int getNumberOfAdditionalParams() const;

	class Iterator: public boost::iterator_facade<Iterator, ParticleCoord,
			boost::random_access_traversal_tag, ParticleCoord> {
	private:
		Step* step;
		int index;
		Iterator(Step* step, int index)
			: step(step), index(index) {}

		friend class boost::iterator_core_access;
		friend class Step;
		friend void iter_swap(Step::Iterator& it1, Step::Iterator& it2);

		ParticleCoord dereference() const
		{
			float* coordinates = step->_coordinates;
			return ParticleCoord(&coordinates[COORDINATES_NUMBER * index]);
		}
		bool equal(const Iterator& other) const
		{
			return this->index == other.index;
		}

		void increment() { index++; }
		void decrement() { index--; }

		void advance(int n) { index += n; }
		int distance_to(const Iterator& other) const { return other.index - this->index; }

	public:
		virtual ~Iterator() {}

	};

	Iterator begin();
	Iterator end();
	Iterator at(int index);

	friend std::ostream& operator<<(std::ostream& stream, const Step& step);
	friend void iter_swap(Step::Iterator& it1, Step::Iterator& it2);
	friend class Iterator;
};

#endif /* STEP_H_ */

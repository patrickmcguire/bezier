/*
 * Curve.h
 *
 *  Created on: Nov 16, 2011
 *      Author: pjm2119
 */

#ifndef CURVE_H_
#define CURVE_H_

/* Worry about surfaces at a later point */
typedef struct Curve {
	int vDegree, uDegree;
	float transform[4][4];
	float ** points;
	~Curve();
} Curve;

Curve::~Curve() {
	delete[] points;
}

#endif /* CURVE_H_ */

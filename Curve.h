/*
 * Curve.h
 *
 *  Created on: Nov 16, 2011
 *      Author: pjm2119
 */

#ifndef CURVE_H_
#define CURVE_H_

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MIN_PRECISION 1
#define MAX_PRECISION 5

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/* Worry about surfaces at a later point */
class Curve {
private:
	int uDegree, vDegree;
	float * transform;
	float ** points;
	int precision;
	float bernstein(int i, int n, float t);
	void drawCurve();
	void drawSurface();
	int factorial(int n);
public:
	Curve(int uDegree, int vDegree, float * transform, float ** points, int precision);
	void draw();
	void setPrecision(int precision);
	~Curve();
};

#endif /* CURVE_H_ */

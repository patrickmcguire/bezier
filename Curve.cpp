/*
 * Curve.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: pjm
 */

#include "Curve.h"
#include <stddef.h>
#include <math.h>
#include <iostream>

Curve::Curve(int uDegree, int vDegree, float * transform, float ** points, int precision)
{
	this->uDegree = uDegree;
	this->vDegree = vDegree;
	this->transform = transform;
	this->points = points;
	this->precision = precision;
}

void Curve::draw()
{
	if(0 == vDegree) {
		drawCurve();
	} else {
		drawSurface();
	}
}

void Curve::drawCurve()
{
	glPushMatrix();
	glMultMatrixf(transform);
	int numPoints = pow(3,precision-1);
	glBegin(GL_LINES);
		float * lastV = NULL;
		float * v = NULL;
		for(int sample = 0; sample <= numPoints; sample++) {
			float pointsCopy[uDegree + 1][3];
			float t = (float) sample / (float) numPoints;
			if((NULL == lastV) && (NULL == v)) {
				v = new float[3];
			} else {
				if(NULL != lastV) {
					delete[] lastV;
				}
				lastV = v;
				v = new float[3];
			}
			for(int j = 0; j < uDegree + 1; j++) {
				pointsCopy[j][0] = points[j][0];
				pointsCopy[j][1] = points[j][1];
				pointsCopy[j][2] = points[j][2];
			}
			for(int i = uDegree - 1; i >= 0; i--) { //we refer to every i from i-1, so one less than limit
				for(int j = 0; j <= i; j++) {
					pointsCopy[j][0] = (1-t) * pointsCopy[j][0] + t * pointsCopy[j+1][0];
					pointsCopy[j][1] = (1-t) * pointsCopy[j][1] + t * pointsCopy[j+1][1];
					pointsCopy[j][2] = (1-t) * pointsCopy[j][2] + t * pointsCopy[j+1][2];
				}
			}
			v[0] = pointsCopy[0][0];
			v[1] = pointsCopy[0][1];
			v[2] = pointsCopy[0][2];
			if(NULL != lastV) {
				glVertex3fv(lastV);
				glVertex3fv(v);
			}
		}
		if(NULL != v) {
			delete[] v;
		}
		if(NULL != lastV) {
			delete[] lastV;
		}
	glEnd();
	glPopMatrix();
}

void Curve::drawSurface()
{
	/*
	 * 			for(int row = 0; row <= vDegree; row++) {
				std::vector<std::string> strs;
				boost::split(strs, line, boost::is_space());
				for(int i = 0; i < 3*(uDegree+1); i++) {
					string d = strs.at(i);
					sscanf(d.c_str(),"%f",&(coordinates[i][index]));
				}
			}
	 *
	 */

	/* First we get the triangle vertices, then we draw the mesh */
	float *** realPoints = new float**[vDegree+1];
	for(int v = vDegree; v >= 0; v--) {
		realPoints[v] = new float*[uDegree+1];
		for(int u = 0; u <= uDegree; u++) {
			float * coord = new float[3];
			coord[0] = points[v][3*u];
			coord[1] = points[v][3*u+1];
			coord[2] = points[v][3*u+2];
			realPoints[v][u] = coord;
		}
	}

	int numSamples = pow(3,precision-1) * vDegree;
	float *** matrix = new float**[numSamples + 1];
	for(int i = 0; i <= numSamples; i++) {
		matrix[i] = new float*[numSamples + 1];
	}
	for(int vIndex = 0; vIndex <= numSamples; vIndex++) {
		for(int uIndex = 0; uIndex <= numSamples; uIndex++) {
			float * coordinates = new float[3];
			coordinates[0] = 0;
			coordinates[1] = 0;
			coordinates[2] = 0;
			for(int i = 0; i < vDegree+1; i++) {
				for(int j = 0; j < uDegree+1; j++) {
					float v = (float) vIndex / (float) numSamples;
					float u = (float) uIndex / (float) numSamples;
					float * b_ij = realPoints[i][j];
					float B_i = bernstein(i, vDegree, v);
					float B_j = bernstein(j, uDegree, u);
					float c = B_i + B_j;
					coordinates[0] += c * b_ij[0];
					coordinates[1] += c * b_ij[1];
					coordinates[2] += c * b_ij[2];
				}
			}
			matrix[vIndex][uIndex] = coordinates;
		}
	}

	glPushMatrix();
	glMultMatrixf(transform);
		/* Now we draw the mesh from the sampled points */
		bool br = false;
		float black[] = {0.0, 0.0, 0.0};
		float red[] = {1.0, 0.0, 0.0};
		for(int v = 0; v < numSamples; v++) {
			glBegin(GL_TRIANGLE_STRIP);
			for(int u = 0; u <= numSamples; u++) {
				float * p1 = matrix[v][u];
				float * p2 = matrix[v+1][u];
				if(br) {
					glColor3fv(black);
					br = false;
				} else {
					glColor3fv(red);
					br = true;
				}
				glVertex3fv(p1);
				glVertex3fv(p2);
			}
			glEnd();
		}
	glPopMatrix();

	for(int i = 0; i <= numSamples; i++) {
		for(int j = 0; j <= numSamples; j++) {
			delete[] matrix[i][j];
		}
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Curve::setPrecision(int precision)
{
	this->precision = precision;
}

int Curve::factorial(int n)
{
	int r = 1;
	for(int i = n; i > 0; i--) {
		r *= i;
	}
	return r;
}

/* n > i */
float Curve::bernstein(int i, int n, float t)
{
	float base = (float) factorial(n) / (float) (factorial(i) * factorial(n - i));
	base *= powf(t,i);
	base *= powf(1-t,n-i);
	return base;
}

Curve::~Curve() {
	delete[] points;
}





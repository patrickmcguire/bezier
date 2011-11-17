/*
 * CurveFile.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: pjm2119
 */

#include "Curve.h"
#include <stddef.h>
#include <fstream>
#include <boost/algorithm/string.hpp>

#define STREAM_SIZE 256
using namespace std;

static std::vector<Curve *> * readFile(char * filename)
{
	ifstream input(filename);
	char line[STREAM_SIZE];
	int numCurves;
	if(input) {
		input.getline(line, STREAM_SIZE);
		sscanf(line, "%d", &numCurves);
	}
	Curve ** curves = new Curve * [numCurves];
	for(int i = 0; i < numCurves; i++) {
		curves[i] = NULL;
	}

	std::vector<Curve *> * rCurves = new std::vector<Curve *>(numCurves);
	for(int curveCounter = 0; curveCounter < numCurves; curveCounter++) {
		input.getline(line, STREAM_SIZE);
		Curve * c = new Curve;
		sscanf(line, "%d %d", &(c->uDegree), &(c->vDegree));
		curves[curveCounter] = c;

		for(int transformCounter = 0; transformCounter < 4; transformCounter++) {
			input.getline(line, STREAM_SIZE);
			sscanf(line, "%f %f %f %f", &(c->transform[transformCounter][0]),
										&(c->transform[transformCounter][1]),
										&(c->transform[transformCounter][2]),
										&(c->transform[transformCounter][3]));
		}

		if(c->vDegree == 0) {
			float ** coordinates = new float*[c->uDegree];
			for(int pointCounter = 0; pointCounter < (c->uDegree + 1); pointCounter++) {
				input.getline(line, STREAM_SIZE);
				float * coordinate = new float[3];
				sscanf(line, "%f %f %f", &(coordinate[0]),
										 &(coordinate[1]),
										 &(coordinate[2]));
				coordinates[pointCounter] = coordinate;
			}
			c->points = coordinates;
			rCurves->push_back(c);
		}
		else {
			float ** grid = new float*[c->uDegree];
			for(int i = 0; i < c->uDegree; i++) {
				grid[i] = new float[c->vDegree];
			}
			/* Just get them in here so we can start working */
			for(int i = 0; i < vDegree + 1; i++) {
				input.getline(line, STREAM_SIZE);
				std::vector<string> strs;
				boost::split(strs, line, boost::is_any_of(" "));
				for(int coord = 0; coord < c->uDegree + 1; coord++){
					for(int dim = 0; dim < 3; dim++) {
						int index = coord * 3 + dim;
						string d = strs.at(index);
						sscanf(d.c_str(),"%f",&(grid[i][index]));
					}
				}
			}
			c->points = grid;
			/*Now my floats are upside down. Don't you hate it when your floats are upside down? */
		}
	}
	return rCurves;
}


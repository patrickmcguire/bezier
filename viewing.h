/*
 * Views.h
 *
 *  Created on: Oct 14, 2011
 *      Author: pjm
 */

#include "util.h"

#ifndef VIEWS_H_
#define VIEWS_H_

void drawOrthoView( float angle, float x, float y, float z, int quadRow, int quadCol );
void drawSceneMatrix( int quadRow, int quadCol );
void drawScene();
void drawPerspView( int quadRow, int quadCol );

#endif /* VIEWS_H_ */

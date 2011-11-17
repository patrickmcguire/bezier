/*
 * Views.cpp
 *
 *  Created on: Oct 14, 2011
 *      Author: pjm
 */

#include "viewing.h"
#include "shapes.h"
#include "util.h"
#include <iostream>


void drawScene()
{
	glPushMatrix();
		drawFloor();
		drawTorus();
		drawSphere();
		drawBox_Teapot();
	glPopMatrix();
}

void drawOrthoView( float angle, float x, float y, float z, int quadRow, int quadCol)
{
	glPushMatrix();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			glRotatef( angle, x, y, z );
			drawSceneMatrix( quadRow, quadCol );
		glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
}

void drawSceneMatrix( int quadRow, int quadCol)
{
	int ww = glutGet( GLUT_WINDOW_WIDTH );
	int wh = glutGet( GLUT_WINDOW_HEIGHT );

	glViewport(quadCol * ww/2, (1 - quadRow) * wh/2,
				ww/2, wh/2);
	drawScene();
}

void drawPerspView( int quadRow, int quadCol )
{
	glPushMatrix();
		glFrustum(-5.0, 5.0, -5.0, 5.0, 3.5, 80.0);
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			gluLookAt( -15,15,10, 0,0,0, 0,1,0 );
			drawSceneMatrix( quadRow, quadCol );
		glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
}



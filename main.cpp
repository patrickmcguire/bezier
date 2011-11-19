/*
 * main.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: pjm
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <vector>
#include <cmath>

#include "Curve.h"
#include "CurveFile.h"

using namespace std;

#define PI 3.1415926535898

static int width = 600;
static int height = 600;
float camera_theta = PI/2.0;
float camera_phi = 0.0;
float camera_r = 30.0;
std::vector<Curve *> * curves;

void init()
{
  //glEnable(GL_SCISSOR_TEST);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_RESCALE_NORMAL);
  //GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
  //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glClearColor(0.4, 0.4, 0.4, 1.0);
  glShadeModel(GL_FLAT);
  glDisable(GL_COLOR_MATERIAL);
}


void draw(std::vector<Curve *> * c)
{
	for(unsigned int i = 0; i < c->size(); i++) {
		Curve * curve = c->at(i);
		curve->draw();
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*	// orthographic top
	if (width > height)
		glViewport((width-height)/4, height/2, height/2, height/2);
	else // h > w
		glViewport(0, height/2+(height-width)/4, width/2, width/2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, 0.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    	gluLookAt(0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    	draw(curves);
    glPopMatrix();

    // orthographic front
    if (width > height)
    	glViewport((width-height)/4, 0, height/2, height/2);
    else // h > w
    	glViewport(0, (height-width)/4, width/2, width/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    	gluLookAt(10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    	draw(curves);
    glPopMatrix();

    // orthographic side
    if (width > height)
    	glViewport(width/2+(width-height)/4, 0, height/2, height/2);
    else // h > w
    	glViewport(width/2, (height-width)/4, width/2, width/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, 0.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    	draw(curves);
    glPopMatrix();*/
/*
  // perspective camera
  if (width > height)
    glViewport(width/2+(width-height)/4, height/2, height/2, height/2);
  else // height > width
    glViewport(width/2, height/2+(height-width)/4, width/2, width/2);*/
	glViewport(1,1,width-2,height-2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    gluLookAt(camera_r*sin(camera_theta)*cos(camera_phi), camera_r*cos(camera_theta), camera_r*sin(camera_theta)*sin(camera_phi),
	      0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    draw(curves);
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

void setAllPrecisions(int precision)
{
	for(unsigned int i = 0; i < curves->size(); i++) {
		curves->at(i)->setPrecision(precision);
	}
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'z':
	  if(camera_r - 1.0/18.0 > 0)
		  camera_r -= 1.0;
	  break;
  case 'x':
	  camera_r += 1.0;
	  break;
  case '1':
	  setAllPrecisions(1);
	  break;
  case '2':
	  setAllPrecisions(2);
	  break;
  case '3':
	  setAllPrecisions(3);
	  break;
  case '4':
	  setAllPrecisions(4);
	  break;
  case '5':
	  setAllPrecisions(5);
	  break;
  }
  glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch(key) {
	case GLUT_KEY_LEFT:
		camera_theta -= PI/18.0;
		break;
	case GLUT_KEY_RIGHT:
		camera_theta += PI/18.0;
		break;
	case GLUT_KEY_UP:
		camera_phi += PI/18;
		break;
	case GLUT_KEY_DOWN:
		camera_phi -= PI/18;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	//don't forget to free
	curves = readFile(argv[1]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}



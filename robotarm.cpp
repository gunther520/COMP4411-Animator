// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include "mat.h"
#include "modelerglobals.h"
#include <math.h>
#include <chrono>
#include "particleSystem.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView
{
public:
	SampleModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) {
		time = 0;
	}

	virtual void draw();
	int time;
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char* label)
{
	return new SampleModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
	GLfloat matrix1[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix1);
	// change the matrix to a Mat4f
	//create a Mat4f object that is 0
	Mat4f mat1;
	mat1.getGLMatrix(matrix1);

	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();

	// draw the floor
	/*setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5,0,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();*/

	// draw the sample model
	time++;
	setAmbientColor(VAL(AMBIDIENT_R), VAL(AMBIDIENT_G), VAL(AMBIDIENT_B));
	setDiffuseColor(COLOR_GREEN);

	glPushMatrix();

	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS)); //slider 


	glPushMatrix();//draw a cylinder for model body
	drawCylinder(VAL(HEIGHT), 1, 1);

	glPushMatrix();//move to the top of the body
	glTranslated(0, 0, VAL(HEIGHT));
	glPushMatrix();//draw a cylinder for the neck
	glRotated(VAL(NECK), 0.0, 0.0, 1.0);
	drawCylinder(0.6, 0.5, 0.3);
	glTranslated(0, 0, 0.6);
	glPushMatrix();//draw a sphere for the head
	glRotated(VAL(HEAD), 1.0, 0.0, 0.0);
	drawSphere(0.7);

	glPushMatrix();//draw eyes on the head
	setDiffuseColor(0, 0, 0);
	glTranslated(0.3, 0.3, 0.5);
	drawSphere(0.1);
	glTranslated(-0.6, 0, 0);
	drawSphere(0.1);
	glPopMatrix();

	glPushMatrix();
	setDiffuseColor(1, 1, 0);
	glTranslated(0, 0, 1.1);
	drawTexCude3D(0.5, 0.6, 0.7);
	glTranslated(0, 0, 0.7);

	drawRhombus(0.5, 0.7);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPushMatrix();//move to upper left part of the body for drawing left arm

	setDiffuseColor(COLOR_RED);
	glTranslated(0.5, 0, VAL(HEIGHT) - 0.5);
	glRotated(90, 0.0, 1.0, 0.0);
	glRotated(VAL(Left_ARM1_X), 1.0, 0.0, 0.0);
	glRotated(VAL(Left_ARM1_Y), 0.0, 1.0, 0.0);
	glRotated(VAL(Left_ARM1_Z), 0.0, 0.0, 1.0);

	glPushMatrix();
	//draw a cylinder for left arm
	drawCylinder(0.7, 0.4, 0.4);
	drawCylinder(1.5, 0.3, 0.3);
	glTranslated(0, 0, 1.5);

	glRotated(VAL(LEFT_ARM2), 1.0, 0.0, 0.0);

	glPushMatrix();//draw a forearm
	drawSphere(0.3);
	drawCylinder(1.5, 0.3, 0.2);
	glTranslated(0, 0, 1.5);
	glPushMatrix();//draw a hand
	glTranslated(-0.5, -0.2, 0);
	drawBox(1, 0.5, 0.1);
	glTranslated(0.5, 0.2, 0);

	//TODO: draw weapon teeth
	glPushMatrix();//draw weapon1
	glTranslated(-0.4, -0.2, 0);
	drawBox(0.1, 0.5, 0.6);
	glPopMatrix();

	glPushMatrix();//draw weapon2
	glTranslated(0.3, -0.2, 0);
	drawBox(0.1, 0.5, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0.6);
	drawTorus(0.2, 0.5, 30, 30);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


	glPushMatrix();//move to upper right part of the body for drawing right arm

	setDiffuseColor(COLOR_BLUE);
	glTranslated(-0.5, 0, VAL(HEIGHT) - 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHT_ARM1_X), 1.0, 0.0, 0.0);
	glRotated(VAL(RIGHT_ARM1_Y), 0.0, 1.0, 0.0);
	glRotated(VAL(RIGHT_ARM1_Z), 0.0, 0.0, 1.0);
	glPushMatrix();
	//draw a cylinder for right arm
	drawCylinder(0.7, 0.4, 0.4);
	drawCylinder(1.5, 0.3, 0.3);
	glTranslated(0, 0, 1.5);
	glRotated(VAL(RIGHT_ARM2), 1.0, 0.0, 0.0);

	glPushMatrix();//draw a forearm
	drawSphere(0.3);
	drawCylinder(1.5, 0.3, 0.2);
	glTranslated(0, 0, 1.5);
	glPushMatrix();//draw a hand
	glTranslated(0, 0, 0.1);

	drawRhombus(0.8, 0.4);

	glPushMatrix();//particle
	//get the current transformation matrix
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	// change the matrix to a Mat4f
	//create a Mat4f object that is 0
	Mat4f mat;
	mat.getGLMatrix(matrix);

	//get the current local position of the particle

	//transform the position of the particle 
	Vec4f pos = Vec4f(0, 0, 0,1);

	//get the global position of the particle


	auto gopos = mat1.inverse() * mat * pos;

	//normalize the position and velocity
	Vec3f position = Vec3f(gopos[0], gopos[1], gopos[2]);
	Vec3f velocity = Vec3f(0, 0, 0);


	ModelerApplication::Instance()->GetParticleSystem()->spawnParticle(position, velocity, 10.0, 3.0f);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPushMatrix(); //move to the bottom of the body for drawing left leg
	setDiffuseColor(COLOR_CYAN);
	glTranslated(0.4, 0, 0);
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	//draw a cylinder for left leg
	glRotated(VAL(LEG_RUN), 1, 0, 0);
	drawSphere(0.35);
	drawCylinder(1.5, 0.35, 0.3);
	glTranslated(0, 0, 1.5);
	glPushMatrix();//draw the leg
	drawSphere(0.3);
	glRotated(abs(long(VAL(LEG_RUN))), 1, 0, 0);
	drawCylinder(1.0, 0.3, 0.35);
	glTranslated(0, 0, 1.0);
	glPushMatrix(); // draw the foot
	glTranslated(-0.4, -0.4, 0);
	drawBox(0.8, 1, 0.4);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //move to the bottom of the body for drawing right leg
	setDiffuseColor(COLOR_MAGENTA);
	glTranslated(-0.4, 0, 0);
	glRotated(180, 0, 1, 0);
	glPushMatrix();
	//draw a cylinder for right leg
	drawSphere(0.35);
	glRotated(-VAL(LEG_RUN), 1, 0, 0);
	drawCylinder(1.5, 0.35, 0.3);
	glTranslated(0, 0, 1.5);
	glPushMatrix();//draw 
	glRotated(abs(long(VAL(LEG_RUN))), 1, 0, 0);
	drawSphere(0.3);
	drawCylinder(1.0, 0.3, 0.35);
	glTranslated(0, 0, 1.0);
	glPushMatrix(); // draw the foot
	glTranslated(-0.4, -0.4, 0);
	drawBox(0.8, 1, 0.4);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPopMatrix();
	//draw a sphere for model head
	/*glPushMatrix();
	glTranslated(0, 0, VAL(HEIGHT)+0.5);
	drawSphere(0.7);
	glPopMatrix();*/


	//glPushMatrix();
	//glTranslated(-1.5, 0, -2);
	//glScaled(3, 1, 4);
	//drawBox(1,1,1);
	//glPopMatrix();

	//// draw cannon
	//glPushMatrix();
	//glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	//glRotated(-90, 1.0, 0.0, 0.0);
	//drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	//glTranslated(0.0, 0.0, VAL(HEIGHT));
	//drawCylinder(1, 1.0, 0.9);

	//glTranslated(0.0, 0.0, 0.5);
	//glRotated(90, 1.0, 0.0, 0.0);
	//drawCylinder(4, 0.1, 0.2);
	//glPopMatrix();

	glPopMatrix();
	endDraw();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEIGHT] = ModelerControl("Height", 2.5, 4.5, 0.1f, 4);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[NECK] = ModelerControl("Neck", -90, 90, 5, 0); //angle
	controls[HEAD] = ModelerControl("Head", -50, 10, 5, 0); //angle

	controls[Left_ARM1_X] = ModelerControl("Left Arm1 X", -55, 50, 5, 0); //angle
	controls[Left_ARM1_Y] = ModelerControl("Left Arm1 Y", -60, 60, 5, 0); //angle
	controls[Left_ARM1_Z] = ModelerControl("Left Arm1 Z", -45, 45, 5, 0); //angle
	controls[RIGHT_ARM1_X] = ModelerControl("Right Arm1 X", -55, 50, 5, 0); //angle
	controls[RIGHT_ARM1_Y] = ModelerControl("Right Arm1 Y", -60, 60, 5, 0); //angle
	controls[RIGHT_ARM1_Z] = ModelerControl("Right Arm1 Z", -45, 45, 5, 0); //angle
	controls[LEFT_ARM2] = ModelerControl("Left Arm2", -90, 10, 5, 0); //angle
	controls[RIGHT_ARM2] = ModelerControl("Right Arm2", -90, 10, 5, 0); //angle
	controls[LEG_RUN] = ModelerControl("Leg Run", -60, 45, 2, 0); //angle

	controls[AMBIDIENT_R] = ModelerControl("Ambidient R", 0, 1, 0.1, 0.5);
	controls[AMBIDIENT_G] = ModelerControl("Ambidient G", 0, 1, 0.1, 0.5);
	controls[AMBIDIENT_B] = ModelerControl("Ambidient B", 0, 1, 0.1, 0.5);



	ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);

	ParticleSystem* ps = new ParticleSystem();

	// do some more particle system setup


	ModelerApplication::Instance()->SetParticleSystem(ps);
	return ModelerApplication::Instance()->Run();
}

#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{
	XPOS, YPOS, ZPOS, HEIGHT, ROTATE, NECK, HEAD,
	Left_ARM1_X, Left_ARM1_Y, Left_ARM1_Z, RIGHT_ARM1_X, RIGHT_ARM1_Y, RIGHT_ARM1_Z,
	LEFT_ARM2, RIGHT_ARM2, LEG_RUN, AMBIDIENT_R, AMBIDIENT_G, AMBIDIENT_B,

	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f
#define COLOR_YELLOW	1.0f, 1.0f, 0.0f
#define COLOR_CYAN		0.0f, 1.0f, 1.0f
#define COLOR_MAGENTA	1.0f, 0.0f, 1.0f
#define COLOR_BLACK		0.0f, 0.0f, 0.0f
#define COLOR_WHITE		1.0f, 1.0f, 1.0f


// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif
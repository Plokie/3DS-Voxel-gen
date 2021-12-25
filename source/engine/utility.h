#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vectors.h"

float deadzone_min=0.097f;
float deadzone_max=1.0f;



void apply_scaled_deadzone(Vector2 *pos)
{
	if(
		(pos->x > 0) &
		(pos->x < deadzone_min)
		) pos->x=0.0f;
	if(
		(pos->x < 0) &
		(pos->x > -deadzone_min)
		) pos->x=0.0f;
	
	if(
		(pos->y > 0) &
		(pos->y < deadzone_min)
		) pos->y=0.0f;
	if(
		(pos->y < 0) &
		(pos->y > -deadzone_min)
		) pos->y=0.0f;

	// if(abs(pos->x)>deadzone_max) pos->x=deadzone_max;
	// if(abs(pos->y)>deadzone_max) pos->y=deadzone_max;
}

float clamp(float var, float min, float max)
{
	float returnVar;
	if(var<min) returnVar=min;
	else if(var>max) returnVar=max;
	else returnVar=var;

	return returnVar;
}

int floorToInt(float a)
{
	return (int)floorf(a);
}

// static const float pow_int(int a, int b)
// {
// 	return (int)pow((float)a,(float)b);
// }

#endif
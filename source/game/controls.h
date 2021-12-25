#ifndef CONTROLS_H
#define CONTROLS_H

#include <3ds.h>
#include "..\engine\vectors.h"
#include "..\game\chunk.h"
#include "..\game\lightsystem.h"

#define M_PI		3.14159265358979323846 //To get intellisense to shut up

Vector2 scaled_circlePos(circlePosition *pos)
{
	Vector2 newVec;
	newVec.x=(float)pos->dx/154.0f;
	newVec.y=(float)pos->dy/154.0f;
	return newVec;
}

void updateControls(Transform *camera)
{
    u32 kHeld = hidKeysHeld();
	//hidKeysUp returns information about which buttons have been just released
	//u32 kUp = hidKeysUp();
	circlePosition pos;
	hidCircleRead(&pos);
	Vector2 sPos = scaled_circlePos(&pos);
	//printf("\x1b[2;2HUnscaled circle pos: %i, %i ", pos.dx, pos.dy);
	printf("\x1b[2;2HCircle pos: %f, %f ", sPos.x, sPos.y);
	apply_scaled_deadzone(&sPos);


	float sensitivity=0.05f;
    float movementSpeedHorizontal=0.1f;
    float movementSpeedVertical=0.1f;

	camera->rotation.x-=sPos.y*sensitivity;
	camera->rotation.y+=sPos.x*sensitivity;

	camera->rotation.x=clamp(camera->rotation.x, C3D_AngleFromDegrees(-90.0f), C3D_AngleFromDegrees(90.0f));

	
	
	if(kHeld & KEY_X)
	{
		camera->position.z+=cos(camera->rotation.y)*movementSpeedHorizontal;
		camera->position.x-=sin(camera->rotation.y)*movementSpeedHorizontal;
	}
	if(kHeld & KEY_B)
	{
		camera->position.z-=cos(camera->rotation.y)*movementSpeedHorizontal;
		camera->position.x+=sin(camera->rotation.y)*movementSpeedHorizontal;
	}
	if(kHeld & KEY_Y)
	{
		camera->position.z+=sin(camera->rotation.y)*movementSpeedHorizontal;
		camera->position.x+=cos(camera->rotation.y)*movementSpeedHorizontal;
	}
	if(kHeld & KEY_A)
	{
		camera->position.z-=sin(camera->rotation.y)*movementSpeedHorizontal;
		camera->position.x-=cos(camera->rotation.y)*movementSpeedHorizontal;
	}

	if(kHeld & KEY_DDOWN) camera->position.y+=movementSpeedVertical;
	if(kHeld & KEY_DUP) camera->position.y-=movementSpeedVertical;

	if(kHeld & KEY_DLEFT) printf("\x1b[23;2HSample: %i     ", sample_world_noise_func((int)roundf(-camera->position.x),(int)roundf(-camera->position.y),  (int)roundf(-camera->position.z),  -1,true,0));
	if(kHeld & KEY_DRIGHT) svcSignalEvent(lightHandle);


	// if(kHeld & KEY_DLEFT)
	// {
	// 	//Chunk basicChunk;
	// 	//basicChunk.blocks[0][0][0]=(int)BLOCK_GOLD_ORE;
	// 	//printf("\x1b[15;2H %i",basicChunk.blocks[0][0][0]);
	// 	//generate_chunk(&basicChunk);
	// }

	touchPosition touch;
	hidTouchRead(&touch);

    printf("\x1b[27;2HPos: %f, %f, %f ", camera->position.x, camera->position.y, camera->position.z);
	printf("\x1b[28;2HRot: %f, %f, %f ", camera->rotation.x, camera->rotation.y, camera->rotation.z);
    printf("\x1b[29;2HTch: %i, %i ", touch.px, touch.py);
}

#endif
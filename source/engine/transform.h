#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vectors.h"

typedef struct {
    Vector3 position;
    Vector3 rotation;
} Transform;

Vector3 Transform_Vec(const Transform *transform, const float x, const float y, const float z)
{
	Vector3 vector=(Vector3){x,y,z};

	Vector3 returnVec;
	returnVec = Vector3_Matrix(&vector,'x', transform->rotation.x);
	returnVec = Vector3_Matrix(&returnVec,'y',transform->rotation.y);
	returnVec = Vector3_Matrix(&returnVec,'z',transform->rotation.z);

	return returnVec;
}

Vector3 Transform_Vec_Inverse(const Transform *transform, const float x, const float y, const float z)
{
	Vector3 vector= (Vector3){x,y,z};

	Vector3 returnVec;
	returnVec = Vector3_Matrix(&vector,'x', -transform->rotation.x);
	returnVec = Vector3_Matrix(&returnVec,'y',-transform->rotation.y);
	returnVec = Vector3_Matrix(&returnVec,'z',-transform->rotation.z);

	return returnVec;
}

#endif
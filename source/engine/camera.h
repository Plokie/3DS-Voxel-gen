#ifndef CAMERA_H
#define CAMERA_H

#include <citro3d.h>

#include "transform.h"
#include "vectors.h"

typedef struct{
    Transform transform;
    C3D_Mtx modelView;
} Camera;

#endif
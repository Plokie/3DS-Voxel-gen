#ifndef VECTORS_H
#define VECTORS_H

typedef struct{
    float x,y;
} Vector2;

typedef struct{
    int x,y;
} Vector2Int;

typedef struct{
    float x,y,z;
} Vector3;

typedef struct{
	int x,y,z;
} Vector3Int;

Vector3 New_Vector3(float x, float y, float z)
{
	return (Vector3){ x, y, z};
}

Vector2 New_Vector2(float x, float y)
{
	return (Vector2){ x, y };
}

//Rotates a vector3 by a rotation matrix by float t
Vector3 Vector3_Matrix(const Vector3 *v3, const char m, const float t)
{
    Vector3 vecReturn;

	float mX[3][3]={
		{1.0f,          0.0f,           0.0f},
		{0.0f,          cos(v3->x),      -sin(v3->x)},
		{0.0f,          sin(v3->x),      cos(v3->x)}
	};
	float mY[3][3]={
		{cos(v3->y),     0.0f,           sin(v3->y)},
		{0.0f,          1.0f,           0.0f},
		{-sin(v3->y),    0.0f,           cos(v3->y)}
	};
	float mZ[3][3]={
		{cos(v3->z),     -sin(v3->z),     0.0f},
		{sin(v3->z),     cos(v3->z),      0.0f},
		{0.0f,          0.0f,           1.0f}
	};
	if(m=='x')
	{
		vecReturn.x=(v3->x * mX[0][0]) + (v3->y * mX[1][0]) + (v3->z * mX[2][0]);
		vecReturn.y=(v3->x * mX[0][1]) + (v3->y * mX[1][1]) + (v3->z * mX[2][1]);
		vecReturn.z=(v3->x * mX[0][2]) + (v3->y * mX[1][2]) + (v3->z * mX[2][2]);
	}

	else if(m=='y')
	{
		vecReturn.x=(v3->x * mY[0][0]) + (v3->y * mY[1][0]) + (v3->z * mY[2][0]);
		vecReturn.y=(v3->x * mY[0][1]) + (v3->y * mY[1][1]) + (v3->z * mY[2][1]);
		vecReturn.z=(v3->x * mY[0][2]) + (v3->y * mY[1][2]) + (v3->z * mY[2][2]);
	}
	
	else if(m=='z')
	{
		vecReturn.x=(v3->x * mZ[0][0]) + (v3->y * mZ[1][0]) + (v3->z * mZ[2][0]);
		vecReturn.y=(v3->x * mZ[0][1]) + (v3->y * mZ[1][1]) + (v3->z * mZ[2][1]);
		vecReturn.z=(v3->x * mZ[0][2]) + (v3->y * mZ[1][2]) + (v3->z * mZ[2][2]);
	}
	// return 1;
    return vecReturn;
}

Vector2 Vector2Int_mult_float(Vector2Int v2int, float scale)
{
	return (Vector2){ (float)v2int.x*scale, (float)v2int.y*scale };
}

Vector2 Vector2Int_div_float(Vector2Int v2int, float scale)
{
	return (Vector2){ (float)v2int.x/scale, (float)v2int.y/scale };
}

Vector2 Vector2Int_add_float(Vector2Int v2int, float t)
{
	return(Vector2){ (float)v2int.x+t, (float)v2int.y+t };
}
Vector2 Vector2_add(Vector2 v1, Vector2 v2)
{
	return(Vector2){ v1.x+v2.x, v1.y+v2.y};
}

Vector3Int Vector3Int_Add(Vector3Int v1, Vector3Int v2)
{
	return(Vector3Int){ v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}
Vector3Int Vector3Int_Div(Vector3Int* v1, int a)
{
	return(Vector3Int){ v1->x/a, v1->y/a, v1->z/a};
}
bool Vector3Int_Compare(Vector3Int v1, Vector3Int v2)
{
	return (v1.x==v2.x) & (v1.y==v2.y) & (v1.z==v2.z);
}



Vector3 Vector3Int_To_Vector3(Vector3Int *vec)
{
	return(Vector3){(float)vec->x,(float)vec->y,(float)vec->z};
}
Vector3Int Vector3_To_Vector3Int(Vector3 *vec)
{
	return(Vector3Int) { (int)roundf(vec->x), (int)roundf(vec->y), (int)roundf(vec->z)};
}





#endif
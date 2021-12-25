#ifndef MESH_H
#define MESH_H

#include "atlas.h"
#include "..\game\blocks.h"
#include "utility.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct { float position[3]; float texcoord[2]; float normal[3]; } vertex;

int assignedVertices=0;
vertex vertex_list[65536*9];
//#define vertex_list_count (sizeof(vertex_list)/sizeof(vertex_list[0]))
#define vertex_list_count (sizeof(vertex_list)/sizeof(vertex_list[0]))
void add_vertex(vertex vert)
{
    if(assignedVertices<vertex_list_count)
    {
        vertex_list[assignedVertices]=vert;
        //*list[assignedVertices]=vert;
        assignedVertices++;
   }
}
void print_vertex_info()
{
    printf("\x1b[8;2HVertices : %i %fmb ", vertex_list_count, (double)sizeof(vertex_list)/1000000.0);
    printf("\x1b[9;2HAllocated: %i %fmb %i.p ", assignedVertices, ((double)sizeof(vertex)*(double)assignedVertices)/1000000.0, (int)roundf(((float)assignedVertices/(float)vertex_list_count)*100.0f) );
}

/** @brief Constructs and puts a vertex list of a cube constructed by the information given
 *  @param[out] cube_v_list Pointer to store list in
 *  @param[in] block Block to create (used for textures)
 *  @param[in] faces Each PZ,NZ,PX,NX,PY,NY face is true or false to render
 */
void construct_cube(const BlockID blockID, bool pz, bool nz, bool px, bool nx, bool py, bool ny, Vector3 pos)
{
    if((!pz) & (!nz) & (!px) & (!nx) & (!py) & (!ny)) return;
    Block block = blockDict[(int)blockID];

    Vector2 blockTopTexCoord = Vector2Int_mult_float(texDict[(int)block.topTex],texTileSize);;

    //printf("\x1b[12;3Hnulltest %d ", (int)block.sideTex);

    Vector2 blockSideTexCoord; 
    if(block.sideTex==NULLBLOCK) blockSideTexCoord = blockTopTexCoord;
    else blockSideTexCoord = Vector2Int_mult_float(texDict[(int)block.sideTex],texTileSize);
    
    Vector2 blockBottomTexCoord;
    if(block.bottomTex==NULLBLOCK) blockBottomTexCoord=blockSideTexCoord;
    else blockBottomTexCoord = Vector2Int_mult_float(texDict[(int)block.bottomTex],texTileSize);

    //printf("\x1b[10;2H:: %f, %f ", blockSideTexCoord.x, blockSideTexCoord.y);

    //* (float)texDict[(int)block.sideTex].x;
    //* (float)texDict[(int)block.sideTex].y;

    blockSide side= (blockSide){ blockSideTexCoord, Vector2_add(blockSideTexCoord, (Vector2){texTileSize,texTileSize}) };
    blockSide top= (blockSide){ blockTopTexCoord, Vector2_add(blockTopTexCoord, (Vector2){texTileSize,texTileSize}) };
    blockSide bottom= (blockSide){ blockBottomTexCoord, Vector2_add(blockBottomTexCoord, (Vector2){texTileSize,texTileSize}) };
    //Vector2 UVCoordBLside = blockSideTexCoord;
    //Vector2 UVCoordTRside = Vector2_add(blockSideTexCoord, (Vector2){texTileSize,texTileSize});
    

    if(pz)
    {
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.top.y}, {0.0f, 0.0f, +1.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.top.y}, {0.0f, 0.0f, +1.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.btm.y}, {0.0f, 0.0f, +1.0f} });
        
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.btm.y}, {0.0f, 0.0f, +1.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.btm.y}, {0.0f, 0.0f, +1.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.top.y}, {0.0f, 0.0f, +1.0f} });
        //;
    };
    if(nz)
    {
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.top.y}, {0.0f, 0.0f, -1.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.btm.y}, {0.0f, 0.0f, -1.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.top.y}, {0.0f, 0.0f, -1.0f} });
        
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.btm.y}, {0.0f, 0.0f, -1.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.btm.y}, {0.0f, 0.0f, -1.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.top.y}, {0.0f, 0.0f, -1.0f} });
    }
    if(px)
    {
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.top.y}, {+1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.btm.y}, {+1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.btm.y}, {+1.0f, 0.0f, 0.0f} });
        
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.btm.y}, {+1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {side.top.x, side.top.y}, {+1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.btm.x, side.top.y}, {+1.0f, 0.0f, 0.0f} });
    }
    if(nx)
    {
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.top.y}, {-1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.top.y}, {-1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.btm.y}, {-1.0f, 0.0f, 0.0f} });
        
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {side.btm.x, side.btm.y}, {-1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.btm.y}, {-1.0f, 0.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {side.top.x, side.top.y}, {-1.0f, 0.0f, 0.0f} });
    }
    if(py)
    {
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {top.top.x, top.top.y}, {0.0f, +1.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {top.top.x, top.btm.y}, {0.0f, +1.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {top.btm.x, top.btm.y}, {0.0f, +1.0f, 0.0f} });
        
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, +0.5f+pos.z}, {top.btm.x, top.btm.y}, {0.0f, +1.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {top.btm.x, top.top.y}, {0.0f, +1.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, +0.5f+pos.y, -0.5f+pos.z}, {top.top.x, top.top.y}, {0.0f, +1.0f, 0.0f} });
    }
    if(ny)
    {
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {bottom.top.x, bottom.top.y}, {0.0f, -1.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {bottom.btm.x, bottom.top.y}, {0.0f, -1.0f, 0.0f} });
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {bottom.btm.x, bottom.btm.y}, {0.0f, -1.0f, 0.0f} });
        
        add_vertex((vertex){ {+0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {bottom.btm.x, bottom.btm.y}, {0.0f, -1.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, +0.5f+pos.z}, {bottom.top.x, bottom.btm.y}, {0.0f, -1.0f, 0.0f} });
        add_vertex((vertex){ {-0.5f+pos.x, -0.5f+pos.y, -0.5f+pos.z}, {bottom.top.x, bottom.top.y}, {0.0f, -1.0f, 0.0f} });
    }
}

//* Old vertex list
// vertex vertex_list[] =
// {
// 	// First face (PZ)
// 	// First triangle
// 	{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
// 	{ {+0.5f, -0.5f, +0.5f}, {texTileSize, 0.0f}, {0.0f, 0.0f, +1.0f} },
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, 0.0f, +1.0f} },
// 	// Second triangle
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, 0.0f, +1.0f} },
// 	{ {-0.5f, +0.5f, +0.5f}, {0.0f, texTileSize}, {0.0f, 0.0f, +1.0f} },
// 	{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },

// 	// Second face (MZ)
// 	// First triangle
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },
// 	{ {-0.5f, +0.5f, -0.5f}, {texTileSize, 0.0f}, {0.0f, 0.0f, -1.0f} },
// 	{ {+0.5f, +0.5f, -0.5f}, {texTileSize, texTileSize}, {0.0f, 0.0f, -1.0f} },
// 	// Second triangle
// 	{ {+0.5f, +0.5f, -0.5f}, {texTileSize, texTileSize}, {0.0f, 0.0f, -1.0f} },
// 	{ {+0.5f, -0.5f, -0.5f}, {0.0f, texTileSize}, {0.0f, 0.0f, -1.0f} },
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f} },

// 	// Third face (PX)
// 	// First triangle
// 	{ {+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} },
// 	{ {+0.5f, +0.5f, -0.5f}, {texTileSize, 0.0f}, {+1.0f, 0.0f, 0.0f} },
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {+1.0f, 0.0f, 0.0f} },
// 	// Second triangle
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {+1.0f, 0.0f, 0.0f} },
// 	{ {+0.5f, -0.5f, +0.5f}, {0.0f, texTileSize}, {+1.0f, 0.0f, 0.0f} },
// 	{ {+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {+1.0f, 0.0f, 0.0f} },

// 	// Fourth face (MX)
// 	// First triangle
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} },
// 	{ {-0.5f, -0.5f, +0.5f}, {texTileSize, 0.0f}, {-1.0f, 0.0f, 0.0f} },
// 	{ {-0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {-1.0f, 0.0f, 0.0f} },
// 	// Second triangle
// 	{ {-0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {-1.0f, 0.0f, 0.0f} },
// 	{ {-0.5f, +0.5f, -0.5f}, {0.0f, texTileSize}, {-1.0f, 0.0f, 0.0f} },
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f} },

// 	// Fifth face (PY)
// 	// First triangle
// 	{ {-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, +1.0f, 0.0f} },
// 	{ {-0.5f, +0.5f, +0.5f}, {texTileSize, 0.0f}, {0.0f, +1.0f, 0.0f} },
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, +1.0f, 0.0f} },
// 	// Second triangle
// 	{ {+0.5f, +0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, +1.0f, 0.0f} },
// 	{ {+0.5f, +0.5f, -0.5f}, {0.0f, texTileSize}, {0.0f, +1.0f, 0.0f} },
// 	{ {-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, +1.0f, 0.0f} },

// 	// Sixth face (MY)
// 	// First triangle
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} },
// 	{ {+0.5f, -0.5f, -0.5f}, {texTileSize, 0.0f}, {0.0f, -1.0f, 0.0f} },
// 	{ {+0.5f, -0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, -1.0f, 0.0f} },
// 	// Second triangle
// 	{ {+0.5f, -0.5f, +0.5f}, {texTileSize, texTileSize}, {0.0f, -1.0f, 0.0f} },
// 	{ {-0.5f, -0.5f, +0.5f}, {0.0f, texTileSize}, {0.0f, -1.0f, 0.0f} },
// 	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f} },
// };





#endif
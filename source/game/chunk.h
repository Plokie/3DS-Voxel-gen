#ifndef CHUNK_H
#define CHUNK_H

#include <3ds.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "blocks.h"
#include "worldgen.h"
#include "..\engine\vectors.h"
#include "..\engine\mesh.h"
#include "..\engine\utility.h"
#include "..\engine\mesh.h"
//#include "..\utility\noise.h"
#include "..\utility\FastNoiseLite.h"

#define NUMTHREADS 8
#define STACKSIZE (4 * 1024)

#define CHUNKSIZE 16

int threads_activated=0;

typedef struct{
    int assigned;
    vertex vertices[ ( CHUNKSIZE*CHUNKSIZE*CHUNKSIZE*3*12 ) / 2 ];
} ChunkVertices;

// typedef struct{
//     Chunk* parentChunk;
//     int blocks[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
// } WaterChunk;

/** @brief Contains a collection of blocks to be rendered and destroyed.
 *  @param[in] Vector3Int::position
 *  @param[in] int::blocks[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE]
 */
typedef struct{
    Vector3Int position;
    int blocks[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
    //WaterChunk* waterChunk;
    ChunkVertices* vertices;
} Chunk;


typedef struct{
    bool loaded;
    Chunk *chunk;
} Chunk_Reg;

//Chunk_Reg loadedChunks[54]={ [0 ... 53]=(Chunk_Reg){false,(Chunk*){0}} };
//Chunk_Reg loadedChunks[54]={ [0 ... 53]=0 };
Chunk_Reg loadedChunks[54]={ 0 };
//Chunk_Reg loadedChunks[54]=malloc(54*sizeof(Chunk_Reg));


void reload_chunk(Chunk *chunk)
{
}

void reload_chunk_by_pos(Vector3Int pos)
{
    for(int i=0; i<54; i++)
    {
        if( Vector3Int_Compare( loadedChunks[ i ].chunk->position, pos ) )
        {
            reload_chunk(loadedChunks[i].chunk);
        }
    }
}

void reload_chunks_adjacent_to(Vector3Int pos)
{
    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){1,0,0} ) );
    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){-1,0,0} ) );

    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){0,1,0} ) );
    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){0,-1,0} ) );

    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){0,0,1} ) );
    reload_chunk_by_pos( Vector3Int_Add( pos, (Vector3Int){0,0,-1} ) );
}

void register_chunk(Chunk *chunk)
{
    for(int i=0; i<54; i++)
    {
        if(!loadedChunks[i].loaded)
        {
            loadedChunks[i]=(Chunk_Reg){ true, chunk };
            return;
        }
    }
}

void generate_chunk(Chunk *chunk)
{
    //It seems the 3DS wont let me use 3D even arrays above size around [19][19][19], thats annoying...
    //Cubic chunks it is! (Headache incoming)
    for(int x=0; x<CHUNKSIZE; x++) { //Loop X
        for(int z=0; z<CHUNKSIZE; z++) { // Loop Z
            Vector2Int pos2D = (Vector2Int){x+chunk->position.x,z+chunk->position.z};
            int height;
            height = sample_world_height(pos2D.x, pos2D.y);
            
            // height=(int)round(Perlin_Get2d((double)x+chunk->position.x,(double)z+chunk->position.z, 0.05, 10)*20.0f)+45;

            for(int y=0; y<CHUNKSIZE; y++) { // Loop Y
                Vector3Int pos = (Vector3Int){x+chunk->position.x,y+chunk->position.y,z+chunk->position.z};
                chunk->blocks[x][y][z] = sample_world_noise_func(pos.x,pos.y,pos.z,height,false,0);
            }

            
        }
    }
}

// void construct_water_chunk(WaterChunk *waterChunk)
// {
//     for(int x=0; x<CHUNKSIZE; x++)
//     {
//         for(int z=0; z<CHUNKSIZE; z++)
//         {

//         }
//     }
// }

void construct_chunk(Chunk *chunk)
{
    int x,y,z;
    for(x=0; x<CHUNKSIZE; x++) { //Loop X
        for(z=0; z<CHUNKSIZE; z++) { // Loop Z
            Vector2Int pos2D =(Vector2Int){x+chunk->position.x,z+chunk->position.z};
            int height=sample_world_height(pos2D.x,pos2D.y);
            for(y=0; y<CHUNKSIZE; y++) { // Loop Y
                Vector3Int pos = (Vector3Int){x+chunk->position.x,y+chunk->position.y,z+chunk->position.z};
                if(chunk->blocks[x][y][z]!=0)
                {
                    bool px,nx,pz,nz,py,ny;
                    px=false; nx=false; pz=false; nz=false; ny=false; py=false;

                    if(x==15)px=sample_world_noise_func(pos.x+1,pos.y,  pos.z,  height-2,true,chunk->blocks[x][y][z])==0;else px=(chunk->blocks[x+1][y][z]==0);
                    if(x== 0)nx=sample_world_noise_func(pos.x-1,pos.y,  pos.z,  height-2,true,chunk->blocks[x][y][z])==0;else nx=(chunk->blocks[x-1][y][z]==0);
                    if(z==15)pz=sample_world_noise_func(pos.x,  pos.y,  pos.z+1,height-2,true,chunk->blocks[x][y][z])==0;else pz=(chunk->blocks[x][y][z+1]==0);
                    if(z== 0)nz=sample_world_noise_func(pos.x,  pos.y,  pos.z-1,height-2,true,chunk->blocks[x][y][z])==0;else nz=(chunk->blocks[x][y][z-1]==0);
                    if(y==15)py=sample_world_noise_func(pos.x,  pos.y+1,pos.z,  height-2,true,chunk->blocks[x][y][z])==0;else py=(chunk->blocks[x][y+1][z]==0);
                    if(y== 0)ny=sample_world_noise_func(pos.x,  pos.y-1,pos.z,  height-2,true,chunk->blocks[x][y][z])==0;else ny=(chunk->blocks[x][y-1][z]==0);

                    construct_cube((BlockID)chunk->blocks[x][y][z],pz,nz,px,nx,py,ny,Vector3Int_To_Vector3(&pos));
                }
            }
        }
    }
}

void rebuild_chunk(Chunk* chunk)
{

}




void load_chunk_area(Vector3 playerPos)
{
    Vector3Int pos = Vector3_To_Vector3Int(&playerPos);
    pos = Vector3Int_Div(&pos,CHUNKSIZE);
    for(int x=-3; x<4; x++)
	{
		for(int y=0; y<8; y++)
		{
			for(int z=-3; z<4; z++)
            {
                Chunk newChunk;
                newChunk.position=(Vector3Int){x*CHUNKSIZE,y*CHUNKSIZE,z*CHUNKSIZE};
            }
        }
    }
}

void default_chunk_circle()
{
    for(int x=-3; x<4; x++)
	{
		for(int y=0; y<8; y++)
		{
			for(int z=-3; z<4; z++)
			{
				Chunk newChunk;
				newChunk.position=(Vector3Int){x*CHUNKSIZE,y*CHUNKSIZE,z*CHUNKSIZE};
				generate_chunk(&newChunk);
				//register_chunk(&newChunk);
				construct_chunk(&newChunk);
			}
		}
	}
}

#endif
#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <3ds.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "..\utility\FastNoiseLite.h"

#define WATERLEVEL 62

bool random_seed=true;
int world_seed=274797109;
fnl_state noise;
fnl_state stone_accents;
fnl_state alpha_caves;
void init_noise_func()
{
    if(random_seed)
    {
        srand(time(NULL));
        world_seed=rand();
    }

    //Land noise
    noise=fnlCreateState();
    noise.noise_type=FNL_NOISE_PERLIN;
    noise.seed=world_seed;

    noise.frequency=0.010f;

    noise.domain_warp_type=FNL_DOMAIN_WARP_OPENSIMPLEX2;
    noise.domain_warp_amp=90.0f;

    noise.fractal_type=FNL_FRACTAL_FBM;
    noise.lacunarity=2.20f;

    stone_accents=fnlCreateState();
    stone_accents.noise_type=FNL_NOISE_PERLIN;
    stone_accents.seed=world_seed;

    alpha_caves=fnlCreateState();
    alpha_caves.noise_type=FNL_NOISE_PERLIN;
    alpha_caves.seed=world_seed;
    alpha_caves.frequency=0.035f;
    alpha_caves.fractal_type=FNL_FRACTAL_FBM;
}
int sample_world_height(int x, int z) { return (int)ceilf(fnlGetNoise2D(&noise, x, z)*50.0f+74.0f); }
int sample_world_noise_func(int x, int y, int z, int height, bool cullCall, int debugID)
{
    int returnVal=0;
    if(height==-1) height = sample_world_height(x,z);

    

    if(y==0)
    {
        returnVal= (int)BLOCK_BEDROCK;
    }
    else if(y<=height)
    {
        if(fnlGetNoise3D(&alpha_caves,x,y,z)>0.25f)
        {
            returnVal= (int)BLOCK_AIR;
        }
        
        else if(y==height)
        {   
            if(y<=WATERLEVEL+1)
            {
                returnVal= (int)BLOCK_SAND;
            }
            else
            {
                returnVal= (int)BLOCK_GRASS;
            }
        }
        else if(y==height-1 || y==height-2)
        {
            if(y<=WATERLEVEL+1)
            {
                returnVal= (int)BLOCK_GRAVEL;
            }
            else if(fnlGetNoise3D(&stone_accents,x,y,z)>0.4f)
            {
                returnVal= (int)BLOCK_GRAVEL;
            }
            else
            {
                returnVal= (int)BLOCK_DIRT;
            }
            
        } 
        else if(y<height)
        {
            if(fnlGetNoise3D(&stone_accents,x,y,z)>0.4f)
            {
                returnVal= (int)BLOCK_BLACKSTONE;
            }
            else
            {
                returnVal= (int)BLOCK_STONE;
            }
        }
        else
        {
            returnVal= (int)BLOCK_AIR;
        }
    }
    else
    {
        returnVal= (int)BLOCK_AIR;
    }

    //if(cullCall) printf("\x1b[17;2Hcull for %i %i %i was found to be %i %i       ", x,y,z,returnVal,height);

    return returnVal;
}

#endif
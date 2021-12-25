#ifndef ATLAS_H
#define ATLAS_H


#include "vectors.h"

typedef struct
{
    Vector2 top;
    Vector2 btm;
} blockSide;


const int texSize=256;
const int tileSize=16;
const float texTileSize=1.0f/(float)tileSize;

// typedef struct{
//     Vector2 p1,p2,p3;
// } AtlasTexture;
typedef enum{
    NULLBLOCK,
    TEX_DIRT,
    TEX_GRASS_SIDE,
    TEX_GRASS_TOP,
    TEX_SPRUCE_GRASS_SIDE,
    TEX_SPRUCE_GRASS_TOP,
    TEX_DESERT_GRASS_SIDE,
    TEX_DESERT_GRASS_TOP,
    TEX_CHERRY_GRASS_SIDE,
    TEX_CHERRY_GRASS_TOP,
    TEX_SAND,
    TEX_STONE,
    TEX_COBBLE,
    TEX_COAL_ORE,
    TEX_COPPER_ORE,
    TEX_GOLD_ORE,
    TEX_AMETHYST_ORE,
    TEX_TITANIUM_ORE,
    TEX_OAK_LOG_SIDE,
    TEX_OAK_LOG_TOP,
    TEX_OAK_LEAVES,
    TEX_OAK_PLANKS,
    TEX_GRAVEL,
    TEX_CLAY,
    TEX_GLASS,

    TEX_WOOL_WHITE,
    TEX_WOOL_BLACK,
    TEX_WOOL_RED,
    TEX_WOOL_GREEN,
    TEX_WOOL_BLUE,
    TEX_WOOL_ORANGE,
    TEX_WOOL_YELLOW,
    TEX_WOOL_PURPLE,
    TEX_WOOL_PINK,

    TEX_GLASS_WHITE,
    TEX_GLASS_BLACK,
    TEX_GLASS_RED,
    TEX_GLASS_GREEN,
    TEX_GLASS_BLUE,
    TEX_GLASS_ORANGE,
    TEX_GLASS_YELLOW,
    TEX_GLASS_PURPLE,
    TEX_GLASS_PINK,

    TEX_BLACKSTONE,
    TEX_BLACKCOBBLE,
    TEX_BLACK_COAL_ORE,
    TEX_BLACK_COPPER_ORE,
    TEX_BLACK_GOLD_ORE,
    TEX_BLACK_AMETHYST_ORE,
    TEX_BLACK_TITANIUM_ORE,

    TEX_BIRCH_LOG_SIDE,
    TEX_BIRCH_LOG_TOP,
    TEX_BIRCH_LEAVES,
    TEX_BIRCH_PLANKS,

    TEX_SPRUCE_LOG_SIDE,
    TEX_SPRUCE_LOG_TOP,
    TEX_SPRUCE_LEAVES,
    TEX_SPRUCE_PLANKS,

    TEX_CHERRY_LOG_SIDE,
    TEX_CHERRY_LOG_TOP,
    TEX_CHERRY_LEAVES,
    TEX_CHERRY_PLANKS,

    TEX_BEDROCK,
    TEX_WATER,
} BlockTex;
//pass in (int)BlockTex and it will return the Vector2Int coordinates of the texture#
//
//x,y, where 0,0=top left tile, and 1,0 is the one to the right, 
//and 1,1 is the one to the right and below, and so on...
static Vector2Int texDict[]={
    {15,15}, //NULLBLOCK
    {0,0}, //Dirt
    {1,0}, //Grass side
    {2,0}, //Grass top
    {2,2}, //Spruce grass side
    {3,2}, //Spruce grass top
    {2,3}, //Desert grass side
    {3,3}, //Desert grass top
    {2,4}, //Cherry grass side
    {3,4}, //Cherry grass top
    {3,0}, //Sand
    {4,0}, //Stone
    {4,2}, //Cobble
    {5,0}, //Coal
    {6,0}, //Copper
    {7,0}, //Gold
    {8,0}, //Amethyst
    {9,0}, //Titanium
    {10,0}, //Oak log side
    {11,0}, //Oak log top
    {12,0}, //Oak leaves
    {13,0}, //Oak planks

    //{0,1} //Water
    {1,1}, //Gravel
    {2,1}, //Clay
    {3,1}, //Glass

    //Wool
    {0,2}, //white
    {0,3}, //black
    {0,4}, //red
    {0,5}, //green
    {0,6}, //Blue
    {0,7}, //orange
    {0,8}, //yellow
    {0,9}, //purple
    {0,10}, //pink

    //Colour glass
    {1,2}, //white
    {1,3}, //black
    {1,4}, //red
    {1,5}, //green
    {1,6}, //Blue
    {1,7}, //orange
    {1,8}, //yellow
    {1,9}, //purple
    {1,10}, //pink

    {4,1}, //BLACKSTONE
    {4,3}, //BLACK COBBLE
    {5,1}, //BLACK COAL
    {6,1}, //BLACK COPPER
    {7,1}, //BLACK GOLD
    {8,1}, //BLACK AMETHYST
    {9,1}, //BLACK TITANIUM

    {10,1}, //BIRCH LOG SIDE
    {11,1}, //BIRCH LOG TOP
    {12,1}, //BIRCH LEAVES
    {13,1}, //BIRCH PLANKS

    {10,2}, //SPRUCE LOG SIDE
    {11,2}, //SPRUCE LOG TOP
    {12,2}, //SPRUCE LEAVES
    {13,2}, //SPRUCE PLANKS

    {10,3}, //CHERRY LOG SIDE
    {11,3}, //CHERRY LOG TOP
    {12,3}, //CHERRY LEAVES
    {13,3}, //CHERRY PLANKS

    {0,1}, //Bedrock
    {9,2}, //Water
};
#endif
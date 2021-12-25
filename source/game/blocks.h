#ifndef BLOCKS_H
#define BLOCKS_H

#include "..\engine\atlas.h"

typedef enum{
    BLOCK
} BlockShape;

typedef enum{
    BLOCK_AIR,
    BLOCK_GRASS,
    BLOCK_SPRUCE_GRASS,
    BLOCK_DESERT_GRASS,
    BLOCK_CHERRY_GRASS,
    BLOCK_DIRT,
    BLOCK_STONE,
    BLOCK_COBBLE,
    BLOCK_SAND,
    BLOCK_COAL_ORE,
    BLOCK_COPPER_ORE,
    BLOCK_GOLD_ORE,
    BLOCK_AMETHYST_ORE,
    BLOCK_TITANIUM_ORE,
    BLOCK_OAK_LOG,
    BLOCK_OAK_LEAVES,
    BLOCK_OAK_PLANKS,
    BLOCK_GRAVEL,
    BLOCK_CLAY,
    BLOCK_GLASS,

    BLOCK_WOOL_WHITE,
    BLOCK_WOOL_BLACK,
    BLOCK_WOOL_RED,
    BLOCK_WOOL_GREEN,
    BLOCK_WOOL_BLUE,
    BLOCK_WOOL_ORANGE,
    BLOCK_WOOL_YELLOW,
    BLOCK_WOOL_PURPLE,
    BLOCK_WOOL_PINK,

    BLOCK_GLASS_WHITE,
    BLOCK_GLASS_BLACK,
    BLOCK_GLASS_RED,
    BLOCK_GLASS_GREEN,
    BLOCK_GLASS_BLUE,
    BLOCK_GLASS_ORANGE,
    BLOCK_GLASS_YELLOW,
    BLOCK_GLASS_PURPLE,
    BLOCK_GLASS_PINK,

    BLOCK_BLACKSTONE,
    BLOCK_BLACKCOBBLE,
    BLOCK_BLACKSTONE_COAL_ORE,
    BLOCK_BLACKSTONE_COPPER_ORE,
    BLOCK_BLACKSTONE_GOLD_ORE,
    BLOCK_BLACKSTONE_AMETHYST_ORE,
    BLOCK_BLACKSTONE_TITANIUM_ORE,

    BLOCK_BEDROCK,
} BlockID;

typedef struct{
    BlockShape shape;
    bool isTransparent;
    BlockTex topTex;
    BlockTex bottomTex;
    BlockTex sideTex;
} Block;
//TOP, BOTTOM, SIDE
//Only pass one and rest will be copied
static const Block blockDict[]=
{
    {BLOCK,false,NULLBLOCK},
    {BLOCK,false,TEX_GRASS_TOP,TEX_DIRT,TEX_GRASS_SIDE},
    {BLOCK,false,TEX_SPRUCE_GRASS_TOP,TEX_DIRT,TEX_SPRUCE_GRASS_SIDE},
    {BLOCK,false,TEX_DESERT_GRASS_TOP,TEX_DIRT,TEX_DESERT_GRASS_SIDE},
    {BLOCK,false,TEX_CHERRY_GRASS_TOP,TEX_DIRT,TEX_CHERRY_GRASS_SIDE},
    {BLOCK,false,TEX_DIRT},
    {BLOCK,false,TEX_STONE},
    {BLOCK,false,TEX_COBBLE},
    {BLOCK,false,TEX_SAND},
    {BLOCK,false,TEX_COAL_ORE},
    {BLOCK,false,TEX_COPPER_ORE},
    {BLOCK,false,TEX_GOLD_ORE},
    {BLOCK,false,TEX_AMETHYST_ORE},
    {BLOCK,false,TEX_TITANIUM_ORE},
    {BLOCK,false,TEX_OAK_LOG_TOP,TEX_OAK_LOG_TOP,TEX_OAK_LOG_SIDE},
    {BLOCK,true,TEX_OAK_LEAVES},
    {BLOCK,false,TEX_OAK_PLANKS},
    {BLOCK,false,TEX_GRAVEL},
    {BLOCK,false,TEX_CLAY},
    {BLOCK,true,TEX_GLASS},

    {BLOCK,true,TEX_WOOL_WHITE},
    {BLOCK,true,TEX_WOOL_BLACK},
    {BLOCK,true,TEX_WOOL_RED},
    {BLOCK,true,TEX_WOOL_GREEN},
    {BLOCK,true,TEX_WOOL_BLUE},
    {BLOCK,true,TEX_WOOL_ORANGE},
    {BLOCK,true,TEX_WOOL_YELLOW},
    {BLOCK,true,TEX_WOOL_PURPLE},
    {BLOCK,true,TEX_WOOL_PINK},

    {BLOCK,true,TEX_GLASS_WHITE},
    {BLOCK,true,TEX_GLASS_BLACK},
    {BLOCK,true,TEX_GLASS_RED},
    {BLOCK,true,TEX_GLASS_GREEN},
    {BLOCK,true,TEX_GLASS_BLUE},
    {BLOCK,true,TEX_GLASS_ORANGE},
    {BLOCK,true,TEX_GLASS_YELLOW},
    {BLOCK,true,TEX_GLASS_PURPLE},
    {BLOCK,true,TEX_GLASS_PINK},

    {BLOCK,false,TEX_BLACKSTONE},
    {BLOCK,false,TEX_BLACKCOBBLE},
    {BLOCK,false,TEX_BLACK_COAL_ORE},
    {BLOCK,false,TEX_BLACK_COPPER_ORE},
    {BLOCK,false,TEX_BLACK_GOLD_ORE},
    {BLOCK,false,TEX_BLACK_AMETHYST_ORE},
    {BLOCK,false,TEX_BLACK_TITANIUM_ORE},

    {BLOCK,false,TEX_BEDROCK}
};

#define BLOCK_COUNT (sizeof(blockDict)/sizeof(blockDict[0]))


#endif
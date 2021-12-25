#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "vshader_shbin.h"
#include "atlas_t3x.h"

#include "engine/vectors.h"
#include "engine/transform.h"
#include "engine/atlas.h"
#include "engine/mesh.h"
#include "engine/bottomscreen.h"

#include "game/blocks.h"
#include "game/controls.h"
#include "game/chunk.h"
#include "game/worldgen.h"
#include "game/lightsystem.h"

#define M_PI		3.14159265358979323846 //Had to put to get intellisense to shut up

#define CLEAR_COLOR 0x7AC3F0FF

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

Transform camera;

static DVLB_s* vshader_dvlb;
static shaderProgram_s program;
static int uLoc_projection, uLoc_modelView;
static int uLoc_lightVec, uLoc_lightHalfVec, uLoc_lightClr, uLoc_material;
static C3D_Mtx projection;
static C3D_Mtx material =
{
	{
	{ { 0.0f, 0.2f, 0.2f, 0.2f } }, // Ambient
	{ { 0.0f, 0.4f, 0.4f, 0.4f } }, // Diffuse
	{ { 0.0f, 0.8f, 0.8f, 0.8f } }, // Specular
	{ { 1.0f, 0.0f, 0.0f, 0.0f } }, // Emission
	}
};

static void* vbo_data;
static C3D_Tex atlas_tex;
// Helper function for loading a texture from memory
static bool loadTextureFromMem(C3D_Tex* tex, C3D_TexCube* cube, const void* data, size_t size)
{
	Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, tex, cube, false);
	if (!t3x)
		return false;

	// Delete the t3x object since we don't need it
	Tex3DS_TextureFree(t3x);
	return true;
}

static void sceneInit(void)
{
	//initialize_chunk_list();
	camera.position = New_Vector3(10.46f,-19.89f,-48.56f);
	camera.rotation = New_Vector3(0.4831f,0.5334f,0.0f);

	//Chunk newChunks[0];

	init_noise_func();
	initLightThread();

	default_chunk_circle();

	for(int i=0; i<BLOCK_COUNT; i++)
	{
		construct_cube((BlockID)i,true,true,true,true,false,false,(Vector3){0.0f,(float)i,0.0f});
		if(i==0) construct_cube((BlockID)i,false,false,false,false,false,true,(Vector3){0.0f,(float)i,0.0f});
		if(i==BLOCK_COUNT-1) construct_cube((BlockID)i,false,false,false,false,true,false,(Vector3){0.0f,(float)i,0.0f});
		//if(i!=0) construct_cube((BlockID)i,true,true,true,true,false,false,(Vector3){0.0f,-(float)i,0.0f});
		//if(i==BLOCK_COUNT-1) construct_cube((BlockID)i,false,false,false,false,false,true,(Vector3){0.0f,-(float)i,0.0f});
	}
	print_vertex_info();
	
	// Load the vertex shader, create a shader program and bind it
	vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
	C3D_BindProgram(&program);

	// Get the location of the uniforms
	uLoc_projection   = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
	uLoc_modelView    = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");
	uLoc_lightVec     = shaderInstanceGetUniformLocation(program.vertexShader, "lightVec");
	uLoc_lightHalfVec = shaderInstanceGetUniformLocation(program.vertexShader, "lightHalfVec");
	uLoc_lightClr     = shaderInstanceGetUniformLocation(program.vertexShader, "lightClr");
	uLoc_material     = shaderInstanceGetUniformLocation(program.vertexShader, "material");

	// Configure attributes for use with the vertex shader
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v1=texcoord
	AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // v2=normal

	// Compute the projection matrix
	Mtx_PerspTilt(&projection, C3D_AngleFromDegrees(80.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, false);

	// Create the VBO (vertex buffer object)
	vbo_data = linearAlloc(sizeof(vertex_list));
	memcpy(vbo_data, vertex_list, sizeof(vertex_list));

	// Configure buffers
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 3, 0x210);

	// Load the texture and bind it to the first texture unit
	if (!loadTextureFromMem(&atlas_tex, NULL, atlas_t3x, atlas_t3x_size))
		svcBreak(USERBREAK_PANIC);
	C3D_TexSetFilter(&atlas_tex, GPU_NEAREST, GPU_NEAREST);
	C3D_TexBind(0, &atlas_tex);

	// Configure the first fragment shading substage to blend the texture color with
	// the vertex color (calculated by the vertex shader using a lighting algorithm)
	// See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	//C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, 0);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);
}

static void sceneRender(void)
{
	updateControls(&camera);

	C3D_Mtx modelView;
	C3D_Mtx lightDir;
	// Calculate the modelView matrix
	Mtx_Identity(&modelView);
	Mtx_RotateX(&modelView, camera.rotation.x, true);
	Mtx_RotateY(&modelView, camera.rotation.y, true);
	Mtx_RotateZ(&modelView, camera.rotation.z, true);
	Mtx_Translate(&modelView, camera.position.x, camera.position.y, camera.position.z, true);
	
	Mtx_Identity(&lightDir);
	Mtx_RotateX(&lightDir, camera.rotation.x, true);
	Mtx_RotateY(&lightDir, camera.rotation.y, true);
	Mtx_RotateZ(&lightDir, camera.rotation.z, true);
	Mtx_Translate(&lightDir, camera.position.x, camera.position.y, camera.position.z, true);
	Mtx_Translate(&lightDir, 0.0f, 0.0f, -1.0f, true);

	//Mtx_

	// Update the uniforms
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelView,  &modelView);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_material,   &material);
	
	//Remove these 2 lines to remove default light vec (do so later)
	C3D_FVUnifSet(GPU_VERTEX_SHADER, uLoc_lightVec,     0.0f, 0.0f, -1.0f, 0.0f);
	C3D_FVUnifSet(GPU_VERTEX_SHADER, uLoc_lightHalfVec, 0.0f, 0.0f, -1.0f, 0.0f);
	//Replace later with light level flood system


	C3D_FVUnifSet(GPU_VERTEX_SHADER, uLoc_lightClr,     1.0f, 1.0f,  1.0f, 1.0f);

	// Draw the VBO
	C3D_DrawArrays(GPU_TRIANGLES, 0, assignedVertices);
}

static void sceneExit(void)
{
	// Free the texture
	C3D_TexDelete(&atlas_tex);

	// Free the VBO
	linearFree(vbo_data);

	// Free the shader program
	shaderProgramFree(&program);
	DVLB_Free(vshader_dvlb);
}

int main()
{
	// Initialize graphics
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Initialize the render target
	C3D_RenderTarget* target = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(target, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

	consoleInit(GFX_BOTTOM, NULL);
	// Initialize the scene
	sceneInit();

	printf("\x1b[1;1HDebug info: ");
	printf("\x1b[11;2HChunk size: %fmb", (double)sizeof(Chunk)/1000000.0);


	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C3D_RenderTargetClear(target, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
			C3D_FrameDrawOn(target);
			sceneRender();			
		C3D_FrameEnd(0);
	}

	// Deinitialize the scene
	sceneExit();

	killLightThread();

	// Deinitialize graphics
	C3D_Fini();
	gfxExit();
	return 0;
}

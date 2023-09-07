#include <nds.h>
#include <malloc.h>
#include <stdio.h>
#include <cmath>
#include <filesystem.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <algorithm>
#include <gl2d.h>
#include "drunkenlogo.h"

#include "UseHeaders/globals.h"
//#include "Mud_pcx.h"
//#include "World_txt.h"


int DrawGLScene();
int DrawFileTextTemp();


int	texture[1];			// Storage For 1 Textures (only going to use 1 on the DS for this demo)

//SECTOR sector1;				// Our Model Goes Here:

bool TempPausePress = false;

void KeyUp(int KeyUp){
	//Keys Up
		if(KeyUp & (KEY_UP))
			Controls.Up = false;
		if(KeyUp & (KEY_DOWN))
			Controls.Down = false;
		if(KeyUp & (KEY_LEFT))
			Controls.Left = false;
		if(KeyUp & (KEY_RIGHT))
			Controls.Right = false;

		if(KeyUp & (KEY_A))
			Controls.A = false;
		if(KeyUp & (KEY_B))
			Controls.B = false;
		if(KeyUp & (KEY_X))
			Controls.X = false;
		if(KeyUp & (KEY_Y))
			Controls.Y = false;

		if(KeyUp & (KEY_L))
			Controls.L = false;
		if(KeyUp & (KEY_R))
			Controls.R = false;

		if(KeyUp & (KEY_START))
			Controls.Str = false;
		if(KeyUp & (KEY_SELECT))
			Controls.Slt = false;
}

void KeyDown(int KeyDown){
	//Keys Down
		if(KeyDown & (KEY_UP))
			Controls.Up = true;
		if(KeyDown & (KEY_DOWN))
			Controls.Down = true;
		if(KeyDown & (KEY_LEFT))
			Controls.Left = true;
		if(KeyDown & (KEY_RIGHT))
			Controls.Right = true;

		if(KeyDown & (KEY_A))
			Controls.A = true;
		if(KeyDown & (KEY_B))
			Controls.B = true;
		if(KeyDown & (KEY_X))
			Controls.X = true;
		if(KeyDown & (KEY_Y))
			Controls.Y = true;
	
		if(KeyDown & (KEY_L))
			Controls.L = true;
		if(KeyDown & (KEY_R))
			Controls.R = true;

		if(KeyDown & (KEY_START))
			Controls.Str = true;
		if(KeyDown & (KEY_SELECT))
			Controls.Slt = true;
}

void InitTextAssets(){
	int i;
	u8* gfx = (u8*)AtlasTiles;
	for(i = 0; i < 12; i++)
	{
		Text_sprite_mem[i] = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
		dmaCopy(gfx, Text_sprite_mem[i], 16*16);
		gfx += 16*16;
	}
}

int main() {

	// Setup the Main screen for 3D
	//consoleDemoInit();
	//DrawFileTextTemp();

	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_TEXTURE);                        //NEW  must set up some memory for textures
	vramSetBankD(VRAM_D_SUB_SPRITE);
	
	// initialize the 3D engine
	glInit();

	// initialize gl2d
	//glScreen2D();

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	dmaCopy(AtlasPal,SPRITE_PALETTE_SUB,512);
	// enable antialiasing
	glEnable(GL_ANTIALIAS);
	
	// enable textures
	//glEnable(GL_TEXTURE_2D);
	
	// Set our viewport to be the same size as the screen
	glViewport(0,0,255,191);
	
	// setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.01, 100);
	
	glLight(0, RGB15(31,31,31) , 0,	floattov10(-1.0), 0);
	
	//need to set up some material properties since DS does not have them set by default
	glMaterialf(GL_AMBIENT, RGB15(16,16,16));
	glMaterialf(GL_DIFFUSE, RGB15(16,16,16));
	glMaterialf(GL_SPECULAR, BIT(15) | RGB15(8,8,8));
	glMaterialf(GL_EMISSION, RGB15(16,16,16));
	
	//ds uses a table for shinyness..this generates a half-ass one
	glMaterialShinyness();
	
	//ds specific, several attributes can be set here
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
	
	// Set the current matrix to be the model matrix
	glMatrixMode(GL_MODELVIEW);
	
	// Specify the Clear Color and Depth
	//glClearColor(15, 20, 30,31);
	glClearColor(15,20,30,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);
	
	// set the vertex color to white
	glColor3f(1.0,1.0,1.0);

	touchPosition	thisXY;
	touchPosition	lastXY = { 0,0,0,0 };	
	
	//consoleEnable
	consoleDemoInit();
	LoadLevel("World.txt");

	//InitTextAssets();

	//DrawFileTextTemp();
	printf("\x1b[1;1HPropulsion Demo");
	
	//printf("      Hello DS World\n");
	//printf("     www.devkitpro.org\n");
	//printf("   www.drunkencoders.com\n");

	while (1)
	{
		//these little button functions are pretty handy
		scanKeys();

		int held = keysHeld();
		int KeyCDown = keysDown();
		int KeyCUp = keysUp();
		if(KeyCUp)
			KeyUp(KeyCUp);
		if(KeyCDown)
			KeyDown(KeyCDown);

		if (held & KEY_START) break;
		// Camera rotation by touch screen

		if (held & KEY_TOUCH)
		{
			touchRead(&thisXY);
			Controls.TpX = thisXY.px;
			Controls.TpY = thisXY.py;

		}

		//Pausing
		if(Controls.Slt && !TempPausePress){
			PauseGame = !PauseGame;
			TempPausePress = true;
		}else if (!Controls.Slt){
			TempPausePress = false;
		}

		//Updates
		if(PauseGame == false || CanPause == false){
			for (GameObject* OBJ : gameObjects)
			{
				OBJ->Update();
			}
			GameMasterUpdate();
		}
		//Drawing
		//Push our original Matrix onto the stack (save state)
		glPushMatrix();
		DrawGLScene();
		// Pop our Matrix from the stack (restore state)

		for (GameObject* OBJ : gameObjects)
		{
			OBJ->Draw();
		}

		glPopMatrix(1);

		glBegin2D();
			for (GameObject* OBJ : gameObjects)
			{
				OBJ->Draw2DTop();
			}
		glEnd2D();

		// flush to screen
		glFlush(0);

		for (GameObject* ROJ : RemoveObjects)
		{
			//RemoveObjects.swap(RemoveObjects.back(), ROJ);
			//auto it = std::find(RemoveObjects.begin(), RemoveObjects.end(), ROJ);
			//gameObjects.erase(it);
			gameObjects.remove(ROJ);
		}
		RemoveObjects.clear();

		for (GameObject* ROJ : PushObjects)
		{
			gameObjects.push_back(ROJ);
		}
		PushObjects.clear();
		
		//DrawText
		GameMasterDraw();
		swiWaitForVBlank();

		oamUpdate(&oamSub);
		oamClear(&oamSub, 0 ,128);
		SpriteAssetIndex = 0;
	}

	return 0;
}

int DrawGLScene()
{
	// Reset The View

	float x_m, y_m, z_m;
	t16 u_m, v_m;
	float xtrans = -xpos * worldScale;
	float ztrans = -zpos * worldScale;
	float ytrans = -ypos * worldScale;
	int sceneroty = 360 - yrot;

	glLoadIdentity();

	int numQuads;

	glRotatef(lookupdown,1,0,0);
	glRotatef(sceneroty,0,1,0);

	glTranslatef(xtrans, ytrans, ztrans);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	numQuads = Rsector.numQuads;
	// Process Each Triangle
	glBegin(GL_QUAD);
	for (int loop_m = 0; loop_m < numQuads; loop_m++)
	{
			//glNormal3f(0,1,0);
			glColor3f((float)Rsector.Quad[loop_m].color.r/255.0f,(float)Rsector.Quad[loop_m].color.g/255.0f,(float)Rsector.Quad[loop_m].color.b/255.0f);	
			x_m = Rsector.Quad[loop_m].vertex[0].x;
			y_m = Rsector.Quad[loop_m].vertex[0].y;
			z_m = Rsector.Quad[loop_m].vertex[0].z;
			//u_m = sector1.triangle[loop_m].vertex[0].u;
			//v_m = sector1.triangle[loop_m].vertex[0].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3f(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[1].x;
			y_m = Rsector.Quad[loop_m].vertex[1].y;
			z_m = Rsector.Quad[loop_m].vertex[1].z;
			//u_m = sector1.triangle[loop_m].vertex[1].u;
			//v_m = sector1.triangle[loop_m].vertex[1].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3f(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[2].x;
			y_m = Rsector.Quad[loop_m].vertex[2].y;
			z_m = Rsector.Quad[loop_m].vertex[2].z;
			//u_m = sector1.triangle[loop_m].vertex[2].u;
			//v_m = sector1.triangle[loop_m].vertex[2].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3f(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[3].x;
			y_m = Rsector.Quad[loop_m].vertex[3].y;
			z_m = Rsector.Quad[loop_m].vertex[3].z;
			//u_m = sector1.triangle[loop_m].vertex[3].u;
			//v_m = sector1.triangle[loop_m].vertex[3].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3f(x_m,y_m,z_m);
	}
	//glTranslatef(-xtrans, -ytrans, -ztrans);
	glEnd();
	return TRUE;												// Everything Went OK

}

int DrawFileTextTemp(){
	if (nitroFSInit(NULL)) {

		//dirlist("/");
		
		{
			// now, try reading a file to make sure things are working OK.
			FILE* inf = fopen("World.txt","rb");
			if(inf)
			{
				int len;

				fseek(inf,0,SEEK_END);
				len = ftell(inf);
				fseek(inf,0,SEEK_SET);

				printf("\nthe following %d bytes message\nfrom file1.txt is\nbrought to you by fread:\n",len);
				{
					char *entireFile = (char*)malloc(len+1);
					entireFile[len] = 0;
					if(fread(entireFile,1,len,inf) != len)
						printf("savage error reading the bytes from the file!\n");
					else
						printf("%s\n-done-\n",entireFile);
					free(entireFile);
				}

				fclose(inf);
			}
		}

		printf("here is the dirlist once more:\n");
		//dirlist("/");

	} else {
		printf("nitroFSInit failure: terminating\n");
	}
}

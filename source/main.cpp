/********************************************************************************************
 * 		Nehe lesson 10 modification which uses the touch screen to control the camera and dpad
 *		to move the player.

 * 		Author: revo																		*
 *		Updated by revo (from 10b) - added camera moving by touching touch screen
 *
 ********************************************************************************************/

#include <nds.h>
#include <malloc.h>
#include <stdio.h>

#include <filesystem.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "UseHeaders/globals.h"
#include "Mud_pcx.h"
//#include "World_txt.h"


int DrawGLScene();
int DrawFileTextTemp();

float heading;
int32 xpos;
int32 zpos;
int32 ypos = 1024;
float yrot;				// Y Rotation
int walkbiasangle = 0;
float lookupdown = 0;


int	texture[1];			// Storage For 1 Textures (only going to use 1 on the DS for this demo)

//SECTOR sector1;				// Our Model Goes Here:
QSECTOR Rsector;

void GenerateLevel(){
	Rsector.numQuads = 3;

	/*
	Rsector.Quad[0].vertex[0] = {-2000,2000,0};
	Rsector.Quad[0].vertex[1] = {2000,2000,0};
	Rsector.Quad[0].vertex[2] = {2000,-2000,0};
	Rsector.Quad[0].vertex[3] = {-2000,-2000,0};
	*/

	Rsector.Quad[1].vertex[0] = {-2000,0,0};
	Rsector.Quad[1].vertex[1] = {-1000,0,1500};
	Rsector.Quad[1].vertex[2] = {1000,0,1500};
	Rsector.Quad[1].vertex[3] = {2000,0,0};

	Rsector.Quad[2].vertex[0] = {-2000,0,0};
	Rsector.Quad[2].vertex[1] = {2000,0,0};
	Rsector.Quad[2].vertex[2] = {1000,0,-1500};
	Rsector.Quad[2].vertex[3] = {-1000,0,-1500};
}

int main() {

	// Setup the Main screen for 3D
	//consoleDemoInit();
	//DrawFileTextTemp();

	videoSetMode(MODE_0_3D);
	vramSetBankA(VRAM_A_TEXTURE);                        //NEW  must set up some memory for textures
	
	// initialize the 3D engine
	glInit();
	
	// enable textures
	//glEnable(GL_TEXTURE_2D);
	
	// Set our viewport to be the same size as the screen
	glViewport(0,0,255,191);
	
	// setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);
	
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
	glClearColor(0,0,0,31);
	glClearDepth(0x7FFF);
	
	// set the vertex color to white
	glColor3f(1.0,1.0,1.0);

	touchPosition	thisXY;
	touchPosition	lastXY = { 0,0,0,0 };	
	
	GenerateLevel();
	
	printf("      Hello DS World\n");
	printf("     www.devkitpro.org\n");
	printf("   www.drunkencoders.com\n");

	while (1)
	{
		//these little button functions are pretty handy
		scanKeys();

		int held = keysHeld();

		if (held & KEY_START) break;

		if (held & (KEY_LEFT|KEY_Y))
		{
			xpos -= cosLerp(heading)>>5;
			zpos += sinLerp(heading)>>5;
		}
		if (held & (KEY_RIGHT|KEY_A))
		{
			xpos += cosLerp(heading) >> 5;
			zpos -= sinLerp(heading) >> 5;
		}
		if (held & (KEY_DOWN|KEY_B))
		{

			xpos -= cosLerp(heading + degreesToAngle(90)) >> 5;
			zpos += sinLerp(heading + degreesToAngle(90)) >> 5;

			walkbiasangle += degreesToAngle(5);
		}
		if (held & (KEY_UP|KEY_X))
		{
			xpos += cosLerp(heading + degreesToAngle(90)) >> 5;
			zpos -= sinLerp(heading + degreesToAngle(90)) >> 5;

			if (walkbiasangle <= 0)
			{
				walkbiasangle = DEGREES_IN_CIRCLE;
			}
			else
			{
				walkbiasangle -= degreesToAngle(5);
			}
		}

		// Camera rotation by touch screen

		if (held & KEY_TOUCH)
		{
			touchRead(&thisXY);

			int16 dx = thisXY.px - lastXY.px;
			int16 dy = thisXY.py - lastXY.py;

			// filtering measurement errors
			if (dx<20 && dx>-20 && dy<20 && dy>-20)
			{
				if(dx>-3&&dx<3)
					dx=0;

				if(dy>-2&&dy<2) dy=0;

					lookupdown = clip(lookupdown - degreesToAngle(dy), -8000, 8000);

					heading += degreesToAngle(dx);
					yrot = heading;
			}

			lastXY = thisXY;
		}

		//Push our original Matrix onto the stack (save state)
		glPushMatrix();

		DrawGLScene();

		// Pop our Matrix from the stack (restore state)
		glPopMatrix(1);

		// flush to screen
		glFlush(0);

	}

	return 0;
}

int DrawGLScene()											// Here's Where We Do All The Drawing
{
											// Reset The View

	v16 x_m, y_m, z_m;
	t16 u_m, v_m;
	int32 xtrans = -xpos;
	int32 ztrans = -zpos;
	int32 ytrans = -ypos;
	int sceneroty = DEGREES_IN_CIRCLE - (int)yrot;

	glLoadIdentity();

	int numQuads;

	glRotatef32i((int)lookupdown,(1<<12),0,0);
	glRotatef32i(sceneroty,0,(1<<12),0);

	glTranslatef32(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	numQuads = Rsector.numQuads;


	// Process Each Triangle
	for (int loop_m = 0; loop_m < numQuads; loop_m++)
	{
		glBegin(GL_QUADS);
			glNormal(NORMAL_PACK( 0, 0, 1<<10));
			glColor3f(0.1f,0.5f,0.1f);	
			x_m = Rsector.Quad[loop_m].vertex[0].x;
			y_m = Rsector.Quad[loop_m].vertex[0].y;
			z_m = Rsector.Quad[loop_m].vertex[0].z;
			//u_m = sector1.triangle[loop_m].vertex[0].u;
			//v_m = sector1.triangle[loop_m].vertex[0].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3v16(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[1].x;
			y_m = Rsector.Quad[loop_m].vertex[1].y;
			z_m = Rsector.Quad[loop_m].vertex[1].z;
			//u_m = sector1.triangle[loop_m].vertex[1].u;
			//v_m = sector1.triangle[loop_m].vertex[1].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3v16(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[2].x;
			y_m = Rsector.Quad[loop_m].vertex[2].y;
			z_m = Rsector.Quad[loop_m].vertex[2].z;
			//u_m = sector1.triangle[loop_m].vertex[2].u;
			//v_m = sector1.triangle[loop_m].vertex[2].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3v16(x_m,y_m,z_m);

			x_m = Rsector.Quad[loop_m].vertex[3].x;
			y_m = Rsector.Quad[loop_m].vertex[3].y;
			z_m = Rsector.Quad[loop_m].vertex[3].z;
			//u_m = sector1.triangle[loop_m].vertex[3].u;
			//v_m = sector1.triangle[loop_m].vertex[3].v;
			//glTexCoord2t16(u_m,v_m); 
			glVertex3v16(x_m,y_m,z_m);
		glEnd();
	}
	return TRUE;										// Everything Went OK

}

int DrawFileTextTemp(){
		consoleDemoInit();
	
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

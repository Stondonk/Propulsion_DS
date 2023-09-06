#include "UseHeaders/LevelLoader.h"
#include "UseHeaders/globals.h"
#include "nds.h"
#include <malloc.h>

void LoadLevel(std::string file){
	/*
	int HexAmount = 16;
	int h = 0;
	for (int h = 0; h < HexAmount; h++)
	{
		HexTile* TempTile = new HexTile();
		TempTile->x = 0;
		TempTile->y = h*0.5;
		TempTile->z = h*2;
		TempTile->scale = 1;
		Hexs.push_back(TempTile);
	}
	*/
	
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
				
				char *entireFile = (char*)malloc(len+1);
				if(fread(entireFile,1,len,inf) == len){
					if(entireFile[0] == 'P'){
						HexTile* TempTile = new HexTile();
						TempTile->x = 0;
						TempTile->y = -1;
						TempTile->z = 0;
						TempTile->scale = 1;
						Hexs.push_back(TempTile);
					}
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
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
			FILE* inf = fopen(file.c_str(),"rb");
			if(inf)
			{
				int len;
				fseek(inf,0,SEEK_END);
				len = ftell(inf);
				fseek(inf,0,SEEK_SET);
				
				char *entireFile = (char*)malloc(len+1);
				std::list<std::string> AssetList;
				if(fread(entireFile,1,len,inf) == len){
					int i = 0;
					std::string TempLine = "";
					for ( i = 0; i < sizeof(entireFile); i++)
					{
						if(entireFile[i] != ' '){
							TempLine += entireFile[i];}
						else if(entireFile[i] == ' '){
							AssetList.push_back(TempLine);
							printf(("BALSS"));
							TempLine = "";
						}
					}
				}

				std::string Nums;
				std::list<float> NumSd;
				std::list<std::string> SequenceString;
				for (std::string CurrentLine : AssetList)
				{
					if(CurrentLine[0] == 'H'){
						HexTile* TempHex = new HexTile();
						TempHex->scale = 1;
						int LC = 1;
						for (LC = 1; LC < CurrentLine.size(); LC++)
						{
							if(CurrentLine[LC] != ',')
								Nums+=(CurrentLine[LC]);
							else{
								printf(("\x1b[1;" + Nums).c_str());
								NumSd.push_back(stof(Nums));
								SequenceString.push_back(Nums);
								Nums.clear();
							}
						}
						int Idx = 0;
						for (float r: NumSd)
						{
							//Bad implmentation fixes variable Override Problem
							switch (Idx)
							{
								case 0:
								TempHex->x = r;break;
								case 1:
								TempHex->y = r;break;
								case 2:
								TempHex->z = r; break;
								case 3:
								TempHex->scale = r;break;
								case 4:
								TempHex->Type = r;break;
								case 5:
								TempHex->ID = r;break;
							}
							Idx++;
							
						}
						Hexs.push_back(TempHex);
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
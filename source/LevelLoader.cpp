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
					for ( i = 0; i < strlen(entireFile); i++)
					{
						if(entireFile[i] != '\n'){
							TempLine += entireFile[i];}
						else if(entireFile[i] == '\n'){
							AssetList.push_back(TempLine);
							//printf(("Enter"));
							TempLine.clear();
						}
						
					}
				}

				std::string Nums;
				std::vector<float> NumSd;
				std::list<std::string> SequenceString;
				for (std::string CurrentLine : AssetList)
				{
					if(CurrentLine[0] == 'H'){
						HexTile* TempHex = new HexTile();
						TempHex->scale = 1;
						NumSd.clear();
						SequenceString.clear();
						Nums.clear();
					
						int LC = 1;
						for (LC = 1; LC < CurrentLine.size(); LC++)
						{
							if(CurrentLine[LC] != ',')
								Nums+=(CurrentLine[LC]);
							else{
								NumSd.push_back(stof(Nums));
								SequenceString.push_back(Nums);
								Nums.clear();
							}
						}
						TempHex->x = NumSd[0];
						TempHex->y = NumSd[1];
						TempHex->z = NumSd[2];
						NumSd.clear();
						SequenceString.clear();
						Nums.clear();
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

	GenerateLevel();
}

void GenerateLevel(){
	
	//Rsector.numQuads = 6;
	//int NumOfTris = 4;
	//sector1.Triangle = (TRIANGLE*)malloc(NumOfTris*sizeof(TRIANGLE));
	//sector1.numTriangles = NumOfTris;

	int NumOfQuads = (int)sizeof(Hexs);
	Rsector.Quad = (QUAD*)malloc((NumOfQuads)*sizeof(QUAD));
	Rsector.numQuads = NumOfQuads;

	/*
	Rsector.Quad[0].vertex[0] = {-2000,2000,0};
	Rsector.Quad[0].vertex[1] = {2000,2000,0};
	Rsector.Quad[0].vertex[2] = {2000,-2000,0};
	Rsector.Quad[0].vertex[3] = {-2000,-2000,0};
	*/

	int i = 0;
	//int lengthOfT = (Rsector.numQuads / 2);
	for (HexTile* Hex : Hexs)
	{
		int distance = i * 2;
		float x = Hex->x, y = Hex->y, z = Hex->z;
		float Scale = Hex->scale;
		int Point = ((i) * 2);
		Color color = HexColors[rand()%4];

		Rsector.Quad[Point].vertex[0] = {((-1 * Scale) + x) * worldScale,(y) * worldScale,(0 + z) * worldScale};
		Rsector.Quad[Point].vertex[1] = {((-0.5f * Scale) + x) * worldScale,(y) * worldScale,((0.75f * Scale) + z) * worldScale};
		Rsector.Quad[Point].vertex[2] = {((0.5f * Scale) + x) * worldScale,(y) * worldScale,((0.75f * Scale) + z) * worldScale};
		Rsector.Quad[Point].vertex[3] = {((1 * Scale) + x) * worldScale,(y) * worldScale,(0 + z) * worldScale};

		Rsector.Quad[Point + 1].vertex[0] = {((-1 * Scale) + x) * worldScale,(y) * worldScale,(0 + z) * worldScale};
		Rsector.Quad[Point + 1].vertex[3] = {((1 * Scale) + x) * worldScale,(y) * worldScale,(0 + z) * worldScale};
		Rsector.Quad[Point + 1].vertex[2] = {((0.5f * Scale) + x) * worldScale,(y) * worldScale,((-0.75f*Scale) + z) * worldScale};
		Rsector.Quad[Point + 1].vertex[1] = {((-0.5f * Scale) + x) * worldScale,(y) * worldScale,((-0.75f*Scale) + z) * worldScale};

		Rsector.Quad[Point].color = color;
		Rsector.Quad[Point+1].color = color;
	}

	gameObjects.push_back(new Player());
}
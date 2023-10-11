#include <nds/memory.h>
#include <nds/system.h>
#include <nds/card.h>

#include <fat.h>
#include <filesystem.h>

#include "UseHeaders/levelFile.h"

#include "UseHeaders/LevelLoader.h"
#include "UseHeaders/globals.h"
#include "UseHeaders/gameMaster.h"
#include "nds.h"
#include <malloc.h>

constexpr unsigned int string2int(const char* str, int h = 0)
{
    // DJB Hash function
    // not my code but can't remember where I got it from
    return !str[h] ? 5381 : (string2int(str, h+1)*33) ^ str[h];
}

void LoadLevelTransition(std::string file, float Start){
	 if(Trasnitionlocation == ""){
        TransitionTime = Start + 1;
        Trasnitionlocation = file;
    }
}

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
	//resetVariables
	CanPause = false;
	GameMasterEnable = false;
	Hexs.clear();
	PauseTimer = false;
	//gameObjects.clear();
	RemoveObjects.clear();
	RemoveObjects = gameObjects;

	//Fog Reset
	glEnable(GL_FOG);
	glFogShift(2);
	glFogColor(0,0,0,10);
	for(int i=0;i<32;i++)
		glFogDensity(i,i*2);
	glFogDensity(31,127);
	glFogOffset(0x6000);
	
	GameMasterReset();

    if (nitroFSInit(NULL)) {
		//dirlist("/");
		
		
			// now, try reading a file to make sure things are working OK.
			FILE* inf = fopen((file).c_str(),"rt");
			CurrentStage = file;
			std::list<std::string> AssetList;
			if(inf)
			{

				int len;
				fseek(inf,0,SEEK_END);
				len = ftell(inf);
				fseek(inf,0,SEEK_SET);
				
				char *entireFile = (char*)malloc(len+1);
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
				
				
				//free(entireFile);
				fclose(inf);
				//free(inf);
				}

			for (std::string CurrentLine : AssetList)
			{
				std::string Nums;
				std::vector<float> NumSd;
				std::vector<std::string> SequenceString;
				int LC = 1;
				for (LC = 1; LC < CurrentLine.size(); LC++)
				{
					if(CurrentLine[LC] != ',')
						Nums+=(CurrentLine[LC]);
					else{
						//NumSd.push_back(stof(Nums));
						SequenceString.push_back(Nums);
						Nums.clear();
					}
				}

				if(CurrentLine[0] == 'O'){
					
					switch (string2int(SequenceString[0].c_str()))
					{
						//All spawnable entities
						//Player
						case string2int("Player") : {
							Player* TempPL = new Player();
							TempPL->plx = stof(SequenceString[1]);
							TempPL->ply = stof(SequenceString[2]);
							TempPL->plz = stof(SequenceString[3]);
							TempPL->RotY = stof(SequenceString[4]);
							gameObjects.push_back(TempPL);
						} break;
						//extra
						case string2int("Menu") : {
							MainMenu* TempMen = new MainMenu();
							TempMen->plx = 0;
							TempMen->ply = 0;
							TempMen->plz = 0;
							TempMen->RotY = 0;
							gameObjects.push_back(TempMen);
						} break;
						case string2int("Gamemaster") : {
							CanPause = true;
							GameMasterEnable = true;
						} break;
						case string2int("BGC") : {
							glClearColor(stoi(SequenceString[1]),stoi(SequenceString[2]),stoi(SequenceString[3]),31);
						}break;
						case string2int("NoFog") : {
							//FOG RESET
							glDisable(GL_FOG);
						}break;
						case string2int("Goal") : {
							GoalOBJ* TempGol = new GoalOBJ();
							TempGol->plx = stof(SequenceString[1]);
							TempGol->ply = stof(SequenceString[2]);
							TempGol->plz = stof(SequenceString[3]);
							TempGol->RotY = stof(SequenceString[4]);
							TempGol->FileLocation = (SequenceString[5]);
							gameObjects.push_back(TempGol);
						} break;
					};
							
				}
				else if(CurrentLine[0] == 'H'){
					
					HexTile* TempHex = new HexTile();
					TempHex->x = stof(SequenceString[0]);
					TempHex->y = stof(SequenceString[1]);
					TempHex->z = stof(SequenceString[2]);
					TempHex->scale = stof(SequenceString[3]);
					TempHex->Type = stoi(SequenceString[4]);
					Hexs.push_back(TempHex);
				}
				//delete CurrentLine.c_str();
			}
			//Sub screen color reset
			SetSubBgColorf({0,0,0});
			

		printf("here is the dirlist once more:\n");
		//dirlist("/");

	} else {
		printf("nitroFSInit failure: terminating\n");
	}
	if(Hexs.size() > 0)
		GenerateLevel();
	else{
		Rsector.Quad = 0;
		Rsector.numQuads = 0;
	}

}

void LoadHeaderLevel(std::string file){
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
	//resetVariables
	CurrentStage = file;
	
	CanPause = false;
	GameMasterEnable = false;
	Hexs.clear();
	PauseTimer = false;
	//gameObjects.clear();
	RemoveObjects.clear();
	RemoveObjects = gameObjects;

	//Fog Reset
	glEnable(GL_FOG);
	glFogShift(2);
	glFogColor(0,0,0,10);
	for(int i=0;i<32;i++)
		glFogDensity(i,i*2);
	glFogDensity(31,127);
	glFogOffset(0x6000);
	
	GameMasterReset();

    if (nitroFSInit(NULL)) {
		//dirlist("/");
		std::string CurrentFile = "";
		for (levelFile CurrentLevel : LevelFiles)
		{
			if(CurrentLevel.FileName == file)
				CurrentFile = CurrentLevel.FileData;
		}

		std::vector<std::string> AssetList;
			
		int i = 0;
		std::string TempLine = "";
		for ( i = 0; i < strlen(CurrentFile.c_str()); i++)
		{
			if(CurrentFile[i] != ' '){
			TempLine += CurrentFile[i];}
			else if(CurrentFile[i] == ' '){
				AssetList.push_back(TempLine);
				//printf(("Enter"));
			TempLine.clear();
			}
						
		}
			// now, try reading a file to make sure things are working OK.


			for (std::string CurrentLine : AssetList)
			{
				std::string Nums;
				std::vector<float> NumSd;
				std::vector<std::string> SequenceString;
				int LC = 1;
				for (LC = 1; LC < CurrentLine.size(); LC++)
				{
					if(CurrentLine[LC] != ',')
						Nums+=(CurrentLine[LC]);
					else{
						//NumSd.push_back(stof(Nums));
						SequenceString.push_back(Nums);
						Nums.clear();
					}
				}

				if(CurrentLine[0] == 'O'){
					
					switch (string2int(SequenceString[0].c_str()))
					{
						//All spawnable entities
						//Player
						case string2int("Player") : {
							Player* TempPL = new Player();
							TempPL->plx = stof(SequenceString[1]);
							TempPL->ply = stof(SequenceString[2]);
							TempPL->plz = stof(SequenceString[3]);
							TempPL->RotY = stof(SequenceString[4]);
							gameObjects.push_back(TempPL);
						} break;
						//extra
						case string2int("Menu") : {
							MainMenu* TempMen = new MainMenu();
							TempMen->plx = 0;
							TempMen->ply = 0;
							TempMen->plz = 0;
							TempMen->RotY = 0;
							gameObjects.push_back(TempMen);
						} break;
						case string2int("Gamemaster") : {
							CanPause = true;
							GameMasterEnable = true;
						} break;
						case string2int("BGC") : {
							glClearColor(stoi(SequenceString[1]),stoi(SequenceString[2]),stoi(SequenceString[3]),31);
						}break;
						case string2int("NoFog") : {
							//FOG RESET
							glDisable(GL_FOG);
						}break;
						case string2int("Goal") : {
							GoalOBJ* TempGol = new GoalOBJ();
							TempGol->plx = stof(SequenceString[1]);
							TempGol->ply = stof(SequenceString[2]);
							TempGol->plz = stof(SequenceString[3]);
							TempGol->RotY = stof(SequenceString[4]);
							TempGol->FileLocation = (SequenceString[5]);
							gameObjects.push_back(TempGol);
						} break;
					};
							
				}
				else if(CurrentLine[0] == 'H'){
					
					HexTile* TempHex = new HexTile();
					TempHex->x = stof(SequenceString[0]);
					TempHex->y = stof(SequenceString[1]);
					TempHex->z = stof(SequenceString[2]);
					TempHex->scale = stof(SequenceString[3]);
					TempHex->Type = stoi(SequenceString[4]);
					Hexs.push_back(TempHex);
				}
				//delete CurrentLine.c_str();
			}
			//Sub screen color reset
			SetSubBgColorf({0,0,0});
			

		printf("here is the dirlist once more:\n");
		//dirlist("/");

	} else {
		printf("nitroFSInit failure: terminating\n");
	}
	if(Hexs.size() > 0)
		GenerateLevel();
	else{
		Rsector.Quad = 0;
		Rsector.numQuads = 0;
	}
}

void GenerateLevel(){
	
	//Rsector.numQuads = 6;
	//int NumOfTris = 4;
	//sector1.Triangle = (TRIANGLE*)malloc(NumOfTris*sizeof(TRIANGLE));
	//sector1.numTriangles = NumOfTris;
	int offSetHex = 0;
	if(sizeof(Hexs) < 5)
		offSetHex = 1;
	int NumOfQuads = (int)(sizeof(Hexs) * 2) - offSetHex;
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
		Color color = HexColors[Hex->Type];

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
		i++;
	}

	//gameObjects.push_back(new Player());
}
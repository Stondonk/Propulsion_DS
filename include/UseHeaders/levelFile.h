#pragma once
#include <nds.h>
#include <malloc.h>
#include <stdio.h>

#include <filesystem.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<iostream>
#include <vector>
#include <list>
#include "globals.h"

struct levelFile
{
    std::string FileName = "";
    std::string FileData = "";
};


std::vector<levelFile> LevelFiles = {
    {"MenuWorld.txt","OMenu, OBGC,0,0,0, ONoFog, "},
    {"World1.txt","OPlayer,0,0,0,180, OGamemaster, H0,-1,0,1,0, H0,-0.85,2,1,0, H0,-0.85,3,1,0, H1.35,-0.50,5,1,0, H0,0,7,1,0, H2,0.125,9,1,0, H0,0.25,11,1,0, H-2,0.25,13,1,0, OGoal,-2,0.5,13,0,World2.txt, OBGC,15,20,30, "},
    {"World2.txt","OPlayer,0,0,0,0, OGamemaster, H0,-1,0,2,1, H0,-0.85,-3,1,1, H0,-0.85,-5,1,2, H0,1,-7,1,1, H1.5,1,-8.5,1,1, H4,1,-8.5,1,2, H7,1.25,-8.5,1,1, H9,1.25,-6.5,1,1, H9,1.25,-4.5,1,1, OGoal,9,1.5,-4.5,0,World3.txt, OBGC,17,29,30, "},
    {"World3.txt","OPlayer,0,0,0,0, OGamemaster, H0,-1,0,2,0, H0,-1,-4,1,3, H2,-1,-6,1,0, H5,-0.5,-6,1,2, H9,-0.5,-6,2,0, H9,-0.5,-2,1,2, H9,0,0,1,0, OGoal,9,0.25,0,0,World4.txt, OBGC,15,20,30, "},
    {"World4.txt","OPlayer,0,0,0,0, OGamemaster, H0,-1,0,2,0, H0,-1,-2.25,1,3, H0,-0.5,-4.5,1,2, H0,0,-7,1,3, H0,0.5,-9.25,1,2, H-3,0.5,-9.25,1,1, H-6,0.8,-9.25,1,1, H-9,0.8,-6.25,1,1, H-9,1,-3.25,1,2, H-9,1,-1,1,0, OGoal,-9,1.25,-1,0,WorldV.txt, OBGC,15,20,30, "},
    {"WorldV.txt","OPlayer,0,0,0,0, OGamemaster, H0,-1,0,1,0, H0,0.5,-2,1,2, H0,0,0,1,3, H0,0,2,1,0, H0,1.5,-4,1,1, H0,1.5,-6,1,1, H2,2.5,-4,1,1, H2,2,-6,1,1, H2,2.5,-2,1,3, H2,3,0,1,2, H2,3.5,2,1,0, OGoal,2,3.75,2,0,MenuWorld.txt, OBGC,15,20,30, "},
};

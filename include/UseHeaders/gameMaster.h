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
#include "gameObject.h"
#include "Player.h"
#include "rocket.h"
#include "Atlas.h"

void GameMasterDraw();
void GameMasterUpdate();
void GameMasterReset();
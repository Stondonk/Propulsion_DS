#include "UseHeaders/gameMaster.h"
#include "UseHeaders/globals.h"
#include <math.h>

using namespace std;

float Time = 0;

void GameMasterDraw(){
    int mintues = (round(Time) / 60);
    int seconds = (round(Time) - (mintues * 60));
    std::string buffer0 = "";
    if(seconds <= 9)
        buffer0 = "0";
	DrawText(std::to_string(mintues) + "." + buffer0 + std::to_string(seconds), 0, 128,88);
}
void GameMasterUpdate(){
    Time+=0.013;
}
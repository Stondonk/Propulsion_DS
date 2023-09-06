#include "UseHeaders/gameMaster.h"
#include "UseHeaders/globals.h"
#include <math.h>

using namespace std;

float Time = 0;

void GameMasterDraw(){
    int mintues = (round(Time) / 60);
    int seconds = (round(Time) - (mintues * 60));
    int milliSecs = round((Time - round(Time)) * 100);
    std::string buffer0 = "", buffer1 = "";
    if(seconds <= 9)
        buffer0 = "0";
    if(milliSecs <= 9)
        buffer1 = "0";
    DrawSprite16(0, (int)(256 * ((float)milliSecs / 100.0)) + 128, 82 + (sin((float)milliSecs / 4) * 16));
	DrawText(std::to_string(mintues) + "." + buffer0 + std::to_string(seconds), 0, 128,88);
}
void GameMasterUpdate(){
    Time+=0.013;
}
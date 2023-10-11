#include "UseHeaders/gameMaster.h"
#include "UseHeaders/globals.h"
#include <math.h>

using namespace std;

float Time = 0;
bool PauseTimer = false;
Vector2 milliPoint = {0,0};
float MilGrav = 0;

bool Settings =false;
bool Tapped = false;

void GameMasterDraw(){
    if(!PauseGame){
        int mintues = (round(Time) / 60);
        int seconds = (round(Time) - (mintues * 60));
        int milliSecs = round((Time - round(Time)) * 100);
        std::string buffer0 = "", buffer1 = "";
        if(seconds <= 9)
            buffer0 = "0";
        if(milliSecs <= 9)
            buffer1 = "0";
        if(!PauseTimer){
            milliPoint.x = (256 * ((float)milliSecs / 100.0)) + 128;
            milliPoint.y = 82 + (sin((float)milliSecs / 4) * 16);
            MilGrav = 0;
        }else{
            milliPoint.y = clip(milliPoint.y + MilGrav, -16,208);
            MilGrav += 0.013*7;
        }
        DrawSprite16(0, (int)milliPoint.x, (int)milliPoint.y,false,false);
        DrawText(std::to_string(mintues) + "." + buffer0 + std::to_string(seconds), 0, 128,88);
    }else{
        if(!Settings)
            DrawSprite16(21,120,80,false,false);
        else{
            DrawSprite16(29+((int)InvertLook),112,8,false,false);
            DrawSprite16(31,128,8,false,false);
        }
        DrawSprite16(22,8,168,false,false);
        DrawSprite16(28,SCREEN_WIDTH - 24,168,false,false);
    }
}
void GameMasterUpdate(){
    if(!PauseGame && !PauseTimer){
        Time+=0.013;
        Settings = false;
    }else{
        if(Controls.Touching && !Tapped){
            if(Controls.TpX < 32 && Controls.TpY > 160){ //exit
                LoadLevelTransition("MenuWorld.txt",0);Settings=false;}
            else if(Controls.TpX > SCREEN_WIDTH - 32 && Controls.TpY > 160){
                Settings = !Settings; Tapped = true;}
            else{ //resume
                if(Settings == false)
                    PauseGame = false;
                else{
                    //SettingsMenu
                    if(Controls.TpY > 0 && Controls.TpY < 32){
                        InvertLook = !InvertLook; Tapped = true;}

                }
            }
        }
        if(!Controls.Touching)
            Tapped = false;
    }
}

void GameMasterReset(){
    Time = 0;
}
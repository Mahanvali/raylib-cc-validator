#include <iostream>
#include <string>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui.h"
using namespace std;

const int screenWidth = 400;
const int screenHeight = 200;

char CCchar[128] = "\0";
char Output[128] = "\0";

void Update();
bool IsNumberString(const string& s);

int main(){
    InitWindow(screenWidth, screenHeight, "Credit Card Validator");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        Update();
        BeginDrawing();
            DrawText("INPUT", 20, 30, 10, RED);
            DrawText("OUTPUT", 20, 90, 10, RED);
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
}

void Update(){
    Rectangle CCInputRec = {80, 20, 220, 30};
    Rectangle CCOutputRec = {80, 80, 220, 30};
    GuiTextBox(CCInputRec, CCchar, 128, true);
    GuiTextBox(CCOutputRec, Output, 128, false);

    string ccString(CCchar);
    //  LUHNS ALGORITHM
    int len = ccString.length();
    int doubleEvenSum = 0;

    // Step 1 is to double every second digit, starting from the right. If it
    // results in a two digit number, add both the digits to obtain a single
    // digit number. Finally, sum all the answers to obtain 'doubleEvenSum'.   
        
        for (int i = len - 2; i >= 0; i = i - 2) {
            int dbl = ((ccString[i] - 48) * 2);
            if (dbl > 9) {
                dbl = (dbl / 10) + (dbl % 10);
            }
            doubleEvenSum += dbl;
        }
        
    // Step 2 is to add every odd placed digit from the right to the value
    // 'doubleEvenSum'.
        
    for (int i = len - 1; i >= 0; i = i - 2) {
        doubleEvenSum += (ccString[i] - 48);
    }

    if(IsKeyPressed(KEY_ENTER)){
        if(!IsNumberString(ccString)){
            sprintf(Output, "%s", "Please do not include any characters!");
        } else {
            sprintf(Output, "%s", doubleEvenSum % 10 == 0 ? "Valid!" : "Invalid!");
        }
    }
}

bool IsNumberString(const string& s)
{
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] < '0' || s[i] > '9')
        return false;
    }
    return true;
}

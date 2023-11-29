/***************include requsites****************/

//#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/raylib.h"
#include <time.h>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "sandf.h"


/***************Window size****************/
#define WINDOW_X 1800
#define WINDOW_Y 900



int main(){


/******Global variables*****/
Color clrpicked;
float Nsize = 10.f;
float Nlength = 10.f;
float Nspeed = 3.f;
float zoomMult = 1.f;
float zoomMultF = 100.f;

int toggle = 0;



float angle = 0.0f;
node * head = (node *)malloc(sizeof(node));//define head of linked list
node * tail = head;
head->prev = NULL;
head->next = NULL;
node * current = head;
/*------------------------------------*/

InitWindow(WINDOW_X, WINDOW_Y, "I SPIN YOU RIGHT ROUND BABY RIGHT ROUND");

head->circle = newCricle((Color){170,170,170,255},4,0,GetScreenWidth()/2,GetScreenHeight()/2,0.f);//give head (:P) a circle at the middle of the screen



srand(time(NULL));


SetTargetFPS(60);
        //clear both buffers
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();


    while (!WindowShouldClose())
    {   
        /*------Gui s**t-------*/
        GuiColorPicker((Rectangle){20,10,110,110},"select color",&clrpicked);

        clrpicked.a = 255; // for some reason when i use the mingw complier alpha is always zero

        GuiToggleSlider((Rectangle){20,(float)GetScreenHeight() - 60,130,20}, "TRACE OFF;TRACE ON", &toggle);                            
        GuiSliderBar((Rectangle){20,(float)GetScreenHeight() - 30,130,20},"","Zoom",&zoomMultF,1.f,300.f);

        DrawText("q -> adds random circle \n w -> deletes last circle \n Esc to exit", GetScreenWidth() - 200, 20, 15, LIGHTGRAY);

        DrawText("Trace funcionalty is a bit buggy and will flicker",160,(float)GetScreenHeight() - 57, 15, LIGHTGRAY);


        GuiSliderBar((Rectangle){20,130,110,20},"","Size",&Nsize,5.f,50.f);
        GuiSliderBar((Rectangle){20,160,110,20},"","Rod Length",&Nlength,5.f,50.f);
        GuiSliderBar((Rectangle){20,190,110,20},"","Speed",&Nspeed,-30.f,30.f);
        if(GuiButton((Rectangle){20,220,130,20},"Add Circle")){
            appEnd(&tail,newCricle(clrpicked,Nsize,Nlength,tail->circle->x,tail->circle->y,Nspeed));
        }
        if(GuiButton((Rectangle){20,250,130,20},"Add Random Circle")){
            addRandCircle(&tail);
            }
        if(GuiButton((Rectangle){20,280,130,20},"Remove Circle")){
            delEnd(&tail);
        }
        if(GuiButton((Rectangle){20,310,130,20},"Add 5 Random Circles")){
            for(int i = 0; i<5;i++){
            addRandCircle(&tail);
            }
        }

        if(GuiButton((Rectangle){20,(float)GetScreenHeight() - 90,130,20},"Clear Trace")){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();
            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();

        }

        if(GuiButton((Rectangle){20,340,130,20},"Remove 5 Circles")){
            for(int i = 0; i<5;i++){
                if(tail != head){
                delEnd(&tail);
                }
            }
        }
        /*-----------------------*/

        current = head; // set current pointer to head

        zoomMult = zoomMultF/100;// this so the zoom slider is smoother

        /*Advance angle if its not bigger than 360 if so go back to zero */
        if(angle>=360.0f){
            angle = angle - 359.998f;
        }
        else {
            angle += 0.002f;
        }


        
        /*Drawing part*/
        BeginDrawing();

        if(!toggle)ClearBackground(RAYWHITE);
        
        DrawCircle(current->circle->x,current->circle->y,current->circle->size,current->circle->color);

            if(current->next != NULL){
                current->next->circle->x = current->circle->x;
                current->next->circle->y = current->circle->y;
            }
            current = current->next;

        while(current != NULL){     //iterate trough linked list
        
            double endx = (current->circle->length + current->circle->size)*sin(angle*current->circle->speed)*zoomMult;
            double endy = (current->circle->length + current->circle->size)*cos(angle*current->circle->speed)*zoomMult;
            if(!toggle){
            DrawCircle(current->circle->x, current->circle->y, current->circle->size*zoomMult + 2, BLACK);
            }
            DrawCircle(current->circle->x, current->circle->y, current->circle->size*zoomMult, current->circle->color);
            if(current->next != NULL){
                int endendx = (int)(current->circle->x + endx + current->next->circle->size*sin(angle*current->circle->speed)*zoomMult);
                int endendy = (int)(current->circle->y + endy + current->next->circle->size*cos(angle*current->circle->speed)*zoomMult);
                current->next->circle->x = endendx;
                current->next->circle->y = endendy;
                DrawLine(current->circle->x,current->circle->y, endendx, endendy ,BLACK);
                
            }


            current = current->next;
        }

        EndDrawing();

        if(IsKeyPressed(KEY_Q)){
            addRandCircle(&tail);
        }
        if(IsKeyPressed(KEY_W)){
            delEnd(&tail);
        }
        
    }

    CloseWindow();

    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/raylib.h"
#include <time.h>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#define WINDOW_X 1800
#define WINDOW_Y 900

typedef struct Circle{
    Color color;
    float length;
    float size;
    int x;
    int y;
    float speed;

}Circle ;

typedef struct node {
    Circle* circle;
    struct node * prev;
    struct node * next;
} node;



void appEnd(node **tail_t,Circle* data);
void delEnd(node **tail);
void addRandCircle(node** tail);
Circle* newCricle(Color color, float size,float length, int x,int y,float speed);

int main(){

Color clrpicked;
float Nsize = 10.f;
float Nlength = 10.f;
float Nspeed = 3.f;
float zoomMult = 1.f;
float zoomMultF = 100.f;



srand(time(NULL));

InitWindow(WINDOW_X, WINDOW_Y, "I SPIN YOU RIGHT ROUND BABY RIGHT ROUND");
SetTargetFPS(60);
float angle = 0.0f;
node * head = (node *)malloc(sizeof(node));
node * tail = head;
head->prev = NULL;
head->next = NULL;
node * current = head;
head->circle = newCricle((Color){170,170,170,255},4,0,GetScreenWidth()/2,GetScreenHeight()/2,0.f);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();


    while (!WindowShouldClose())
    {   

        GuiColorPicker((Rectangle){20,10,110,110},"select color",&clrpicked);
        
        GuiSliderBar((Rectangle){20,GetScreenHeight() - 30,110,20},"","Zoom",&zoomMultF,1.f,300.f);
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

        if(GuiButton((Rectangle){20,340,130,20},"Remove 5 Circles")){
            for(int i = 0; i<5;i++){
                if(tail != head){
                delEnd(&tail);
                }
            }
        }

        zoomMult = zoomMultF/100;
        if(angle>=360.0f){
            angle = angle + 359.998f;
        }
        else {
            angle += 0.002f;
        }
        current = head;

        BeginDrawing();
        //ClearBackground(RAYWHITE);
        
        DrawCircle(current->circle->x,current->circle->y,current->circle->size,current->circle->color);

            if(current->next != NULL){
                current->next->circle->x = current->circle->x;
                current->next->circle->y = current->circle->y;
            }
            current = current->next;

        while(current != NULL){
        
            double endx = (current->circle->length + current->circle->size)*sin(angle*current->circle->speed)*zoomMult;
            double endy = (current->circle->length + current->circle->size)*cos(angle*current->circle->speed)*zoomMult;
            
            DrawCircle(current->circle->x, current->circle->y, current->circle->size*zoomMult + 2, BLACK);
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
        if(IsKeyPressed(KEY_Q)){
            addRandCircle(&tail);
        }
        if(IsKeyPressed(KEY_W)){
            delEnd(&tail);
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;

}


Circle* newCricle(Color color, float size,float length, int x,int y,float speed){
    Circle* newcirc = (Circle *)malloc(sizeof(Circle));
    newcirc->color = color;
    newcirc->size = size;
    newcirc->length = length + size;
    newcirc->x = x;
    newcirc->y = y;
    newcirc->speed = speed;
    return newcirc;
}

void delEnd(node **tail){
    node * temp = (*tail);
    if((*tail)->prev == NULL);
    else{
        (*tail) = (*tail)->prev;
        (*tail)->next = NULL;
        free(temp->circle);
        free(temp);
    }
}

void appEnd(node **tail_t, Circle* data){
    (*tail_t)->next = (node *)malloc(sizeof(node));
    node * prev = (*tail_t);
    (*tail_t) = (*tail_t)->next;
    (*tail_t)->prev = prev;
    (*tail_t)->circle = data;
    (*tail_t)->next = NULL;
}

void addRandCircle(node** tail){
    int r = (int)(((float)rand()/(float)(RAND_MAX)) * 255);
            int g = (int)(((float)rand()/(float)(RAND_MAX)) * 255);
            int b = (int)(((float)rand()/(float)(RAND_MAX)) * 255);
            float size = (((float)rand()/(float)(RAND_MAX)) * 20.f);
            float length = (((float)rand()/(float)(RAND_MAX)) * 10.f + 4.f);
            float speed = (((float)rand()/(float)(RAND_MAX)) * 40.f -20.f);

            appEnd(tail,newCricle((Color){r,g,b,255},size,length,(*tail)->circle->x,(*tail)->circle->y,speed));
}
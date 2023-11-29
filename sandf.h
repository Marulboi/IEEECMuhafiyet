#pragma once
#include <stdlib.h>
#include <math.h>
#include "include/raylib.h"


/****Circle Type****/
typedef struct Circle{
    Color color;
    float length;
    float size;
    int x;
    int y;
    float speed;

}Circle ;


/*********Node Type of doubly linked list********/
typedef struct node {
    Circle* circle;
    struct node * prev;
    struct node * next;
} node;


/******Function protypes*********/
void appEnd(node **tail_t,Circle* data); //add to end of linked list
void delEnd(node **tail); //delete from end of linked list if it is not the head
void addRandCircle(node** tail); //add random circle to end of linked list
Circle* newCricle(Color color, float size,float length, int x,int y,float speed); //Create new circle and returns its pointer

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
        float size = (((float)rand()/(float)(RAND_MAX)) * 30.f);
        float length = (((float)rand()/(float)(RAND_MAX)) * 10.f + 4.f);
        float speed = (((float)rand()/(float)(RAND_MAX)) * 40.f -20.f);
        appEnd(tail,newCricle((Color){r,g,b,255},size,length,(*tail)->circle->x,(*tail)->circle->y,speed));
}
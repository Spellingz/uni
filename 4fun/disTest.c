#include <raylib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// CUSTOM DEFINED VARIABLES
#define ARR_LENGTH(x) (sizeof(x) / sizeof((x)[0]))
#define ARR_SIZE 500
//
// MAIN VARIABLES:
//
int disArr[ARR_SIZE][ARR_SIZE];
int nextArr[ARR_SIZE][ARR_SIZE];

// CUSTOM STRUCT / FUNCTIONS
typedef struct Point
{
  int x, y;
} Point;

typedef struct Rect
{
  Point p1, p2;
} Rect;

void drawPointRect(Point p1, Point p2, Color color)
{
  DrawRectangle(p1.x, p1.y, p2.x-p1.x, p2.y-p1.y, color);
}

bool checkSpot(int i, int j)
{
  if (disArr[i][j] == 1)
    return false;
  return true;
}

void* checkGravity(void* arg)
{
  while (!WindowShouldClose()) 
  {
    usleep(2000);
    // CHECK GRAVITY
    for (int i = 0; i < ARR_SIZE; i++)
      for (int j = 0; j < ARR_SIZE-1; j++)
      {
        if (disArr[i][j] == 1)
        {
          // STRAIGHT GRAVITY
          if (checkSpot(i, j+1))
          {
            disArr[i][j] = 0;
            nextArr[i][j] = 0;
            nextArr[i][j+1] = 1;
          }
          else if (i > 0 && i < ARR_SIZE-1)
          {
            if (checkSpot(i+1, j+1) && checkSpot(i-1, j+1))// CHECK SIDE GRAVITY
            {
              disArr[i][j] = 0;
              nextArr[i][j] = 0;
              if (rand() & 1)
                nextArr[i+1][j+1] = 1;
              else
                nextArr[i-1][j+1] = 1;
            }
            else if (checkSpot(i+1, j+1))
            {
              disArr[i][j] = 0;
              nextArr[i][j] = 0;
              nextArr[i+1][j+1] = 1;
            }
            else if (checkSpot(i-1, j+1))
            {
              disArr[i][j] = 0;
              nextArr[i][j] = 0;
              nextArr[i-1][j+1] = 1;
            }
          }
        }
      }
    memcpy(disArr, nextArr, sizeof(disArr));
  }
  return NULL;
}


void moreSand(int i, int j)
{
  int sandSize = 3;
  int extend = sandSize/ 2;

  for (int newi = i-extend; newi <= i+extend; newi++)
    if (newi-extend > 0 && newi+extend < ARR_SIZE)
      for (int newj = j-extend; newj <= j+extend; newj++)
        if (newj-extend > 0 && newj+extend < ARR_SIZE)
          disArr[newi][newj] = 1;
}


// MAIN SECTION

int main(void) 
{
  // RENDER SETUP
  int renderWidth = 600;
  int renderHeight = 800;
  InitWindow(renderWidth, renderHeight, "Test Display");
  SetTargetFPS(60);


  pthread_t thread;
  pthread_create(&thread, NULL, checkGravity, NULL);

  
  // VARIABLE DECLARATIONS


  for (int i = 0; i < ARR_SIZE; i++)
    for (int j = 0; j < ARR_SIZE; j++)
      disArr[i][j] = 0;

  // MAIN LOOP

  while (!WindowShouldClose()) 
  {
    //WINDOW RESIZE REDEFINE
    if (IsWindowResized())
    {
      renderHeight = GetRenderHeight();
      renderWidth = GetRenderWidth();
      printf("New Window: %d, %d\n", renderHeight, renderWidth);
    }


    // MAIN CODE:


    if (IsMouseButtonDown(0))
    {
      Point mouse = { GetMouseX(), GetMouseY() };
      for (int i = 0; i < ARR_SIZE; i++)
      {
        for (int j = 0; j < ARR_SIZE; j++)
        {
          Rect tempRect = (Rect)
          {
            { (renderWidth/ARR_SIZE)*i, (renderHeight/ARR_SIZE)*j},
            { (renderWidth/ARR_SIZE)*(i+50), (renderHeight/ARR_SIZE)*(j+50) },
          };
          if (mouse.x >= tempRect.p1.x && mouse.x < tempRect.p2.x && mouse.y >= tempRect.p1.y && mouse.y < tempRect.p2.y)
          {
            moreSand(i,j);
            if (checkSpot(i, j))
              disArr[i][j] = 1;
          }
        }
      }
    }
    
    
    // RENDER SECTION
    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < ARR_SIZE; i++)
    {
      for (int j = 0; j < ARR_SIZE; j++)
      {
        Rect tempRect = (Rect)
        {
          { (renderWidth/ARR_SIZE)*i, (renderHeight/ARR_SIZE)*j},
          { (renderWidth/ARR_SIZE)*(i+1), (renderHeight/ARR_SIZE)*(j+1) },
        };

        switch(disArr[i][j])
        {
          case 0:
            drawPointRect(tempRect.p1, tempRect.p2, WHITE);
            break;
          case 1:
            drawPointRect(tempRect.p1, tempRect.p2, BLACK);
            break;
          default:
            drawPointRect(tempRect.p1, tempRect.p2, PINK);
            break;
        }


        // DRAW CHECKERED PATTERN
        // if ((i+j) % 2 == 0)
        // {
        //   drawPointRect(tempRect.p1, tempRect.p2, WHITE);
        // }
        // else
        // {
        //   drawPointRect(tempRect.p1, tempRect.p2, BLACK);
        // }
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}


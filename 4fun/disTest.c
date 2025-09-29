#include <raylib.h>
#include <stdio.h>

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

int main(void) 
{
  int renderHeight = 800;
  int renderWidth = 600;
  InitWindow(renderWidth, renderHeight, "Test Display");
  SetTargetFPS(15);
  
  Rect rect;

  while (!WindowShouldClose()) 
  {
    if (IsWindowResized())
    {
      renderHeight = GetRenderHeight();
      renderWidth = GetRenderWidth();
      printf("New Window: %d, %d\n", renderHeight, renderWidth);
    }
    // MAIN CODE:
    rect = (Rect){
      { renderWidth*(1.f/4.f), renderHeight*(1.f/4.f) },
      { renderWidth*(3.f/4.f), renderHeight*(3.f/4.f) }
    };

    BeginDrawing();
    ClearBackground(BLACK);

    drawPointRect(rect.p1, rect.p2, WHITE);

    EndDrawing();
    printf("Tried to draw square in canvas x: %d, y: %d, where point1: %d, %d, point2: %d, %d\n", renderHeight, renderWidth, rect.p1.x, rect.p1.y, rect.p2.x, rect.p2.y);
    printf("\n");
  }

  CloseWindow();
  return 0;
}


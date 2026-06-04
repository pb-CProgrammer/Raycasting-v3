#include "raylib.h"
#include "math.h"

#define screenWidth 960
#define screenHeight 960
#define fakeScreenWidth 10
#define mapWidth 24
#define mapHeight 24
#define tileSize 40

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main()
{
    InitWindow(screenWidth, screenHeight, "Raycasting");
    SetTargetFPS(60);

    double posX = 22.5, posY = 12.5;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);

            for (int x = 0; x < mapWidth; x++)
            {
                for (int y = 0; y < mapWidth; y++)
                {
                    if (worldMap[x][y] > 0)
                    {
                        DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLUE);
                    }

                    DrawRectangleLines(x * tileSize, y * tileSize, tileSize, tileSize, BLACK);
                }
            }

            DrawCircle(posX * tileSize, posY * tileSize, 10, RED);
            DrawLine(posX * tileSize, posY * tileSize, (posX + dirX) * tileSize, (posY + dirY) * tileSize, RED);
            DrawLine((posX + dirX - planeX) * tileSize, (posY + dirY - planeY) * tileSize, (posX + dirX + planeX) * tileSize, (posY + dirY + planeY) * tileSize, RED);



            for(int x = 0; x < fakeScreenWidth; x++)
            {
                double cameraX = 2 * x / (double)fakeScreenWidth - 1;
                double rayDirX = dirX + planeX * cameraX;
                double rayDirY = dirY + planeY * cameraX;
                DrawCircle((posX + rayDirX) * tileSize, (posY + rayDirY) * tileSize, 2, PINK);

                int mapX = (int)posX;
                int mapY = (int)posY;
                DrawCircle(mapX * tileSize, mapY * tileSize, 5, BLUE);


                double deltaDistX = rayDirX == 0.0 ? 1e30 : fabs(1 / rayDirX);
                double deltaDistY = rayDirY == 0.0 ? 1e30 : fabs(1 / rayDirY);
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

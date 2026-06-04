#include "raylib.h"
#include <math.h>

#define screenWidth 1920
#define screenHeight 1080
#define mapWidth 24
#define mapHeight 24

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

double scale = 1.0;

int main()
{
    InitWindow(screenWidth, screenHeight, "Raycasting");
    SetTargetFPS(60);

    double posX = 22, posY = 12;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;

    while (!WindowShouldClose())
    {
        double moveSpeed = GetFrameTime() * 5.0;
        double rotSpeed = GetFrameTime() * 3.0;

        if(IsKeyDown(KEY_W))
        {
            double newPosX = posX + dirX * moveSpeed;
            double newPosY = posY + dirY * moveSpeed;

            if(worldMap[(int)newPosX][(int)posY] == 0)
            {
                posX = newPosX;
            }

            if(worldMap[(int)posX][(int)newPosY] == 0)
            {
                posY = newPosY;
            }
        }

        if(IsKeyDown(KEY_S))
        {
            double newPosX = posX - dirX * moveSpeed;
            double newPosY = posY - dirY * moveSpeed;

            if(worldMap[(int)newPosX][(int)posY] == 0)
            {
                posX = newPosX;
            }

            if(worldMap[(int)posX][(int)newPosY] == 0)
            {
                posY = newPosY;
            }
        }

        if(IsKeyDown(KEY_A))
        {
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }

        if(IsKeyDown(KEY_D))
        {
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }

        if(IsKeyDown(KEY_Q))
        {
            scale += 1 * GetFrameTime();
        }
        if(IsKeyDown(KEY_E))
        {
            scale -= 1 * GetFrameTime();
        }

        BeginDrawing();

        ClearBackground(BLACK);

        for (int x = 0; x < screenWidth; x++)
        {
            double cameraX = 2 * x / (double)screenWidth - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            int mapX = (int)posX;
            int mapY = (int)posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            double perpWallDist;

            int stepX;
            int stepY;

            int hit = 0;
            int side;

            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1 - posY) * deltaDistY;
            }

            while (hit == 0)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                if (worldMap[mapX][mapY] > 0)
                {
                    hit = 1;
                }
            }

            if (side == 0)
            {
                perpWallDist = sideDistX - deltaDistX;
            }
            else
            {
                perpWallDist = sideDistY - deltaDistY;
            }

            int lineHeight = (int)(screenHeight / perpWallDist * scale);

            int drawStart = screenHeight / 2 - (lineHeight / 2);
            if (drawStart < 0)
            {
                drawStart = 0;
            }

            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if (drawEnd >= screenHeight)
            {
                drawEnd = screenHeight - 1;
            }

            Color color;
            switch (worldMap[mapX][mapY])
            {
                case 1: color = RED;
                break;
                case 2: color = GREEN;
                break;
                case 3: color = BLUE;
                break;
                case 4: color = WHITE;
                break;
                default: color = YELLOW;
                break;
            }

            if (side == 1)
            {
                color = (Color) {color.r / 2, color.g / 2, color.b / 2, color.a / 2};
            }

            DrawLine(x, drawStart, x, drawEnd, color);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

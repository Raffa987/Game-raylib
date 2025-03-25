#include "raylib.h"
#include "raymath.h"
#include "time.h"
#include "cstdlib"
#include "iostream"
#include "vector"

using namespace std;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
} Ball;



int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bouncy");
    srand(time(NULL));

    Ball ball;
    ball.position.x = WINDOW_WIDTH / 2;
    ball.position.y = WINDOW_HEIGHT / 2;
    ball.radius = 60;
    ball.color = GREEN;

    int direction_x = (rand() % 2) + 1;
    int direction_y = (rand() % 2) + 1;
    int speedModifier_x = pow(-1, direction_x)*((rand() % 10) + 500);
    int speedModifier_y = pow(-1, direction_y)*((rand() % 10) + 500);


	bool exitWindowRequested = false;  
	bool exitWindow = false;

    bool isGameStarted = false;
    bool isGameWon = false;
    bool isGameLost = false;

    int points = 0;
    int Health = 3;

    int textDimension = 40;
    int textWidth = MeasureText("Clicca per iniziare", textDimension);

	while (!exitWindow) {

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation

            if (IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (exitWindowRequested)
        {
            DrawRectangle(0, 100, WINDOW_WIDTH, 200, BLACK);
            DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
        }
        else
        {
            if (!isGameStarted && !isGameWon && !isGameLost) {
                DrawText("Click to start playing", (WINDOW_WIDTH/2 - MeasureText("Clicca per iniziare", textDimension) /2), (WINDOW_HEIGHT / 8), textDimension, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    isGameStarted = true;
                }

            }
            else if(isGameStarted && !isGameWon && !isGameLost){
                DrawText(TextFormat("Points: %d", points), 10, 10, 20, DARKGRAY);
                DrawText(TextFormat("Health: %d", Health), 10, 30, 20, DARKGRAY);
                DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
                ball.speed.x = speedModifier_x * GetFrameTime();
                ball.speed.y = speedModifier_y * GetFrameTime();
                ball.position.x += ball.speed.x;
                ball.position.y += ball.speed.y;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    Vector2 mouse = GetMousePosition();
                    if (CheckCollisionPointCircle(mouse, ball.position, ball.radius)) {
                        points += 1;
                    }
                    else {
                        Health -= 1;
                    }
                }

                if ((ball.position.x + ball.radius) >= WINDOW_WIDTH || (ball.position.x - ball.radius) <= 0) {
                    speedModifier_x = -speedModifier_x;
                }

                if ((ball.position.y + ball.radius) >= WINDOW_HEIGHT || (ball.position.y - ball.radius) <= 0) {
                    speedModifier_y = -speedModifier_y;
                }

                if (points >= 10) {
                    isGameWon = true;
                    DrawText("You Won!", (WINDOW_WIDTH / 2 - MeasureText("You Won!", textDimension)/ 2), (WINDOW_HEIGHT / 8), textDimension, BLACK);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        points = 0;
                        Health = 3;
                        isGameWon = false;
                        isGameStarted = false;
                    }
                }
                else if (Health <= 0) {
                    isGameLost = true;
                    DrawText("You Lost!", (WINDOW_WIDTH / 2 - MeasureText("You Lost!", textDimension) / 2), (WINDOW_HEIGHT / 8), textDimension, BLACK);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        Health = 3;
                        points = 0;
                        isGameLost = false;
                        isGameStarted = false;
                    }
                }

            }
          
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}

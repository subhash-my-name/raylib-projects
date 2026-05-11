#include "raylib.h"

int main(void)
{
	const int sW = 1280;
	const int sH = 720;
	
	InitWindow(sW, sH, "Collision Simulator");

	Rectangle rec1 = {0, (float)sH/2.0f, 100, 100};
	Rectangle rec2 = {sW - 100, (float)sH/2.0f, 100, 100};

	float m1 = 50; 
	float m2 = 64;
			   
	int paused = 0;
	int collision = 0;

	float u1 = 10.0f;
	float u2 = -20.0f;
	float v1, v2;

	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		// make em move
		if(!paused)
		{
			rec1.x += u1;
			rec2.x += u2;
		}

		// rectangles bounce back from the wall and the collision continues
		if(((rec1.x + 100) >= sW) || (rec1.x <= 0)) u1 *= -1.0f;
		if(((rec2.x + 100) >= sW) || (rec2.x <= 0)) u2 *= -1.0f;
		
		// to check collision
		collision = CheckCollisionRecs(rec1, rec2);

		// update velocity upon collision
		if(collision)
		{
			v1 = ((m1 - m2) * u1 + 2 * m2 * u2) / (m1 + m2);
			v2 = ((m2 - m1) * u2 + 2 * m1 * u1) / (m1 + m2);
			u1 = v1;
			u2 = v2;
		}

		if(IsKeyPressed(KEY_SPACE)) paused = !paused;
		if(IsKeyPressed(KEY_R)) 
		{
			rec1.x = 0;
			rec2.x = sW - 100;
			u1 = 10;
			u2 = -10;
		}

		BeginDrawing();

			ClearBackground(RAYWHITE);
			
			// draws both the rectangles
			DrawRectangle(rec1.x, rec1.y, 100, 100, GOLD);
			DrawRectangle(rec2.x, rec1.y, 100, 100, BLUE);
									
			DrawText("Press SPACE to pause/resume", (float)sW/2 - 150, sH - 35, 20, MAROON);
			DrawText("Press R to reset", (float)sW/2 - 150, sH - 70, 20, MAROON);

		EndDrawing();

	}
}

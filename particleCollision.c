#include <time.h>
#include "raylib.h"
#include <stdlib.h>

int x_range()
{
	int store, size = 1914, rd_choice, xLim[size];

	for(int i = 5; i < 1906; i++)
		xLim[i] = i + 3;
	
	size = sizeof(xLim) / sizeof(xLim[0]);
	rd_choice = rand() % size;
	size--;
	store = xLim[rd_choice];
	
	for(int i = rd_choice; i < size; i++)
		xLim[i] = xLim[i + 1];
	
	return store;
}

int y_range()
{
	int store, size = 1074, rd_choice, yLim[size];

	for(int i = 5; i < 1065; i++)
		yLim[i] = i + 3;
	
	size = sizeof(yLim) / sizeof(yLim[0]);
	rd_choice = rand() % size;
	size--;
	store = yLim[rd_choice];
	
	for(int i = rd_choice; i < size; i++)
		yLim[i] = yLim[i + 1];
	
	return store;
}

typedef struct particle
{
	float mass;
	int pCollision;
	int wCol1, wCol2, wCol3, wCol4;
	Vector2 position;
	Vector2 u;
	Vector2 velocity;
} particle;

int main(void)
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	InitWindow(screenWidth, screenHeight, "Collision of Particles");

	Vector2 topLeft = {0, 0};
	Vector2 topRight = {1920, 0};
	Vector2 bLeft = {0, 1080};
	Vector2 bRight = {1920, 1080};

	const int PARTICLE_COUNT = 200;
	const int radius = 6;
	float v_list[] = {-1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
	int v_list_size = sizeof(v_list) / sizeof(v_list[0]);
	
	srand(time(NULL));
	
	particle particles[PARTICLE_COUNT];

	for(int i = 0; i < PARTICLE_COUNT; i++)
	{
		particles[i].position.x = x_range();
		particles[i].position.y = y_range();
		
		particles[i].mass = rand() % 15 + 1;

                particles[i].pCollision = 0;
                particles[i].wCol1 = 0;
		particles[i].wCol2 = 0;
		particles[i].wCol3 = 0;
		particles[i].wCol4 = 0;

		particles[i].velocity.x = 0.1 * (v_list[rand() % v_list_size]);
		particles[i].velocity.y = 0.1 * (v_list[rand() % v_list_size]);
	}

	while(!WindowShouldClose())
	{

		for(int i = 0; i < PARTICLE_COUNT; i++)
		{
			particles[i].position.y += particles[i].velocity.y;
			particles[i].position.x += particles[i].velocity.x;
		}

		for(int i = 0; i < PARTICLE_COUNT; i++)
		{
			for(int j = i + 1; j < PARTICLE_COUNT; j++)
			{
				particles[j].pCollision = CheckCollisionCircles(particles[i].position, radius, particles[j].position, radius);
				particles[i].pCollision = particles[j].pCollision;

				if(particles[j].pCollision)
				{
					particles[j].u.x = particles[j].velocity.x;
					particles[i].u.x = particles[i].velocity.x;
					particles[j].velocity.x = ((particles[j].mass - particles[i].mass) * particles[j].u.x + 2 * particles[i].mass * particles[i].u.x) / (particles[j].mass + particles[i].mass);
					particles[i].velocity.x = ((particles[i].mass - particles[j].mass) * particles[i].u.x + 2 * particles[j].mass * particles[j].u.x) / (particles[j].mass + particles[i].mass);

					particles[j].u.y = particles[j].velocity.y;
					particles[i].u.y = particles[i].velocity.y;

					particles[j].velocity.y = ((particles[j].mass - particles[i].mass) * particles[j].u.y + 2 * particles[i].mass * particles[i].u.y) / (particles[j].mass + particles[i].mass);
					particles[i].velocity.y = ((particles[i].mass - particles[j].mass) * particles[i].u.y + 2 * particles[j].mass * particles[j].u.y) / (particles[j].mass + particles[i].mass);
				}
			}
		}

		for(int i = 0; i < PARTICLE_COUNT; i++)
		{
			particles[i].wCol1 = CheckCollisionCircleLine(particles[i].position, radius, topLeft, topRight); 		
			if(particles[i].wCol1) particles[i].velocity.y *= -1;

			particles[i].wCol2 = CheckCollisionCircleLine(particles[i].position, radius, bRight, topRight); 
			if(particles[i].wCol2) particles[i].velocity.x *= -1;

			particles[i].wCol3 = CheckCollisionCircleLine(particles[i].position, radius, bLeft, bRight); 
			if(particles[i].wCol3) particles[i].velocity.y *= -1;

			particles[i].wCol4 = CheckCollisionCircleLine(particles[i].position, radius, topLeft, bLeft); 
			if(particles[i].wCol4) particles[i].velocity.x *= -1;
		}

		BeginDrawing();
			
		ClearBackground(BLACK);
		
		for(int i = 0; i < PARTICLE_COUNT; i++)
		{
//			particles[i].position.x = x_range(); // just for fun
//			particles[i].position.y = y_range(); // just for fun
			DrawCircle(particles[i].position.x, particles[i].position.y, radius, WHITE);
		}

		EndDrawing();
	}
}

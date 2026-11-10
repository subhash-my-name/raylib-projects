#include "raylib.h"
#include "matrix.h"
#include <iostream>

const int screenWidth = 1000;
const int screenHeight = 1000;
const float scale = 50.0; // as in, uhhh, 1 math unit should be 50 pixels.

Vector2 CartesianCoordToRaylibWindow(Vector2 position){
	return Vector2{
		(screenWidth / 2.0f) + (position.x * scale),
		(screenHeight / 2.0f) - (position.y * scale)
	};
}

Vector2 VectorTransformation(const MY_MATRIX::Matrix& transform, Vector2 v){
	// unfortunately, i am too lazy to rewrite all the class Matrix into float
	// so i am converting to float, because raylib uses float.
	float new_x = static_cast<float>(transform(0, 0) * v.x + transform(0, 1) * v.y);
	float new_y = static_cast<float>(transform(1, 0) * v.x + transform(1, 1) * v.y);
	return Vector2{new_x, new_y};
}

int main(){
	InitWindow(screenWidth, screenHeight, "can't think of a name right now");
	SetTargetFPS(60);

	MY_MATRIX::Matrix transformerMatrix1, transformerMatrix2;

	std::cout << "Enter first transformer matrix values:" << '\n';
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			int x;
			std::cout << "(" << i << ", " << j << " ): ";
			std::cin >> x;
			transformerMatrix1(i, j) = x;
		}

	std::cout << "Enter second transformer matrix values:" << '\n';
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++){
			int x;
			std::cout << "(" << i << ", " << j << " ): ";
			std::cin >> x;
			transformerMatrix2(i, j) = x;
		}

	MY_MATRIX::Matrix transformerMatrix3 = transformerMatrix1 + transformerMatrix2;

	// to draw the 'graph,' i will use this as a reference
	// as in, each one unit of this will be converted to like
	// 50 pixels because of CartesianCoordsToRaylib() function
	// and then to draw the graph's grid, this unit square will be used
	Vector2 unitSquare[4] = {
		{0, 0}, {1, 0}, {1, 1}, {0, 1}
	};

	while(!WindowShouldClose()){
		BeginDrawing();

		ClearBackground(BLACK);
		DrawLine(0, screenHeight / 2, screenWidth, screenWidth / 2, WHITE);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

		for(int i = 0; i < 4; i++){
			int nextLine = (i + 1) % 4;

			// to see how the grid transforms because of the transformer matrix,
			// i will draw both: grid before and grid after transformation. 
			// but for now, i am tired and i dont want to get into drawing the
			// entire grid. one square is just fine.
			Vector2 before_1 = CartesianCoordToRaylibWindow(unitSquare[i]);
			Vector2 before_2 = CartesianCoordToRaylibWindow(unitSquare[nextLine]);
			DrawLineEx(before_1, before_2, 2, YELLOW);

			Vector2 after_1 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix1, unitSquare[i]));
			Vector2 after_2 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix1, unitSquare[nextLine]));
			DrawLineEx(after_1, after_2, 3, RED);

			Vector2 another_after_1 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix2, unitSquare[i]));
			Vector2 another_after_2 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix2, unitSquare[nextLine]));
			DrawLineEx(another_after_1, another_after_2, 3, GREEN);

			Vector2 again_another_after_1 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix3, unitSquare[i]));
			Vector2 again_another_after_2 = CartesianCoordToRaylibWindow(VectorTransformation(transformerMatrix3, unitSquare[nextLine]));
			DrawLineEx(again_another_after_1, again_another_after_2, 3, PURPLE);
		}

		EndDrawing();
	}
}

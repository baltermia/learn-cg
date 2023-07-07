#include "TwoTriangles.h"

/*
 * https://learnopengl.com/Getting-started/Hello-Triangle 
 *
 * Excercise 1:
 * 
 * Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.
*/

int main()
{
	TwoTriangles setup;

	setup.initialize();
	setup.run();
	setup.clean();
}
#include "TwoTriangles2.h"

/*
 * https://learnopengl.com/Getting-started/Hello-Triangle
 *
 * Excercise 2:
 *
 * Now create the same 2 triangles using two different VAOs and VBOs for their data.
*/

int main()
{
	TwoTriangles2 setup;
	setup.initialize();
	setup.run();
	setup.clean();
}

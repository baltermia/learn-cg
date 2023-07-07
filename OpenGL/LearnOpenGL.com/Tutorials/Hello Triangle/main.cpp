#include "HelloTriangle.h"

/*
 * https://learnopengl.com/Getting-started/Hello-Triangle
 */

int main()
{
	HelloTriangle setup;

	setup.initialize();
	setup.run();
	setup.clean();
}
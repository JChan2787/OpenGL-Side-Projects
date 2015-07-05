/*
* Programmed By	: Jay Chan Jr.
* Date Started  : 4 JUL 2015
*/

//Pre Processor Directives
#include "glew.h"
#include <iostream>

int main()
{
	if(!glewInit())
	{
		std::cout << "error" << std::endl;
	}
	else
	{
		std::cout << "you're good" << std::endl;
	}

	return 0;
}
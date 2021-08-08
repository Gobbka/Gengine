#include <iostream>

#include "Windows.h"

int main(int argc,LPSTR*argv) noexcept
{
	std::cout << argc << '\n' << argv[1];
}

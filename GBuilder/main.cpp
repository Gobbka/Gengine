#include "builders/project_builder/project_builder.h"
#include "Windows.h"

int main(int argc,LPSTR*argv) noexcept
{
	if (argc == 1)
		return 0;

	auto gakba = get_msbuild_path();
	delete[] gakba;
}

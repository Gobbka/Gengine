#include "project_builder.h"
#include <Windows.h>

char* get_msbuild_path()
{
	HKEY hKey;
	LONG lRes = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\MSBuild\\ToolsVersions\\4.0", 0, KEY_READ, &hKey);
	if (lRes != ERROR_SUCCESS)
		throw "MSBuild.exe does not installed on this device.";

	DWORD size = 0;
	RegQueryValueExA(hKey, "MSBuildToolsPath", 0, nullptr, nullptr, &size);
	
	BYTE* path = new BYTE[size];
	RegQueryValueExA(hKey, "MSBuildToolsPath", 0, nullptr, path, &size);

	return (char*)path;
}

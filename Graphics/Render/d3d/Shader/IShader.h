#pragma once

namespace Core
{
	class DX11Graphics;
};

namespace Render {
	class __declspec(dllexport) IShader
	{
	protected:
		Core::DX11Graphics* context;

		explicit IShader(Core::DX11Graphics* engine) : context(engine) {}
	};
}

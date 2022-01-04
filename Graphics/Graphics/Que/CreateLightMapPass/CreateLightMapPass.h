#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "Types/Types.h"
#include "../../../Render/d3d/Buffer/ConstantBuffer.h"

namespace Render
{
	struct PointLightCBStruct
	{
		Position3 pos = Position3::null();
		float intensity = 1.f;
	};

	class CreateLightMapPass : public IPass
	{
		ConstantBuffer<PointLightCBStruct> _light_struct;
		Mesh _point_light_cube;
		Core::DX11Graphics* _context;
		void execute(Scene*scene) override;
	public:
		explicit CreateLightMapPass(Core::DX11Graphics* context);
	};
}

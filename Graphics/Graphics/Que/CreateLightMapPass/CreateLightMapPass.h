#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "Types/Types.h"
#include "../../../Render/Common/GraphicsCommon.h"
#include "../../../Render/Common/ConstantBuffer.h"

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
		GEGraphics* _context;
		void execute(Scene*scene) override;
	public:
		explicit CreateLightMapPass(GEGraphics* context);
	};
}

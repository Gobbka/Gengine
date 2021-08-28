#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../I3DObject/Mesh.h"
#include "../Viewer/WorldViewer.h"
#include "Types/Transform.h"

struct Surface;

namespace Render
{
	class DirectionLightComponent;
	class Cube;
	class MaskEngine;
	class BlendEngine;

	struct CameraOptions
	{
		bool render_2d = true;
		bool render_3d = true;
		bool shadows   = true;
		RenderTarget* renderTarget = nullptr;
	};

	class __declspec(dllexport) Camera : public WorldViewer
	{
	private:
		BlendEngine* _blendEngine;

		CameraOptions _cameraOptions;

		std::vector<Canvas::Canvas2DLayer*> _canvas2DLayers;
	public:
		void clear(Color3 color);
		void clear();
		
		void set_position(Position3 pos);
		void adjust_position(Position3 pos);
		void adjust_position_relative(Position3 pos);
		
		void set_rotation(Core::Quaternion3 quat);
		void adjust_rotation(Vector3 rot);
		
		void set_resolution(Surface new_resolution);

		void set_render_target(RenderTarget* target);

		MeshContainerComponent*  point_to_world(Vector2 screen_coordinate);
		Vector2 point_to_screen(Vector3 world_coordinate);
	public:
		CameraOptions* options();
		Core::GraphicsContext* graphics_context();
		ID3D11Device* device() const;
		RenderTarget* get_target_view() const;
		MaskEngine* get_mask_engine() const;
		BlendEngine* blend_engine() const;

		Surface get_screen_resolution() const;
	public:
		
		Camera(Core::GraphicsContext* context,RenderTarget*target);

		void bind();
	};
}

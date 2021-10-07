#pragma once
#include "../Viewer/WorldViewer.h"

struct Surface;

namespace Render
{
	class BlendEngine;

	class __declspec(dllexport) Camera : public WorldViewer
	{
	private:
		BlendEngine* _blendEngine;
	public:


		void clear(Color3XM color);
		void clear();
		
		void set_position(Position3 pos);
		void adjust_position(Position3 pos);
		void adjust_position_relative(Position3 pos);
		
		void set_rotation(Vector3 quat);
		void adjust_rotation(Vector3 rot);
		
		void set_resolution(Surface new_resolution);

		Vector2 point_to_screen(Vector3 world_coordinate);
	public:
		Core::GraphicsContext* graphics_context();
		RenderTarget* get_target_view();
		MaskEngine* get_mask_engine() const;
		BlendEngine* blend_engine() const;
	public:
		
		Camera(Core::GraphicsContext* context,RenderTarget*target);

		void bind();
	};
}

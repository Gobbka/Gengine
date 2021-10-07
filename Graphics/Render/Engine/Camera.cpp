#include "Camera.h"

#include "BlendEngine.h"
#include "MaskEngine.h"
#include "RenderTarget.h"
#include "Types/Types.h"

void Render::Camera::clear(Color3XM color)
{
	render_target->clear(color);
}

void Render::Camera::clear()
{
	render_target->clear();
}

void Render::Camera::set_position(Position3 pos)
{
	_transform.set_position(pos);
	update_position();
}

void Render::Camera::adjust_position(Position3 pos)
{
	_transform.adjust_position(pos);
	update_position();
}

void Render::Camera::adjust_position_relative(Position3 pos)
{
	_transform.adjust_position(pos);
	update_position();
}

void Render::Camera::set_rotation(Vector3 quat)
{
	_transform.set_rotation(quat);
	update_position();
}

void Render::Camera::adjust_rotation(Vector3 rot)
{
	_transform.adjust_rotation(rot);
	update_rotation();
}

void Render::Camera::set_resolution(Surface resolution)
{
	WorldViewer::set_view_resolution(resolution);
}

Core::GraphicsContext* Render::Camera::graphics_context()
{
	return context;
}

Render::RenderTarget* Render::Camera::get_target_view()
{
	return WorldViewer::get_render_target();
}

Render::MaskEngine* Render::Camera::get_mask_engine() const
{
	return mask_engine;
}

Render::BlendEngine* Render::Camera::blend_engine() const
{
	return _blendEngine;
}

Render::Camera::Camera(Core::GraphicsContext* context,RenderTarget*target)
	:
	WorldViewer(context,target)
{
	_blendEngine = new BlendEngine(context);
	mask_engine = new MaskEngine(this);
}

void Render::Camera::bind()
{
	_blendEngine->bind();

	mask_engine->clear_buffer();
	mask_engine->get_disabledState()->bind(0);
	WorldViewer::bind();
}

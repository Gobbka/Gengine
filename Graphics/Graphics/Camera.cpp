#include "Camera.h"

#include <algorithm>

#include "../Render/Common/RenderTarget.h"
#include "Types/Types.h"
#include "../Graphics.h"
#include "../Render/Common/IGContext.h"
#include "../Render/Common/BlendEngine.h"

void Render::Camera::clear(Color3XM color) const
{
	_render_target->clear(color);
	_mask_engine->clear_buffer();
}

void Render::Camera::clear() const
{
	_render_target->clear();
	_mask_engine->clear_buffer();
}

void Render::Camera::set_resolution(Surface resolution)
{
	set_view_resolution(resolution);
}

Render::GEGraphics* Render::Camera::get_graphics() const
{
	return _graphics;
}

Render::DX11RenderTarget* Render::Camera::get_target_view() const
{
	return _render_target;
}

Render::GEMaskEngine* Render::Camera::get_mask_engine() const
{
	return _mask_engine;
}

Render::Camera& Render::Camera::operator=(Camera&& other) noexcept
{
	if (_blendEngine != other._blendEngine)
		delete _blendEngine;
	if (_mask_engine != other._mask_engine)
		delete _mask_engine;
	if (_render_target != other._render_target)
		delete _render_target;

	_blendEngine = other._blendEngine;
	_mask_engine = other._mask_engine;
	_render_target = other._render_target;
	_graphics = other._graphics;

	*(WorldViewer*)this = std::move((WorldViewer&)other);

	return*this;
}


Render::Camera::Camera(Camera&& other) noexcept
	: WorldViewer(other)
	, _blendEngine(other._blendEngine)
	, _render_target(other._render_target)
	, _mask_engine(other._mask_engine)
	, _graphics(other._graphics)
{
	other._blendEngine = nullptr;
	other._mask_engine = nullptr;
	other._render_target = nullptr;
}


Render::Camera::Camera(GEGraphics* graphics, DX11RenderTarget* target)
	: WorldViewer(target->get_texture()->resolution())
	, _blendEngine(new GEBlendEngine(graphics))
	, _render_target(target)
	, _mask_engine(new GEMaskEngine(_render_target))
	, _graphics(graphics)
{}

void Render::Camera::bind() const
{
	_blendEngine->bind();
	_graphics->get_context()->set_render_target(_render_target, _mask_engine);
}

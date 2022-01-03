#include "Camera.h"

#include <algorithm>
#include "BlendEngine.h"
#include "MaskEngine.h"
#include "RenderTarget.h"
#include "Types/Types.h"
#include "../../Graphics.h"
#include "../../IGContext.h"


void Render::Camera::clear(Color3XM color)
{
	_render_target->clear(color);
	_mask_engine->clear_buffer();
}

void Render::Camera::clear()
{
	_render_target->clear();
	_mask_engine->clear_buffer();
}

void Render::Camera::set_resolution(Surface resolution)
{
	WorldViewer::set_view_resolution(resolution);
}

Core::GraphicsContext* Render::Camera::graphics_context()
{
	return _context;
}

Render::RenderTarget* Render::Camera::get_target_view()
{
	return _render_target;
}

Render::MaskEngine* Render::Camera::get_mask_engine() const
{
	return _mask_engine;
}

Render::BlendEngine* Render::Camera::blend_engine() const
{
	return _blendEngine;
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
	_context = other._context;

	*(WorldViewer*)this = std::move((WorldViewer&)other);

	return*this;
}


Render::Camera::Camera(Camera&& other) noexcept
	: WorldViewer(other)
	, _blendEngine(other._blendEngine)
	, _render_target(other._render_target)
	, _mask_engine(other._mask_engine)
	, _context(other._context)
{
	other._blendEngine = nullptr;
	other._mask_engine = nullptr;
	other._render_target = nullptr;
}


Render::Camera::Camera(Core::GraphicsContext* context, RenderTarget* target)
	: WorldViewer(Surface(target->get_texture()->width(), target->get_texture()->height()))
	, _blendEngine(new BlendEngine(context))
	, _render_target(target)
	, _mask_engine(new MaskEngine(_render_target))
	, _context(context)
{}

void Render::Camera::bind() const
{
	_blendEngine->bind();
	_context->get_context()->set_render_target(_render_target, _mask_engine);
}

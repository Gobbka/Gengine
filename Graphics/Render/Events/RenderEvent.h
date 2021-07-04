#pragma once

namespace Render {
	class ILayer;

	struct DrawEvent {
		ILayer* layer;

		DrawEvent(ILayer* layer);
	};
}

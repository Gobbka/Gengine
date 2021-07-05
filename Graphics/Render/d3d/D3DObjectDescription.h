#pragma once

namespace Render
{
	class D3DObjectDescription
	{
	public:
		virtual ~D3DObjectDescription() = default;
		typedef unsigned long INDEX;
	protected:
		INDEX _index = 0u;
	public:
		bool hidden = false;
		
		auto get_index() const { return _index; }
		void set_index(INDEX new_index) { _index = new_index; }

		// must return needed object vertex length
		virtual INDEX size() = 0;
	};
}

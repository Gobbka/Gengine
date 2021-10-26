#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

#include <cassert>
#include "../../Render/d3d/Vertex.h"

void Render::IVertexBuffer::count_normals(IIndexBuffer* buffer) const
{
	auto index_size = buffer->get_size();
	
	// we count only triangles
	assert(index_size % 3 == 0);
	
	for(size_t i = 0;i < index_size;i+=3)
	{
		auto pos1 = data[buffer->operator[](i+0)].pos;
		auto pos2 = data[buffer->operator[](i+1)].pos;
		auto pos3 = data[buffer->operator[](i+2)].pos;

		const auto cross = DirectX::XMVector3Cross(XMLoadFloat3(&pos2) , XMLoadFloat3(&pos3));
		const auto normal = DirectX::XMVectorMultiply(XMLoadFloat3(&pos1), cross);

		DirectX::XMStoreFloat3(&data[i].normal, normal);
		DirectX::XMStoreFloat3(&data[i+1].normal, normal);
		DirectX::XMStoreFloat3(&data[i+2].normal, normal);
	}
}

Render::Vertex& Render::IVertexBuffer::at(unsigned index) const
{
	return data[index];
}

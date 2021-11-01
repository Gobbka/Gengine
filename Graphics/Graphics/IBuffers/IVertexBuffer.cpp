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
		const auto pos1 = XMLoadFloat3(&data[buffer->operator[](i+0)].pos);
		const auto pos2 = XMLoadFloat3(&data[buffer->operator[](i+1)].pos);
		const auto pos3 = XMLoadFloat3(&data[buffer->operator[](i+2)].pos);

		const auto vector1 = DirectX::XMVectorSubtract(pos2,pos1);
		const auto vector2 = DirectX::XMVectorSubtract(pos2,pos3);

		const auto normal = DirectX::XMVector3Cross(vector1, vector2);

		DirectX::XMStoreFloat3(&data[i].normal, normal);
		DirectX::XMStoreFloat3(&data[i+1].normal, normal);
		DirectX::XMStoreFloat3(&data[i+2].normal, normal);
	}

	return;
}

Render::Vertex& Render::IVertexBuffer::at(unsigned index) const
{
	return data[index];
}

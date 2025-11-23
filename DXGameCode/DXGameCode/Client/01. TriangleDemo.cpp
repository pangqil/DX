#include "pch.h"
#include "01. TriangleDemo.h"
<<<<<<< HEAD:GameCode-P2/Client/01. TriangleDemo.cpp

=======
//ì´ˆê¸°í™” ê³¼ì •ì—ì„  Triangle ì‰ì´ë”, vectices positionì„ 
>>>>>>> parent of 5f958db ([ADD] Project Devide):DXGameCode/DXGameCode/Client/01. TriangleDemo.cpp
void TriangleDemo::Init()
{
	_shader = make_shared<Shader>(L"01. Triangle.fx");

	{
		_vertices.resize(3);

		_vertices[0].position = Vec3{-0.5f, 0.f, 0.f};
		_vertices[1].position = Vec3{0.f, 0.5f, 0.f};
		_vertices[2].position = Vec3{0.5f, 0.f, 0.f};
	}

	_buffer = make_shared<VertexBuffer>();
	_buffer->Create(_vertices);
<<<<<<< HEAD:GameCode-P2/Client/01. TriangleDemo.cpp
}
=======
}//Initì—ì„  shaderë¥¼ ë§Œë“¤ê³  bufferë¥¼ ìƒì„±.
>>>>>>> parent of 5f958db ([ADD] Project Devide):DXGameCode/DXGameCode/Client/01. TriangleDemo.cpp

void TriangleDemo::Update()
{

}

void TriangleDemo::Render()
{
	uint32 stride = _buffer->GetStride();
	uint32 offset = _buffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _buffer->GetComPtr().GetAddressOf(), &stride, &offset);

	//_buffer->GetCount()
	_shader->Draw(1, 0, 3);
}
<<<<<<< HEAD:GameCode-P2/Client/01. TriangleDemo.cpp
//Shader °´Ã¼ »ý¼º -> vertices 3°³ Á¤Á¡ ÁÂÇ¥ ¼³Á¤ -> vertex´ã´Â buffer »ý¼º -> buffercreate(verti)
=======
>>>>>>> parent of 5f958db ([ADD] Project Devide):DXGameCode/DXGameCode/Client/01. TriangleDemo.cpp

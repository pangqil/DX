#pragma once
#include "IExecute.h"
#include "Geometry.h"
#include "GameObject.h"

class SamplerDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;


	shared_ptr<Shader> _shader;

	//Object
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Matrix _world = Matrix::Identity;

	//Camera
	shared_ptr<GameObject> _camera;
	//Texture
	shared_ptr<Texture> _texture;
};

//01. vertexbuffer, vertex, shader
//02. vertexbuffer, <geometry>vertexcolor, indexbuffer, shader
//03. 02 + _translation
//04. 03 +  
//05. vertexbuffer, <geometry>vertexcolor, indexbuffer, shader, translation
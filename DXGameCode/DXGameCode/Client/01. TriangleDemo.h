#pragma once
#include "IExecute.h"

class TriangleDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;


	shared_ptr<Shader> _shader;
	vector<VertexData> _vertices;
	shared_ptr<VertexBuffer> _buffer;
};
<<<<<<< HEAD:GameCode-P2/Client/01. TriangleDemo.h

//VertexBuffer, verticle, shader 3°³¸¸ »ç¿ëÇß¾úÀ½
=======
//Shader, verticle, bufferë§Œìœ¼ë¡œ ì‚¼ê°í˜• ê·¸ë¦¬ê¸°
>>>>>>> parent of 5f958db ([ADD] Project Devide):DXGameCode/DXGameCode/Client/01. TriangleDemo.h

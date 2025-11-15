#pragma once

#define _XM_NO_INTRINSICS_

#include "Types.h"
#include "Values.h"
#include "Struct.h"

// STL
#include <memory>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
using namespace std;

// WIN
#include <windows.h>
#include <assert.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

#define CHECK(p)	assert(SUCCEEDED(p))

//Engine
#include "graphics.h"
#include "IndexBuffer.h"
#include "Pipeline/01. InputAssembler/VertexBuffer.h"
#include "Pipeline/01. InputAssembler/InputLayout.h"
#include "Pipeline/00. Geometry/Geometry.h"
#include "Pipeline/00. Geometry/GeometryHelper.h"
#include "Pipeline/00. Geometry/VertexData.h"
#include "Pipeline/02. VertexShader/Shader.h"
#include "Pipeline/02. VertexShader/ConstantBuffer.h"
#include "Pipeline/03. Rasterizer/BlendState.h"
#include "Pipeline/03. Rasterizer/RasterizerState.h"
#include "Pipeline/03. Rasterizer/SamplerState.h"
#include "Pipeline/04. PixelShader/Texture.h"
#include "Pipeline/Pipeline.h"
#include "GameObject/Transform.h"
// #include "GameObject/MonoBehaviour.h"



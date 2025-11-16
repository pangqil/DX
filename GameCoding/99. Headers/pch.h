#pragma once

#define _XM_NO_INTRINSICS_

#include "Struct.h"
#include "Types.h"
#include "Values.h"

// STL
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
using namespace std;

// WIN
#include <assert.h>
#include <windows.h>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
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
#include "Pipeline.h"
#include "00. Geometry/Geometry.h"
#include "00. Geometry/GeometryHelper.h"
#include "00. Geometry/VertexData.h"
#include "01. InputAssembler/IndexBuffer.h"
#include "01. InputAssembler/InputLayout.h"
#include "01. InputAssembler/VertexBuffer.h"
#include "02. VertexShader/ConstantBuffer.h"
#include "02. VertexShader/Shader.h"
#include "03. Rasterizer/BlendState.h"
#include "03. Rasterizer/RasterizerState.h"
#include "03. Rasterizer/SamplerState.h"
#include "04. PixelShader/Texture.h"

// #include "GameObject/MonoBehaviour.h"



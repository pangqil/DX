#pragma once

struct VertexTextureData
{
	Vec3 position = { 0, 0, 0 };
	Vec2 uv = { 0, 0 };

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};//이 데이터는 CreateInputLayout과 정확히 매칭되어야 한다.

struct VertexColorData
{
	Vec3 position = {0, 0, 0};
	Color color = {0, 0, 0, 0 };

	static vector<D3D11_INPUT_ELEMENT_DESC> descs;
};
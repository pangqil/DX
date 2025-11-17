#pragma once
#include "Manager/Resource/ResourceBase.h"

class ShaderBase;
class Texture;

class Material : public ResourceBase
{
    using Super = ResourceBase;

public:
    Material();
    virtual ~Material();

    auto GetShader() { return _shader; }
    auto GetTexture() { return _texture; }

    void SetShader(shared_ptr<ShaderBase> shader) { _shader = shader; }
    void SetTexture(shared_ptr<Texture> texture) { _texture = texture;}
	
private:
    shared_ptr<ShaderBase> _shader;

    // ���̴��� �ѱ�� �°� ���ڵ�
    shared_ptr<Texture> _texture;
};


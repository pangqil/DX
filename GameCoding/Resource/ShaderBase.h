#pragma once
#include "Manager/Resource/ResourceBase.h"

class ShaderBase : public ResourceBase
{
    using Super = ResourceBase;
public:
    ShaderBase();
    virtual ~ShaderBase();

    shared_ptr<InputLayout> GetInputLayout() { return _inputLayout; }
    shared_ptr<VertexShader> GetVertexShader() { return _vertexShader; }
    shared_ptr<PixelShader> GetPixelShader() { return _pixelShader; }	

private:
    friend class ResourceManager;

    shared_ptr<InputLayout> _inputLayout;
    shared_ptr<VertexShader> _vertexShader;
    shared_ptr<PixelShader> _pixelShader;
};


#pragma once
#include "Componen/Component.h"
#include "Resource/Material.h"
#include "Resource/Texture.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
    using Super = Component;
public:
    MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    virtual ~MeshRenderer();

    void SetMaterial(shared_ptr<Material> material) { _material = material; }
    void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
    void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
    void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); };

    auto GetMaterial() { return _material; }
    auto GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
    auto GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
    auto GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }

    shared_ptr<Mesh> GetMesh() { return _mesh; }
    shared_ptr<Texture> GetTexture() { return GetMaterial()->GetTexture(); }

private:
    ComPtr<ID3D11Device> _device;

    friend class RenderManager;

    // Mesh
    shared_ptr<Mesh> _mesh;
    shared_ptr<Material> _material;
};
//Mesh를 어떻게 그릴지 정의하기 위해서는 3가지(mesh, Shader)를 필요로 한다. Color나 Texture는 기법에 따라 달라질 수 있으나 전자는 그렇지 않다.
//material은 mesh에 씌우는 껍질이며, material(Texture, Shader, Color)등이 존재한다. 



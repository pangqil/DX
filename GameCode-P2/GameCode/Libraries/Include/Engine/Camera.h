#pragma once
#include "Component.h"

enum class ProjectionType
{
    Perspective,
    Orthographic,
};



class Camera : public Component
{
    using Super=Component;
public:
    Camera();
    virtual ~Camera();

    virtual void Update() override;

    void SetProjectionType(ProjectionType type) {_type=type;}
    ProjectionType GetProjectionType() {return _type;}

    void UpdateMatrix();

    void SetNear(float value) { _near = value; }
    void SetFar(float value) { _far = value; }
    void SetFOV(float value) { _fov = value; }
    void SetWidth(float value) { _width = value; }
    void SetHeight(float value) { _height = value; }

    Matrix& GetViewMatrix() { return _matView; }
    Matrix& GetProjectionMatrix() { return _matProjection; }

private:
    ProjectionType _type=ProjectionType::Orthographic;

    Matrix _matView = Matrix::Identity;
    Matrix _matProjection = Matrix::Identity;


    float _near = 1.f;
    float _far = 1000.f;
    float _fov = XM_PI / 4.f;
    float _width = 0.f;
    float _height = 0.f;

public:
    static Matrix S_MatView;
    static Matrix S_MatProjection;
};
/*
Camera는 View와 Projection을 다루는데, 
View는 vec3타입의 up, focus, eye 3개를 가지고 있는 타입이며, 
projection은 여기서 fov, aspect, near등이 추가된다.
최종적으로 저 3개의 변수와 view를 활용해 사용자에게 Ortho로 보여줄것인지, 
perspective로 보여줄것인지를 정한다.
ortho(직교)는 보통 ui나 지도, sprite등에 사용되며 perspective과 원금감이 있는 
우리의 시뮬레이션 화면이다.
*/
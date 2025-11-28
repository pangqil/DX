#pragma once
#include "../Component.h"

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

private:
    ProjectionType _type=ProjectionType::Orthographic;

public:
    static Matrix S_MatView;
    static Matrix S_MatProjection;
};
//Camera는 View와 Projection을 다루는데, View는 vec3타입의 up, focus, eye 3개를 가지고 있는 타입이며, projection은 여기서 fov, aspect, near등이 추가된다.
//최종적으로 저 3개의 변수와 view를 활용해 사용자에게 Ortho로 보여줄것인지, perspective로 보여줄것인지를 정한다.
//ortho(직교)는 보통 ui나 지도, sprite등에 사용되며 perspective과 원금감이 있는 우리의 시뮬레이션 화면이다.
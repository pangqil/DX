# DX

**DirectX 11 렌더링 파이프라인을 직접 구현하며 공부한 기록** (2025.10 ~ 2025.12)

`C++` `DirectX 11` `HLSL` `Effects11(FX11)` `DirectXTex` `Assimp` `ImGui` `SimpleMath`

---

## 📖 공부 방식

**1. 단계마다 프로젝트를 복제해서 쌓아 올리기**

- 한 프로젝트를 계속 덮어쓰지 않고, 단계가 끝나면 폴더째 복제한 뒤 다음 기능을 추가
- 그래서 폴더 하나하나가 그 시점의 완성된 스냅숏 → 어느 단계든 바로 열어서 실행·비교 가능

**2. 파이프라인 단계별로 코드를 나눠 보기**

- 첫 단계에서는 D3D11 리소스를 파이프라인 순서대로 폴더를 나눠 직접 작성
  - `00. Geometry` → `01. InputAssembler` → `02. VertexShader` → `03. Rasterizer` → `04. PixelShader`
- 각 단계가 어떤 리소스를 만들고 언제 바인딩하는지 구분하고, 초기화 순서는 `order.md`에 따로 정리
  - 정점 데이터 준비 → 셰이더 컴파일(Blob) → Vertex/Index Buffer 생성 → Blob과 정점 DESC로 InputLayout 생성

**3. 기능 하나 = 데모 하나**

- 새 개념은 `Client/NN. XxxDemo` + `Shaders/NN. Xxx.fx` 한 쌍으로 따로 구현
- 번호 순서가 곧 공부 순서 → 삼각형 하나에서 시작해 조명, 모델, 애니메이션, 인스턴싱까지 단계적으로 확장

**4. 엔진 구조로 정리하기**

- 데모가 늘어나면서 공통 코드를 `Engine`, 실습 코드를 `Client`로 분리
- GameObject · Component · Transform · MonoBehaviour 기반의 컴포넌트 구조와 Scene · Resource · Render · Time · Input 매니저를 직접 구성

---

## 🗺 단계별 진행

| 순서 | 폴더 | 기간 | 주요 내용 |
| --- | --- | --- | --- |
| 1 | `RenderingPipeline` | 2025.10 ~ 11 | Win32 + D3D11 초기화, 파이프라인 단계별 클래스 분리, GameObject·Component 구조, Camera·MeshRenderer, 각종 매니저, Animator |
| 2 | `DemoPipeline` | 2025.11 | Engine/Client 분리, FX11·DirectXTex 도입. 데모 01~18 (Triangle → Quad → ConstBuffer → Camera → Texture → Sampler → HeightMap → Normal → Mesh → DepthStencil → Ambient·Diffuse·Specular·Emissive → Lighting → Material → Normal Mapping) |
| 3 | `MeshImportPipeline` | 2025.12 | Assimp 기반 `AssimpTool`로 외부 모델을 자체 포맷으로 변환, Static Mesh 렌더링, ImGui |
| 4 | `AnimationPipeline` | 2025.12 | 모델 계층 구조 렌더링(Model Demo), 스키닝 애니메이션 시작 |
| 5 | `InstancingPipeline` | 2025.12 | 스키닝 애니메이션, 애니메이션 전환(Tween), Skybox, 인스턴싱 데모 19~22 (Instancing → Mesh → Model → Animation Instancing) |
| 6 | `FinalPipeline` | 2025.12 | 지금까지의 기능을 통합한 Render Demo(23), Frustum, InstancingManager |

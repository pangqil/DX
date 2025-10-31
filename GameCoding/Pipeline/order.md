프레임워크의 논리적 초기화 순서는 다음과 같습니다.

1. 정점 데이터 준비: $\text{Geometry}$ 클래스를 사용하여 $\text{CPU}$ 메모리에 $\text{vertices}$와 
$\text{indices}$를 채웁니다.
2. 셰이더 컴파일: $\text{Vertex Shader}$ 파일(.hlsl)을 컴파일하여 **$\text{ID3DBlob}$**을 얻습니다.
3. 버퍼 생성: $\text{VertexBuffer::Create}$ 및 **$\text{IndexBuffer::Create}$**를 호출하여 $\text{GPU}$에 데이터를 업로드합니다.
4. 레이아웃 생성: **$\text{InputLayout::Create}$**를 호출할 때, 미리 정의한 $\text{VertexData}$의 $\text{DESC}$ 배열과 **$\text{Blob}$**을 함께 넘겨 $\text{InputLayout}$을 생성합니다.
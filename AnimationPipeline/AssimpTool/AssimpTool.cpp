#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{

	{
		shared_ptr<Converter> converter = make_shared<Converter>();
		// FBX -> Memory
		// Memory -> CustomData (File)
		// CustomData (File) -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");
		
	}
	
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}

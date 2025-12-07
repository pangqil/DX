#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct asBone
{
	string name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct asMesh
{
	string name;
	aiMesh* mesh;
	vector<VertexType> vertices;
	vector<uint32> indices;

	int32 boneIndex;
	string materialName;
};

struct asMaterial
{
	string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	string diffuseFile;
	string specularFile;
	string normalFile;
};

struct asBlendWeight
{
	void Set(uint32 index, uint32 boneindex, float weight)
	{
		float i=(float)boneindex;
		float w=weight;

		switch (index)
		{
		case 0 : indices.x=i;weights.x=w; break;
		case 1 : indices.y=i;weights.y=w; break;
		case 2 : indices.z=i;weights.z=w; break;
		case 3 : indices.w=i;weights.w=w; break;
		}
	}
	
	Vec4 indices = Vec4(0, 0, 0, 0);
	Vec4 weights = Vec4(0, 0, 0, 0);
};

struct asBoneWeights
{
	void AddWeights(uint32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
			return;

		auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) { return weight > p.second; });
	//이거 뭐임
		//insert (1, 0.4) (2, 0.5)
		boneWeights.insert(findIt, Pair(boneIndex, weight));
	}

	asBlendWeight GetBlendWeights()
	{
		asBlendWeight blendWeights;

		for (uint32 i = 0; i < boneWeights.size(); i++)
		{
			if (i >= 4)
				break;

			blendWeights.Set(i, boneWeights[i].first, boneWeights[i].second);
		}

		return blendWeights;
	}

	void Normalize()
	{
		if (boneWeights.size() >= 4)
			boneWeights.resize(4);

		float totalWeight = 0.f;
		for (const auto& item : boneWeights)
			totalWeight += item.second;

		float scale = 1.f / totalWeight;
		for (auto& item : boneWeights)
			item.second *= scale;
	}

	using Pair = pair<int32, float>;
	vector<Pair> boneWeights;
};

struct asKeyframeData
{
	float time;
	Vec3 Scale;
	Quaternion rotation;//float3랑 같으면서 짐벌락 문제를 해결하기 위해서, xyz 이외에 w를 사용하는 공간.
	Vec3 translation;
};

struct asKeyframe
{
	string boneName;
	vector<asKeyframeData> transforms;
};

struct asAnimation
{
	string name;
	uint32 frameCount;
	float frameRate;
	float duration;
	vector<asKeyframe> keyframes;
};

//Cache
struct asAnimationNode
{
	aiString name;
	vector<asKeyframeData> keyframe;
};
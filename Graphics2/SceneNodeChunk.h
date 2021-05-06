#pragma once

#include "SceneNodeMesh.h"
#include "Graphics2.h"
#include "PerlinNoise.h"
#include "PerlinRevised.h"
#include "SceneNodeTile.h"
#include "SceneNodeWater.h"
#include "SceneNodeTree.h"
#include <math.h>

class SceneNodeChunk : public SceneNodeMesh
{

public:
	SceneNodeChunk(wstring name) : SceneNodeMesh(name) {};

	bool Initialise() override;
	virtual void Render() override;
	virtual void Shutdown() override;

	void GenerateTerrain(XMFLOAT3 terrainOffset, SceneGraph* sceneGraph);
	float terrain[16][16];

	void AddQuad(SceneNodeTile* mesh, float chunkX, float chunkZ, int x, int z, float scl, int index, float heights[4]);

	int chunkSize = 16; //50

	std::vector<SceneNode*> entities;
	SceneNodeTile* ground = new SceneNodeTile(L"Ground");
	SceneNodeTile* water = new SceneNodeWater(L"Water");
	SceneNodeTree* tree = new SceneNodeTree(L"Tree");

private:
	float CalculateHeight(float chunkX, float chunkZ, float x, float z, float tileScale);


};

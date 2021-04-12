#include "SceneNodeTerrain.h"
#include "SceneNodeWater.h"
#include "SceneNodeChunk.h"

bool SceneNodeTerrain::Initialise()
{
    return true;
}

void SceneNodeTerrain::Render()
{
	GenerateChunkIfWeNeedTo();
}

void SceneNodeTerrain::Shutdown()
{
}

void SceneNodeTerrain::SetSceneGraph(SceneGraphPointer ptr)
{
    this->sceneGraph = ptr;
}

void SceneNodeTerrain::GenerateChunkAt(XMFLOAT3 position)
{
	shared_ptr<SceneNodeChunk> chunk = make_shared<SceneNodeChunk>(L"Chunk");
	sceneGraph->Add(chunk);
	chunk->GenerateTerrain(position, sceneGraph);
	chunks.push_back({ position });
}

void SceneNodeTerrain::GenerateChunkIfWeNeedTo()
{
	float camX = ChunkX();
	float camZ = ChunkZ();

	for (float x = camX - viewSize; x <= camX + viewSize; x++) {
		for (float z = camZ - viewSize; z <= camZ + viewSize; z++) {
			if (!ChunkExistsAt(XMFLOAT3(x, 0, z))) {
				GenerateChunkAt(XMFLOAT3(x, 0, z));
			}
		}
	}
}

bool SceneNodeTerrain::ChunkExistsAt(XMFLOAT3 position)
{
	for (Chunk chunk : chunks) {
		if (round(chunk.position.x) == round(position.x) &&
			round(chunk.position.y) == round(position.y) &&
			round(chunk.position.z) == round(position.z));
			return true;
	}
	return false;
}

float SceneNodeTerrain::ChunkX(void)
{
	XMVECTOR cameraPosition = DirectXFramework::GetDXFramework()->GetCamera()->GetCameraPosition();
	XMFLOAT4 position;
	XMStoreFloat4(&position, cameraPosition);
	return roundf(position.x / (1 * chunkSize));
}

float SceneNodeTerrain::ChunkZ(void)
{
	XMVECTOR cameraPosition = DirectXFramework::GetDXFramework()->GetCamera()->GetCameraPosition();
	XMFLOAT4 position;
	XMStoreFloat4(&position, cameraPosition);
	return roundf(position.z / (1 * chunkSize));
}

#pragma once

#include "SceneNodeEntity.h"
#include "Graphics2.h"

class SceneNodeFish : public SceneNodeEntity
{

public:
	SceneNodeFish(wstring name) : SceneNodeEntity(name) {};

	bool Initialise() override;
	virtual void Tick(XMMATRIX& completeTransform) override;
	virtual void SetupMesh() override;
	virtual void Shutdown() override;

private:
	float rotationY;
};
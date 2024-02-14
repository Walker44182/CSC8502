#pragma once
#include "../nclgl/SceneNode.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/ChildMeshInterface.h"
#include "../nclgl/HeightMap.h"
#include <vector>

class Terrain :public SceneNode {
public:
	Terrain();
	~Terrain() {};
	void Update(float dt) override;
protected:
	SceneNode* heightMapNode;
	SceneNode* MinecraftTerrain;
	SceneNode* Pool_1;
	SceneNode* Wolf;
	SceneNode* ArmourStand;
	SceneNode* Creeper;
	SceneNode* Panda;
	SceneNode* Pickaxe;
	SceneNode* RedstoneLamp;
	SceneNode* ShroomLight;
	SceneNode* Rotate1;
	SceneNode* Fountain;
	SceneNode* Pool_2;

	HeightMap* heightMap;
	Mesh* minecraftTerrain;
	Mesh* pool_1;
	Mesh* pool_2;
	OBJMesh* wolf;
	OBJMesh* armourStand;
	OBJMesh* creeper;
	OBJMesh* panda;
	OBJMesh* pickaxe;
	OBJMesh* fountain;
	Mesh* redstoneLamp;
	Mesh* shroomLight;
	GLuint trainTexture;
	GLuint quartzTexture;
	GLuint glassTexture;
	GLuint stainedGlassTexture;
	GLuint quartzBumpTexture;
	GLuint quartzSpecTexture;
	GLuint glassBumpTexture;
	GLuint glassSpecTexture;

	float sceneTime = 0.0f;

	Vector3 positions[10];
	void SetPositions();
};
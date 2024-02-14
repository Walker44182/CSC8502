#pragma once
#include "../nclgl/SceneNode.h"
#include "../nclgl/OBJMesh.h"
#include "../nclgl/ChildMeshInterface.h"

class SolarSystem :public SceneNode {
public:
	SolarSystem();
	~SolarSystem() {};
	void Update(float dt) override;

protected:
	SceneNode* Sun;
	SceneNode* Mercury;
	SceneNode* Venus;
	SceneNode* Earth;
	SceneNode* Mars;
	SceneNode* MirrorPlanet;
	SceneNode* Moon;
	SceneNode* Satellite;

	Mesh* sun;
	Mesh* mercury;
	Mesh* venus;
	Mesh* earth;
	Mesh* mars;
	Mesh* mirrorPlanet;
	Mesh* moon;
	OBJMesh* satellite;

	bool sunlight = true;
};
#pragma once
#include "../nclgl/SceneNode.h"
#include <vector>

class Animation :public SceneNode {
public:
	Animation();
	~Animation() {}
	void Update(float dt) override;

protected:
	Mesh* mesh1;
	MeshMaterial* material1;
	MeshAnimation* anim1;
	vector<GLuint> matTextures1;

	Mesh* mesh2;
	MeshMaterial* material2;
	MeshAnimation* anim2;
	vector<GLuint> matTextures2;

	Mesh* mesh3;
	MeshMaterial* material3;
	MeshAnimation* anim3;
	vector<GLuint> matTextures3;

	SceneNode* AnimationNode;
	SceneNode* Character1;
	SceneNode* Character2;
	SceneNode* Chicken1;
	SceneNode* Chicken2;
	SceneNode* Chicken3;
	SceneNode* BirchTree1;
	SceneNode* BirchTree2;
	SceneNode* BirchTree3;
	SceneNode* BirchTree4;
	SceneNode* BirchTree5;
}; 
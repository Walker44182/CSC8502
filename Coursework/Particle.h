#pragma once
#include "../nclgl/SceneNode.h"
#include <vector>

struct Particle {
	Vector3 speed;
	Vector3 position;
};

class Snow :public SceneNode {
public:
	Snow();
	~Snow() {};
	void Update(float dt) override;

	void SetSnowActive(bool s) { isSnowActive = s; }
	bool GetSnowActive() const { return isSnowActive; }
protected:
	Mesh* snowball;

	float numLaunchParticles = 1500;
	vector<Particle> particles;

	bool isSnowActive;
};

class Block :public SceneNode {
public:
	Block();
	~Block() {};
	void Update(float dt) override;

	void SetBlocksActive(bool s) { isBlocksActive = s; }
	bool GetBlocksActive() const { return isBlocksActive; }
protected:
	Mesh* cube;
	GLuint textures[15];

	float numLaunchParticles = 500;
	vector<Particle> particles;

	bool isBlocksActive;
};
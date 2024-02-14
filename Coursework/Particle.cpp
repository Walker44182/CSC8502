#include "Particle.h"

Snow::Snow() {
	std::cout << "\n-------------------Loading Snowball Particles...-------------------\n\n";

	snowball = Mesh::LoadFromMeshFile("Sphere.msh");
	snowball->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"diamond_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	if (!snowball->GetTexture()) {
		init = false;
		std::cout << "Snowball Particle: Texture Load Failed!!" << std::endl;
		return;
	}

	for (int i = 0; i < numLaunchParticles; ++i) {
		Particle particle;
		particle.position = Vector3((rand() % 5000) - 1500, 3000, (rand() % 5000) - 1750);
		float speed = (rand() % 15) + 1;
		float scale = (rand() % 10) + 10;
		particle.speed = Vector3(0, -speed, 0);
		particles.push_back(particle);

		SceneNode* SnowBall = new SceneNode();
		SnowBall->SetMesh(snowball);
		SnowBall->SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f));
		SnowBall->SetDrawMethodType(6);
		SnowBall->SetTransform(Matrix4::Translation(particle.position));
		SnowBall->SetModelScale(Vector3(scale, scale, scale));
		AddChild(SnowBall);
	}
	isSnowActive = false;
}

void Snow::Update(float dt) {
	if (isSnowActive) {
		for (int i = 0; i < numLaunchParticles; i++) {
			if (children[i]->GetTransform().GetPositionVector().y <= 0) {
				children[i]->SetTransform(Matrix4::Translation(
					Vector3((rand() % 5000) - 1500, 3000, (rand() % 5000) - 1750)));
				float speed = (rand() % 15) + 1;
				particles[i].speed = Vector3(0, -speed, 0);
			}
			children[i]->SetTransform(children[i]->GetTransform() * Matrix4::Translation(particles[i].speed));
		}
	}
	SceneNode::Update(dt);
}

Block::Block() {
	std::cout << "\n-------------------Loading Block Particles...-------------------\n\n";

	cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");

	textures[0] = SOIL_load_OGL_texture(TEXTUREDIR"diamond_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[1] = SOIL_load_OGL_texture(TEXTUREDIR"sea_lantern.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[2] = SOIL_load_OGL_texture(TEXTUREDIR"glowstone.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[3] = SOIL_load_OGL_texture(TEXTUREDIR"amethyst_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[4] = SOIL_load_OGL_texture(TEXTUREDIR"beacon.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[5] = SOIL_load_OGL_texture(TEXTUREDIR"emerald_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[6] = SOIL_load_OGL_texture(TEXTUREDIR"enchanting_table_top.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[7] = SOIL_load_OGL_texture(TEXTUREDIR"jack_o_lantern.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[8] = SOIL_load_OGL_texture(TEXTUREDIR"magenta_glazed_terracotta.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[9] = SOIL_load_OGL_texture(TEXTUREDIR"ochre_froglight_top.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[10] = SOIL_load_OGL_texture(TEXTUREDIR"pearlescent_froglight_top.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[11] = SOIL_load_OGL_texture(TEXTUREDIR"pink_stained_glass.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[12] = SOIL_load_OGL_texture(TEXTUREDIR"tnt_side.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[13] = SOIL_load_OGL_texture(TEXTUREDIR"verdant_froglight_top.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	textures[14] = SOIL_load_OGL_texture(TEXTUREDIR"yellow_glazed_terracotta.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (!textures) {
		init = false;
		std::cout << "Block Particle: Texture Load Failed!!" << std::endl;
		return;
	}

	for (int i = 0; i < numLaunchParticles; ++i) {
		Particle particle;
		particle.position = Vector3((rand() % 2000) - 2000, 200, (rand() % 2000) - 2000);
		float speed = (rand() % 15) + 1;
		float scale = (rand() % 5) + 10;
		particle.speed = Vector3(0, speed, 0);
		particles.push_back(particle);

		SceneNode* BlockNode = new SceneNode();
		BlockNode->SetMesh(cube);
		BlockNode->SetTexture(textures[rand() % 15]);
		BlockNode->SetColour(Vector4(1,1,1,1));
		BlockNode->SetDrawMethodType(7);
		BlockNode->SetTransform(Matrix4::Translation(particle.position));
		BlockNode->SetModelScale(Vector3(scale, scale, scale));
		AddChild(BlockNode);
	}
	isBlocksActive = false;
}

void Block::Update(float dt) {
	if (isBlocksActive) {
		for (int i = 0; i < numLaunchParticles; i++) {
			if (children[i]->GetColour().w <= 0) {
				children[i]->SetTransform(Matrix4::Translation(
					Vector3((rand() % 2000) - 2000, 200, (rand() % 2000) - 2000)));
				children[i]->SetColour(Vector4(1, 1, 1, 1));
				float speed = (rand() % 15) + 1;
				particles[i].speed = Vector3(0, speed, 0);
			}
			children[i]->SetTransform(children[i]->GetTransform() * Matrix4::Translation(particles[i].speed) *
				                                                    Matrix4::Rotation((rand() % 10), Vector3(0, rand() & 2, 0)));
			children[i]->SetColour(Vector4(1, 1, 1, children[i]->GetColour().w - 0.003 * (rand() % 10)));
		}
	}
	SceneNode::Update(dt);
}
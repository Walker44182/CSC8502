#include "Terrain.h"

Terrain::Terrain() {
	std::cout << "\n-------------------Loading Terrain...-------------------\n\n";

	SetPositions();

	heightMap = new HeightMap(TEXTUREDIR"noise.png");
	heightMap->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"moss_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"moss_block_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"moss_block_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	glBindTexture(GL_TEXTURE_2D, heightMap->GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, heightMap->GetBumpTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, heightMap->GetSpecTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	minecraftTerrain = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
	minecraftTerrain->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"daylight_detector_top.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	minecraftTerrain->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"daylight_detector_top_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	minecraftTerrain->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"daylight_detector_top_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	pool_1 = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
	pool_1->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"packed_ice.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	pool_1->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"packed_ice_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	pool_1->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"packed_ice_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	pool_2 = Mesh::LoadFromMeshFile("Sphere.msh");
	pool_2->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"water.tga",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	pool_2->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"waterbump.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	pool_2->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"packed_ice_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	redstoneLamp = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
	redstoneLamp->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"redstone_lamp_on.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	redstoneLamp->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"redstone_lamp_on_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	redstoneLamp->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"redstone_lamp_on_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	shroomLight = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
	shroomLight->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"shroomlight.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	shroomLight->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"shroomlight_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	shroomLight->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"shroomlight_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	quartzTexture = (SOIL_load_OGL_texture(TEXTUREDIR"quartz_block_bottom.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	quartzBumpTexture = (SOIL_load_OGL_texture(TEXTUREDIR"quartz_block_bottom_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	quartzSpecTexture = (SOIL_load_OGL_texture(TEXTUREDIR"quartz_block_bottom_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	glassTexture = (SOIL_load_OGL_texture(TEXTUREDIR"glass.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	stainedGlassTexture = (SOIL_load_OGL_texture(TEXTUREDIR"stainedglass.tga",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	glassBumpTexture = (SOIL_load_OGL_texture(TEXTUREDIR"glass_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	trainTexture = (SOIL_load_OGL_texture(TEXTUREDIR"Train.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!heightMap->GetTexture() || !heightMap->GetBumpTexture()|| !heightMap->GetSpecTexture() ||
		!minecraftTerrain->GetTexture() || !minecraftTerrain->GetBumpTexture()|| !minecraftTerrain->GetSpecTexture() ||
		!pool_1->GetTexture() || !pool_1->GetBumpTexture()|| !pool_1->GetSpecTexture() ||
		!pool_2->GetTexture() || !pool_2->GetBumpTexture() ||
		!redstoneLamp->GetTexture() || !shroomLight->GetTexture() || !shroomLight->GetSpecTexture() ||
		!quartzTexture || !quartzBumpTexture|| !quartzSpecTexture ||
		!glassTexture || !stainedGlassTexture || !glassBumpTexture) {
		init = false;
		std::cout << "Terrain: Texture Load Failed!!" << std::endl;
		return;
	}

	Vector3 hSize = heightMap->GetHeightmapSize();
	heightMapNode = new SceneNode(heightMap, Vector4(1, 1, 1, 1));
	heightMapNode->SetDrawMethodType(3);
	heightMapNode->SetCulled(false);
	heightMapNode->SetModelScale(Vector3(1, 1, 1));
	heightMapNode->SetTransform(Matrix4::Translation(Vector3(-2000,0,-2000)));
	AddChild(heightMapNode);

	MinecraftTerrain = new SceneNode(minecraftTerrain, Vector4(1, 1, 1, 1));
	MinecraftTerrain->SetDrawMethodType(3);
	MinecraftTerrain->SetCulled(false);
	MinecraftTerrain->SetModelScale(hSize * 0.25f);
	MinecraftTerrain->SetTransform(Matrix4::Translation(Vector3(1000, 110, 1000)));
	heightMapNode->AddChild(MinecraftTerrain);

	Pool_1 = new SceneNode(pool_1, Vector4(1, 1, 1, 1));
	Pool_1->SetEmissive(true);
	Pool_1->SetDrawMethodType(4);
	Pool_1->SetModelScale(Vector3(250,1,250));
	Pool_1->SetTransform(Matrix4::Translation(Vector3(0, 137, 0)));
	MinecraftTerrain->AddChild(Pool_1);

	OBJMesh* n0 = new OBJMesh;
	n0->LoadOBJMesh(MESHDIR"legopickaxe.obj");
	pickaxe = n0;
	Pickaxe = new SceneNode(pickaxe, Vector4(1, 1, 1, 1));
	Pickaxe->SetDrawMeshType(2);
	Pickaxe->SetOBJMesh(pickaxe);
	Pickaxe->SetModelScale(Vector3(30, 30, 30));
	Pickaxe->SetTransform(Matrix4::Translation(Vector3(600, 137, -430)) *
		Matrix4::Rotation(90.0f, Vector3(0, 1, 0)));
	MinecraftTerrain->AddChild(Pickaxe);

	Rotate1 = new SceneNode();
	Rotate1->SetTransform(Matrix4::Translation(Vector3(600, 137, -430)));
	MinecraftTerrain->AddChild(Rotate1);

	OBJMesh* n1 = new OBJMesh;
	n1->LoadOBJMesh(MESHDIR"Wolf.obj");
	wolf = n1;
	Wolf = new SceneNode(wolf, Vector4(1, 1, 1, 1));
	Wolf->SetDrawMeshType(2);
	Wolf->SetOBJMesh(wolf);
	Wolf->SetModelScale(Vector3(100, 100, 100));
	Wolf->SetTransform(Matrix4::Translation(Vector3(150, 0, 150)) *
		               Matrix4::Rotation(-180.0f, Vector3(0, 1, 0)));
	Rotate1->AddChild(Wolf);

	OBJMesh* n2 = new OBJMesh;
	n2->LoadOBJMesh(MESHDIR"Train.obj");
	armourStand = n2;
	ArmourStand = new SceneNode(armourStand, Vector4(1, 1, 1, 1));
	ArmourStand->SetDrawMeshType(2);
	ArmourStand->SetDrawMethodType(2);
	ArmourStand->SetOBJMesh(armourStand);
	ArmourStand->SetModelScale(Vector3(60, 60, 60));
	ArmourStand->SetTransform(Matrix4::Translation(Vector3(-500, 137, 0)) * 
		                      Matrix4::Rotation(-90.0f, Vector3(0, 1, 0)));
	ArmourStand->SetTexture(trainTexture);
	MinecraftTerrain->AddChild(ArmourStand);

	OBJMesh* n3 = new OBJMesh;
	n3->LoadOBJMesh(MESHDIR"Creeper.obj");
	creeper = n3;
	Creeper = new SceneNode(creeper, Vector4(1, 1, 1, 1));
	Creeper->SetDrawMeshType(2);
	Creeper->SetOBJMesh(creeper);
	Creeper->SetModelScale(Vector3(100, 100, 100));
	Creeper->SetTransform(Matrix4::Translation(Vector3(-500, 137, -200)) *
		Matrix4::Rotation(-90.0f, Vector3(0, 1, 0)));
	MinecraftTerrain->AddChild(Creeper);

	OBJMesh* n4 = new OBJMesh;
	n4->LoadOBJMesh(MESHDIR"Panda.obj");
	panda = n4;
	Panda = new SceneNode(panda, Vector4(1, 1, 1, 1));
	Panda->SetDrawMeshType(2);
	Panda->SetOBJMesh(panda);
	Panda->SetModelScale(Vector3(100, 100, 100));
	Panda->SetTransform(Matrix4::Translation(Vector3(-500, 137, -430)) *
		                Matrix4::Rotation(-90.0f, Vector3(0, 1, 0)));
	MinecraftTerrain->AddChild(Panda);

	RedstoneLamp = new SceneNode(redstoneLamp, Vector4(1, 1, 1, 1));
	RedstoneLamp->SetEmissive(true);
	RedstoneLamp->SetModelScale(Vector3(30,30,30));
	RedstoneLamp->SetTransform(Matrix4::Translation(Vector3(-650, 337, 100)));
	MinecraftTerrain->AddChild(RedstoneLamp);

	ShroomLight = new SceneNode(shroomLight, Vector4(1, 1, 1, 1));
	ShroomLight->SetEmissive(true);
	ShroomLight->SetModelScale(Vector3(30, 30, 30));
	ShroomLight->SetTransform(Matrix4::Translation(Vector3(-350, 437, -600)));
	MinecraftTerrain->AddChild(ShroomLight);

	OBJMesh* n5 = new OBJMesh;
	n5->LoadOBJMesh(MESHDIR"fountain.obj");
	fountain = n5;
	Fountain = new SceneNode(fountain, Vector4(1, 1, 1, 1));
	Fountain->SetCulled(false);
	Fountain->SetDrawMeshType(2);
	Fountain->SetOBJMesh(fountain);
	Fountain->SetModelScale(Vector3(700, 700, 700));
	Fountain->SetTransform(Matrix4::Translation(Vector3(3000, 100, 1000)));
	heightMapNode->AddChild(Fountain);

	Pool_2 = new SceneNode(pool_2, Vector4(1, 1, 1, 1));
	Pool_2->SetCulled(false);
	Pool_2->SetEmissive(true);
	Pool_2->SetDrawMethodType(4);
	Pool_2->SetRotate(true);
	Pool_2->SetModelScale(Vector3(500, 1, 500));
	Pool_2->SetTransform(Matrix4::Translation(Vector3(3000, 200, 1000)));
	heightMapNode->AddChild(Pool_2);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			Mesh* quartzBlock = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
			quartzBlock->SetTexture(quartzTexture);
			quartzBlock->SetBumpTexture(quartzBumpTexture);
			quartzBlock->SetSpecTexture(quartzSpecTexture);
			SceneNode* QuartzBlock = new SceneNode(quartzBlock, Vector4(1, 1, 1, 1));
			QuartzBlock->SetDrawMethodType(3);
			QuartzBlock->SetModelScale(Vector3(60, 60, 60));
			QuartzBlock->SetTransform(Matrix4::Translation(
				                       Vector3(-750, 137 + 120 * i, -500 + j * 120)));
			MinecraftTerrain->AddChild(QuartzBlock);
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			Mesh* glassBlock = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
			glassBlock->SetTexture(glassTexture);
			glassBlock->SetBumpTexture(glassBumpTexture);
			SceneNode* GlassBlock = new SceneNode(glassBlock, Vector4(1, 1, 1, 0.5));
			GlassBlock->SetDrawMethodType(2);
			GlassBlock->SetModelScale(Vector3(60, 60, 60));
			GlassBlock->SetTransform(Matrix4::Translation(
				Vector3(0 - j * 120, 137 + 120 * i, 600)));
			MinecraftTerrain->AddChild(GlassBlock);
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 5; ++j) {
			Mesh* stainedGlassBlock = Mesh::LoadFromMeshFile("OffsetCubeY.msh");
			stainedGlassBlock->SetTexture(stainedGlassTexture);
			stainedGlassBlock->SetBumpTexture(glassBumpTexture);
			stainedGlassBlock->SetSpecTexture(glassSpecTexture);
			SceneNode* StainedGlassBlock = new SceneNode
			                       (stainedGlassBlock, Vector4(1, 1, 1, 0.5));
			StainedGlassBlock->SetDrawMethodType(2);
			StainedGlassBlock->SetModelScale(Vector3(60, 60, 60));
			StainedGlassBlock->SetTransform(Matrix4::Translation(
				Vector3(0 - j * 120, 137 + 120 * i, 720)));
			MinecraftTerrain->AddChild(StainedGlassBlock);
		}
	}

	for (int i = 0; i < 8; ++i) {
		OBJMesh* crystal = new OBJMesh;
		crystal->LoadOBJMesh(MESHDIR"crystal2.obj");
		SceneNode* Crystal = new SceneNode(crystal, Vector4(1, 1, 1, 1));
		Crystal->SetEmissive(true);
		Crystal->SetDrawMeshType(2);
		Crystal->SetOBJMesh(crystal);
		Crystal->SetModelScale(Vector3(5, 5, 5));
		Crystal->SetTransform(Matrix4::Translation(Vector3(1, 1, 1) * positions[i]));
		heightMapNode->AddChild(Crystal);
	}
}

void Terrain::SetPositions() {
	positions[0] = Vector3(2300, 300, 2300);
	positions[1] = Vector3(500,  300, 3000);
	positions[2] = Vector3(2000, 300, 4000);
	positions[3] = Vector3(3500, 300, 2500);
	positions[4] = Vector3(4000, 300, 3500);
	positions[5] = Vector3(3000, 300, 3000);
	positions[6] = Vector3(2300, 300, 3700);
	positions[7] = Vector3(3600, 300, 2500);
}

void Terrain::Update(float dt) {
	sceneTime += dt;
	Pickaxe->SetTransform(Pickaxe->GetTransform() *
		                  Matrix4::Translation(Vector3(0, 0.5 * sin(10* sceneTime), 0)) *
		                  Matrix4::Rotation(40.0f * dt, Vector3(0, 1, 0)));
	Rotate1->SetTransform(Rotate1->GetTransform() *
		                 Matrix4::Rotation(-20.0f * dt, Vector3(0, 1, 0)));

	SceneNode::Update(dt);
}
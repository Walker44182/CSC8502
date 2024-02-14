#include "SolarSystem.h"

SolarSystem::SolarSystem() {
	std::cout << "\n-------------------Loading Solar System...-------------------\n\n";

	sun = Mesh::LoadFromMeshFile("Sphere.msh");
	sun->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"2k_sun.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	mercury = Mesh::LoadFromMeshFile("Sphere.msh");
	mercury->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"sea_lantern.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	mercury->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"sea_lantern_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	mercury->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"sea_lantern_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	venus = Mesh::LoadFromMeshFile("Sphere.msh");
	venus->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"glowstone.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	venus->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"glowstone_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	venus->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"glowstone_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	earth = Mesh::LoadFromMeshFile("Sphere.msh");
	earth->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"2k_earth_daymap.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	earth->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"2k_earth_normal_map.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	earth->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"2k_earth_specular_map.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	mars = Mesh::LoadFromMeshFile("Sphere.msh");
	mars->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"nether_gold_ore.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	mars->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"nether_gold_ore_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	mars->SetSpecTexture(SOIL_load_OGL_texture(TEXTUREDIR"nether_gold_ore_s.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	mirrorPlanet = Mesh::LoadFromMeshFile("Sphere.msh");
	mirrorPlanet->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"diamond_block.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	mirrorPlanet->SetBumpTexture(SOIL_load_OGL_texture(TEXTUREDIR"diamond_block_n.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	moon = Mesh::LoadFromMeshFile("Sphere.msh");
	moon->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"2k_moon.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	if (!sun->GetTexture() || !moon->GetTexture() ||
		!mercury->GetTexture() || !mercury->GetBumpTexture() || !mercury->GetSpecTexture() ||
		!venus->GetTexture() || !venus->GetBumpTexture() || !venus->GetSpecTexture() ||
		!earth->GetTexture() || !earth->GetBumpTexture() || !earth->GetSpecTexture() ||
		!mars->GetTexture() || !mars->GetBumpTexture() || !mars->GetSpecTexture() ||
		!mirrorPlanet->GetTexture() || !mirrorPlanet->GetBumpTexture()  ) {
		init = false;
		std::cout << "SolarSystem: Texture Load Failed!!" << std::endl;
		return;
	}
    
	Sun = new SceneNode(sun, Vector4(1, 1, 1, 1));
	Sun->SetCulled(false);
	Sun->SetEmissive(sunlight);
	Sun->SetDrawMethodType(1);
	Sun->SetModelScale(Vector3(200, 200, 200));
	Sun->SetTransform(Matrix4::Translation(Vector3(0, 2000, 0)));
	AddChild(Sun);

	
	Mercury = new SceneNode(mercury, Vector4(1, 1, 1, 1));
	Mercury->SetDrawMethodType(3);
	Mercury->SetModelScale(Vector3(10, 10, 10));
	Mercury->SetTransform(Matrix4::Translation(Vector3(270, 0, 0)));
	Sun->AddChild(Mercury);

	
	Venus = new SceneNode(venus, Vector4(1, 1, 1, 1));
	Venus->SetDrawMethodType(3);
	Venus->SetModelScale(Vector3(20, 20, 20));
	Venus->SetTransform(Matrix4::Translation(Vector3(400, 0, 0)));
	Sun->AddChild(Venus);

	
	Earth = new SceneNode(earth, Vector4(1, 1, 1, 1));
	Earth->SetDrawMethodType(3);
	Earth->SetModelScale(Vector3(40, 40, 40));
	Earth->SetTransform(Matrix4::Translation(Vector3(560, 0, 0)) * 
		                Matrix4::Rotation(180.0f, Vector3(1, 0, 0)));
	Sun->AddChild(Earth);

	
	Mars = new SceneNode(mars, Vector4(1, 1, 1, 1));
	Mars->SetDrawMethodType(3);
	Mars->SetModelScale(Vector3(35, 35, 35));
	Mars->SetTransform(Matrix4::Translation(Vector3(750, 0, 0)));
	Sun->AddChild(Mars);

	
	MirrorPlanet = new SceneNode(mirrorPlanet, Vector4(1, 1, 1, 1));
	MirrorPlanet->SetEmissive(true);
	MirrorPlanet->SetDrawMethodType(4);
	MirrorPlanet->SetModelScale(Vector3(60, 60, 60));
	MirrorPlanet->SetTransform(Matrix4::Translation(Vector3(945, 0, 0)));
	Sun->AddChild(MirrorPlanet);

	
	Moon = new SceneNode(moon, Vector4(1, 1, 1, 1));
	Moon->SetModelScale(Vector3(10, 10, 10));
	Moon->SetTransform(Matrix4::Translation(Vector3(60, 0, 0)) * 
		               Matrix4::Rotation(180.0f, Vector3(1, 0, 0)));
	Earth->AddChild(Moon);

	OBJMesh* m = new OBJMesh();
	m->LoadOBJMesh(MESHDIR"Beam_Satellite(Gold).obj");
	satellite = m;
	Satellite = new SceneNode(satellite, Vector4(1, 1, 1, 1));
	Satellite->SetOBJMesh(satellite);
	Satellite->SetDrawMeshType(2);
	Satellite->SetModelScale(Vector3(1, 1, 1));
	Satellite->SetTransform(Matrix4::Translation(Vector3(60, 0, 40)) *
		                    Matrix4::Rotation(45.0f, Vector3(0, 1, 0)));
	Earth->AddChild(Satellite);
}

void SolarSystem::Update(float dt) {
	Sun->SetTransform(Sun->GetTransform() * 
		              Matrix4::Rotation(10.0f * dt, Vector3(0, 1, 0)));
	Mercury->SetTransform(Mercury->GetTransform() * 
		              Matrix4::Rotation(90.0f * dt, Vector3(0, 1, 0)));
	Venus->SetTransform(Venus->GetTransform() * 
		              Matrix4::Rotation(80.0f * dt, Vector3(0, 1, 0)));
	Earth->SetTransform(Earth->GetTransform() * 
		              Matrix4::Rotation(-60.0f * dt, Vector3(0, 1, 0)));
	Moon->SetTransform(Moon->GetTransform() * 
		              Matrix4::Rotation(360.0f * dt, Vector3(0, 1, 0)));
	Mars->SetTransform(Mars->GetTransform() * 
		              Matrix4::Rotation(55.0f * dt, Vector3(0, 1, 0)));
	MirrorPlanet->SetTransform(MirrorPlanet->GetTransform() * 
		              Matrix4::Rotation(30.0f * dt, Vector3(0, 1, 0)));

	SceneNode::Update(dt);
}
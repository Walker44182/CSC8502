#include "Animation.h"

Animation::Animation() {
	std::cout << "\n--------------------Loading Animations...--------------------\n\n";

	mesh1 = Mesh::LoadFromMeshFile("Role_T.msh");
	anim1 = new MeshAnimation("Role_T.anm");
	material1 = new MeshMaterial("Role_T.mat");
	for (int i = 0; i < mesh1->GetSubMeshCount(); ++i) {
		const MeshMaterialEntry* matEntry =
			material1->GetMaterialForLayer(i);

		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string path = TEXTUREDIR + *filename;
		GLuint texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTextures1.emplace_back(texID);
	}

	mesh2 = Mesh::LoadFromMeshFile("Toon Chicken.msh");
	anim2 = new MeshAnimation("Toon Chicken.anm");
	material2 = new MeshMaterial("Toon Chicken.mat");
	for (int i = 0; i < mesh2->GetSubMeshCount(); ++i) {
		const MeshMaterialEntry* matEntry =
			material2->GetMaterialForLayer(i);

		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string path = TEXTUREDIR + *filename;
		GLuint texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTextures2.emplace_back(texID);
	}

	mesh3 = Mesh::LoadFromMeshFile("tree-maple-low-poly-Anim.msh");
	anim3 = new MeshAnimation("tree-maple-low-poly-Anim.anm");
	material3 = new MeshMaterial("tree-maple-low-poly-Anim.mat");
	for (int i = 0; i < mesh3->GetSubMeshCount(); ++i) {
		const MeshMaterialEntry* matEntry =
			material3->GetMaterialForLayer(i);

		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string path = TEXTUREDIR + *filename;
		GLuint texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTextures3.emplace_back(texID);
	}

	currentFrame = 0;
	frameTime = 0.0f;

	AnimationNode = new SceneNode();
	AnimationNode->SetTransform(Matrix4::Translation(Vector3(-2000, 0, -2000)));
	AddChild(AnimationNode);

	Character1 = new SceneNode(mesh1, Vector4(1, 1, 1, 1));
	Character1->SetMaterial(material1);
	Character1->SetAnimation(anim1);
	Character1->SetMatList(matTextures1);
	Character1->SetDrawMethodType(5);
	Character1->SetModelScale(Vector3(250, 250, 250));
	Character1->SetTransform(Matrix4::Translation(Vector3(2000, 0, 3000)) *
		                    Matrix4::Rotation(-90.0f, Vector3(0, 1, 0)));
	AnimationNode->AddChild(Character1);

	Character2 = new SceneNode(mesh1, Vector4(0, 1, 0, 1));
	Character2->SetMaterial(material1);
	Character2->SetAnimation(anim1);
	Character2->SetMatList(matTextures1);
	Character2->SetDrawMethodType(5);
	Character2->SetModelScale(Vector3(200, 200, 200));
	Character2->SetTransform(Matrix4::Translation(Vector3(800, 0, 3000)) *
		Matrix4::Rotation(90.0f, Vector3(0, 1, 0)));
	AnimationNode->AddChild(Character2);

	Chicken1 = new SceneNode(mesh2, Vector4(1, 1, 1, 1));
	Chicken1->SetMaterial(material2);
	Chicken1->SetAnimation(anim2);
	Chicken1->SetMatList(matTextures2);
	Chicken1->SetDrawMethodType(5);
	Chicken1->SetModelScale(Vector3(200, 200, 200));
	Chicken1->SetTransform(Matrix4::Translation(Vector3(3000, 0, 2000)));
	AnimationNode->AddChild(Chicken1);

	Chicken2 = new SceneNode(mesh2, Vector4(1, 1, 1, 1));
	Chicken2->SetMaterial(material2);
	Chicken2->SetAnimation(anim2);
	Chicken2->SetMatList(matTextures2);
	Chicken2->SetDrawMethodType(5);
	Chicken2->SetModelScale(Vector3(200, 200, 200));
	Chicken2->SetTransform(Matrix4::Translation(Vector3(1500, 0, 3500)));
	AnimationNode->AddChild(Chicken2);

	Chicken3 = new SceneNode(mesh2, Vector4(1, 1, 1, 1));
	Chicken3->SetMaterial(material2);
	Chicken3->SetAnimation(anim2);
	Chicken3->SetMatList(matTextures2);
	Chicken3->SetDrawMethodType(5);
	Chicken3->SetModelScale(Vector3(200, 200, 200));
	Chicken3->SetTransform(Matrix4::Translation(Vector3(3500, 0, 3000)));
	AnimationNode->AddChild(Chicken3);

	BirchTree1 = new SceneNode(mesh3, Vector4(1, 1, 1, 1));
	BirchTree1->SetMaterial(material3);
	BirchTree1->SetAnimation(anim3);
	BirchTree1->SetMatList(matTextures3);
	BirchTree1->SetDrawMethodType(5);
	BirchTree1->SetModelScale(Vector3(50, 50, 50));
	BirchTree1->SetTransform(Matrix4::Translation(Vector3(3000, 0, 2700)));
	AnimationNode->AddChild(BirchTree1);

	BirchTree2 = new SceneNode(mesh3, Vector4(1, 1, 1, 1));
	BirchTree2->SetMaterial(material3);
	BirchTree2->SetAnimation(anim3);
	BirchTree2->SetMatList(matTextures3);
	BirchTree2->SetDrawMethodType(5);
	BirchTree2->SetModelScale(Vector3(50, 50, 50));
	BirchTree2->SetTransform(Matrix4::Translation(Vector3(1700, 0, 3700)));
	AnimationNode->AddChild(BirchTree2);

	BirchTree3 = new SceneNode(mesh3, Vector4(1, 1, 1, 1));
	BirchTree3->SetMaterial(material3);
	BirchTree3->SetAnimation(anim3);
	BirchTree3->SetMatList(matTextures3);
	BirchTree3->SetDrawMethodType(5);
	BirchTree3->SetModelScale(Vector3(50, 50, 50));
	BirchTree3->SetTransform(Matrix4::Translation(Vector3(3700, 0, 1700)));
	AnimationNode->AddChild(BirchTree3);

	BirchTree4 = new SceneNode(mesh3, Vector4(1, 1, 1, 1));
	BirchTree4->SetMaterial(material3);
	BirchTree4->SetAnimation(anim3);
	BirchTree4->SetMatList(matTextures3);
	BirchTree4->SetDrawMethodType(5);
	BirchTree4->SetModelScale(Vector3(50, 50, 50));
	BirchTree4->SetTransform(Matrix4::Translation(Vector3(4000, 0, 4000)));
	AnimationNode->AddChild(BirchTree4);

	BirchTree5 = new SceneNode(mesh3, Vector4(1, 1, 1, 1));
	BirchTree5->SetMaterial(material3);
	BirchTree5->SetAnimation(anim3);
	BirchTree5->SetMatList(matTextures3);
	BirchTree5->SetDrawMethodType(5);
	BirchTree5->SetModelScale(Vector3(50, 50, 50));
	BirchTree5->SetTransform(Matrix4::Translation(Vector3(3800, 0, 500)));
	AnimationNode->AddChild(BirchTree5);
}

void Animation::Update(float dt) {
	Character1->SetFrameTime(Character1->GetFrameTime() - dt);
	while (Character1->GetFrameTime() < 0.0f) {
		Character1->SetCurrentFrame((Character1->GetCurrentFrame() + 1) %
			Character1->GetAnim()->GetFrameCount());
		Character1->SetFrameTime(Character1->GetFrameTime() + 1.0f /
			Character1->GetAnim()->GetFrameRate());
	}
	Character2->SetFrameTime(Character2->GetFrameTime() - dt);
	while (Character2->GetFrameTime() < 0.0f) {
		Character2->SetCurrentFrame((Character2->GetCurrentFrame() + 1) %
			Character2->GetAnim()->GetFrameCount());
		Character2->SetFrameTime(Character2->GetFrameTime() + 0.5f /
			Character2->GetAnim()->GetFrameRate());
	}
	Chicken1->SetFrameTime(Chicken1->GetFrameTime() - dt);
	while (Chicken1->GetFrameTime() < 0.0f) {
		Chicken1->SetCurrentFrame((Chicken1->GetCurrentFrame() + 1) %
			Chicken1->GetAnim()->GetFrameCount());
		Chicken1->SetFrameTime(Chicken1->GetFrameTime() + 1.0f /
			Chicken1->GetAnim()->GetFrameRate());
	}
	Chicken2->SetFrameTime(Chicken2->GetFrameTime() - dt);
	while (Chicken2->GetFrameTime() < 0.0f) {
		Chicken2->SetCurrentFrame((Chicken2->GetCurrentFrame() + 1) %
			Chicken2->GetAnim()->GetFrameCount());
		Chicken2->SetFrameTime(Chicken2->GetFrameTime() + 1.0f /
			Chicken2->GetAnim()->GetFrameRate());
	}
	Chicken3->SetFrameTime(Chicken3->GetFrameTime() - dt);
	while (Chicken3->GetFrameTime() < 0.0f) {
		Chicken3->SetCurrentFrame((Chicken3->GetCurrentFrame() + 1) %
			Chicken3->GetAnim()->GetFrameCount());
		Chicken3->SetFrameTime(Chicken3->GetFrameTime() + 1.0f /
			Chicken3->GetAnim()->GetFrameRate());
	}
	BirchTree1->SetFrameTime(BirchTree1->GetFrameTime() - dt);
	while (BirchTree1->GetFrameTime() < 0.0f) {
		BirchTree1->SetCurrentFrame((BirchTree1->GetCurrentFrame() + 1) %
			BirchTree1->GetAnim()->GetFrameCount());
		BirchTree1->SetFrameTime(BirchTree1->GetFrameTime() + 0.5f /
			BirchTree1->GetAnim()->GetFrameRate());
	}
	BirchTree2->SetFrameTime(BirchTree2->GetFrameTime() - dt);
	while (BirchTree2->GetFrameTime() < 0.0f) {
		BirchTree2->SetCurrentFrame((BirchTree2->GetCurrentFrame() + 1) %
			BirchTree2->GetAnim()->GetFrameCount());
		BirchTree2->SetFrameTime(BirchTree2->GetFrameTime() + 1.0f /
			BirchTree2->GetAnim()->GetFrameRate());
	}
	BirchTree3->SetFrameTime(BirchTree3->GetFrameTime() - dt);
	while (BirchTree3->GetFrameTime() < 0.0f) {
		BirchTree3->SetCurrentFrame((BirchTree3->GetCurrentFrame() + 1) %
			BirchTree3->GetAnim()->GetFrameCount());
		BirchTree3->SetFrameTime(BirchTree3->GetFrameTime() + 0.7f /
			BirchTree3->GetAnim()->GetFrameRate());
	}
	BirchTree4->SetFrameTime(BirchTree4->GetFrameTime() - dt);
	while (BirchTree4->GetFrameTime() < 0.0f) {
		BirchTree4->SetCurrentFrame((BirchTree4->GetCurrentFrame() + 1) %
			BirchTree4->GetAnim()->GetFrameCount());
		BirchTree4->SetFrameTime(BirchTree4->GetFrameTime() + 1.0f /
			BirchTree4->GetAnim()->GetFrameRate());
	}
	BirchTree5->SetFrameTime(BirchTree5->GetFrameTime() - dt);
	while (BirchTree5->GetFrameTime() < 0.0f) {
		BirchTree5->SetCurrentFrame((BirchTree5->GetCurrentFrame() + 1) %
			BirchTree5->GetAnim()->GetFrameCount());
		BirchTree5->SetFrameTime(BirchTree5->GetFrameTime() + 0.3f /
			BirchTree5->GetAnim()->GetFrameRate());
	}
	SceneNode::Update(dt);
}
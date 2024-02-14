#include "Renderer.h"
#include <algorithm>

#define SHADOWSIZE 2048

void Renderer::InitLights() {
	std::cout << "\n-------------------Initializing Lights...-------------------\n\n";

	SunLight = new Light(Vector3(0, 2000, 0), Vector4(1, 1, 1, 1), 6000);
	LanternLight = new Light(Vector3(2000, 1500, 2000), Vector4(1, 1, 1, 1), 6000);

	crystalLights = new Light[8];
	Light& l1 = crystalLights[0];
	l1.SetPosition(Vector3(300, 300, 300));
	l1.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l1.SetRadius(250.0f + (rand() % 250));
	Light& l2 = crystalLights[1];
	l2.SetPosition(Vector3(-1500, 300, 1000));
	l2.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l2.SetRadius(250.0f + (rand() % 250));
	Light& l3 = crystalLights[2];
	l3.SetPosition(Vector3(0, 300, 2000));
	l3.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l3.SetRadius(250.0f + (rand() % 250));
	Light& l4 = crystalLights[3];
	l4.SetPosition(Vector3(1500, 300, 500));
	l4.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l4.SetRadius(250.0f + (rand() % 250));
	Light& l5 = crystalLights[4];
	l5.SetPosition(Vector3(2000, 300, 1500));
	l5.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l5.SetRadius(250.0f + (rand() % 250));
	Light& l6 = crystalLights[5];
	l6.SetPosition(Vector3(1000, 300, 1000));
	l6.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l6.SetRadius(250.0f + (rand() % 250));
	Light& l7 = crystalLights[6];
	l7.SetPosition(Vector3(300, 300, 1700));
	l7.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l7.SetRadius(250.0f + (rand() % 250));
	Light& l8 = crystalLights[7];
	l8.SetPosition(Vector3(1600, 300, 500));
	l8.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		0.5f + (float)(rand() / (float)RAND_MAX),
		1));
	l8.SetRadius(250.0f + (rand() % 250));
	ShroomLight = new Light(Vector3(-1350, 437, -1600), Vector4(1, 0.5, 0, 1), 500);
	RedStoneLight = new Light(Vector3(-1650, 437, -890), Vector4(1, 1, 0, 1), 500);
}

void Renderer::LoadShaders() {
	std::cout << "\n-------------------Loading Shaders...-------------------\n\n";

	shader1 = new Shader("PerPixelSceneVertex.glsl", "PerPixelBufferFragment.glsl");
	shader2 = new Shader("BumpSceneVertex.glsl", "BumpBufferFragment.glsl");
	shader3 = new Shader("BumpSceneVertex.glsl", "SpecBufferFragment.glsl");
	shader4 = new Shader("reflectSceneVertex.glsl", "reflectBufferFragment.glsl");
	shader5 = new Shader("SkinningPerPixelVertex.glsl", "PerPixelBufferFragment.glsl");
	shadowShader1 = new Shader("PerPixelSceneVertex.glsl", "PerPixelShadowFrag.glsl");
	shadowShader2 = new Shader("SkinningPerPixelVertex.glsl", "PerPixelShadowFrag.glsl");
	skyboxShader = new Shader("skyboxVertex.glsl", "skyboxFragment.glsl");
	lanternLightShader1 = new Shader("pointlightvertex.glsl", "lanternLightFragment1.glsl");
	pointLightShader1 = new Shader("pointlightvertex.glsl", "pointLightFragment1.glsl");
	spotLightShader1 = new Shader("pointlightvertex.glsl", "spotLightFragment1.glsl");
	lanternLightShader2 = new Shader("pointlightvertex.glsl", "lanternLightFragment2.glsl");
	pointLightShader2 = new Shader("pointlightvertex.glsl", "pointLightFragment2.glsl");
	spotLightShader2 = new Shader("pointlightvertex.glsl", "spotLightFragment2.glsl");
	combineShader = new Shader("combinevert.glsl", "combinefrag.glsl");
	correctionShader = new Shader("processVertex.glsl", "correctionFrag.glsl");
	blurShader = new Shader("processVertex.glsl", "processfrag.glsl");
	presentShader =new Shader("processVertex.glsl", "TexturedFragment.glsl");
	miniMapShader1 = new Shader("SceneVertex.glsl", "SceneFragment.glsl");
	miniMapShader2 = new Shader("SkinningSceneVertex.glsl", "SceneFragment.glsl");

	if (!shader1->LoadSuccess() || !shader2->LoadSuccess() || !shader3->LoadSuccess() ||
		!shader4->LoadSuccess() || !shader5->LoadSuccess() ||
		!shadowShader1->LoadSuccess() || !shadowShader2->LoadSuccess() ||
		!lanternLightShader1->LoadSuccess() || !lanternLightShader2->LoadSuccess() ||
		!pointLightShader1->LoadSuccess() || !pointLightShader2->LoadSuccess() ||
		!spotLightShader1->LoadSuccess() || !spotLightShader2->LoadSuccess() ||
		!combineShader->LoadSuccess() || !correctionShader->LoadSuccess() ||
		!blurShader->LoadSuccess() || !presentShader->LoadSuccess() ||
		!miniMapShader1->LoadSuccess() || !miniMapShader2->LoadSuccess()) {
		std::cout << "Shader Load Failed!!" << std::endl;
		return;
	}
}

void Renderer::CreateSceneGraph() {
	std::cout << "\n-------------------Creating Scene Graph...-------------------\n\n";

	SolarSystemNode = new SolarSystem();
	TerrainNode = new Terrain();
	AnimationNode = new Animation();
	SnowNode = new Snow();
	Blocks = new Block();

	OBJMesh* n6 = new OBJMesh();
	n6->LoadOBJMesh(MESHDIR"Graveyard_Lantern_01.obj");
	OBJMesh* lantern = n6;

	OBJMesh* n7 = new OBJMesh();
	n7->LoadOBJMesh(MESHDIR"UFO.obj");
	OBJMesh* ufo = n7;

	OBJMesh* n8 = new OBJMesh;
	n8->LoadOBJMesh(MESHDIR"Magic_Lamp.obj");
	OBJMesh* lamp = n8;

	if (!SolarSystemNode->GetInit() || !TerrainNode->GetInit() ||
		!SnowNode->GetInit() || !Blocks->GetInit()) {
		std::cout << "Scene Node Texture Load Failed!!" << std::endl;
		return;
	}
	root = new SceneNode();

	Lantern = new SceneNode(lantern, Vector4(1, 1, 1, 1));
	Lantern->SetEmissive(true);
	Lantern->SetDrawMeshType(2);
	Lantern->SetOBJMesh(lantern);
	Lantern->SetModelScale(Vector3(200, 200, 200));
	Lantern->SetTransform(Matrix4::Translation(Vector3(2000, 1500, 2000)));

	UFO = new SceneNode(ufo, Vector4(1, 1, 1, 1));
	UFO->SetModelScale(Vector3(1, 1, 1));
	UFO->SetTransform(Matrix4::Translation(Vector3(0, 700, 0)));

	Rotate2 = new SceneNode();
	Rotate2->SetTransform(Matrix4::Translation(Vector3(1000, 100, -1000)));

	Lamp = new SceneNode(lamp, Vector4(1, 1, 1, 1));
	Lamp->SetEmissive(true);
	Lamp->SetDrawMeshType(2);
	Lamp->SetOBJMesh(lamp);
	Lamp->SetModelScale(Vector3(200, 200, 200));
	Lamp->SetTransform(Matrix4::Translation(Vector3(500, 600, 0)) *
		Matrix4::Rotation(45.0f, Vector3(0, 0, 1)));

	root->AddChild(Lantern);
	root->AddChild(UFO);
	root->AddChild(SolarSystemNode);
	root->AddChild(TerrainNode);
	root->AddChild(Rotate2);
	root->AddChild(SnowNode);
	root->AddChild(Blocks);
	TerrainNode->AddChild(AnimationNode);
	Rotate2->AddChild(Lamp);
}



void Renderer::InitFBOs() {
	std::cout << "\n-------------------Initializing Frame Buffers...-------------------\n\n";

	glGenFramebuffers(1, &bufferFBO);
	glGenFramebuffers(1, &pointLightFBO);
	glGenFramebuffers(1, &shadowFBO);
	glGenFramebuffers(1, &skyboxFBO);
	glGenFramebuffers(1, &combinedFBO);
	glGenFramebuffers(1, &processFBO);

	GLenum buffers[5] = {
	GL_COLOR_ATTACHMENT0 ,
	GL_COLOR_ATTACHMENT1 ,
	GL_COLOR_ATTACHMENT2 ,
	GL_COLOR_ATTACHMENT3 ,
	GL_COLOR_ATTACHMENT4
	};

	InitCubeMap();
	GenerateShadowTexture();
	GenerateScreenTexture(skyboxTex);
	GenerateScreenTexture(bufferDepthTex, true);
	GenerateScreenTexture(bufferColourTex);
	GenerateScreenTexture(bufferNormalTex);
	GenerateScreenTexture(bufferSpecTex);
	GenerateScreenTexture(bufferEmisTex);
	GenerateScreenTexture(bufferShadowTex);
	GenerateScreenTexture(lightDiffuseTex);
	GenerateScreenTexture(lightSpecularTex);
	GenerateScreenTexture(processTex);
	GenerateCombinedTexture();

	// And now attach them to our FBOs
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, bufferColourTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
		GL_TEXTURE_2D, bufferNormalTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
		GL_TEXTURE_2D, bufferSpecTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3,
		GL_TEXTURE_2D, bufferEmisTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4,
		GL_TEXTURE_2D, bufferShadowTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, bufferDepthTex, 0);
	glDrawBuffers(5, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "bufferFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, pointLightFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, lightDiffuseTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
		GL_TEXTURE_2D, lightSpecularTex, 0);
	glDrawBuffers(2, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "pointLightFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, shadowTex, 0);
	glDrawBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "shadowFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, skyboxFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, skyboxTex, 0);
	glDrawBuffers(1, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "skyboxFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, combinedFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, combinedTex, 0);
	glDrawBuffers(1, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "correctionFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, processFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, processTex, 0);
	glDrawBuffers(1, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "processFBO Load Failed!!" << std::endl;
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::GenerateScreenTexture(GLuint& into, bool depth) {
	glGenTextures(1, &into);
	glBindTexture(GL_TEXTURE_2D, into);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLuint format1 = depth ? GL_DEPTH_COMPONENT24 : GL_RGBA8;
	GLuint type = depth ? GL_DEPTH_COMPONENT : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0,
		format1, width, height, 0, type, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::GenerateShadowTexture() {
	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOWSIZE, SHADOWSIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::GenerateCombinedTexture() {
	glGenTextures(1, &combinedTex);
	glBindTexture(GL_TEXTURE_2D, combinedTex);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0,
		GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::InitCubeMap() {
	std::string name[6] = {
		TEXTUREDIR"skybox_left.png",TEXTUREDIR"skybox_right.png",
		TEXTUREDIR"skybox_up.png",TEXTUREDIR"skybox_down.png",
		TEXTUREDIR"skybox_front.png",TEXTUREDIR"skybox_back.png"
	};

	GLuint axis[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	glGenTextures(1, &cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	int iWidth, iHeight;

	for (int i = 0; i < 6; ++i) {
		unsigned char* image = SOIL_load_image(name[i].c_str(),
			&iWidth, &iHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(axis[i], 0, GL_RGB, iWidth, iHeight,
			0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
		SOIL_free_image_data(image);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
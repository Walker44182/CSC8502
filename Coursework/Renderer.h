#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/SceneNode.h"
#include "../nclgl/Frustum.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/Camera.h"
#include "../nclgl/Light.h"
#include "SolarSystem.h"
#include "Terrain.h"
#include "Animation.h"
#include "Particle.h"
class Camera;
class SceneNode;
class Mesh;
class Shader;
class Light;

class Renderer :public OGLRenderer {
public:
	Renderer(Window& parent);
	~Renderer(void);

	void UpdateScene(float msec) override;
	void RenderScene() override;
	inline void SetUFOPosition(Vector3 p, float r) { 
		UFOTranslation = p;
		UFORotation = r;
	}
	inline void SetUFOLightColour(Vector4 c) { UFOLightColour = c; }
	inline void SetUFOColour(Vector4 c) { UFOColour = c; }
	inline void SetUFOEmissive() {
		if (!sunlight && !shadow) UFO->SetEmissive(true);
		else UFO->SetEmissive(false);
	}
	inline float GetExposure() { return exposure; }
	inline void SetExposure(float e) { exposure = e; }
	inline void SwitchShadow() { shadow = !shadow; LanternEmissive = !LanternEmissive; }
	inline void SwitchSunlight() { sunlight = !sunlight; }
	inline void SwitchSpecularMap() { specularMap = !specularMap; }
	inline void SwitchCorrection() { process = 1; }
	inline void SwitchBlur() { process = 2; }
	inline void EscapeProcess() { process = 0; }
	inline void SwitchFrustum() { if(!snow && !blocks) useFrustum = !useFrustum; }
	inline void SwitchMovingCamera() { freeCamera = false; }
	inline void SwitchMiniMap() { miniMapActive = !miniMapActive; }
	inline void SwitchSnow() {
		snow = !snow;
		SnowNode->SetSnowActive(!SnowNode->GetSnowActive());
	}
	inline void SwitchBlocks() {
		blocks = !blocks;
		Blocks->SetBlocksActive(!Blocks->GetBlocksActive());
	}
	inline void SwitchTerrainCamera() {
		freeCamera = true;
		camera->SetPosition(Vector3(1500, 500, 1500));
		camera->SetPitch(0.0f);
		camera->SetYaw(30.0f);	
		sunlight = true;
		shadow = false;
		LanternEmissive = false;
		snow = false;
		SnowNode->SetSnowActive(false);
		blocks = false;
		Blocks->SetBlocksActive(false);
	}
	inline void SwitchSpaceCamera() {
		freeCamera = true;
		camera->SetPosition(Vector3(-1000, 2400, -1500));
		camera->SetPitch(-27.0f);
		camera->SetYaw(210.0f);
		sunlight = true;
		shadow = false;
		LanternEmissive = false;
		snow = false;
		SnowNode->SetSnowActive(false);
		blocks = false;
		Blocks->SetBlocksActive(false);
	}


protected:
	void GenerateScreenTexture(GLuint& into, bool depth = false);
	void GenerateShadowTexture();
	void GenerateCombinedTexture();
	void InitCubeMap();
	void InitLights();
	void LoadShaders();
	void CreateSceneGraph();
	void InitFBOs();
	void CameraUpdate();
	void LightsUpdate(float dt);
	void BuildNodeLists(SceneNode* from);
	void SortNodeLists();
	void ClearNodeLists();
	void ClearAllBuffers();
	void DrawSkyBoxBuffer();
	void DrawShadowBuffer();
	void DrawNodes(int mode = 0);
	void DrawNode(SceneNode* n, int mode = 0);
	void DrawMethod1(SceneNode* n);
	void DrawMethod2(SceneNode* n);
	void DrawMethod3(SceneNode* n);
	void DrawMethod4(SceneNode* n);
	void DrawMethod5(SceneNode* n);
	void DrawMethod6(SceneNode* n);
	void DrawMethod7(SceneNode* n);
	void DrawShadowMethod1(SceneNode* n);
	void DrawShadowMethod2(SceneNode* n);
	void DrawShadowMethod3(SceneNode* n);
	void DrawShadowMethod4(SceneNode* n);
	void DrawMiniMapMethod1(SceneNode* n);
	void DrawMiniMapMethod2(SceneNode* n);
	void DrawWorldBuffer(); //G- Buffer Fill Render Pass
	void DrawLightsBuffer(); // Lighting Render Pass
	void DrawLanternLight();
	void DrawPointLights();
	void DrawSpotLight();
	void CombineBuffers(); // Combination Render Pass
	void DrawCorrectionBuffer();
	void DrawBlurBuffer();
	void PresentBuffer();
	void DrawMiniMap();

	HeightMap* heightMap;
	Camera* camera;
	Camera* topCamera;
	int cameraMove = 0;
	bool camera1 = true;
	bool camera2 = false;
	bool camera3 = false;
	bool camera4 = false;
	bool camera5 = false;

	Light* SunLight;
	Light* LanternLight;
	Light* crystalLights;
	Light* RedStoneLight;
	Light* ShroomLight;
	Light* LampLight;
	Light* UFOLight;
	Vector4 UFOLightColour;

	Mesh* quad;
	Mesh* sphere;

	Shader* shader1;
	Shader* shader2;
	Shader* shader3;
	Shader* shader4;
	Shader* shader5;
	Shader* skyboxShader;
	Shader* shadowShader1;
	Shader* shadowShader2;
	Shader* lanternLightShader;
	Shader* pointLightShader;
	Shader* spotLightShader;
	Shader* lanternLightShader1;
	Shader* pointLightShader1;
	Shader* spotLightShader1;
	Shader* lanternLightShader2;
	Shader* pointLightShader2;
	Shader* spotLightShader2;
	Shader* combineShader;
	Shader* correctionShader;
	Shader* blurShader;
	Shader* presentShader;
	Shader* miniMapShader1;
	Shader* miniMapShader2;

	GLuint texture;
	GLuint bumpMap;
	GLuint specMap;
	GLuint cubeMap;

	SceneNode* root;
	SceneNode* Lantern;
	SceneNode* UFO;
	SceneNode* Rotate2;
	SceneNode* Lamp;
	SolarSystem* SolarSystemNode;
	Terrain* TerrainNode;
	Animation* AnimationNode;
	Snow* SnowNode;
	Block* Blocks;
	vector<SceneNode*> transparentNodeList;
	vector<SceneNode*> nodeList;
	Vector4 UFOColour;
	Vector3 UFOTranslation;
	float UFORotation;
	bool LanternEmissive = false;


	GLuint bufferFBO; // FBO for our G- Buffer pass
	GLuint bufferColourTex; // Albedo goes here
	GLuint bufferNormalTex; // Normals go here
	GLuint bufferSpecTex; // Speculars go here
	GLuint bufferEmisTex; //Emissive go here
	GLuint bufferDepthTex; // Depth goes here
	GLuint bufferShadowTex; //Shadow goes here

	GLuint pointLightFBO; // FBO for our lighting pass
	GLuint lightDiffuseTex; // Store diffuse lighting
	GLuint lightSpecularTex; // Store specular lighting

	GLuint skyboxFBO;
	GLuint skyboxTex;

	GLuint shadowFBO;
	GLuint shadowTex;

	GLuint combinedFBO;
	GLuint combinedTex;

	GLuint processFBO;
	GLuint processTex;

	Frustum frameFrustum;

	float updateRate;

	float waterRotate;
	float waterCycle;
	float exposure = 1.0f;

	int mode = 0;
	int process = 0;
	bool shadow = false;
	bool sunlight = true;
	bool specularMap = false;
	bool useFrustum = false;
	bool freeCamera = false;
	bool snow = false;
	bool blocks = false;
	bool miniMapActive = true;
};
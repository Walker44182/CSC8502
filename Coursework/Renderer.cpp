#include "Renderer.h"
#include <algorithm>

#define SHADOWSIZE 2048
const int POST_PASSES = 10;

Renderer::Renderer(Window& parent) :OGLRenderer(parent) {
	std::cout << "\n-------------------Loading Renderer...-------------------\n\n";

	camera = new Camera(-30.0f, 30.0f, (Vector3(1500, 1500, 1500)));
	topCamera = new Camera(-90.0f, 0.0f, Vector3(0, 5500, 0));
	quad = Mesh::GenerateQuad();
	sphere = Mesh::LoadFromMeshFile("Sphere.msh");
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	LoadShaders();
	InitLights();
	InitFBOs();
	CreateSceneGraph();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	updateRate = 1.0;
	waterRotate = 0.0f;
	waterCycle = 0.0f;
	init = true;
}

Renderer::~Renderer() {
	delete root;
	delete quad;
	delete sphere;
	delete camera;

	delete SunLight;
	delete LanternLight;
	delete[] crystalLights;
	delete ShroomLight;
	delete RedStoneLight;

	delete shader1;
	delete shader2;
	delete shader3;
	delete shader4;
	delete shader5;
	delete shadowShader1;
	delete shadowShader2;
	delete skyboxShader;
	delete lanternLightShader1;
    delete lanternLightShader2;
	delete pointLightShader1;
	delete pointLightShader2;
	delete spotLightShader1;
	delete spotLightShader2;
	delete combineShader;
	delete correctionShader;
	delete blurShader;
	delete presentShader;
	delete miniMapShader1;
	delete miniMapShader2;

	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &bumpMap);
	glDeleteTextures(1, &specMap);
	glDeleteTextures(1, &cubeMap);
	glDeleteTextures(1, &shadowTex);
	glDeleteTextures(1, &skyboxTex);
	glDeleteTextures(1, &bufferColourTex);
	glDeleteTextures(1, &bufferNormalTex);
	glDeleteTextures(1, &bufferSpecTex);
	glDeleteTextures(1, &bufferEmisTex);
	glDeleteTextures(1, &bufferDepthTex);
	glDeleteTextures(1, &lightDiffuseTex);
	glDeleteTextures(1, &lightSpecularTex);
	glDeleteTextures(1, &processTex);
	glDeleteTextures(1, &combinedTex);

	glDeleteFramebuffers(1, &bufferFBO);
	glDeleteFramebuffers(1, &pointLightFBO);
	glDeleteFramebuffers(1, &shadowFBO);
	glDeleteFramebuffers(1, &skyboxFBO);
	glDeleteFramebuffers(1, &combinedFBO);
	glDeleteFramebuffers(1, &processFBO);
}

void Renderer::UpdateScene(float dt) {
	if (freeCamera)camera->UpdateCamera(dt);
	else if (!freeCamera)CameraUpdate();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);
	frameFrustum.FromMatrix(projMatrix * viewMatrix);
	if (snow || blocks) useFrustum = true;
	waterRotate += dt * 2.0f;
	waterCycle += dt * 0.25f;
	Rotate2->SetTransform(Rotate2->GetTransform() *
		Matrix4::Rotation(-40.0f * dt, Vector3(0, 1, 0)));
	UFO->SetTransform(Matrix4::Translation(UFOTranslation) *
		              Matrix4::Rotation(UFORotation, Vector3(0, 1, 0)));
	SetUFOEmissive();
	if (!snow) { UFO->SetColour(UFOColour); Lamp->SetColour(Vector4(1, 1, 1, 1)); }
	if (snow) { LightsUpdate(dt); }
	Lantern->SetEmissive(LanternEmissive);
	root->Update(dt);
}

void Renderer::CameraUpdate() {
	if (camera1) {
		camera->SetPosition(Vector3(-500 + 1.0 * cameraMove, 500, 2000));
		camera->SetPitch(0.0f);
		camera->SetYaw(0.0f);
		blocks = false;
		Blocks->SetBlocksActive(false);
		useFrustum = false;
		++cameraMove;
		if (cameraMove == 1500) {
			cameraMove = 0;
			camera1 = false;
			camera2 = true;
		}
	}
	else if (camera2) {
		camera->SetPosition(Vector3(-1500 + 1.0 * cameraMove, 500,-2000 + 0.2 * cameraMove));
		camera->SetPitch(0.0f);
		camera->SetYaw(140.0f);
		shadow = true;
		LanternEmissive = true;
		++cameraMove;
		if (cameraMove == 1500) {
			cameraMove = 0;
			camera3 = true;
			camera2 = false;
		}
	}
	else if (camera3) {
		camera->SetPosition(Vector3(1000 - 1.0 * cameraMove, 2450, 1500));
		camera->SetPitch(-30.0f);
		camera->SetYaw(0.0f);
		shadow = false;
		LanternEmissive = false;
		++cameraMove;
		if (cameraMove == 1500) {
			cameraMove = 0;
			camera3 = false;
			camera4 = true;
		}
	}	
	else if (camera4) {
		camera->SetPosition(Vector3(-250, 650, -2600));
		camera->SetPitch(0.0f);
		camera->SetYaw(205.0f);
		sunlight = false;
		shadow = true;
		LanternEmissive = true;
		snow = true;
		SnowNode->SetSnowActive(true);
		++cameraMove;
		if (cameraMove == 1500) {
			cameraMove = 0;
			camera4 = false;
			camera5 = true;
		}
	}
	else if (camera5) {
		camera->SetPosition(Vector3(0, 400, 0));
		camera->SetPitch(0.0f);
		camera->SetYaw(45.0f);
		sunlight = true;
		shadow = false;
		LanternEmissive = false;
		snow = false;
		SnowNode->SetSnowActive(false);
		blocks = true;
		Blocks->SetBlocksActive(true);
		++cameraMove;
		if (cameraMove == 1500) {
			cameraMove = 0;
			camera5 = false;
			camera1 = true;
		}
	}
}

void Renderer::LightsUpdate(float dt) {
	updateRate -= dt;
	while (updateRate < 0) {
		Lamp->SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			1.0f));
		UFO->SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			1.0f));
		updateRate = 1.0f;
	}
}

void Renderer::RenderScene() {
	BuildNodeLists(root);
	SortNodeLists();
	ClearAllBuffers();

	glViewport(0, 0, width, height);
	DrawShadowBuffer();
	DrawSkyBoxBuffer();
	DrawWorldBuffer();
	DrawLightsBuffer();
	CombineBuffers();
	if (process == 1)
	DrawCorrectionBuffer();
	if (process == 2) {
		DrawBlurBuffer();
		PresentBuffer();
	}

	if (miniMapActive) {
		glClear(GL_DEPTH_BUFFER_BIT);
		glViewport(-97.0, 0.66 * height + 10.0, (width / height) * width / 3, (width / height) * height / 3);
		DrawMiniMap();
	}

	ClearNodeLists();
}

void Renderer::BuildNodeLists(SceneNode* from) {
	if (frameFrustum.InsideFrustum(*from) || !from->GetCulled() || !useFrustum) {
		Vector3 dir = from->GetWorldTransform().GetPositionVector() -
			camera->GetPosition();
		from->SetCameraDistance(Vector3::Dot(dir, dir));

		if (from->GetColour().w < 1.0f) {
			transparentNodeList.push_back(from);
		}
		else {
			nodeList.push_back(from);
		}
	}

	for (vector<SceneNode*>::const_iterator i =
		from->GetChildIteratorStart();
		i != from->GetChildIteratorEnd(); ++i) {
		BuildNodeLists(*i);
	}
}

void Renderer::SortNodeLists() {
	std::sort(transparentNodeList.rbegin(),
		transparentNodeList.rend(),
		SceneNode::CompareByCameraDistance);
	std::sort(nodeList.begin(),
		nodeList.end(),
		SceneNode::CompareByCameraDistance);
}

void Renderer::DrawNodes(int mode) {
	for (const auto& i : nodeList) {
		DrawNode(i, mode);
	}
	for (const auto& i : transparentNodeList) {
		DrawNode(i, mode);
	}
}

void Renderer::DrawNode(SceneNode* n, int mode) {
	if (n->GetMesh()) {
		if (mode == 0) {
			if (n->GetDrawMethodType() == 1) {
				DrawMethod1(n);
			}
			else if (n->GetDrawMethodType() == 2) {
				DrawMethod2(n);
			}
			else if (n->GetDrawMethodType() == 3) {
				DrawMethod3(n);
			}
			else if (n->GetDrawMethodType() == 4) {
				DrawMethod4(n);
			}
			else if (n->GetDrawMethodType() == 5) {
				DrawMethod5(n);
			}
			else if (n->GetDrawMethodType() == 6) {
				DrawMethod6(n);
			}
			else if (n->GetDrawMethodType() == 7) {
				DrawMethod7(n);
			}
		}
		else if(mode == 1) {
			if (n->GetDrawMethodType() < 5) {
				DrawShadowMethod1(n);
			}
			else if (n->GetDrawMethodType() == 5) {
				DrawShadowMethod2(n);
			}
			else if (n->GetDrawMethodType() == 6) {
				DrawShadowMethod3(n);
			}
			else if (n->GetDrawMethodType() == 7) {
				DrawShadowMethod4(n);
			}
		}
		else if (mode == 2) {
			if (n->GetDrawMethodType() < 5) {
				DrawMiniMapMethod1(n);
			}
			else if (n->GetDrawMethodType() == 5) {
				DrawMiniMapMethod2(n);
			}
		}
	}
}

void Renderer::ClearAllBuffers() {
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, skyboxFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, pointLightFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, combinedFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, processFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::DrawShadowBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);

	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, SHADOWSIZE, SHADOWSIZE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	DrawNodes(1);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glViewport(0, 0, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawSkyBoxBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, skyboxFBO);
	glDepthMask(GL_FALSE);
	BindShader(skyboxShader);

	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(
		skyboxShader->GetProgram(), "cubeTex"), 6);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	quad->Draw();

	glDepthMask(GL_TRUE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawWorldBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	DrawNodes();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawLightsBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, pointLightFBO);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_ALWAYS);
	glDepthMask(GL_FALSE);

	if(shadow)DrawLanternLight();
	DrawPointLights();
	DrawSpotLight();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::CombineBuffers() {
	if(process)glBindFramebuffer(GL_FRAMEBUFFER, combinedFBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BindShader(combineShader);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();
	//UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferColourTex);

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "diffuseLight"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightDiffuseTex);

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "specularLight"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, lightSpecularTex);

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "emissiveLight"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, bufferEmisTex);

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "skyboxTex"), 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, skyboxTex);

	glUniform1i(glGetUniformLocation(
		combineShader->GetProgram(), "depthTex"), 5);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, bufferDepthTex);

	quad->Draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawCorrectionBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BindShader(correctionShader);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(
		correctionShader->GetProgram(), "correctionTex"), 8);
	glUniform1f(glGetUniformLocation(
		correctionShader->GetProgram(), "exposure"), exposure);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, combinedTex);
	quad->Draw();
}

void Renderer::DrawBlurBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, processFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, processTex, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	BindShader(blurShader);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();
	UpdateShaderMatrices();

	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE9);
	glUniform1i(glGetUniformLocation(
		blurShader->GetProgram(), "sceneTex"), 9);
	for (int i = 0; i < POST_PASSES; ++i) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, processTex, 0);
		glUniform1i(glGetUniformLocation(blurShader->GetProgram(),
			"isVertical"), 0);

		glBindTexture(GL_TEXTURE_2D, combinedTex);
		quad->Draw();
		// Now to swap the colour buffers, and do the second blur pass
		glUniform1i(glGetUniformLocation(blurShader->GetProgram(),
			"isVertical"), 1);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, combinedTex, 0);
		glBindTexture(GL_TEXTURE_2D, processTex);
		quad->Draw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::PresentBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	BindShader(presentShader);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();
	UpdateShaderMatrices();
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, combinedTex);
	glUniform1i(glGetUniformLocation(
		presentShader->GetProgram(), "diffuseTex"), 9);
	quad->Draw();
}

void Renderer::DrawMiniMap() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	DrawNodes(2);
}

void Renderer::ClearNodeLists() {
	transparentNodeList.clear();
	nodeList.clear();
}
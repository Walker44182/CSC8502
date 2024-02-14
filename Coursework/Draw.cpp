#include "Renderer.h"
#include <algorithm>

void Renderer::DrawShadowMethod1(SceneNode* n) {
	BindShader(shadowShader1);
	modelMatrix.ToIdentity();
	viewMatrix = Matrix4::BuildViewMatrix(
		Vector3(2000, 1500, 2000), Vector3(0, 0, 0));
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);
	shadowMatrix = projMatrix * viewMatrix;
	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shadowShader1->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(shadowShader1->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(shadowShader1->GetProgram(),
		"diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(
		shadowShader1->GetProgram(), "emissive"), n->GetEmissive());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	n->Draw(*this);
}

void Renderer::DrawShadowMethod2(SceneNode* n) {
	BindShader(shadowShader2);
	modelMatrix.ToIdentity();
	viewMatrix = Matrix4::BuildViewMatrix(
		Vector3(2000, 2000, 2000), Vector3(0, 0, 0));
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);
	shadowMatrix = projMatrix * viewMatrix;

	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(shadowShader2->GetProgram(),
		"diffuseTex"), 0);

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shadowShader2->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(shadowShader2->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	glUniform1i(glGetUniformLocation(
		shadowShader2->GetProgram(), "emissive"), n->GetEmissive());

	vector<Matrix4> frameMatrices;

	const Matrix4* invBindPose = n->GetMesh()->GetInverseBindPose();
	const Matrix4* frameData = n->GetAnim()->GetJointData(n->GetCurrentFrame());

	for (unsigned int i = 0; i < n->GetMesh()->GetJointCount(); ++i) {
		frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
	}

	int j = glGetUniformLocation(shadowShader2->GetProgram(), "joints");
	glUniformMatrix4fv(j, frameMatrices.size(), false,
		(float*)frameMatrices.data());
	for (int i = 0; i < n->GetMesh()->GetSubMeshCount(); ++i) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, n->GetMat(i));
		n->GetMesh()->DrawSubMesh(i);
	}
}

void Renderer::DrawShadowMethod3(SceneNode* n) {
	if (snow) {
		BindShader(shadowShader1);
		modelMatrix.ToIdentity();
		viewMatrix = Matrix4::BuildViewMatrix(
			Vector3(2000, 1500, 2000), Vector3(0, 0, 0));
		projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
			(float)width / (float)height, 45.0f);
		shadowMatrix = projMatrix * viewMatrix;
		UpdateShaderMatrices();

		Matrix4 model = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(shadowShader1->GetProgram(),
				"modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shadowShader1->GetProgram(),
			"nodeColour"), 1, (float*)&n->GetColour());

		texture = n->GetMesh()->GetTexture();
		glUniform1i(glGetUniformLocation(shadowShader1->GetProgram(),
			"diffuseTex"), 0);
		glUniform1i(glGetUniformLocation(
			shadowShader1->GetProgram(), "emissive"), n->GetEmissive());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		n->Draw(*this);
	}
}

void Renderer::DrawShadowMethod4(SceneNode* n) {
	if (blocks) {
		BindShader(shadowShader1);
		modelMatrix.ToIdentity();
		viewMatrix = Matrix4::BuildViewMatrix(
			Vector3(2000, 1500, 2000), Vector3(0, 0, 0));
		projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
			(float)width / (float)height, 45.0f);
		shadowMatrix = projMatrix * viewMatrix;
		UpdateShaderMatrices();

		Matrix4 model = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(shadowShader1->GetProgram(),
				"modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shadowShader1->GetProgram(),
			"nodeColour"), 1, (float*)&n->GetColour());

		texture = n->GetMesh()->GetTexture();
		glUniform1i(glGetUniformLocation(shadowShader1->GetProgram(),
			"diffuseTex"), 0);
		glUniform1i(glGetUniformLocation(
			shadowShader1->GetProgram(), "emissive"), n->GetEmissive());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		n->Draw(*this);
	}
}

void Renderer::DrawMethod1(SceneNode* n) {
	BindShader(shader1);
	SetShaderLight(*SunLight);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shader1->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(shader1->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(shader1->GetProgram(),
		"diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(
		shader1->GetProgram(), "emissive"), n->GetEmissive());
	glUniform1i(glGetUniformLocation(shader1->GetProgram(),
		"shadowTex"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	n->Draw(*this);
}

void Renderer::DrawMethod2(SceneNode* n) {
	BindShader(shader2);
	SetShaderLight(*SunLight);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shader2->GetProgram(),
			"modelMatrix"), 1, false, model.values);

	glUniform4fv(glGetUniformLocation(shader2->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(shader2->GetProgram(),
		"diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	bumpMap = n->GetMesh()->GetBumpTexture();
	glUniform1i(glGetUniformLocation(
		shader2->GetProgram(), "bumpTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpMap);

	glUniform1i(glGetUniformLocation(
		shader2->GetProgram(), "emissive"), n->GetEmissive());
	glUniform1i(glGetUniformLocation(shader2->GetProgram(),
		"shadowTex"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	n->Draw(*this);
}

void Renderer::DrawMethod3(SceneNode* n) {
	BindShader(shader3);
	SetShaderLight(*SunLight);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shader3->GetProgram(),
			"modelMatrix"), 1, false, model.values);

	glUniform4fv(glGetUniformLocation(shader3->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(shader3->GetProgram(),
		"diffuseTex"), 0);

	bumpMap = n->GetMesh()->GetBumpTexture();
	glUniform1i(glGetUniformLocation(
		shader3->GetProgram(), "bumpTex"), 1);

	specMap = n->GetMesh()->GetSpecTexture();
	glUniform1i(glGetUniformLocation(
		shader3->GetProgram(), "specTex"), 2);

	glUniform1i(glGetUniformLocation(
		shader3->GetProgram(), "emissive"), n->GetEmissive());

	glUniform1i(glGetUniformLocation(shader3->GetProgram(),
		"shadowTex"), 3);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specMap);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	n->Draw(*this);
}

void Renderer::DrawMethod4(SceneNode* n) {
	BindShader(shader4);
	SetShaderLight(*SunLight);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	if (n->GetRotate()) {
		textureMatrix =
			Matrix4::Translation(Vector3(waterCycle, 0.0f, waterCycle)) *
			Matrix4::Scale(Vector3(10, 10, 10)) *
			Matrix4::Rotation(waterRotate, Vector3(0, 0, 1));
	}
	else {
		textureMatrix.ToIdentity();
	}
	UpdateShaderMatrices();

	glUniform3fv(glGetUniformLocation(shader4->GetProgram(),
		"cameraPos"), 1, (float*)&camera->GetPosition());

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shader4->GetProgram(),
			"modelMatrix"), 1, false, model.values);

	glUniform4fv(glGetUniformLocation(shader4->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(
		shader4->GetProgram(), "diffuseTex"), 0);

	bumpMap = n->GetMesh()->GetBumpTexture();
	glUniform1i(glGetUniformLocation(
		shader4->GetProgram(), "bumpTex"), 1);

	specMap = n->GetMesh()->GetSpecTexture();
	glUniform1i(glGetUniformLocation(
		shader4->GetProgram(), "specTex"), 2);

	glUniform1i(glGetUniformLocation(
		shader4->GetProgram(), "emissive"), n->GetEmissive());

	glUniform1i(glGetUniformLocation(
		shader4->GetProgram(), "cubeTex"), 7);

	glUniform1i(glGetUniformLocation(shader4->GetProgram(),
		"shadowTex"), 4);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specMap);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	n->Draw(*this);
}

void Renderer::DrawMethod5(SceneNode* n) {
	BindShader(shader5);
	SetShaderLight(*SunLight);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(shader5->GetProgram(),
		"diffuseTex"), 0);

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(shader5->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(shader5->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	glUniform1i(glGetUniformLocation(
		shader5->GetProgram(), "emissive"), n->GetEmissive());

	glUniform1i(glGetUniformLocation(shader5->GetProgram(),
		"shadowTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	vector<Matrix4> frameMatrices;

	const Matrix4* invBindPose = n->GetMesh()->GetInverseBindPose();
	const Matrix4* frameData = n->GetAnim()->GetJointData(n->GetCurrentFrame());

	for (unsigned int i = 0; i < n->GetMesh()->GetJointCount(); ++i) {
		frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
	}

	int j = glGetUniformLocation(shader5->GetProgram(), "joints");
	glUniformMatrix4fv(j, frameMatrices.size(), false,
		(float*)frameMatrices.data());
	for (int i = 0; i < n->GetMesh()->GetSubMeshCount(); ++i) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, n->GetMat(i));
		n->GetMesh()->DrawSubMesh(i);
	}
}

void Renderer::DrawMethod6(SceneNode* n) {
	if (snow) {
		BindShader(shader1);
		SetShaderLight(*SunLight);
		modelMatrix.ToIdentity();
		viewMatrix = camera->BuildViewMatrix();
		projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
			(float)width / (float)height, 45.0f);

		UpdateShaderMatrices();

		Matrix4 model = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(shader1->GetProgram(),
				"modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shader1->GetProgram(),
			"nodeColour"), 1, (float*)&n->GetColour());

		texture = n->GetMesh()->GetTexture();
		glUniform1i(glGetUniformLocation(shader1->GetProgram(),
			"diffuseTex"), 0);
		glUniform1i(glGetUniformLocation(
			shader1->GetProgram(), "emissive"), n->GetEmissive());
		glUniform1i(glGetUniformLocation(shader1->GetProgram(),
			"shadowTex"), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowTex);

		n->Draw(*this);
	}
}

void Renderer::DrawMethod7(SceneNode* n) {
	if (blocks) {
		BindShader(shader1);
		SetShaderLight(*SunLight);
		modelMatrix.ToIdentity();
		viewMatrix = camera->BuildViewMatrix();
		projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
			(float)width / (float)height, 45.0f);

		UpdateShaderMatrices();

		Matrix4 model = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(shader1->GetProgram(),
				"modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(shader1->GetProgram(),
			"nodeColour"), 1, (float*)&n->GetColour());

		texture = n->GetTexture();
		glUniform1i(glGetUniformLocation(shader1->GetProgram(),
			"diffuseTex"), 0);
		glUniform1i(glGetUniformLocation(
			shader1->GetProgram(), "emissive"), n->GetEmissive());
		glUniform1i(glGetUniformLocation(shader1->GetProgram(),
			"shadowTex"), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowTex);

		n->Draw(*this);
	}
}

void Renderer::DrawLanternLight() {
	if (specularMap) lanternLightShader = lanternLightShader1;
	else lanternLightShader = lanternLightShader2;
	BindShader(lanternLightShader);

	glUniform1i(glGetUniformLocation(
		lanternLightShader->GetProgram(), "depthTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferDepthTex);

	glUniform1i(glGetUniformLocation(
		lanternLightShader->GetProgram(), "normTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bufferNormalTex);

	glUniform1i(glGetUniformLocation(
		lanternLightShader->GetProgram(), "specTex"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, bufferSpecTex);

	glUniform1i(glGetUniformLocation(
		lanternLightShader->GetProgram(), "shadowTex"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, bufferShadowTex);

	glUniform3fv(glGetUniformLocation(lanternLightShader->GetProgram(),
		"cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform2f(glGetUniformLocation(lanternLightShader->GetProgram(),
		"pixelSize"), 1.0f / width, 1.0f / height);

	Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
	glUniformMatrix4fv(glGetUniformLocation(
		lanternLightShader->GetProgram(), "inverseProjView"),
		1, false, invViewProj.values);

	UpdateShaderMatrices();
	SetShaderLight(*LanternLight);
	sphere->Draw();
}

void Renderer::DrawPointLights() {
	if (specularMap) pointLightShader = pointLightShader1;
	else pointLightShader = pointLightShader2;
	BindShader(pointLightShader);

	glUniform1i(glGetUniformLocation(
		pointLightShader->GetProgram(), "depthTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferDepthTex);

	glUniform1i(glGetUniformLocation(
		pointLightShader->GetProgram(), "normTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bufferNormalTex);

	glUniform1i(glGetUniformLocation(
		pointLightShader->GetProgram(), "specTex"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, bufferSpecTex);

	glUniform3fv(glGetUniformLocation(pointLightShader->GetProgram(),
		"cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform2f(glGetUniformLocation(pointLightShader->GetProgram(),
		"pixelSize"), 1.0f / width, 1.0f / height);

	Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
	glUniformMatrix4fv(glGetUniformLocation(
		pointLightShader->GetProgram(), "inverseProjView"),
		1, false, invViewProj.values);

	UpdateShaderMatrices();

	for (int i = 0; i < 8; ++i) {
		Light& l = crystalLights[i];
		SetShaderLight(l);
		sphere->Draw();
	}

	if (sunlight) {
		SetShaderLight(*SunLight);
		sphere->Draw();
	}
	SetShaderLight(*ShroomLight);
	sphere->Draw();
	SetShaderLight(*RedStoneLight);
	sphere->Draw();
	if(snow)LampLight = new Light(Lamp->GetWorldTransform().GetPositionVector(), Lamp->GetColour(), 700);
	else LampLight = new Light(Lamp->GetWorldTransform().GetPositionVector(), Vector4(1,1,0,1), 700);
	SetShaderLight(*LampLight);
	sphere->Draw();
}

void Renderer::DrawSpotLight() {
	if (specularMap) spotLightShader = spotLightShader1;
	else spotLightShader = spotLightShader2;
	BindShader(spotLightShader);

	glUniform1i(glGetUniformLocation(
		spotLightShader->GetProgram(), "depthTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferDepthTex);

	glUniform1i(glGetUniformLocation(
		spotLightShader->GetProgram(), "normTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bufferNormalTex);

	glUniform1i(glGetUniformLocation(
		spotLightShader->GetProgram(), "specTex"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, bufferSpecTex);

	glUniform3fv(glGetUniformLocation(spotLightShader->GetProgram(),
		"cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform2f(glGetUniformLocation(spotLightShader->GetProgram(),
		"pixelSize"), 1.0f / width, 1.0f / height);

	Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
	glUniformMatrix4fv(glGetUniformLocation(
		spotLightShader->GetProgram(), "inverseProjView"),
		1, false, invViewProj.values);

	UpdateShaderMatrices();

	if(!snow)UFOLight = new Light(UFO->GetWorldTransform().GetPositionVector(), UFOLightColour, 700);
	else UFOLight = new Light(UFO->GetWorldTransform().GetPositionVector(), UFO->GetColour(), 700);
	SetShaderLight(*UFOLight);
	sphere->Draw();
}

void Renderer::DrawMiniMapMethod1(SceneNode* n) {
	BindShader(miniMapShader1);
	viewMatrix = topCamera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(miniMapShader1->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(miniMapShader1->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());

	texture = n->GetMesh()->GetTexture();
	glUniform1i(glGetUniformLocation(miniMapShader1->GetProgram(),
		"diffuseTex"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	n->Draw(*this);
}

void Renderer::DrawMiniMapMethod2(SceneNode* n) {
	BindShader(miniMapShader2);
	viewMatrix = topCamera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f,
		(float)width / (float)height, 45.0f);

	UpdateShaderMatrices();

	Matrix4 model = n->GetWorldTransform() *
		Matrix4::Scale(n->GetModelScale());
	glUniformMatrix4fv(
		glGetUniformLocation(miniMapShader2->GetProgram(),
			"modelMatrix"), 1, false, model.values);
	glUniform4fv(glGetUniformLocation(miniMapShader2->GetProgram(),
		"nodeColour"), 1, (float*)&n->GetColour());
	glUniform1i(glGetUniformLocation(shader5->GetProgram(),
		"diffuseTex"), 0);

	vector<Matrix4> frameMatrices;

	const Matrix4* invBindPose = n->GetMesh()->GetInverseBindPose();
	const Matrix4* frameData = n->GetAnim()->GetJointData(n->GetCurrentFrame());

	for (unsigned int i = 0; i < n->GetMesh()->GetJointCount(); ++i) {
		frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
	}

	int j = glGetUniformLocation(miniMapShader2->GetProgram(), "joints");
	glUniformMatrix4fv(j, frameMatrices.size(), false,
		(float*)frameMatrices.data());
	for (int i = 0; i < n->GetMesh()->GetSubMeshCount(); ++i) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, n->GetMat(i));
		n->GetMesh()->DrawSubMesh(i);
	}
}
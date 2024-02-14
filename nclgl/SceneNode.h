#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "ChildMeshInterface.h"
#include "MeshAnimation.h"
#include "MeshMaterial.h"
#include "Shader.h"

class SceneNode {
public:
	SceneNode(Mesh* m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
	~SceneNode(void);

	void SetTransform(const Matrix4& matrix) { transform = matrix; }
	const Matrix4& GetTransform() const { return transform; }
	Matrix4 GetWorldTransform() const { return worldTransform; }

	Vector4 GetColour() const { return colour; }
	void SetColour(Vector4 c) { colour = c; }

	Vector3 GetModelScale() const { return modelScale; }
	void SetModelScale(Vector3 s) { modelScale = s; }

	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh* m) { mesh = m; }

	OBJMesh* GetOBJMesh() const { return OBJmesh; }
	void SetOBJMesh(OBJMesh* m) { OBJmesh = m; }

	float GetBoundingRadius() const { return boundingRadius; }
	void SetBoundingRadius(float f) { boundingRadius = f; }

	float GetCameraDistance() const { return distanceFromCamera; }
	void SetCameraDistance(float f) { distanceFromCamera = f; }

	GLuint GetTexture() const { return texture; }
	void SetTexture(GLuint tex) { texture = tex; }

	bool GetCulled() const { return culled; }
	void SetCulled(bool c) { culled = c; }

	bool GetRepeating() const { return repeating; }
	void SetRepeating(bool r) { repeating = r; }

	int GetDrawMeshType() const { return DrawMeshType; }
	void SetDrawMeshType(int msh) { DrawMeshType = msh; }

	int GetDrawMethodType() const { return DrawMethodType; }
	void SetDrawMethodType(int t) { DrawMethodType = t; }

	void SetMaterial(MeshMaterial* m) { material = m; }
	void SetAnimation(MeshAnimation* a) { anim = a; }

	int GetCurrentFrame() const { return currentFrame; }
	void SetCurrentFrame(int f) { currentFrame = f; }

	float GetFrameTime() const { return frameTime; }
	void SetFrameTime(float f) { frameTime = f; }

	int GetEmissive() const { return emissive; }
	void SetEmissive(int e) { emissive = e; }

	bool GetRotate() const { return TextureRotate; }
	void SetRotate(bool r) { TextureRotate = r; }

	MeshAnimation* GetAnim() const { return anim; }

	bool GetInit() const { return init; }

	void SetMatList(vector<GLuint> m) { matTextures.assign(m.begin(), m.end()); }
	GLuint GetMat(int i) const { return matTextures[i]; }



	static bool CompareByCameraDistance(SceneNode* a, SceneNode* b) {
		return (a->distanceFromCamera <
			b->distanceFromCamera) ? true : false;
	}
	
	void AddChild(SceneNode* s);
	virtual void Update(float dt);
	virtual void Draw(const OGLRenderer& r);


	std::vector<SceneNode*>::const_iterator GetChildIteratorStart() {
		return children.begin();}

	std::vector<SceneNode*>::const_iterator GetChildIteratorEnd() {
		return children.end();}
protected:
	SceneNode* parent;
	Mesh* mesh;
	OBJMesh* OBJmesh;
	Matrix4 worldTransform;
	Matrix4 transform;
	Vector3 modelScale;
	Vector4 colour;
	MeshAnimation* anim;
	MeshMaterial* material;
	vector<GLuint> matTextures;
	std::vector<SceneNode*> children;
	float distanceFromCamera;
	float boundingRadius;
	GLuint texture;
	bool culled;
	bool repeating;
	int DrawMeshType;
	int DrawMethodType;
	bool emissive;
	int currentFrame;
	float frameTime;
	bool init;
	bool TextureRotate;
};
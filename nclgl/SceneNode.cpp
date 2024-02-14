#include "SceneNode.h"

SceneNode::SceneNode(Mesh* mesh, Vector4 colour) {
	this->mesh = mesh;
	this->colour = colour;
	this->material = NULL;
	this->anim = NULL;
	parent = NULL;
	OBJmesh = NULL;
	modelScale = Vector3(1, 1, 1);
	boundingRadius = 1.0f;
	distanceFromCamera = 0.0f;
	texture = 0;
	culled = true;
	repeating = false;
	DrawMeshType = 1;
	DrawMethodType = 1;
	currentFrame = 0;
	frameTime = 0.0f;
	emissive = false;
	init = true;
	TextureRotate = false;
}

SceneNode::~SceneNode(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void SceneNode::AddChild(SceneNode* s) {
	children.push_back(s);
	s->parent = this;
}
void SceneNode::Draw(const OGLRenderer& r) {
	if (mesh) 
		if(this->GetDrawMeshType() == 1)
	{ mesh->Draw(); }
		else if(this->GetDrawMeshType() == 2)
	{OBJmesh->OBJDraw();}
			
}
void SceneNode::Update(float dt) {
	if (parent) {
		worldTransform = parent->worldTransform * transform;
	}
	else {
		worldTransform = transform;
	}
	for (vector<SceneNode*>::iterator i = children.begin();
		                              i != children.end(); ++i) {
		(*i)->Update(dt);
	}
}





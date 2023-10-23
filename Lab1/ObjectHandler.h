#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>
#include "transform.h"
#include "TextureMap.h"
#include "MeshHandler.h"
#include "ShaderHandler.h"
#include "WorldCamera.h"
#include "AudioHandler.h"

// Each indivdual object that will be stored by the handler
struct Object
{
public:
	Object()
	{
		
	};
	// Overrides to make it easier to create objects
	Object(MeshHandler& mesh, TextureMap& texture, ShaderHandler& shader)
	{
		LoadObject(mesh, texture, shader);
	};
	
	Object(const std::string& fileName, TextureMap& texture, ShaderHandler& shader)
	{
		LoadObjectFILE(fileName, texture, shader);
	};
	// For passing in an already loaded mesh
	void LoadObject(MeshHandler& mesh, TextureMap& texture, ShaderHandler& shader)
	{
		_texture = texture;
		_shader = shader;
		_mesh = mesh;
		_transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetScale(glm::vec3(1.0, 1.0, 1.0));
	}
	// Pass in a mesh to load from a file
	void LoadObjectFILE(const std::string& fileName, TextureMap& texture, ShaderHandler& shader)
	{
		_texture = texture;
		_shader = shader;
		_mesh.loadModel(fileName);
		_transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		_transform.SetScale(glm::vec3(1.0, 1.0, 1.0));
	}
	
	inline void SetObjectPos(glm::vec3& pos) {_transform.SetPos(pos);}
	inline void SetObjectRot(glm::vec3& rot) { _transform.SetRot(rot);}
	inline void SetObjectScale(glm::vec3& scale) { _transform.SetScale(scale);}
	
	// The objects variables to use in rendering
	Transform _transform;
	TextureMap _texture;
	ShaderHandler _shader;
	MeshHandler _mesh;
	
private:
	
};

class ObjectHandler
{
public:
	
	ObjectHandler();

	~ObjectHandler();
	void initObjects();
	void initTextures();
	void initShaders();
	void initMeshes();
	void drawObjects(WorldCamera& myCamera, float counter, float newCount);
	bool collision(float deltatime, AudioHandler& audio);

	
private:
	// These temp variables are used to avoid the deconstructors when moving the object into the vector array.
	Object tempObject;
	TextureMap tempTexture;
	ShaderHandler tempShader;
	MeshHandler tempMesh;
	
	// objects is a vector of objects that will be drawn in the scene. 
	std::vector<Object> objects;
	// Arrays of all possible tex/shaders/meshes an object can have 
	std::vector<TextureMap> textures;
	std::vector<ShaderHandler> shaders;
	std::vector<MeshHandler> meshs;
	
};


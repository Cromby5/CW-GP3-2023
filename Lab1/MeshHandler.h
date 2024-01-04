#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"
#include "ShaderHandler.h"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using std::vector;

struct Vertex
{
public:
	/*
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	*/
	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }


	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
private:

};

struct Sphere
{
public:

	Sphere()
	{
		this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
		this->radius = 1.0f;
	}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

// The start of implementing assimp, basically starting from scratch to avoid the issues with the obj loader to
// remove it safely and to learn how to use assimp while trying to improve performance passing by reference. 
// Thanks to the tutorial at http://www.learnopengl.com/#!Model-Loading/Model

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	// mesh data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, const vector<Texture>& textures);

	void Draw(const ShaderHandler& shader);
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};

class Model
{
public:
	Model();
	Model(std::string const &path)
	{
		loadModel(path);
	}
	void Draw(const ShaderHandler& shader);
	void loadModel(std::string const& path);
private:
	// model data
	vector<Mesh> meshes;
	vector<Texture> textures_loaded; 
	std::string directory;


	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int Model::TextureFromFile(const char* path, const std::string& directory);
};


// OLD
class MeshHandler
{
public:
	MeshHandler();
	MeshHandler(const std::string& filename);
	~MeshHandler();

	void draw();
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);
	void updateSphereData(glm::vec3 pos, float radius);
	glm::vec3 getSpherePos() { return meshSphere.GetPos(); }
	float getSphereRadius() { return meshSphere.GetRadius(); }

private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshSphere;
	GLuint VAO;
	GLuint VAB[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; // how much of the vertexArrayObject do we want to draw
};
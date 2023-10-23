#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
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
#include "ObjectHandler.h"
#include <iostream>

ObjectHandler::ObjectHandler()
{
	
}


ObjectHandler::~ObjectHandler()
{
	
}
// Extra mess from previous coursework, not really related to graphics programming so it will stay like this.
void ObjectHandler::initObjects()
{
	// Unsure whats going on that I can't use the constructor to load the objects directly into the vector of objects without the data being wrong in someway,
	// making a temp new object/texture/shader and then loading it into the vector works fine though from testing.
	// Pre load the assets to save time and memory
	initTextures();
	initShaders();
	initMeshes();
	
	objects.reserve(15); // reserve 15 objects to prevent reallocation of the vector in this example scene.

	tempObject.LoadObject(meshs[0], textures[2], shaders[5]); // Exploding monkey head
	objects.emplace_back(tempObject); // Add the object to the vector of objects
	// Adjust position,rotation,scale
	objects[0].SetObjectPos(glm::vec3(10.0, 1.5, 3.0));
	
	//tempObject.LoadObject(meshs[1], textures[0], shaders[4]); // Light Cube
	//objects.emplace_back(tempObject);
	//objects[1].SetObjectPos(glm::vec3(0.0, 3.0, 0.0));
	
	// MANDEL A (Final, As seen in document)
	tempObject.LoadObject(meshs[2], textures[2], shaders[7]);
	objects.emplace_back(tempObject);
	objects[1].SetObjectPos(glm::vec3(0, -6.0, 0));
	objects[1].SetObjectRot(glm::vec3(0, 0, 0));

	// MANDEL B (First Attempt, left in for fun)
	tempObject.LoadObject(meshs[2], textures[2], shaders[8]);
	objects.emplace_back(tempObject);
	objects[2].SetObjectPos(glm::vec3(45, -6.0, 45));
	objects[2].SetObjectRot(glm::vec3(0, 0, 0));

	// Emap cube
	tempObject.LoadObject(meshs[1], textures[1], shaders[6]);
	objects.emplace_back(tempObject);
	objects[3].SetObjectPos(glm::vec3(0, 2, 2));
	
	// Repeat for every object to be added
	/*
	tempObject.LoadObject(meshs[0], textures[1], shaders[0]); // Monkey head 2
	objects.emplace_back(tempObject);
	objects[1].SetObjectPos(glm::vec3(100.0, 5, 3.0));
	*/
	//tempObject.LoadObject(meshs[2], textures[0], shaders[3]); // Cart, Refraction
	//objects.emplace_back(tempObject);
	//objects[3].SetObjectPos(glm::vec3(0.0, 0.5, 8.0));
	//objects[3].SetObjectScale(glm::vec3(5.0, 5.0, 5.0));

	//tempObject.LoadObject(meshs[3], textures[2], shaders[0]); // Canoe
	//objects.emplace_back(tempObject);
	//objects[4].SetObjectPos(glm::vec3(-5.0, -2.5, 3.0));
	//objects[4].SetObjectScale(glm::vec3(0.5, 0.5, 0.5));

	//tempObject.LoadObject(meshs[4], textures[3], shaders[0]); // Backpack
	//objects.emplace_back(tempObject);
	//objects[5].SetObjectPos(glm::vec3(5.0, -2.0, 0.0));

	//tempObject.LoadObject(meshs[5], textures[4], shaders[0]); // Wooden Crate
	//objects.emplace_back(tempObject);
	//objects[5].SetObjectPos(glm::vec3(-3.0, -2.0, 0.0));
}

void ObjectHandler::initTextures()
{
	// Load in all the textures and store them in the vector to be used later by any object.
	textures.reserve(10); // prevent reallocation of the vector in this example scene.

	tempTexture.LoadTexture("..\\res\\Textures\\bricks.jpg",0);
	tempTexture.LoadTexture("..\\res\\Textures\\bricksNormal.png", 1);
	tempTexture.LoadTexture("..\\res\\Textures\\BricksSpecularMap.png", 2);
	textures.emplace_back(tempTexture);
	
	tempTexture.LoadTexture("..\\res\\Textures\\water.jpg",0);
	tempTexture.LoadTexture("..\\res\\Textures\\water.jpg", 1);
	textures.emplace_back(tempTexture);

	tempTexture.LoadTexture("..\\res\\Textures\\Oak-Architextures.jpg", 0);
	textures.emplace_back(tempTexture);

	tempTexture.LoadTexture("..\\res\\Textures\\diffuse.jpg", 0);
	tempTexture.LoadTexture("..\\res\\Textures\\normal.png", 1); // Backpack normal
	tempTexture.LoadTexture("..\\res\\Textures\\specular.jpg", 2); // Backpack specular
	textures.emplace_back(tempTexture);

	tempTexture.LoadTexture("..\\res\\Textures\\Walnut-Architextures.jpg", 0);
	textures.emplace_back(tempTexture);

}

void ObjectHandler::initShaders()
{
	// Load in all the shaders and store them in the vector to be used later by any object.
	shaders.reserve(10); // prevent reallocation of the vector in this example scene.
	
	tempShader.init("..\\res\\shader"); // 0:
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\SkyboxShader"); // 1:
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\ReflectShader"); // 2:
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\RefractShader"); // 3:
	shaders.emplace_back(tempShader);
	
	tempShader.init("..\\res\\LightShader"); // 4:
	shaders.emplace_back(tempShader);

	// NEW for Graphics Programming
	
	tempShader.initGeo(); // 5: Force Exploding Shader, only reason for this is to show the use of a geometry shader which is required.
	shaders.emplace_back(tempShader);

	tempShader.init("..\\res\\eMapping"); // 6: The shader for the environment mapping, Slightly different from the reflect shader since textures can be used ontop
	shaders.emplace_back(tempShader);

	tempShader.init("..\\res\\Mandelbrot"); // 7: The main shader for the mandelbrot set, 
	shaders.emplace_back(tempShader);

	tempShader.init("..\\res\\MandelbrotB"); // 8: The backup shader for the mandelbrot set, broken.
	shaders.emplace_back(tempShader);
	
	// Custom Technique
}

void ObjectHandler::initMeshes()
{
	// Load in all the meshes and store them in the vector to be used later by any object.
	meshs.reserve(10); // prevent reallocation of the vector in this example scene.
	
	tempMesh.loadModel("..\\res\\Models\\monkey3.obj"); // Load a mesh from a file
	meshs.emplace_back(tempMesh);
	
	tempMesh.loadModel("..\\res\\Models\\cube.obj");
	meshs.emplace_back(tempMesh);

	tempMesh.loadModel("..\\res\\Models\\plane.obj");
	meshs.emplace_back(tempMesh);

	/*
	tempMesh.loadModel("..\\res\\Models\\cart.obj");
	meshs.emplace_back(tempMesh);

	tempMesh.loadModel("..\\res\\Models\\canoe.obj");
	meshs.emplace_back(tempMesh);

	tempMesh.loadModel("..\\res\\Models\\backpack.obj");
	meshs.emplace_back(tempMesh);

	tempMesh.loadModel("..\\res\\Models\\Wooden Crate 01.obj");
	meshs.emplace_back(tempMesh);
	*/

}

void ObjectHandler::drawObjects(WorldCamera& myCamera , float counter, float newCount)
{
	// For each object in the vector of objects, draw it with their own properties.
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		// For Emap Forcing, This may be required for proper appearence and of course should not be here.
		if (i == 3)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			objects[i]._texture.Bind(1);
		}
		
		objects[i]._shader.Use();
		objects[i]._shader.Update(objects[i]._transform, myCamera, counter, newCount);
		objects[i]._texture.Bind(0);
		// Temp overrides, carried across from inital project state to test the new object handler.
		// For spec/normal map testing on the bricks and backpack
		/*
		if ( i == 3 || i == 6)
		{
			objects[i]._texture.Bind(1);
			objects[i]._texture.Bind(2);
		}
		*/


		// For collision tests with the monkey models
		/*
		if (i == 0)
		{
			objects[i].SetObjectPos(glm::vec3(sinf(counter),0.5f,0.0f));
		}
		if (i == 1)
		{
			objects[i].SetObjectPos(glm::vec3(-sinf(counter),-0.5f, 0.0f));
		}
		*/
		objects[i]._mesh.draw();
		objects[i]._mesh.updateSphereData(objects[i]._transform.GetPos(), 1.0f);
	}
}

// Limited to the first 2 objects created for demo purposes and to prevent unecssarsary performance loss for our objects that will never move in this example.
// Disabled for Graphics Programming
bool ObjectHandler::collision(float deltatime, AudioHandler& audio)
{
	while (deltatime > 0) // To keep the amount of collisions the same between any frame rate change
	{
		glm::vec3 m1Pos = objects[0]._mesh.getSpherePos();
		float m1Rad = objects[0]._mesh.getSphereRadius();
		glm::vec3 m2Pos = objects[1]._mesh.getSpherePos();
		float m2Rad = objects[1]._mesh.getSphereRadius();

		float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

		if (distance * distance < (m1Rad + m2Rad))
		{
			audio.playSound(0);
			std::cout << distance << '\n';
			return true;
		}
		else
		{
			return false;
		}
	}
	// To make sure all paths return a value
	return false;
}




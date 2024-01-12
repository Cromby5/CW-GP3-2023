#include "Scene.h"
#include "Entity.h"




//ECS Architecture Attempt using EnTT https://github.com/skypjack/entt, bound to be a bit messy to fit the project requirements
// ObjectHandler is not really supposed be used, old code that I didn't want to remove in case I needed it later
Scene::Scene()
{
	//entt::entity entity = m_registry.create();
}

Scene::~Scene()
{
}

Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = Entity(m_registry.create(), this);
	entity.AddComponent<Transform>(); // add transform component to entity, this is a default component for all entities in the scene 
	// A tag component is a component that has no data, it is just a way to tag an entity as something specific, default component
	auto& tag = entity.AddComponent<Tag>();
	tag.name = name.empty() ? "Entity" : name; // if name is empty, set tag to "Entity", otherwise set it to the name passed in
	return entity;
}

void Scene::Update(float deltaTime, const WorldCamera& cam, float counter, float newCounter)
{
	auto view = m_registry.view<Tag>();

	//if (imgui)
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "ENTITY LIST");
		ImGui::BeginChild("Scrolling");
		for (auto entity : view)
		{
			auto& tag = view.get<Tag>(entity);
			ImGui::Text("Entity name: %s", tag.name.c_str());

		}
		ImGui::EndChild();
	//endif

	auto group = m_registry.group<Transform>(entt::get<Model, ShaderHandler, TextureMap, Sphere>);
	for (auto entity : group)
	{
		auto& [transform, sceneModel, shader, texMap, sphereCollider] = group.get<Transform, Model, ShaderHandler, TextureMap, Sphere>(entity);
		std :: cout << "Updating Scene" << std::endl;

		shader.Use();
		shader.Update(transform, cam , 0.5f, 0.5f);
		texMap.Bind(0);

		sceneModel.Draw(shader);

		sphereCollider.SetPos(transform.GetPos());
		sphereCollider.SetRadius(1.0f);

	}

	auto viewMissile = m_registry.view<Missile,Transform>();
	for (auto entity : viewMissile)
	{
		auto& missile = viewMissile.get<Missile>(entity);
		auto& missileTransform = viewMissile.get<Transform>(entity);
		missileTransform.MoveForward(2.0f * deltaTime);
		missile.updateMissile(deltaTime);

	}

	auto & player = m_registry.view<Transform, Player>();
	for (auto entity : player)
	{
		//auto& player1 = player.get<Player>(entity);
		auto& playTransform = player.get<Transform>(entity);
		playTransform.SetPos(cam.GetPos());

	}

}



void Scene::CheckCollisionsEntity(Entity entity, float deltaTime)
{
	
	auto view = m_registry.view<Sphere>();

	auto& sphereCollider = view.get<Sphere>(entity);

	for (auto otherEnt : view)
	{
		if (otherEnt == entity)
			continue;

		auto& otherSphere = view.get<Sphere>(otherEnt);

			glm::vec3 m1Pos = sphereCollider.GetPos();
			float m1Rad = sphereCollider.GetRadius();
			glm::vec3 m2Pos = otherSphere.GetPos();
			float m2Rad = otherSphere.GetRadius();

			float distance = ((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

			if (distance * distance < (m1Rad + m2Rad))
			{
				m_registry.destroy(otherEnt);
			}
			else
			{
				//return false;
			}
	}
}

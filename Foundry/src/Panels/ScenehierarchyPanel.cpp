#include "Panels/ScenehierarchyPanel.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ember
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
		: m_Context(context)
	{
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		auto view = m_Context->m_Registry.view<entt::entity>();
		ImGui::Text("Scene 1");
		view.each([&](auto entityID) {
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});
		ImGui::Separator();

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_SelectionContext = {};
		}

		// Right-click on blank space
		if(ImGui::BeginPopupContextWindow(0, 1 | ImGuiPopupFlags_NoOpenOverItems))
		{
			if (ImGui::MenuItem("Create an Entity"))
			{
				m_Context->CreateEntity("New Entity");
			}

			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);			
		}
		ImGui::End();

	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if(ImGui::BeginPopupContextItem())
		{
			if(ImGui::MenuItem("Delete Entity"))
			{
				entityDeleted = true;
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if(entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if(m_SelectionContext == entity)
			{
				m_SelectionContext = {};
			}
		}
	}

	// Labels need to be unique
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValues = 0.0, float columnWidth = 100.0)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);

		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight};

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if(ImGui::Button("X", buttonSize))
		{
			values.x = resetValues;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if(ImGui::Button("Y", buttonSize))
		{
			values.y = resetValues;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 0.1f });
		ImGui::PushFont(boldFont);
		if(ImGui::Button("Z", buttonSize))
		{
			values.z = resetValues;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionaAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionaAvailable.x - lineHeight * 0.5f);

			if(ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if(ImGui::BeginPopup("ComponentSettings"))
			{

				if(ImGui::MenuItem("Remove Component"))
				{
					removeComponent = true;
				}

				ImGui::EndPopup();
			}

			if(open)
			{
				uiFunction(component);

				ImGui::TreePop();
			}

			if(removeComponent)
			{
				entity.RemoveComponent<T>();
			}
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if(entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy(buffer, tag.c_str(), sizeof(buffer));
			if(ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				entity.UpdateComponent<TagComponent>(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if(ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponent");
		}

		if(ImGui::BeginPopup("AddComponent"))
		{
			if(!entity.HasComponent<CameraComponent>())
			{
				if(ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
			}

			if (!entity.HasComponent<SpriteRendererComponent>())
			{
				if(ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", entity, [this, entity](auto& component)
		{
			DrawVec3Control("Translation", component.Translation);
			glm::vec3 rotation = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rotation);
			component.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", component.Scale, 1.0f);
		});

		DrawComponent<CameraComponent>("Camera", entity, [this, entity](CameraComponent& component)
		{
			auto& camera = component.Camera;

			if(ImGui::Checkbox("Primary", &component.Primary))
			{
				for(auto otherEntity : m_Context->m_Registry.view<CameraComponent>())
				{
					Entity other = { otherEntity, m_Context.get() };
					if(other != entity && other.GetComponent<CameraComponent>().Primary)
					{
						other.GetComponent<CameraComponent>().Primary = false;
					}
				}
			}

			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

			if(ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for(int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if(ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if(isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			if(camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float verticalFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
				if(ImGui::DragFloat("Vertical FOV", &verticalFOV))
				{
					camera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));
				}

				float near = camera.GetPerspectiveNearClip();
				if(ImGui::DragFloat("Near", &near))
				{
					camera.SetPerspectiveNearClip(near);
				}
				
				float far = camera.GetPerspectiveFarClip();
				if(ImGui::DragFloat("Far", &far))
				{
					camera.SetPerspectiveFarClip(far);
				}
			}

			if(camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float size = camera.GetOrthographicSize();
				if(ImGui::DragFloat("Size", &size))
				{
					camera.SetOrthographicSize(size);
				}

				float near = camera.GetOrthographicNearClip();
				if(ImGui::DragFloat("Near", &near))
				{
					camera.SetOrthographicNearClip(near);
				}
				
				float far = camera.GetOrthographicFarClip();
				if(ImGui::DragFloat("Far", &far))
				{
					camera.SetOrthographicFarClip(far);
				}

				ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
			}
		});

		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [this, entity](auto& component)
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
		});

	}

	void SceneHierarchyPanel::DrawAddComponent(Entity entity)
	{
	}

}

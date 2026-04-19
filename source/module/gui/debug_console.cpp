#include"debug_console.hpp"
void debugconsole::Render(DinosaurData& dinosaurData, GroundData& groundData, ObstacleData& obstacleData, glm::vec2& camera, bool& freeMode, bool& isDead)
{
	ImGui::Begin("DebugConsole");
	if(ImGui::BeginTabBar("DebugTabBar"))
	{
		if (ImGui::BeginTabItem("General"))
		{
			ImGui::DragFloat("CameraX", &camera.x);
			ImGui::DragFloat("CameraY", &camera.y);
			ImGui::Checkbox("FreeMode", &freeMode);
			ImGui::Checkbox("IsDead", &isDead);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			ImGui::DragFloat("X", &dinosaurData.position.x);
			ImGui::DragFloat("Y", &dinosaurData.position.y);
			ImGui::DragFloat("SpeedX", &dinosaurData.speed.x);
			ImGui::DragFloat("SpeedY", &dinosaurData.speed.y);
			ImGui::InputFloat("Direction", &dinosaurData.direction);
			ImGui::InputFloat("AirTime", &dinosaurData.airTime);
			ImGui::DragFloat("WalkSpeed", &dinosaurData.walkSpeed);
			ImGui::DragFloat("SpeedLimit", &dinosaurData.speedLimit);
			ImGui::DragFloat("IncreaseSpeed", &dinosaurData.increaseSpeed);
			ImGui::DragFloat("Gravity", &dinosaurData.gravity);
			ImGui::DragFloat("JumpSpeed", &dinosaurData.jumpSpeed);
			ImGui::DragFloat("CoyoteTime", &dinosaurData.coyoteTime);
			ImGui::InputScalar("AnimationState", ImGuiDataType_U64, &dinosaurData.animationState);
			ImGui::InputFloat("AnimationFrame", &dinosaurData.animationFrame);
			ImGui::InputScalar("AnimationIdle", ImGuiDataType_U64, &dinosaurData.animationIdle);
			ImGui::InputFloat("AnimationSpeed", &dinosaurData.animationSpeed);
			ImGui::InputScalar("RunAnimationStart", ImGuiDataType_U64, &dinosaurData.runAnimationStart);
			ImGui::InputScalar("RunAnimationFrameCount", ImGuiDataType_U64, &dinosaurData.runAnimationFrameCount);
			ImGui::DragFloat("CollisionBoxLeft", &dinosaurData.collisionBox.left);
			ImGui::DragFloat("CollisionBoxRight", &dinosaurData.collisionBox.right);
			ImGui::DragFloat("CollisionBoxUp", &dinosaurData.collisionBox.up);
			ImGui::DragFloat("CollisionBoxDown", &dinosaurData.collisionBox.down);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Obstacle"))
		{
			ImGui::InputScalar("InstanceCount", ImGuiDataType_U64, &obstacleData.instanceCount);
			ImGui::InputFloat("MinRespawnOffset", &obstacleData.minRespawnOffset);
			ImGui::InputFloat("MaxRespawnOffset", &obstacleData.maxRespawnOffset);
			ImGui::InputFloat("SafetyValue", &obstacleData.safetyValue);
			ImGui::InputFloat("GenerateDistance", &obstacleData.generateDistance);
			ImGui::InputFloat("PositionY", &obstacleData.positionY);
			ImGui::InputFloat("Spacing", &obstacleData.spacing);
			if (ImGui::BeginTable("ObstacleDataTable", 10, ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("PositionsX");
				ImGui::TableSetupColumn("PositionsY");
				ImGui::TableSetupColumn("Indices");
				ImGui::TableSetupColumn("SizesX");
				ImGui::TableSetupColumn("SizesY");
				ImGui::TableSetupColumn("TextureIndices");
				ImGui::TableSetupColumn("CollisionBoxesLeft");
				ImGui::TableSetupColumn("CollisionBoxesRight");
				ImGui::TableSetupColumn("CollisionBoxesUp");
				ImGui::TableSetupColumn("CollisionBoxesDown");
				ImGui::TableHeadersRow();
				for (size_t i = 0; i < obstacleData.indices.size(); i++)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%.2f", obstacleData.positions[i].x);
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%.2f", obstacleData.positions[i].y);
					ImGui::TableSetColumnIndex(2);
					ImGui::Text("%zu", obstacleData.indices[i]);
					ImGui::TableSetColumnIndex(3);
					ImGui::Text("%.2f", obstacleData.sizes[obstacleData.indices[i]].x);
					ImGui::TableSetColumnIndex(4);
					ImGui::Text("%.2f", obstacleData.sizes[obstacleData.indices[i]].y);
					ImGui::TableSetColumnIndex(5);
					ImGui::Text("%zu", obstacleData.textureIndices[obstacleData.indices[i]]);
					ImGui::TableSetColumnIndex(6);
					ImGui::Text("%.2f", obstacleData.collisionBoxes[obstacleData.indices[i]].left);
					ImGui::TableSetColumnIndex(7);
					ImGui::Text("%.2f", obstacleData.collisionBoxes[obstacleData.indices[i]].right);
					ImGui::TableSetColumnIndex(8);
					ImGui::Text("%.2f", obstacleData.collisionBoxes[obstacleData.indices[i]].up);
					ImGui::TableSetColumnIndex(9);
					ImGui::Text("%.2f", obstacleData.collisionBoxes[obstacleData.indices[i]].down);
				}
				ImGui::EndTable();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Ground"))
		{
			ImGui::DragFloat("SizeX", &groundData.size.x);
			ImGui::DragFloat("SizeY", &groundData.size.y);
			ImGui::DragFloat("CollisionBoxLeft", &groundData.collisionBox.left);
			ImGui::DragFloat("CollisionBoxRight", &groundData.collisionBox.right);
			ImGui::DragFloat("CollisionBoxUp", &groundData.collisionBox.up);
			ImGui::DragFloat("CollisionBoxDown", &groundData.collisionBox.down);
			if (ImGui::BeginTable("GroundDataTable", 3, ImGuiTableFlags_Borders))
			{
				ImGui::TableSetupColumn("PositionsX");
				ImGui::TableSetupColumn("PositionsY");
				ImGui::TableSetupColumn("StyleIndices");
				ImGui::TableHeadersRow();
				for (size_t i = 0; i < groundData.styleIndices.size(); i++)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%.2f", groundData.positions[i].x);
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%.2f", groundData.positions[i].y);
					ImGui::TableSetColumnIndex(2);
					ImGui::Text("%zu", groundData.styleIndices[i]);
				}
				ImGui::EndTable();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}
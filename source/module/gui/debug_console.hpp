#pragma once
#include<glm/glm.hpp>
#include<imgui.h>
#include<string>
#include"../entity/dinosaur.hpp"
#include"../scene/ground.hpp"
#include"../entity/obstacle.hpp"
namespace debugconsole
{
	void Render(DinosaurData& dinosaurData, GroundData& groundData, ObstacleData& obstacleData, glm::vec2& camera, bool& freeMode, bool& isDead);
}
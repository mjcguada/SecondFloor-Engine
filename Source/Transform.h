#pragma once

// Matrix and vectors
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
	glm::vec3 Position;
	glm::vec4 Rotation;
	glm::vec3 Scale;
};


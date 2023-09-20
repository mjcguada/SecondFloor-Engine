#pragma once
#include "Transform.h"

// Smart pointers
#include <memory>
#include <vector>


class GameObject
{
public:
	std::unique_ptr<GameObject> parent;
	std::vector<std::unique_ptr<GameObject>> children;

	
};


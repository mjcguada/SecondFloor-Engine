#include <iostream>
#include "Engine.h"

int main()
{
	Engine* engine = new Engine(1280, 1000, "Second Floor");
	engine->Initialize();
	engine->Run();

	delete engine;

	return 0;
}
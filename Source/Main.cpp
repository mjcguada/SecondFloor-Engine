#include <iostream>
#include "Engine.h"

int main()
{
	Engine* engine = new Engine();
	engine->Initialize(1280, 1000, "Second Floor");
	engine->Run();
	engine->Stop();

	return 0;
}
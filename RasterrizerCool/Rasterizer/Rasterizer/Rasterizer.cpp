// StraalTraceerder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Renderer.h"
#include "Texture.h"
#include "Color.h"
#include "Scene.h"
#include "Line.h"


#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300



SDL_Window* window = NULL;
Renderer* renderer = NULL;
Texture* rayTexture = NULL;
SDL_Event eventHandler;
bool loop = true;

Uint32 fps_lasttime;	//last recorded time
Uint32 fps_current;
Uint32 fps_frames = 0;	// since last recorded
Uint32 fps_interval = 1;

bool initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("driehoekje Tekener", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	fps_lasttime = SDL_GetTicks();
	renderer = new Renderer(window);

	return renderer->IsValid();
}

void destroy()
{
	delete renderer;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

float get_random()
{
	static std::default_random_engine e;
	static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
	return dis(e);
}

int main(int argc, char* args[])
{
	std::cout << "Hello World!\n";

	SDL_SetMainReady();
	if (!initialize())
	{
		printf("Failed to initialize");
		destroy();
		return 0;
	}

	// Generate a 720p texture
	rayTexture = new Texture(SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer->AddTextureToRender(rayTexture);

	std::cout << "Hello World!\n";
	Scene* scene = new Scene();

	Camera* cam = new Camera(1.0f, SCREEN_WIDTH, SCREEN_HEIGHT, glm::mat4(1.0f));
	scene->AddCamera(cam);
	scene->AddLine(new Line(glm::vec3(1, 1, 0), glm::vec3(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0), Color(0,0,255), Color(255, 0, 0)));
	scene->AddLine(new Line(glm::vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), glm::vec3(SCREEN_WIDTH , SCREEN_HEIGHT /2, 0), Color(255, 0, 255), Color(0, 255, 0)));


	glm::mat4 meshTransform = glm::mat4(1);
	meshTransform = glm::rotate(0.785398f, glm::vec3(0, 1, 0));
	meshTransform = glm::scale(meshTransform, glm::vec3(0.5, 0.5, 0.5));
	meshTransform[3] = glm::vec4(0, 0, -1.5, 1);


	scene->SetActiveCamera(0);
	std::cout << "Created new objects!\n";

	//Texture generation
	auto rayrenderer = [](Scene* scene)
	{
		while (loop)
		{
			// Render our ray traced result to the texture
			scene->Render(*rayTexture);
		}
	};
	std::thread raythread(rayrenderer, scene);

	// Main game loop
	while (loop)
	{
		// Check SDL Events
		while (SDL_PollEvent(&eventHandler) != 0)
		{
			// Alt-F4 or X btn.
			if (eventHandler.type == SDL_QUIT)
			{
				loop = false;
			}
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_SPACE])
		{
			scene->ToggleActiveCamera();
		}

		// Render the scene
		if (renderer->IsValid())
		{
			renderer->OnTick();
		}

		// Calculate FPS and dump it to the cli every second.
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - (fps_interval * 1000))
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			printf("Current FPS: %i\n", fps_current);
			fps_frames = 0;
		}
	}

	raythread.join();

	destroy();
	return 0;
}
#pragma once

#include <SDL.h>
#include "Texture.h"

class Renderer
{
public:
	Renderer();
	Renderer(SDL_Window* window);
	~Renderer();

	inline bool IsValid() { return m_Renderer != NULL; }

	void OnTick();
	void AddTextureToRender(Texture* t);

private:
	SDL_Renderer* m_Renderer;
	std::vector<Texture*> m_TexturesToRender;

	void InitializeRenderer(SDL_Window* window);
	void Free();
};


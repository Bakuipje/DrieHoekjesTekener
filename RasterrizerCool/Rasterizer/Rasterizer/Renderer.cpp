#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{

}

Renderer::Renderer(SDL_Window* window)
{
	this->InitializeRenderer(window);
}

Renderer::~Renderer()
{
	this->Free();
}

void Renderer::OnTick()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);

	for (unsigned int i = 0; i < m_TexturesToRender.size(); i++)
	{
		if (m_TexturesToRender[i]->IsValid()) 
		{
			m_TexturesToRender[i]->UpdatePixels(m_Renderer);
			m_TexturesToRender[i]->Render(m_Renderer);
		}
		else
		{
			printf("Texture with id %i is invalid and could not be rendered!\n", i);
		}
	}

	if (this->IsValid()) 
	{
		SDL_RenderPresent(m_Renderer);
	}
}

void Renderer::AddTextureToRender(Texture* t)
{
	m_TexturesToRender.push_back(t);
	t->UpdatePixels(m_Renderer);
}

void Renderer::InitializeRenderer(SDL_Window* window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (!this->IsValid())
	{
		printf("Could not create renderer: %s\n", SDL_GetError());
	}

	SDL_RendererInfo info;
	SDL_GetRendererInfo(m_Renderer, &info);
	printf("Renderer name: %s\n", info.name);
	printf("Texture formats: \n");
	for (Uint32 i = 0; i < info.num_texture_formats; i++)
	{
		printf("%s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
	}
}

void Renderer::Free()
{
	if (!this->IsValid())
	{
		return;
	}

	SDL_DestroyRenderer(m_Renderer);
}

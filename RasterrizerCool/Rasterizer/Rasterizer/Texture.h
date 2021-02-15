#pragma once

#include <SDL.h>
#include "Color.h"
#include <vector>

class Renderer;

class Texture
{
public:
	Texture();
	Texture(int width, int height);
	~Texture();

	inline bool IsValid() { return m_Texture != NULL; }
	inline std::vector<Color> GetPixels() { return m_Pixels; }
	inline void SetPixels(std::vector<Color> newPixels) { m_Pixels = newPixels; m_TextureNeedsUpdate = true; }
	void SetPixel(int x, int y, Color col, bool ignoreUpdateStatus = false);
	void SetPixel(int pixelIndex, Color col, bool ignoreUpdateStatus = false);
	inline Color GetPixel(int pixelIndex) { return m_Pixels[pixelIndex]; }
	inline void SetNeedsUpdate() { m_TextureNeedsUpdate = true; }

	void UpdatePixels(SDL_Renderer* sdlRenderer);
	std::vector<unsigned char> InternalConvertPixels();	// Converts Color class to a format that SDL_Texture can understand.
	void Render(SDL_Renderer* renderer);

private:
	SDL_Texture* m_Texture;
	int m_Width;
	int m_Height;
	std::vector<Color> m_Pixels;
	bool m_TextureNeedsUpdate = false;

	void Free();
};


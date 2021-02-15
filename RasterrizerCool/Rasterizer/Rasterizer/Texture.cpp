#include "Texture.h"
#include "Renderer.h"

Texture::Texture()
{
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

Texture::Texture(int width, int height)
{
	m_Texture = NULL;
	m_Width = width;
	m_Height = height;
	m_Pixels = std::vector<Color>(width * height);
}

Texture::~Texture()
{
	Free();
}

void Texture::SetPixel(int x, int y, Color col, bool ignoreUpdateStatus)
{
	int pixelId = x + (y*m_Width);
	SetPixel(pixelId, col, ignoreUpdateStatus);
}

void Texture::SetPixel(int pixelIndex, Color col, bool ignoreUpdateStatus)
{
	m_Pixels[pixelIndex] = col; 
	if (!ignoreUpdateStatus)
	{
		m_TextureNeedsUpdate = true;
	}
}

void Texture::UpdatePixels(SDL_Renderer* sdlRenderer)
{
	if (this->IsValid()) 
	{
		if (!this->m_TextureNeedsUpdate)
		{
			return;
		}

		std::vector<unsigned char> pixels = this->InternalConvertPixels();
		unsigned char* lockedPixels;
		int pitch;

		SDL_LockTexture(m_Texture, NULL, reinterpret_cast<void**>(&lockedPixels), &pitch);
		std::copy(pixels.begin(), pixels.end(), lockedPixels);
		SDL_UnlockTexture(m_Texture);

		m_TextureNeedsUpdate = false;
	}
	else
	{
		m_Texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height);
	}
}


std::vector<unsigned char> Texture::InternalConvertPixels()		// TODO: Improve performance
{
	std::vector<unsigned char> toReturn(m_Height * m_Width * 4, 0);

	for (unsigned int i = 0; i < m_Pixels.size(); i++)
	{
		glm::vec4 col = m_Pixels[i].Get();
		const int baseindex = i * 4;
		toReturn[baseindex + 0] = col.z * 255;
		toReturn[baseindex + 1] = col.y * 255;
		toReturn[baseindex + 2] = col.x * 255;
		toReturn[baseindex + 3] = col.w * 255;
	}

	return toReturn;
}

void Texture::Render(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, m_Texture, NULL, NULL);
}

void Texture::Free()
{
	if (!this->IsValid()) 
	{
		return;
	}

	SDL_DestroyTexture(m_Texture);
	m_Width = 0;
	m_Height = 0;
}


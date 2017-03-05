#include "ResourceLoader.hpp"
#include "ResourcePath.hpp"

#define FILETYPE_TEXTURE 0
#define FILETYPE_SOUND 1
#define FILETYPE_FONT 2

ResourceLoader::ResourceLoader(string resourceFilePath)
{
	this->resourceFilePath = resourceFilePath;
	complete = false;
	fileCount = 0;
	filesLoaded = 0;
	currentFileType = -1;

	textureMap = new map<string, sf::Texture*>();
	soundMap = new map<string, sf::SoundBuffer*>();
	fontMap = new map<string, sf::Font*>();
}

////////////////////////////////////////////////////////////////////////

ResourceLoader::~ResourceLoader()
{
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::Run()
{
	CountFiles();

	fileStream.open(resourcePath() + resourceFilePath);

	while (!complete)
	{
		LoadStep();
	}
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::LoadStep()
{
	if (fileStream.eof())
	{
		complete = true;
		fileStream.close();
		return;
	}

	getline(fileStream, line);

	if (line.empty())
	{
		// Empty line, do nothing
		return;
	}
	else if (line.at(0) == '#')
	{
		// Comment, do nothing
		return;
	}
	else if (line.at(0) == '$')
	{
		//FileType tag, change currentFileType
		if (line == "$TEXTURES")
		{
			currentFileType = FILETYPE_TEXTURE;
		}
		else if (line == "$SOUNDS")
		{
			currentFileType = FILETYPE_SOUND;
		}
		else if (line == "$FONTS")
		{
			currentFileType = FILETYPE_FONT;
		}
	}
	else
	{
		//Load file
		switch (currentFileType)
		{
			case FILETYPE_TEXTURE:
				LoadTexture();
				break;
			case FILETYPE_SOUND:
				LoadSound();
				break;
			case FILETYPE_FONT:
				LoadFont();
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////

float ResourceLoader::GetPercentDone()
{
	if (fileCount == 0)
	{
		return 0.0f;
	}
	else
	{
		return (float)filesLoaded / (float)fileCount;
	}
}

////////////////////////////////////////////////////////////////////////

map<string, sf::Texture*>* ResourceLoader::GetTextureMap()
{
	return textureMap;
}

////////////////////////////////////////////////////////////////////////

map<string, sf::SoundBuffer*>* ResourceLoader::GetSoundMap()
{
	return soundMap;
}

////////////////////////////////////////////////////////////////////////

map<string, sf::Font*>* ResourceLoader::GetFontMap()
{
	return fontMap;
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::CountFiles()
{
	//Open resource file
	fileStream.open(resourcePath() + resourceFilePath.c_str());

	//Check if resource file is open
	if (!fileStream.is_open())
	{
		return;
	}

	//Count files
	while (!fileStream.eof())
	{
		getline(fileStream, line);

		if (!line.empty() && line.at(0) != '#' && line.at(0) != '$')
		{
			fileCount++;
		}
	}

	//Divide file count by 2 because each file uses two lines
	fileCount /= 2;

	//Close resource file
	fileStream.close();
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::LoadTexture()
{
	getline(fileStream, currentFilePath);
	(*textureMap)[line] = new sf::Texture();
	(*textureMap)[line]->loadFromFile(resourcePath() + currentFilePath);
	filesLoaded++;
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::LoadSound()
{
	getline(fileStream, currentFilePath);
	(*soundMap)[line] = new sf::SoundBuffer();
	(*soundMap)[line]->loadFromFile(resourcePath() + currentFilePath);
	filesLoaded++;
}

////////////////////////////////////////////////////////////////////////

void ResourceLoader::LoadFont()
{
	getline(fileStream, currentFilePath);
	(*fontMap)[line] = new sf::Font();
	(*fontMap)[line]->loadFromFile(resourcePath() + currentFilePath);
	filesLoaded++;
}

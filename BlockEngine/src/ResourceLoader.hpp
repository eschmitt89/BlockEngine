#ifndef ResourceLoader_hpp
#define ResourceLoader_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <map>

using namespace std;

class ResourceLoader
{
public:
	ResourceLoader(string resourceFilePath);
	~ResourceLoader();
	void Run();
	void LoadStep();
	float GetPercentDone();
	map<string, sf::Texture*>* GetTextureMap();
	map<string, sf::SoundBuffer*>* GetSoundMap();
	map<string, sf::Font*>* GetFontMap();

private:
	map<string, sf::Texture*>* textureMap;
	map<string, sf::SoundBuffer*>* soundMap;
	map<string, sf::Font*>* fontMap;

	ifstream fileStream;
	string resourceFilePath;
	string currentFilePath;
	string line;

	bool complete;
	int currentFileType;
	int fileCount;
	int filesLoaded;

	void CountFiles();

	void LoadTexture();
	void LoadSound();
	void LoadFont();
};

#endif /* ResourceLoader_hpp */


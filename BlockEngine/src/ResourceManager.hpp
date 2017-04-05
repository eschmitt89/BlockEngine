//
//  ResourceManager.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include "ResourceLoader.hpp"

using namespace std;

class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}
	~ResourceManager();

	void LoadAll(string resourceFilePath);

	const sf::Texture* GetTexture(string texture);
	const sf::SoundBuffer* GetSound(string sound);
	const sf::Font* GetFont(string font);

	vector<string> GetTextureNames(string filter);

private:
	ResourceManager() {}
	ResourceManager(ResourceManager const &);
	void operator = (ResourceManager const &) {}

	map<string, sf::Texture*>* textureMap;
	map<string, sf::SoundBuffer*>* soundMap;
	map<string, sf::Font*>* fontMap;
};


#endif /* ResourceManager_hpp */


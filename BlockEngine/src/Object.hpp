#ifndef Object_hpp
#define Object_hpp

#include <SFML/Graphics.hpp>
#include "ObjectType.hpp"

class Object
{
public:
	Object(const sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	Object(sf::Vector2f position, sf::Vector2f size) : Object(nullptr, position, size) { }
    virtual ~Object();
	virtual ObjectType GetObjectType() { return ObjectType_Object; }

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	sf::Vector2f GetCenter();

	void SetPosition(sf::Vector2f position);
	void SetSize(sf::Vector2f size);
    
protected:
	sf::RectangleShape sprite;
	sf::Vector2f position;
	sf::Vector2f size;
};

#endif /* Object_hpp */

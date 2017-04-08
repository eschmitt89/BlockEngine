#ifndef GridView_hpp
#define GridView_hpp

#include "Clickable.hpp"

using namespace std;

class GridView : public Clickable
{
public:
	GridView(sf::Vector2f position, sf::Vector2f size);
	~GridView();

	void Draw(sf::RenderWindow& window);

protected:
	void LeftPressed();
	void RightPressed();
	void MiddlePressed();

	void LeftClick();
	void RightClick();
	void MiddleClick();

private:
};

#endif /* GridView_hpp */
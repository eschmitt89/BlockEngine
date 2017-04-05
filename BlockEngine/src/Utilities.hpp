//
//  Utilties.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Utilties_hpp
#define Utilties_hpp

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

inline sf::Vector2f GetMousePosition(const sf::RenderWindow& window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

////////////////////////////////////////////////////////////////////////

inline bool Intersect(const sf::Vector2f& position1, const sf::Vector2f& size1, const sf::Vector2f& position2, const sf::Vector2f& size2)
{
	return (position1.x + size1.x > position2.x && position1.x < position2.x + size2.x && position1.y + size1.y > position2.y && position1.y < position2.y + size2.y);
}

////////////////////////////////////////////////////////////////////////

inline bool Intersect(const sf::Vector2i& position1, const sf::Vector2i& size1, const sf::Vector2i& position2, const sf::Vector2i& size2)
{
	return (position1.x + size1.x > position2.x && position1.x < position2.x + size2.x && position1.y + size1.y > position2.y && position1.y < position2.y + size2.y);
}

////////////////////////////////////////////////////////////////////////

float inline VectorLength(const sf::Vector2f vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

////////////////////////////////////////////////////////////////////////

sf::Vector2f inline NormalizeVector(const sf::Vector2f& vector)
{
	float vectorLength = VectorLength(vector);
	if (!vectorLength) return sf::Vector2f();
	return vector / vectorLength;
}

////////////////////////////////////////////////////////////////////////

float inline DotProduct(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

////////////////////////////////////////////////////////////////////////

float inline Distance(sf::Vector2f position1, sf::Vector2f position2)
{
	return sqrt(((position2.x - position1.x)*(position2.x - position1.x)) + ((position2.y - position1.y)*(position2.y - position1.y)));
}

////////////////////////////////////////////////////////////////////////

float inline AbsoluteDistance(sf::Vector2f position1, sf::Vector2f position2)
{
	return abs(Distance(position1, position2));
}

////////////////////////////////////////////////////////////////////////

int inline Random(int min, int max)
{
	if (max < min)
	{
		int tmp = max;
		max = min;
		min = tmp;
	}

	return (rand() % (max - min + 1)) + min;
}

////////////////////////////////////////////////////////////////////////

float inline Random()
{
	return (float)rand() / INT_MAX;
}

////////////////////////////////////////////////////////////////////////

bool inline StringContains(string s, string subString)
{
	return s.find(subString) != string::npos;
}

////////////////////////////////////////////////////////////////////////

template <typename T> void inline VectorEraseElement(vector<T>& vector, T element)
{
	vector.erase(remove(vector.begin(), vector.end(), element), vector.end());
}

////////////////////////////////////////////////////////////////////////

struct Vector4i 
{
	int x1;
	int y1;
	int x2;
	int y2;

	Vector4i(sf::Vector2i vector1, sf::Vector2i vector2)
	{
		x1 = vector1.x;
		y1 = vector1.y;
		x2 = vector2.x;
		y2 = vector2.y;
	}

	bool operator==( const Vector4i &v)
	{
		return ((x1 == v.x1) && (x2 == v.x2) && (y1 == v.y1) && (y2 = v.y2));
	}
};

////////////////////////////////////////////////////////////////////////

template <typename T> struct TypeValue
{
	TypeValue<T>() { }
	TypeValue<T>(const T& type, float value)
	{
		this->type = type;
		this->value = value;
	}
	~TypeValue<T>() { }

	T type;
	float value;
};

////////////////////////////////////////////////////////////////////////

template <typename T> struct TypeTransition
{
	TypeTransition<T>() { 
	}
	TypeTransition<T>(TypeValue<T> start, TypeValue<T> end)
	{
		this->start = start;
		this->end = end;
		this->percent = 0;
	}

	TypeValue<T> start;
	TypeValue<T> end;
	float percent;
};

////////////////////////////////////////////////////////////////////////

template<typename T> inline TypeTransition<T> FindTransitionPoints(vector<TypeValue<T>> keyframes, float percent)
{
	TypeTransition<T> transition;

	for (int i = 0; i < keyframes.size(); i++)
	{
		if (keyframes[i].value >= percent)
		{
			transition.end = keyframes[i];

			if (i > 0)
			{
				transition.start = keyframes[i - 1];
			}

			break;
		}
	}

	transition.percent = (percent - transition.start.value) / (transition.end.value - transition.start.value);

	return transition;
}

////////////////////////////////////////////////////////////////////////

template <typename T> class DropRateCollection
{
public:
	DropRateCollection<T>() { }
	~DropRateCollection<T>() { }

	void AddDropRate(T type, float dropRate)
	{
		if (dropRates.size() > 0)
		{
			dropRates.push_back(TypeValue<T>(type, dropRates[dropRates.size() - 1].value + dropRate));
		}
		else
		{
			dropRates.push_back(TypeValue<T>(type, dropRate));
		}

		if (dropRates[dropRates.size() - 1].value > 1.0)
		{
			throw new exception("Total drop % of collection exceeds 100%.");
		}
	}

	T Roll()
	{
		float roll = Random(1, 1000) / 1000.f;

		for (int i = 0; i < dropRates.size(); i++)
		{
			if (roll <= dropRates[i].value)
			{
				return dropRates[i].type;
			}
		}
	}

private:
	vector<TypeValue<T>> dropRates;
};

////////////////////////////////////////////////////////////////////////

template <typename T> T GetTypeFromString(map<T, string> typeMap, string s)
{
	for (map<T, string>::iterator itor = typeMap.begin(); itor != typeMap.end(); itor++)
	{
		if (StringContains(s, itor->second))
		{
			return itor->first;
		}
	}
}

#endif /* Utilties_hpp */

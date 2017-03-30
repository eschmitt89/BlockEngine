//
//  Keyframe.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef Keyframe_hpp
#define Keyframe_hpp
 
template <typename T>

struct Keyframe 
{
	Keyframe<T>(float key, const T& value)
	{
		this->key = key;
		this->value = value;
	}
    ~Keyframe<T>() { }

	float key;
	T value;
};

#endif /* Keyframe_hpp */

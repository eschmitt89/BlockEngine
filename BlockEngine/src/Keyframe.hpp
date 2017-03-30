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
	Keyframe(float key, const T& value);
    ~Keyframe();

	float key;
	T value;
};

#endif /* Keyframe_hpp */

//
//  PlayerState.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef PlayerState_hpp
#define PlayerState_hpp

enum PlayerState
{
	Idle,
	TryGrabLadder,
	OnLadder,
	TryGrabLedge,
	OnLedge,
	TryDropThroughPlatform,
};

#endif /* PlayerState_hpp */

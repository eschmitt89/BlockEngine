//
//  MovementState.hpp
//  BlockEngine
//
//  Created by Eric Schmitt on 3/2/17.
//  Copyright © 2017 Eric Schmitt. All rights reserved.
//

#ifndef MovementState_hpp
#define MovementState_hpp

enum MovementState
{
	MovementStateNone,
	TryGrabLadder,
	OnLadder,
	TryGrabLedge,
	OnLedge,
	TryDrop,
	Dropped,
	InLiquid,
};

#endif /* MovementState_hpp */

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
	MovementState_None,
	MovementState_TryGrabLadder,
	MovementState_OnLadder,
	MovementState_TryGrabLedge,
	MovementState_OnLedge,
	MovementState_TryDrop,
	MovementState_Dropped,
	MovementState_InLiquid,
};

#endif /* MovementState_hpp */

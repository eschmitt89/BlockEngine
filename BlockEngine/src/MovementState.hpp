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

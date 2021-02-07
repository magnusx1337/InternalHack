
#pragma once

#include "Hacks.h"

class clegit : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd* pCmd, bool& bSendPacket);
private:
	// Targetting
	int GetTargetCrosshair();
	bool TargetMeetsRequirements(IClientEntity* pEntity);
	float FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int HitBox);
	bool AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd* pCmd, bool& bSendPacket);

	void SyncWeaponSettings();

	// Functionality
	void DoAimbot(CUserCmd* pCmd, bool& bSendPacket);
	void DoTrigger(CUserCmd* pCmd);

	// Aimbot
	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;

	float Speed;
	float FoV;
	bool RecoilControl;

};
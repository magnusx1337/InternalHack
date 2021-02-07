#include "legit.h"
#include "RenderManager.h"

void clegit::Init()
{
	IsLocked = false;
	TargetID = -1;
}

void clegit::Draw()
{

}

void clegit::Move(CUserCmd* pCmd, bool& bSendPacket)
{

	// Master switch
	if (!options::menu.LegitBotTab.Active.GetState())
		return;

	// Aimbot
	if (options::menu.LegitBotTab.AimbotEnable.GetState())
		DoAimbot(pCmd, bSendPacket);

	// Triggerbot
	if (options::menu.LegitBotTab.TriggerEnable.GetState() && (!options::menu.LegitBotTab.TriggerKeyPress.GetState() || GUI.GetKeyState(options::menu.LegitBotTab.TriggerKeyBind.GetKey())))
		DoTrigger(pCmd);
}

void clegit::SyncWeaponSettings()
{
	IClientEntity* pLocal = hackManager.pLocal();
	C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (GameUtils::IsPistol(pWeapon))
	{
		Speed = options::menu.LegitBotTab.WeaponPistSpeed.GetValue();
		FoV = options::menu.LegitBotTab.WeaponPistFoV.GetValue();
		RecoilControl = options::menu.LegitBotTab.WeaponPistRecoil.GetState();

		switch (options::menu.LegitBotTab.WeaponPistHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)csgo_hitboxes::head);
			break;
		case 1:
			HitBox = ((int)csgo_hitboxes::neck);
			break;
		case 2:
			HitBox = ((int)csgo_hitboxes::pelvis);
			break;
		case 3:
			HitBox = ((int)csgo_hitboxes::stomach);
			break;
		}
	}
	else if (GameUtils::IsSniper(pWeapon))
	{
		Speed = options::menu.LegitBotTab.WeaponSnipSpeed.GetValue();
		FoV = options::menu.LegitBotTab.WeaponSnipFoV.GetValue();
		RecoilControl = options::menu.LegitBotTab.WeaponSnipRecoil.GetState();

		switch (options::menu.LegitBotTab.WeaponSnipHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)csgo_hitboxes::head);
			break;
		case 1:
			HitBox = ((int)csgo_hitboxes::neck);
			break;
		case 2:
			HitBox = ((int)csgo_hitboxes::pelvis);
			break;
		case 3:
			HitBox = ((int)csgo_hitboxes::stomach);
			break;
		}
	}
	else
	{
		Speed = options::menu.LegitBotTab.WeaponMainSpeed.GetValue();
		FoV = options::menu.LegitBotTab.WeaponMainFoV.GetValue();
		RecoilControl = options::menu.LegitBotTab.WeaponMainRecoil.GetState();

		switch (options::menu.LegitBotTab.WeaponMainHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)csgo_hitboxes::head);
			break;
		case 1:
			HitBox = ((int)csgo_hitboxes::neck);
			break;
		case 2:
			HitBox = ((int)csgo_hitboxes::pelvis);
			break;
		case 3:
			HitBox = ((int)csgo_hitboxes::stomach);
			break;
		}
	}
}

// Functionality
void clegit::DoAimbot(CUserCmd * pCmd, bool& bSendPacket)
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* pLocal = hackManager.pLocal();
	bool FindNewTarget = true;
	//IsLocked = false;

	// Don't aimbot with the knife..
	C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			//TargetID = 0;
			//pTarget = nullptr;
			//HitBox = -1;
			return;
		}
		SyncWeaponSettings();

	}
	else
		return;

	// Make sure we have a good target
	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = interfaces::ent_list->get_client_entity(TargetID);
		if (pTarget && TargetMeetsRequirements(pTarget))
		{
			SyncWeaponSettings();
			if (HitBox >= 0)
			{
				Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
				Vector View; interfaces::engine->get_viewangles(View);
				View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;
				float nFoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (nFoV < FoV)
					FindNewTarget = false;
			}
		}
	}

	// Find a new target, apparently we need to
	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		TargetID = GetTargetCrosshair();

		// Memes
		if (TargetID >= 0)
		{
			pTarget = interfaces::ent_list->get_client_entity(TargetID);
		}
		else
		{
			pTarget = nullptr;
			HitBox = -1;
		}
	}

	SyncWeaponSettings();

	// If we finally have a good target
	if (TargetID >= 0 && pTarget)
	{
		//HitBox = (int)CSGOHitboxID::Head;//
		SyncWeaponSettings();

		// Key
		if (options::menu.LegitBotTab.AimbotKeyPress.GetState())
		{
			int Key = options::menu.LegitBotTab.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		Vector AimPoint = GetHitboxPosition(pTarget, HitBox);

		if (AimAtPoint(pLocal, AimPoint, pCmd, bSendPacket))
		{
			//IsLocked = true;
			if (options::menu.LegitBotTab.AimbotAutoFire.GetState() && !(pCmd->buttons & IN_ATTACK))
			{
				pCmd->buttons |= IN_ATTACK;
			}
		}
	}

	// Auto Pistol
	static bool WasFiring = false;
	CSWeaponInfo* WeaponInfo = pWeapon->GetCSWpnData();
	if (!WeaponInfo->full_auto && options::menu.LegitBotTab.AimbotAutoPistol.GetState())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}

		WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
	}
}

bool TargetMeetsTriggerRequirements(IClientEntity * pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass* pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && interfaces::engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			// Team Check
			if (pEntity->team() != hackManager.pLocal()->team() || options::menu.LegitBotTab.AimbotFriendlyFire.GetState())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity())
				{
					return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}

void clegit::DoTrigger(CUserCmd * pCmd)
{
	IClientEntity* pLocal = hackManager.pLocal();

	IClientEntity* pLocal4 = hackManager.pLocal();
	C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(pLocal4->GetActiveWeaponHandle());

	IClientEntity* LocalPlayer = hackManager.pLocal();

	//===============================================================================
	auto LocalPlayerWeapon = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(LocalPlayer->GetWeaponHandle());
	auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

	if (LocalPlayerWeapon) {
		if (LocalPlayerWeapon->GetAmmoInClip() == 0)
			return;

		auto ClientClass = WeaponEntity->GetClientClass2();
		if (ClientClass->m_ClassID == (int)CSGOClassID::CKnife ||
			ClientClass->m_ClassID == (int)CSGOClassID::CHEGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CDecoyGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CIncendiaryGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CSmokeGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CC4) {
			return;
		}
	}
	else
		return;
	//===============================================================================

	Vector ViewAngles = pCmd->viewangles;
	if (options::menu.LegitBotTab.TriggerRecoil.GetState())
		ViewAngles += LocalPlayer->GetAimPunch() * 2.0f;

	Vector CrosshairForward;
	AngleVectors(ViewAngles, &CrosshairForward);
	//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
	CrosshairForward *= 8000.f;


	Vector TraceSource = LocalPlayer->GetEyePosition();
	Vector TraceDestination = TraceSource + CrosshairForward;

	Ray_t Ray;
	trace_t Trace;
	CTraceFilter Filter;

	Filter.pSkip = LocalPlayer;

	Ray.Init(TraceSource, TraceDestination);
	interfaces::trace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	if (!Trace.m_pEnt)
		return;
	if (!Trace.m_pEnt->IsAlive())
		return;
	if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
		return;
	if (Trace.m_pEnt->IsImmune())
		return;

	if ((options::menu.LegitBotTab.TriggerHead.GetState() && Trace.hitgroup == ((int)csgo_hitboxes::head)) ||
		(options::menu.LegitBotTab.TriggerChest.GetState() && Trace.hitgroup == ((int)csgo_hitboxes::stomach)) ||
		(options::menu.LegitBotTab.TriggerStomach.GetState() && Trace.hitgroup == ((int)csgo_hitboxes::pelvis)) ||
		(options::menu.LegitBotTab.TriggerArms.GetState() && (Trace.hitgroup == ((int)csgo_hitboxes::left_upper_arm)) || Trace.hitgroup == ((int)csgo_hitboxes::right_upper_arm)) ||
		(options::menu.LegitBotTab.TriggerLegs.GetState() && (Trace.hitgroup == ((int)csgo_hitboxes::left_foot) || Trace.hitgroup == ((int)csgo_hitboxes::right_foot)))) {
		pCmd->buttons |= IN_ATTACK;
	}

	///Original code:
	//IClientEntity* pLocal = hackManager.pLocal();

	//CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	//if (pWeapon)
	//{
	//	if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
	//	{
	//		return;
	//	}
	//}
	//else
	//	return;

	//Vector ViewAngles = pCmd->viewangles;
	//if (Menu::Window.LegitBotTab.TriggerRecoil.GetState())
	//	ViewAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	//Vector src, dst, forward;
	//trace_t tr;
	//Ray_t ray;
	//CTraceFilter filter;

	//AngleVectors(ViewAngles, &forward);
	//forward *= 8192;

	//filter.pSkip = pLocal;
	//src = pLocal->GetOrigin() + pLocal->GetViewOffset();
	//dst = src + forward;

	//ray.Init(src, dst);

	//Interfaces::Trace->TraceRay(ray, 0x46004003, &filter, &tr);

	//if (!tr.m_pEnt)
	//	return;

	//int hitgroup = tr.hitgroup;
	//bool didHit = false;

	//if (Menu::Window.LegitBotTab.TriggerHead.GetState() && hitgroup == HITGROUP_HEAD)
	//	didHit = true;
	//if (Menu::Window.LegitBotTab.TriggerChest.GetState() && hitgroup == HITGROUP_CHEST)
	//	didHit = true;
	//if (Menu::Window.LegitBotTab.TriggerStomach.GetState() && hitgroup == HITGROUP_STOMACH)
	//	didHit = true;
	//if (Menu::Window.LegitBotTab.TriggerArms.GetState() && (hitgroup == HITGROUP_LEFTARM || hitgroup == HITGROUP_RIGHTARM))
	//	didHit = true;
	//if (Menu::Window.LegitBotTab.TriggerLegs.GetState() && (hitgroup == HITGROUP_LEFTLEG || hitgroup == HITGROUP_RIGHTLEG))
	//	didHit = true;

	//float hitchance = 75.f + (Menu::Window.LegitBotTab.TriggerHitChanceAmmount.GetValue() / 4);
	//if (didHit && (!Menu::Window.LegitBotTab.TriggerHitChance.GetState() || (1.0f - pWeapon->GetAccuracyPenalty()) * 100.f >= hitchance))
	//{
	//	if (TargetMeetsTriggerRequirements(tr.m_pEnt))
	//	{
	//		if (Menu::Window.LegitBotTab.TriggerDelay.GetValue() > 1)
	//		{
	//			if (CustomDelay >= Menu::Window.LegitBotTab.TriggerDelay.GetValue() / 30)
	//			{
	//				CustomDelay = 0;
	//				shoot = true;
	//				if (*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 64)
	//					pCmd->buttons |= IN_ATTACK;
	//				else
	//					pCmd->buttons |= IN_ATTACK2;
	//			}
	//			else
	//			{
	//				CustomDelay++;
	//				return;
	//			}
	//		}
	//		else
	//		{
	//			CustomDelay = 0;
	//			shoot = true;
	//			if (*pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 64)
	//				pCmd->buttons |= IN_ATTACK;
	//			else
	//				pCmd->buttons |= IN_ATTACK2;
	//		}
	//	}
	//}
	//else
	//{
	//	if (Menu::Window.LegitBotTab.TriggerBreak.GetValue() > 1)
	//	{
	//		if (CustomBreak <= Menu::Window.LegitBotTab.TriggerBreak.GetValue())
	//			CustomBreak = 0;
	//		shoot = false;
	//	}
	//}
	if (GameUtils::IsPistol(pWeapon) && options::menu.LegitBotTab.AimbotAutoPistol.GetState())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
	}
}

bool clegit::TargetMeetsRequirements(IClientEntity * pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass* pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && interfaces::engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			// Team Check
			if (pEntity->team() != hackManager.pLocal()->team() || options::menu.LegitBotTab.AimbotFriendlyFire.GetState())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity() && GameUtils::IsVisible(hackManager.pLocal(), pEntity, HitBox))
				{
					return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}

float clegit::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity * pEntity, int aHitBox)
{
	// Anything past 180 degrees is just going to wrap around
	CONST FLOAT MaxDegrees = 180.0f;

	// Get local angles
	Vector Angles = View;

	// Get local view / eye position
	Vector Origin = ViewOffSet;

	// Create and intiialize vectors for calculations below
	Vector Delta(0, 0, 0);
	//Vector Origin(0, 0, 0);
	Vector Forward(0, 0, 0);

	// Convert angles to normalized directional forward vector
	AngleVectors(Angles, &Forward);
	Vector AimPos = GetHitboxPosition(pEntity, aHitBox);
	// Get delta vector between our local eye position and passed vector
	VectorSubtract(AimPos, Origin, Delta);
	//Delta = AimPos - Origin;

	// Normalize our delta vector
	Normalize(Delta, Delta);

	// Get dot product between delta position and directional forward vectors
	FLOAT DotProduct = Forward.Dot(Delta);

	// Time to calculate the field of view
	return (acos(DotProduct) * (MaxDegrees / PI));
}

int clegit::GetTargetCrosshair()
{
	// Target selection
	SyncWeaponSettings();
	int target = -1;
	float minFoV = FoV;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; interfaces::engine->get_viewangles(View);
	View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < interfaces::ent_list->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pEntity = interfaces::ent_list->get_client_entity(i);
		if (TargetMeetsRequirements(pEntity))
		{
			int NewHitBox = HitBox;
			if (NewHitBox >= 0)
			{
				float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
				if (fov < minFoV)
				{
					minFoV = fov;
					target = i;
				}
			}
		}
	}

	return target;
}

bool ShouldFire()
{
	IClientEntity* pLocalEntity = (IClientEntity*)interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	if (!pLocalEntity)
		return false;

	C_BaseCombatWeapon* entwep = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(pLocalEntity->GetActiveWeaponHandle());

	float flServerTime = (float)pLocalEntity->GetTickBase() * interfaces::globals->interval_per_tick;
	float flNextPrimaryAttack = entwep->GetNextPrimaryAttack();

	//std::cout << flServerTime << " " << flNextPrimaryAttack << std::endl;

	return !(flNextPrimaryAttack > flServerTime);
}
bool clegit::AimAtPoint(IClientEntity * pLocal, Vector point, CUserCmd * pCmd, bool &bSendPacket)
{
	// Get the full angles
	if (point.Length() == 0) return false;

	Vector angles;
	Vector src = pLocal->GetOrigin() + pLocal->GetViewOffset();

	CalcAngle(src, point, angles);
	GameUtils::NormaliseViewAngle(angles);

	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return false;
	}

	if (RecoilControl)
	{
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			angles -= AimPunch * 2;
			GameUtils::NormaliseViewAngle(angles);
		}
	}

	IsLocked = true;
	//-----------------------------------------------

	Vector shit = angles - pCmd->viewangles;
	bool v = false;

	if (shit.Length() > Speed)
	{
		Normalize(shit, shit);
		shit *= Speed;
	}
	else
	{
		v = true;
	}

	/*if (options::menu.LegitBotTab.TriggerSmokeCheck.GetState())
	{
		Vector ang = angles - pCmd->viewangles;
		Vector Oldview = pCmd->viewangles;
		Vector qAimAngles = pCmd->viewangles;
		float Oldsidemove = pCmd->sidemove;
		float Oldforwardmove = pCmd->forwardmove;

		static int ChokedPackets = -1;

		if (ShouldFire() && ChokedPackets < 6)
		{
			bSendPacket = false;
			pCmd->viewangles += ang;
			pCmd->viewangles = angles;
			ChokedPackets++;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles = Oldview;
			pCmd->sidemove = Oldsidemove;
			pCmd->forwardmove = Oldforwardmove;
			ChokedPackets = -1;
		}

		pCmd->viewangles.z = 0;
	}
	else
	{*/
		pCmd->viewangles += shit;
		interfaces::engine->SetViewAngles(pCmd->viewangles);
	//}

	return v;
}

#include "MiscHacks.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "IClientMode.h"
#include "XorStr.hpp"
#include <chrono>
#include <algorithm>
#include <time.h>
#include "Hooks.h"
#include "position_adjust.h"
#include "RageBot.h"
#include "Autowall.h"
CMiscHacks* c_misc = new CMiscHacks;
template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}
inline float bitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}
inline float FloatNegate(float f)
{
	return bitsToFloat(FloatBits(f) ^ 0x80000000);
}
Vector AutoStrafeView;
void CMiscHacks::Init()
{
	namespam();
}
void CMiscHacks::Draw()
{
	if (!interfaces::engine->IsConnected() || !interfaces::engine->IsInGame())
		return;

}

void set_name(const char* name)
{
	ConVar* nameConvar = interfaces::cvar->FindVar(("name"));
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;
	nameConvar->SetValueChar(name);
}
void set_clan_tag2(const char* tag, const char* clan_name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(Utilities::Memory::FindPatternV2(XorStr("engine.dll"), XorStr("53 56 57 8B DA 8B F9 FF 15")));
	pSetClanTag(tag, clan_name);
}
void CMiscHacks::namespam()
{

	switch (options::menu.ColorsTab.NameChanger.GetIndex())
	{
	case 0:
	{
		switch (int(interfaces::globals->curtime * 2.7) % 23)
		{
		case 0: set_clan_tag2(XorStr(""), ""); break;
		}
	}
	break;
	case 1:
	{
		switch (int(interfaces::globals->curtime * 2.7) % 23)
		{
		case 0: set_clan_tag2(XorStr("G"), "GamSens.ooo"); break;
		case 1: set_clan_tag2(XorStr("Ga"), "GamSens.ooo"); break;
		case 2: set_clan_tag2(XorStr("Gam"), "GamSens.ooo"); break;
		case 3: set_clan_tag2(XorStr("GamS"), "GamSens.ooo"); break;
		case 4: set_clan_tag2(XorStr("GamSe"), "GamSens.ooo"); break;
		case 5: set_clan_tag2(XorStr("GamSen"), "GamSens.ooo"); break;
		case 6: set_clan_tag2(XorStr("GamSens"), "GamSens.ooo"); break;
		case 7: set_clan_tag2(XorStr("GamSens."), "GamSens.ooo"); break;
		case 8: set_clan_tag2(XorStr("GamSens.o"), "GamSens.ooo"); break;
		case 9: set_clan_tag2(XorStr("GamSens.oo"), "GamSens.ooo"); break;
		case 10: set_clan_tag2(XorStr("GamSens.ooo"), "GamSens.ooo"); break;
		case 11: set_clan_tag2(XorStr("GamSens.ooo "), "GamSens.ooo"); break;
			//case 24:game::functions.set_clan_tag( XorStr( "                 " ), "gamesense" ); break;
		}
	}
	break;
	}

	

	
}

void smart_iq()
{
	switch (int(interfaces::globals->curtime * 2.4) % 23)
	{
	case 0: set_clan_tag2(XorStr(""), ""); break;
	}
}
template<class T>
static T* FindHudElement(const char* name)
{
	static auto pThis = *reinterpret_cast<DWORD * *>(Utilities::Memory::FindPatternV2("client_panorama.dll", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 8D 58") + 1);

	static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(Utilities::Memory::FindPatternV2("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39"));
	return (T*)find_hud_element(pThis, name);
}
void CMiscHacks::buybot_primary()
{
	/*bool is_ct = hackManager.pLocal()->team() == TEAM_CS_CT;
	switch (options::menu.ColorsTab.buybot_primary.GetIndex())
	{
	case 1: is_ct ? (interfaces::engine->ExecuteClientCmd("buy scar20;")) : (interfaces::engine->ExecuteClientCmd("buy g3sg1;"));
		break;
	case 2: interfaces::engine->ExecuteClientCmd("buy ssg08;");
		break;
	case 3: interfaces::engine->ExecuteClientCmd("buy awp;");
		break;
	case 4: is_ct ? (interfaces::engine->ExecuteClientCmd("buy m4a1; buy m4a1_silencer")) : (interfaces::engine->ExecuteClientCmd("buy ak47;"));
		break;
	case 5: is_ct ? (interfaces::engine->ExecuteClientCmd("buy aug;")) : (interfaces::engine->ExecuteClientCmd("buy sg556"));
		break;
	case 6: is_ct ? (interfaces::engine->ExecuteClientCmd("buy mp9")) : (interfaces::engine->ExecuteClientCmd("buy mac-10;"));
		break;
	}*/

}

void CMiscHacks::buybot_secondary()
{
	/*switch (options::menu.ColorsTab.buybot_secondary.GetIndex())
	{
	case 1: interfaces::engine->ExecuteClientCmd("buy elite;");
		break;
	case 2: interfaces::engine->ExecuteClientCmd("buy deagle;");
		break;
	case 3: interfaces::engine->ExecuteClientCmd("buy fn57");
		break;
	}*/

}

void CMiscHacks::buybot_otr()
{
	/*std::vector<dropdownboxitem> otr_list = options::menu.ColorsTab.buybot_otr.items;

	if (otr_list[0].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy vest; buy vesthelm;");
	}

	if (otr_list[1].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy hegrenade;");
	}

	if (otr_list[2].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy flashbang;");
	}

	if (otr_list[3].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy smokegrenade;");
	}

	if (otr_list[4].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy molotov;");
	}

	if (otr_list[5].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy taser;");
	}

	if (otr_list[6].GetSelected)
	{
		interfaces::engine->ExecuteClientCmd("buy defuser;");
	}*/

}
inline float FastSqrt(float x)
{
	unsigned int i = *(unsigned int*)&x;
	i += 127 << 23;
	i >>= 1;
	return *(float*)&i;
}
#define square( x ) ( x * x )

void angleVectors(const Vector& angles, Vector& forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void CMiscHacks::LegitBhop(CUserCmd* pCmd)
{

	auto g_LocalPlayer = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	auto userCMD = pCmd;

	float hitchance = options::menu.ColorsTab.Legitbhophitchance.GetValue();
	float restrictlimit = 12;
	float hoplimit = options::menu.ColorsTab.Legitbhopmaxhit.GetValue();
	float minhop = options::menu.ColorsTab.Legitbhopminhit.GetValue();


	static int hops_restricted = 0;
	static int hops_hit = 0;
	if (g_LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
		return;

	if (userCMD->buttons & IN_JUMP && !(g_LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		userCMD->buttons &= ~IN_JUMP;
		hops_restricted = 0;
	}

	else if ((rand() % 100 > hitchance && hops_restricted < restrictlimit) || (hoplimit > 0 && hops_hit > hoplimit && minhop > 0 && hops_hit > minhop))
	{
		userCMD->buttons &= ~IN_JUMP;
		hops_restricted++;
		hops_hit = 0;
	}
	else
	{
		hops_hit++;
	}




}

void CMiscHacks::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity *pLocal = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	IGameEvent* Event;
	if (!hackManager.pLocal()->IsAlive() || oof)
	{
		_done = false;
		return;
	}
	if (pLocal->GetMoveType() == MOVETYPE_LADDER)
		return;

	// ------- Oi thundercunt, this is needed for the weapon configs ------- //

	C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)interfaces::ent_list->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (pWeapon != nullptr)
	{
		if (GetAsyncKeyState(options::menu.aimbot_tab.minimal_walk.GetKey()))
		{
		MinimalWalk(pCmd, get_gun(pWeapon));
		}

		if (GameUtils::AutoSniper(pWeapon))
		{

			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());

		}

		if (GameUtils::IsPistol(pWeapon))
		{

			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());

		}

		if (pWeapon->is_scout())
		{

			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());

		}

		if (pWeapon->is_awp())
		{

			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());

		}

		if (GameUtils::IsRifle(pWeapon) || GameUtils::IsShotgun(pWeapon) || GameUtils::IsMachinegun(pWeapon))
		{

			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());

		}

		if (GameUtils::IsMP(pWeapon))
		{
			options::menu.aimbot_tab.AccuracyHitchance.SetValue((float)options::menu.aimbot_tab.hc_auto.GetValue());
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue((float)options::menu.aimbot_tab.md_auto.GetValue());
		}

		if (GameUtils::IsZeus(pWeapon))
		{
			options::menu.aimbot_tab.AccuracyHitchance.SetValue(20);
			options::menu.aimbot_tab.AccuracyMinimumDamage.SetValue(20);
		} 
	}

	if (options::menu.aimbot_tab.infinite_duck.GetState())
	{
		pCmd->buttons |= IN_BULLRUSH;
	}

	if (options::menu.ColorsTab.override_viewmodel.GetState())
		viewmodel_x_y_z();

	if (options::menu.ColorsTab.Legitbhop.GetState())
		LegitBhop(pCmd);

	//	if (Options::Menu.RageBotTab.AimbotEnable.GetState())
	//		AutoPistol(pCmd);

//	RankReveal(pCmd);

	if (options::menu.ColorsTab.OtherAutoJump.GetState())
		AutoJump(pCmd);
	if (options::menu.MiscTab.airduck_type.GetIndex() != 0)
	{
		airduck(pCmd);
	}
	interfaces::engine->get_viewangles(AutoStrafeView);
	if (options::menu.ColorsTab.OtherAutoStrafe.GetState() && (pLocal->GetMoveType() != MOVETYPE_LADDER))
	{
		strafer(pCmd);
	}

	if (GetAsyncKeyState(options::menu.aimbot_tab.fw.GetKey()) && !options::menu.m_bIsOpen)
	{
		FakeWalk0(pCmd, bSendPacket);
	}

	if (options::menu.visuals2_tab.aspectratio.GetState())
		aspectratio();
		namespam();

	fake_crouch(pCmd, bSendPacket, pLocal);

	if (options::menu.visuals2_tab.DisablePostProcess.GetState())
		PostProcces();

	if (!_done && hackManager.pLocal()->IsAlive())
	{
		if (options::menu.ColorsTab.buybot_primary.GetIndex() != 0)
			buybot_primary();

		if (options::menu.ColorsTab.buybot_secondary.GetIndex() != 0)
			buybot_secondary();

		buybot_otr();

		_done = true;
	}

//	if (options::menu.ColorsTab.NameChanger.GetState())
	//{
		//namespam();
	//}
}

void CMiscHacks::aspectratio()
{

	float ratio = (options::menu.visuals2_tab.aspectratiovalue.GetValue() * 0.1) / 2;
	if (ratio > 0.001)
		interfaces::cvar->FindVar("r_aspectratio")->SetValue(ratio);
	else
		interfaces::cvar->FindVar("r_aspectratio")->SetValue((35 * 0.1f) / 2);
}

int CMiscHacks::GetFPS()
{
	static int fps = 0;
	static int count = 0;
	using namespace std::chrono;
	auto now = high_resolution_clock::now();
	static auto last = high_resolution_clock::now();
	count++;
	if (duration_cast<milliseconds>(now - last).count() > 1000)
	{
		fps = count;
		count = 0;
		last = now;
	}
	return fps;
}
float curtime_fixedx(CUserCmd* ucmd) {
	auto local_player = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	static int g_tick = 0;
	static CUserCmd* g_pLastCmd = nullptr;
	if (!g_pLastCmd || g_pLastCmd->hasbeenpredicted) {
		g_tick = local_player->GetTickBase();
	}
	else {
		++g_tick;
	}
	g_pLastCmd = ucmd;
	float curtime = g_tick * interfaces::globals->interval_per_tick;
	return curtime;
}

void VectorAnglesXXX(Vector forward, Vector &angles)
{
	float tmp, yaw, pitch;

	if (forward[2] == 0 && forward[0] == 0)
	{
		yaw = 0;

		if (forward[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / PI);

		if (yaw < 0)
			yaw += 360;
		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / PI);

		if (pitch < 0)
			pitch += 360;
	}

	if (pitch > 180)
		pitch -= 360;
	else if (pitch < -180)
		pitch += 360;

	if (yaw > 180)
		yaw -= 360;
	else if (yaw < -180)
		yaw += 360;

	if (pitch > 89)
		pitch = 89;
	else if (pitch < -89)
		pitch = -89;

	if (yaw > 180)
		yaw = 180;
	else if (yaw < -180)
		yaw = -180;

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
Vector CalcAngleFakewalk(Vector src, Vector dst)
{
	Vector ret;
	VectorAnglesXXX(dst - src, ret);
	return ret;
}

void rotate_movement(float yaw, CUserCmd* cmd)
{
	Vector viewangles;
	QAngle yamom;
	interfaces::engine->get_viewangles(viewangles);
	float rotation = DEG2RAD(viewangles.y - yaw);
	float cos_rot = cos(rotation);
	float sin_rot = sin(rotation);
	float new_forwardmove = (cos_rot * cmd->forwardmove) - (sin_rot * cmd->sidemove);
	float new_sidemove = (sin_rot * cmd->forwardmove) + (cos_rot * cmd->sidemove);
	cmd->forwardmove = new_forwardmove;
	cmd->sidemove = new_sidemove;
}

float fakewalk_curtime(CUserCmd* ucmd)
{
	auto local_player = hackManager.pLocal();

	if (!local_player)
		return 0;

	int g_tick = 0;
	CUserCmd* g_pLastCmd = nullptr;
	if (!g_pLastCmd || g_pLastCmd->hasbeenpredicted)
	{
		g_tick = (float)local_player->GetTickBase();
	}
	else {
		++g_tick;
	}
	g_pLastCmd = ucmd;
	float curtime = g_tick * interfaces::globals->interval_per_tick;
	return curtime;
}
void CMiscHacks::FakeWalk0(CUserCmd* pCmd, bool &bSendPacket)
{
	IClientEntity* pLocal = hackManager.pLocal();

	globalsh.fakewalk = true;
	static int iChoked = -1;
	iChoked++;
	if (pCmd->forwardmove > 0)
	{
		pCmd->buttons |= IN_BACK;
		pCmd->buttons &= ~IN_FORWARD;
	}
	if (pCmd->forwardmove < 0)
	{
		pCmd->buttons |= IN_FORWARD;
		pCmd->buttons &= ~IN_BACK;
	}
	if (pCmd->sidemove < 0)
	{
		pCmd->buttons |= IN_MOVERIGHT;
		pCmd->buttons &= ~IN_MOVELEFT;
	}
	if (pCmd->sidemove > 0)
	{
		pCmd->buttons |= IN_MOVELEFT;
		pCmd->buttons &= ~IN_MOVERIGHT;
	}
	static int choked = 0;
	choked = choked > 14 ? 0 : choked + 1;

	float nani = options::menu.aimbot_tab.FakeWalkSpeed.GetValue() / 14;

	pCmd->forwardmove = choked < nani || choked > 14 ? 0 : pCmd->forwardmove;
	pCmd->sidemove = choked < nani || choked > 14 ? 0 : pCmd->sidemove; //100:6 are about 16,6, quick maths
	bSendPacket = choked < 1;
}

static __declspec(naked) void __cdecl Invoke_NET_SetConVar(void* pfn, const char* cvar, const char* value)
{
	__asm
	{
		push    ebp
		mov     ebp, esp
		and     esp, 0FFFFFFF8h
		sub     esp, 44h
		push    ebx
		push    esi
		push    edi
		mov     edi, cvar
		mov     esi, value
		jmp     pfn
	}
}

void CMiscHacks::AutoPistol(CUserCmd* pCmd)
{

}
void CMiscHacks::AutoJump(CUserCmd *pCmd)
{
	auto g_LocalPlayer = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	auto userCMD = pCmd;
	if (options::menu.ColorsTab.autojump_type.GetIndex() < 1)
	{
		if (g_LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
		if (userCMD->buttons & IN_JUMP && !(g_LocalPlayer->GetFlags() & FL_ONGROUND))
		{
			userCMD->buttons &= ~IN_JUMP;
		}
	}
	if (options::menu.ColorsTab.autojump_type.GetIndex() > 0)
	{
		if (g_LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || g_LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;
		userCMD->buttons |= IN_JUMP;
	}
}
void CMiscHacks::airduck(CUserCmd *pCmd) // quack
{
	auto local = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());

	if (options::menu.MiscTab.airduck_type.GetIndex() == 1)
	{
		if (!(local->GetFlags() & FL_ONGROUND))
		{
			pCmd->buttons |= IN_DUCK;
		}
	}
	if (options::menu.MiscTab.airduck_type.GetIndex() == 2)
	{
		if (!(local->GetFlags() & FL_ONGROUND))
		{
			static bool counter = false;
			static int counters = 0;
			if (counters == 9)
			{
				counters = 0;
				counter = !counter;
			}
			counters++;
			if (counter)
			{
				pCmd->buttons |= IN_DUCK;
			}
			else
				pCmd->buttons &= ~IN_DUCK;
		}
	}
}
template<class T, class U>
inline T clampangle(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

#define nn(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
bool bHasGroundSurface(IClientEntity* pLocalBaseEntity, const Vector& vPosition)
{
	trace_t pTrace;
	Vector vMins, vMaxs; pLocalBaseEntity->GetRenderBounds(vMins, vMaxs);

	UTIL_TraceLine(vPosition, { vPosition.x, vPosition.y, vPosition.z - 32.f }, MASK_PLAYERSOLID_BRUSHONLY, pLocalBaseEntity, 0, &pTrace);

	return pTrace.fraction != 1.f;
}

void CMiscHacks::strafe_2(CUserCmd * cmd)
{
	auto local = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());

	if (local->GetMoveType() == MOVETYPE_NOCLIP || local->GetMoveType() == MOVETYPE_LADDER  || !local || !local->IsAlive())
		return;

	if (interfaces::m_iInputSys->IsButtonDown(ButtonCode_t::KEY_A) || interfaces::m_iInputSys->IsButtonDown(ButtonCode_t::KEY_D) || interfaces::m_iInputSys->IsButtonDown(ButtonCode_t::KEY_S) || interfaces::m_iInputSys->IsButtonDown(ButtonCode_t::KEY_W) || interfaces::m_iInputSys->IsButtonDown(ButtonCode_t::KEY_LSHIFT))
		return;

	if (!(local->GetFlags() & FL_ONGROUND)) {
		if (cmd->mousedx > 1 || cmd->mousedx < -1) {
			cmd->sidemove = clamp(cmd->mousedx < 0.f ? -450.0f : 450.0f, -450.0f, 450.0f);
		}
		else {
			cmd->forwardmove = 10000.f / local->GetVelocity().Length();
			cmd->sidemove = (cmd->command_number % 2) == 0 ? -450.0f : 450.0f;
			if (cmd->forwardmove > 450.0f)
				cmd->forwardmove = 450.0f;
		}
	}
}

Vector GetAutostrafeView()
{
	return AutoStrafeView;
}

void CMiscHacks::PostProcces()
{
	ConVar* Meme = interfaces::cvar->FindVar("mat_postprocess_enable");
	SpoofedConvar* meme_spoofed = new SpoofedConvar(Meme);
	meme_spoofed->SetString("mat_postprocess_enable 0");
}

void CMiscHacks::MinimalWalk(CUserCmd* cmd, float speed)
{
	if (speed <= 0.f)
		return;

	float fSpeed = (float)(FastSqrt(square(cmd->forwardmove) + square(cmd->sidemove) + square(cmd->upmove)));

	if (fSpeed <= 0.f)
		return;

	if (cmd->buttons & IN_DUCK)
		speed *= 2.94117647f;

	if (fSpeed <= speed)
		return;

	float fRatio = speed / fSpeed;

	cmd->forwardmove *= fRatio;
	cmd->sidemove *= fRatio;
	cmd->upmove *= fRatio;
}
void CMiscHacks::fake_crouch(CUserCmd * cmd, bool &packet, IClientEntity * local)  // appears pasted
{
	static bool counter = false;

	bool once = false;
	if (GetAsyncKeyState(options::menu.aimbot_tab.fake_crouch_key.GetKey()))
	{
		if (options::menu.aimbot_tab.fake_crouch.GetState())
		{
			unsigned int chokegoal = 7;
			auto choke = *(int*)(uintptr_t(interfaces::client_state) + 0x4D28);
			bool mexican_tryhard = choke >= chokegoal;

			if (local->GetFlags() & FL_ONGROUND)
			{
				if (mexican_tryhard || interfaces::client_state->m_flNextCmdTime <= 0.1f)
					cmd->buttons |= IN_DUCK;
				else
					cmd->buttons &= ~IN_DUCK;
			}
		}
	}
}
float CMiscHacks::get_gun(C_BaseCombatWeapon* weapon)
{

	if (!weapon)
		return 0.f;

	if (weapon->isAuto())
		return 40.f;

	else if (weapon->is_scout())
		return 70.f;

	else if (weapon->is_awp())
		return 30.f;

	else
		return 34.f;
}

void CMiscHacks::strafer(CUserCmd* cmd) {

	if (hackManager.pLocal()->GetMoveType() == moveTypes::MOVETYPE_NOCLIP || hackManager.pLocal()->GetMoveType() == moveTypes::MOVETYPE_LADDER)
		return;

	if (!GetAsyncKeyState(VK_SPACE) || hackManager.pLocal()->GetVelocity().Length2D() < 0.5)
		return;

	if (!(hackManager.pLocal()->GetFlags() & FL_ONGROUND))
	{
		static float cl_sidespeed = interfaces::cvar->FindVar("cl_sidespeed")->GetFloat();
		if (fabsf(cmd->mousedx > 2)) {
			cmd->sidemove = (cmd->mousedx < 0.f) ? -cl_sidespeed : cl_sidespeed;
			return;
		}

		if (GetAsyncKeyState('S')) {
			cmd->viewangles.y -= 180;
		}
		else if (GetAsyncKeyState('D')) {
			cmd->viewangles.y += 90;
		}
		else if (GetAsyncKeyState('A')) {
			cmd->viewangles.y -= 90;
		}

		if (!hackManager.pLocal()->GetVelocity().Length2D() > 0.5 || hackManager.pLocal()->GetVelocity().Length2D() == NAN || hackManager.pLocal()->GetVelocity().Length2D() == INFINITE)
		{
			cmd->forwardmove = 400;
			return;
		}

		cmd->forwardmove = clamp(5850.f / hackManager.pLocal()->GetVelocity().Length2D(), -400, 400);
		if ((cmd->forwardmove < -400 || cmd->forwardmove > 400))
			cmd->forwardmove = 0;

		const auto vel = hackManager.pLocal()->GetVelocity();
		const float y_vel = RAD2DEG(atan2(vel.y, vel.x));
		const float diff_ang = normalize_yaw(cmd->viewangles.y - y_vel);

		cmd->sidemove = (diff_ang > 0.0) ? -cl_sidespeed : cl_sidespeed;
		cmd->viewangles.y = normalize_yaw(cmd->viewangles.y - diff_ang);

	}
}

void CMiscHacks::viewmodel_x_y_z()
{
	static int vx, vy, vz, b1g;
	static ConVar* view_x = interfaces::cvar->FindVar("viewmodel_offset_x");
	static ConVar* view_y = interfaces::cvar->FindVar("viewmodel_offset_y");
	static ConVar* view_z = interfaces::cvar->FindVar("viewmodel_offset_z");

	static ConVar* bob = interfaces::cvar->FindVar("cl_bobcycle"); // sv_competitive_minspec 0

	ConVar* sv_cheats = interfaces::cvar->FindVar("sv_cheats");
	SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
	sv_cheats_spoofed->SetInt(1);

	ConVar* sv_minspec = interfaces::cvar->FindVar("sv_competitive_minspec");
	SpoofedConvar* sv_minspec_spoofed = new SpoofedConvar(sv_minspec);
	sv_minspec_spoofed->SetInt(0);


	view_x->nFlags &= ~FCVAR_CHEAT;
	view_y->nFlags &= ~FCVAR_CHEAT;
	view_z->nFlags &= ~FCVAR_CHEAT;
	bob->nFlags &= ~FCVAR_CHEAT;

	vx = options::menu.ColorsTab.offset_x.GetValue();
	vy = options::menu.ColorsTab.offset_y.GetValue();
	vz = options::menu.ColorsTab.offset_z.GetValue();
	b1g = 0.98f;

	view_x->SetValue(vx);

	view_y->SetValue(vy);

	view_z->SetValue(vz);

	if (!paste)
	{
		interfaces::engine->ExecuteClientCmd("cl_bobcycle 0.98"); //  // rate 196608
		interfaces::engine->ExecuteClientCmd("rate 196608");
		paste = true;
	}
}

void CMiscHacks::optimize()
{
	static bool done = false;

	ConVar* sv_cheats = interfaces::cvar->FindVar("sv_cheats");
	SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
	sv_cheats_spoofed->SetInt(1);

	if (!interfaces::engine->IsConnected() || !interfaces::engine->IsInGame())
	{
		done = false;
	}

	if (!done)
	{
		interfaces::engine->ExecuteClientCmd("mat_postprocess_enable 0");
		interfaces::engine->ExecuteClientCmd("mat_disable_bloom 1");
		done = true;
	}


	//	Interfaces::Engine->ExecuteClientCmd("r_drawtranslucentrenderables 0");
}

typedef void(*RevealAllFn)(int);
RevealAllFn fnReveal;
void CMiscHacks::RankReveal(CUserCmd * cmd)
{
	if (!options::menu.ColorsTab.CompRank.GetState())
		return;

	using ServerRankRevealAll = char(__cdecl*)(int*); static uintptr_t RankRevealFnc = Utilities::Memory::FindPatternV2("client_panorama.dll", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 ? A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 ? 85 C0 74 ? 8B C8 E8 ? ? ? ? 8B C8 EB ? 33 C9 89 0D ? ? ? ? 8B 45 ? FF 70 ? E8 ? ? ? ? B0 ? 5D"); printf("RankReveal: 0x%X\n", RankRevealFnc); // Print client_panorama.dll+0x38CF60 int v[3] = { 0, 0, 0 }; reinterpret_cast< ServerRankRevealAll >(RankRevealFnc)(v);
}
void FakeStand(CUserCmd *cmd, bool & packet)
{
	if (!cmd)
	{
		return;
	}

	if (GetAsyncKeyState(options::menu.MiscTab.fake_stand_key.GetKey()))
	{
		if (cmd->buttons & IN_SPEED)
		{
			auto local = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());

			unsigned int chokegoal = 7;
			auto choke = *(int*)(uintptr_t(interfaces::client_state) + 0x4D28);
			bool mexican_tryhard = choke >= chokegoal;

			if (local->GetFlags() & FL_ONGROUND)
			{
				if (mexican_tryhard)
				{
					packet = true;
					cmd->buttons &= ~IN_DUCK;
				}
				else
				{
					cmd->buttons |= IN_DUCK;
					packet = false;
				}
			}
		}
	}
}
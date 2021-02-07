#pragma once
#include "Hacks.h"
class anti_aim
{
public:

	void DoPitch(CUserCmd* pCmd);

	void Base_AntiAim(CUserCmd* pCmd, IClientEntity* pLocal, bool& bSendPacket);
	void jitter_side(CUserCmd* pCmd);
	void DoAntiAim(CUserCmd* pCmd, bool& bSendPacket);
	//---- pitches ----//

	void pitchdown(CUserCmd* pcmd);

	void pitchup(CUserCmd* pcmd);

	void zero(CUserCmd* pcmd);

	void pitchjitter(CUserCmd* pcmd);

	void pitchrandom(CUserCmd* pcmd);

	void fakedown(CUserCmd* pcmd);

	void fakeup(CUserCmd* pcmd);

	//---- yaws ----//

	void backwards(CUserCmd* pcmd, bool moving);

	void lowerbody(CUserCmd* pcmd, bool moving);

	void rand_lowerbody(CUserCmd* pcmd, bool moving);

	void jitter_180(CUserCmd* pcmd, bool moving);

	void manual(CUserCmd* pCmd, bool moving);

	void freestanding_jitter(CUserCmd* pCmd, bool moving);

	void crooked(CUserCmd* pcmd, bool moving);

	void do_desync(CUserCmd* cmd, bool moving, bool packet);


	//---- desync ----//
	float get_feet_yaw();

	void desync_simple(CUserCmd* cmd, bool moving);

	void desync_default(CUserCmd* cmd, bool moving);

	void desync_stretch(CUserCmd* cmd, bool moving);

	void desync_crooked(CUserCmd* cmd, bool moving);

	void desync_switch(CUserCmd* cmd, bool moving);

	void desync_auto(CUserCmd* cmd, bool moving);

	void desync_jitter(CUserCmd* cmd, bool moving);

	void desync_static(CUserCmd* cmd, bool moving);

	void desync_relative(CUserCmd* cmd, bool moving);

	void desync_shuffle(CUserCmd* cmd, bool moving);
	bool DisableAA = false;
	void desync_jitter_aimware(CUserCmd* cmd, bool moving, bool packet);
	void disable(IGameEvent* Event);
	float get_max_desync_delta(IClientEntity* player, CBaseAnimState* anim_state);

	float at_target();

	void auto_direction(CUserCmd* cmd, bool moving);


private:
	bool stand_done = false;
	bool move_done = false;

	//	bool swap_sides_stand = Options::Menu.MiscTab.desync_swapsides_stand.GetState();
	//	bool swap_sides_move = Options::Menu.MiscTab.desync_swapsides_move.GetState();

	float stand_range = options::menu.aimbot_tab.desync_range_stand.GetValue();
	float move_range = options::menu.aimbot_tab.desync_range_move.GetValue();

	float standjit = options::menu.aimbot_tab.stand_jitter.GetValue();
	float movejit = options::menu.aimbot_tab.move_jitter.GetValue();
};

class antiaim_helper
{
public:

	void anti_lby(CUserCmd* cmd, bool& bSendPacket);

	float fov_ent(Vector ViewOffSet, Vector View, IClientEntity* entity, int hitbox);

	int closest();

private:

	float next_lby_update = 0.f;
	int closest_entity = -1;
	float NextPredictedLBYUpdate = 0.f;

};

extern anti_aim* c_antiaim;
extern antiaim_helper* c_helper;
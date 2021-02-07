#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" 
#include "Interfaces.h"
#include "CRC32.h"
#include <fstream>
#include "Playerlist.h"
#include "XorStr.hpp"
#define WINDOW_WIDTH 747 - 130
#define WINDOW_HEIGHT 820 + 100 // 507
mirror_window options::menu;
struct Config_t {
	int id;
	std::string name;
};
std::vector<Config_t> configs;
double PlistArray[102][200];
typedef void(__cdecl* MsgFn)(const char* msg, va_list);


void fcrash2()
{
	Sleep(1000000000000);
}
void MsgX(const char* msg, ...)
{
	if (msg == nullptr)
		return; //If no string was passed, or it was null then don't do anything
	static MsgFn fn = (MsgFn)GetProcAddress(GetModuleHandle("tier0.dll"), "Msg"); 	char buffer[989];
	va_list list;
	va_start(list, msg);
	vsprintf(buffer, msg, list);
	va_end(list);
	fn(buffer, list); //Calls the function, we got the address above.
}

void updatestuff()
{
	static bool boost_fps = false;
	static bool abc = false;
	static bool freakware = false;
	if (!freakware)
	{
		ConVar* staticdrop = interfaces::cvar->FindVar("r_DrawSpecificStaticProp");
		SpoofedConvar* staticdrop_spoofed = new SpoofedConvar(staticdrop);
		staticdrop_spoofed->SetInt(0);
		ConVar* NightSkybox1 = interfaces::cvar->FindVar("sv_skyname");
		*(float*)((DWORD)& NightSkybox1->fnChangeCallback + 0xC) = NULL;
		for (MaterialHandle_t i = interfaces::materialsystem->FirstMaterial(); i != interfaces::materialsystem->InvalidMaterial(); i = interfaces::materialsystem->NextMaterial(i))
		{
			IMaterial* pMaterial = interfaces::materialsystem->GetMaterial(i);

			if (!pMaterial)
				continue;
			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			interfaces::engine->ExecuteClientCmd("mat_queue_mode 2"); // rate 196608

			float sky_r = options::menu.visuals2_tab.sky_r.GetValue() / 100;
			float sky_g = options::menu.visuals2_tab.sky_g.GetValue() / 100;
			float sky_b = options::menu.visuals2_tab.sky_b.GetValue() / 100;

			float test = 100;
			float amountr = options::menu.visuals2_tab.colmod.GetValue() / 100;

			if (options::menu.visuals2_tab.customskies.GetIndex() == 1)
			{
				NightSkybox1->SetValue("sky_csgo_night02b");
			}
			if (options::menu.visuals2_tab.customskies.GetIndex() == 2)
			{
				NightSkybox1->SetValue("sky_l4d_rural02_ldr");
			}
			if (options::menu.visuals2_tab.customskies.GetIndex() == 3)
			{
				NightSkybox1->SetValue("sky_csgo_cloudy01");
			}
			if (options::menu.visuals2_tab.customskies.GetIndex() == 4)
			{
				NightSkybox1->SetValue("sky_csgo_nukeblank2");
			}

			if (options::menu.visuals_tab.ModulateSkyBox.GetState())
			{
				if (strstr(pMaterial->GetTextureGroupName(), ("SkyBox")))
				{
					pMaterial->ColorModulate(sky_r, sky_g, sky_b);
					//	Interfaces::CVar->ConsoleColorPrintf(Color(160, 5, 240, 255), "\n twitch.tv/attysu for giving me some will to keep up with the project \n");
				}
			}
			if (options::menu.visuals2_tab.WorldColor.GetState())
			{

				if (!strcmp(pMaterial->GetTextureGroupName(), "World textures") && options::menu.ColorsTab.asus_type.GetIndex() < 1)  // walls	
				{
					pMaterial->ColorModulate(sky_r, sky_g, sky_b);
				}
				if (!strcmp(pMaterial->GetTextureGroupName(), "World textures") && options::menu.ColorsTab.asus_type.GetIndex() > 0)  // walls	
				{
					//pMaterial->AlphaModulate(test);
					pMaterial->ColorModulate(sky_r, sky_g, sky_b);
				}
				if (!strcmp(pMaterial->GetTextureGroupName(), "StaticProp textures"))
				{
					//pMaterial->AlphaModulate(test);
					pMaterial->ColorModulate(sky_r, sky_g, sky_b);
				}
			}
			else
			{
				if (!strcmp(pMaterial->GetTextureGroupName(), "World textures") && options::menu.ColorsTab.asus_type.GetIndex() < 1)  // walls	
				{
					pMaterial->ColorModulate(amountr, amountr, amountr);
				}
				if (!strcmp(pMaterial->GetTextureGroupName(), "World textures") && options::menu.ColorsTab.asus_type.GetIndex() > 0)  // walls	
				{
					//pMaterial->AlphaModulate(test);
					pMaterial->ColorModulate(amountr, amountr, amountr);
				}
				if (!strcmp(pMaterial->GetTextureGroupName(), "StaticProp textures"))
				{
					//pMaterial->AlphaModulate(test);
					pMaterial->ColorModulate(amountr, amountr, amountr);
				}
			}

		}
	}
	//freakware = true;


}


void save_callback()
{
	static ConVar* Meme = interfaces::cvar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	interfaces::engine->ClientCmd_Unrestricted("cl_fullupdate");
	int should_save = options::menu.SkinTab.ConfigListBox.GetIndex();
	std::string config_directory = "C:\\gamsens\\";
	config_directory += configs[should_save].name; config_directory += ".xml";
	GUI.SaveWindowState(&options::menu, XorStr(config_directory.c_str()));
	interfaces::cvar->ConsoleColorPrintf(Color(255, 10, 10, 255), "[gamsens] ");
	std::string uremam = "saved configuration.     \n";
	MsgX(uremam.c_str());
	updatestuff();
}
void load_callback()
{
	static ConVar* Meme = interfaces::cvar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	interfaces::engine->ClientCmd_Unrestricted("cl_fullupdate");
	int should_load = options::menu.SkinTab.ConfigListBox.GetIndex();
	std::string config_directory = "C:\\gamsens\\";
	config_directory += configs[should_load].name; config_directory += ".xml";
	GUI.LoadWindowState(&options::menu, XorStr(config_directory.c_str()));
	interfaces::cvar->ConsoleColorPrintf(Color(255, 10, 10, 255), "[gamsens] ");
	std::string uremam = "loaded configuration.     \n";
	MsgX(uremam.c_str());
	updatestuff();
}

void list_configs() {
	configs.clear();
	options::menu.SkinTab.ConfigListBox.ClearItems();
	std::ifstream file_in;
	file_in.open("C:\\gamsens\\configs_list.txt");
	if (file_in.fail()) {
		std::ofstream("C:\\gamsens\\configs_list.txt");
		file_in.open("C:\\gamsens\\configs_list.txt");
	}
	int line_count;
	while (!file_in.eof()) {
		Config_t config;
		file_in >> config.name;
		config.id = line_count;
		configs.push_back(config);
		line_count++;
		options::menu.SkinTab.ConfigListBox.AddItem(config.name);
	}
	file_in.close();
	if (configs.size() > 7) options::menu.SkinTab.ConfigListBox.AddItem(" ");
}

void add_config() {
	std::fstream file;
	file.open("C:\\gamsens\\configs_list.txt", std::fstream::app);
	if (file.fail()) {
		std::fstream("C:\\gamsens\\configs_list.txt");
		file.open("C:\\gamsens\\configs_list.txt", std::fstream::app);
	}
	file << std::endl << options::menu.SkinTab.NewConfigName.getText();
	file.close();
	list_configs();
	int should_add = options::menu.SkinTab.ConfigListBox.GetIndex();
	std::string config_directory = "C:\\gamsens\\";
	config_directory += options::menu.SkinTab.NewConfigName.getText(); config_directory += ".xml";
	GUI.SaveWindowState(&options::menu, XorStr(config_directory.c_str()));
	options::menu.SkinTab.NewConfigName.SetText("");
	updatestuff();
}

void remove_config() {
	int should_remove = options::menu.SkinTab.ConfigListBox.GetIndex();
	std::string config_directory = "C:\\gamsens\\";
	config_directory += configs[should_remove].name; config_directory += ".xml";
	std::remove(config_directory.c_str());
	std::ofstream ofs("C:\\gamsens\\configs_list.txt", std::ios::out | std::ios::trunc);
	ofs.close();
	std::fstream file;
	file.open("C:\\gamsens\\configs_list.txt", std::fstream::app);
	if (file.fail()) {
		std::fstream("C:\\gamsens\\configs_list.txt");
		file.open("C:\\gamsens\\configs_list.txt", std::fstream::app);
	}
	for (int i = 0; i < configs.size(); i++) {
		if (i == should_remove) continue;
		Config_t config = configs[i];
		file << std::endl << config.name;
	}
	file.close();
	list_configs();
	updatestuff();
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = interfaces::cvar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	interfaces::engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void UnLoadCallbk()
{
	DoUnload = true;
}
void mirror_window::Setup()
{
	SetPosition(311 - 160, 6);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("GamSens");
	RegisterTab(&aimbot_tab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&visuals_tab);
	RegisterTab(&visuals2_tab);
	RegisterTab(&ColorsTab);
	RegisterTab(&SkinTab);
	//RegisterTab(&PlayersTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;
	aimbot_tab.Setup();
	LegitBotTab.Setup();
	visuals_tab.Setup();
	visuals2_tab.Setup();
	ColorsTab.Setup();
	SkinTab.Setup();
	//PlayersTab.Setup();

#pragma endregion
}

void CAimbotTab::Setup()
{
	SetTitle("Rage");
	// 21 48
	AimbotGroup.SetPosition(-68 + 165 - 21, 83 - 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(215, 210);
	RegisterControl(&AimbotGroup);
	 
	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl(1, "Enable Aimbot", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotAutoFire.SetState(true);
	AimbotGroup.PlaceLabledControl(1, "Automatic Fire", this, &AimbotAutoFire);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotSilentAim.SetState(true);
	AimbotGroup.PlaceLabledControl(1, "Silent Aim", this, &AimbotSilentAim);


	AccuracyAutoScope.SetFileId("aim_scope");
	AccuracyAutoScope.SetState(true);
	//AimbotGroup.PlaceLabledControl(1, "auto scope", this, &AccuracyAutoScope);

	AccuracyHitchance.SetFileId("aim_hc");
	AccuracyHitchance.SetBoundaries(0.f, 100.f);
	AccuracyHitchance.SetValue(20);

	AccuracyMinimumDamage.SetFileId("aim_md");
	AccuracyMinimumDamage.SetBoundaries(0.f, 100.f);
	AccuracyMinimumDamage.SetValue(20);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.extension = XorStr("�");
	AimbotFov.SetValue(180.f);

	lag_pred.SetFileId("aim_lag_pred");
	AimbotGroup.PlaceLabledControl(1, "Lag Prediction", this, &lag_pred);

	extrapolation.SetFileId("aim_acc_extra_P_lation");
	AimbotGroup.PlaceLabledControl(1, "Extrapolation", this, &extrapolation);

	target_auto.SetFileId("tgt_hitbox_auto");
	target_auto.AddItem(XorStr("Head"));
	target_auto.AddItem(XorStr("Head, Chest"));
	target_auto.AddItem(XorStr("Head, Chest, Legs"));
	target_auto.AddItem(XorStr("Head, Chest, Legs, Arms"));
	target_auto.AddItem(XorStr("All Hitboxes"));
	AimbotGroup.PlaceLabledControl(1, "Hitboxes", this, &target_auto);


	hc_auto.SetFileId("auto_hitchance");
	hc_auto.SetBoundaries(0, 100);
	hc_auto.SetValue(25);
	hc_auto.extension = XorStr("%%");
	AimbotGroup.PlaceLabledControl(1, "Hit Chance", this, &hc_auto);

	md_auto.SetFileId("auto_minimumdamage");
	md_auto.SetBoundaries(0, 100);
	md_auto.SetValue(25);
	md_auto.extension = XorStr("%%");
	AimbotGroup.PlaceLabledControl(1, "Minimum Damage", this, &md_auto);

	QuickStop.SetFileId("acc_quickstop1");
	AimbotGroup.PlaceLabledControl(3, "Automatic Stop", this, &QuickStop);

	//ResolverEnable.SetFileId("aim_multipoint_enable");
	//AimbotGroup.PlaceLabledControl(1, "anti-aim correction", this, &ResolverEnable);

	//resolver.SetFileId("acc_aaa");
	//resolver.AddItem("off");
	//resolver.AddItem("stickrpghook");
	//resolver.AddItem("test xd");
	//resolver.AddItem("experimental");
	//AimbotGroup.PlaceLabledControl(1, "", this, &resolver);

	///////////////////////////////////////////////////////////
	multipoint.SetText("Multipoint");
	multipoint.SetPosition(-68 + 165 - 21, 283 - 30);
	multipoint.SetSize(215, 210);
	RegisterControl(&multipoint);

	TargetPointscale.SetFileId("aim_hitbox_Scale");
	TargetPointscale.SetBoundaries(0, 100);
	TargetPointscale.SetValue(50);
	TargetPointscale.extension = ("%%");
	multipoint.PlaceLabledControl(1, "Hitbox Scale", this, &TargetPointscale);

	Multienable.SetFileId("aim_multipoint_enable");
	multipoint.PlaceLabledControl(1, "Enable Multipoint", this, &Multienable);

	Multival2.SetFileId("hitbox_scale_head");
	Multival2.SetBoundaries(0.1, 100);
	Multival2.SetValue(20);
	Multival2.extension = XorStr("%%");
	multipoint.PlaceLabledControl(1, "Head Scale", this, &Multival2);

	Multival.SetFileId("hitbox_scale_body");
	Multival.SetBoundaries(0.1, 100);
	Multival.SetValue(20);
	Multival.extension = XorStr("%%");
	multipoint.PlaceLabledControl(1, "Body Scale", this, &Multival);

	MultiVal3.SetFileId("hitbox_scale_legs");
	MultiVal3.SetBoundaries(0.1, 100);
	MultiVal3.SetValue(20);
	MultiVal3.extension = XorStr("%%");
	multipoint.PlaceLabledControl(1, "Leg Scale", this, &MultiVal3);
	delay_shot.SetFileId("aim_delay_shot");
	delay_shot.AddItem("None");
	delay_shot.AddItem("Sim-Time");
	delay_shot.AddItem("Lag Sompensation");
	delay_shot.AddItem("Refine Shot");
	multipoint.PlaceLabledControl(1, "Delay Shot", this, &delay_shot);

/*	baim_fake.SetFileId("bodyaim_fake");
	multipoint.PlaceLabledControl(4, "baim if fake", this, &baim_fake); // if we have to resort to a brute

	baim_fakewalk.SetFileId("bodyaim_fakewalk");
	multipoint.PlaceLabledControl(4, "baim if slow walk", this, &baim_fakewalk);

	baim_inair.SetFileId("bodyaim_inair");
	multipoint.PlaceLabledControl(4, "baim if air", this, &baim_inair); //if they be flyin like a plane

	BaimIfUnderXHealth.SetFileId("acc_BaimIfUnderXHealth");
	BaimIfUnderXHealth.SetBoundaries(0, 100);
	BaimIfUnderXHealth.extension = XorStr("HP");
	BaimIfUnderXHealth.SetValue(0);
	multipoint.PlaceLabledControl(4, "baim if hp lower than", this, &BaimIfUnderXHealth);

	bigbaim.SetFileId("acc_bigbaim");
	multipoint.PlaceLabledControl(4, "force body aim", this, &bigbaim);*/


	aagroup.SetText("Misc");
	//aagroup.AddTab(CGroupTab("main", 1));
//	aagroup.AddTab(CGroupTab("misc", 2));
	//aagroup.AddTab(CGroupTab("misc", 3));
	//aagroup.AddTab(CGroupTab("desync", 4));
	aagroup.SetPosition(278 + 165 + 24 - 171, 83 - 48);
	aagroup.SetSize(215, 210);
	RegisterControl(&aagroup);


	/*AntiAimEnable.SetFileId("aa_enable");
	aagroup.PlaceLabledControl(1, "enable antiaim", this, &AntiAimEnable);

	disable_on_dormant.SetFileId("disable_on_dormant");
	aagroup.PlaceLabledControl(1, "at targets", this, &disable_on_dormant);
	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("off");
	AntiAimPitch.AddItem("down");
	AntiAimPitch.AddItem("up");
	AntiAimPitch.AddItem("jitter");
	AntiAimPitch.AddItem("random");
	//AntiAimPitch.AddItem("zero");
	aagroup.PlaceLabledControl(1, "pitch", this, &AntiAimPitch);

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("off");
	AntiAimYaw.AddItem("180");
	AntiAimYaw.AddItem("manual");
	AntiAimYaw.AddItem("crooked");
	AntiAimYaw.AddItem("freestanding");
	AntiAimYaw.AddItem("jitter 180");
	AntiAimYaw.AddItem("random lowerbody");
	//	AntiAimYaw.AddItem("Twist");
	aagroup.PlaceLabledControl(1, "standing yaw", this, &AntiAimYaw);

	stand_jitter.SetFileId("c_addjitter_stand");
	stand_jitter.SetBoundaries(0.f, 90.f);
	stand_jitter.SetValue(0.f);
	aagroup.PlaceLabledControl(1, "add jitter", this, &stand_jitter);

	AntiAimYawrun.SetFileId("aa_y2");
	AntiAimYawrun.AddItem("off");
	AntiAimYawrun.AddItem("180");
	AntiAimYawrun.AddItem("manual");
	AntiAimYawrun.AddItem("crooked");
	AntiAimYawrun.AddItem("freestanding");
	AntiAimYawrun.AddItem("180 jitter");
	AntiAimYawrun.AddItem("random lowerbody");
	aagroup.PlaceLabledControl(1, "moving yaw", this, &AntiAimYawrun);

	move_jitter.SetFileId("c_addjitter_move");
	move_jitter.SetBoundaries(0.f, 90.f);
	move_jitter.SetValue(0.f);
	aagroup.PlaceLabledControl(1, "add jitter", this, &move_jitter);

	AntiAimYaw3.SetFileId("aa_y3");
	AntiAimYaw3.AddItem("off");
	AntiAimYaw3.AddItem("180");
	AntiAimYaw3.AddItem("manual");
	AntiAimYaw3.AddItem("crooked");
	AntiAimYaw3.AddItem("freestanding");
	AntiAimYaw3.AddItem("180 jitter");
	AntiAimYaw3.AddItem("random lowerbody");
	aagroup.PlaceLabledControl(1, "jumping yaw", this, &AntiAimYaw3);

	desync_aa_stand.SetFileId("v_desync_aa_stand");
	aagroup.PlaceLabledControl(1, "standing desync", this, &desync_aa_stand);

	desync_aa_move.SetFileId("v_desync_aa_move");
	aagroup.PlaceLabledControl(1, "moving desync", this, &desync_aa_move);*/

	//	air_desync.SetFileId("v_air_desync");
	//	aagroup.PlaceLabledControl(1, "Air Desync", this, &air_desync);

	//	pitch_up.SetFileId("pitch_up");
	//	aagroup.PlaceLabledControl(1, "Pitch Flick", this, &pitch_up);


	//minimal_walk.SetFileId("minimal_walk");
	//aagroup.PlaceLabledControl(2, "slow motion", this, &minimal_walk);

	//	antilby.SetFileId("otr_meh");
		//	antilby.AddItem("Off");
		//	antilby.AddItem("One Flick");
		//	antilby.AddItem("Two Flicks");
		//	antilby.AddItem("Relative");
	//	aagroup.PlaceLabledControl(1, "Anti-LBY", this, &antilby);

		//	BreakLBYDelta2.SetFileId("b_antilby2");
		//	BreakLBYDelta2.SetBoundaries(-180, 180);
		//	BreakLBYDelta2.SetValue(90);
		//	aagroup.PlaceLabledControl(2, "Anti-LBY First Flick", this, &BreakLBYDelta2);

	//	BreakLBYDelta.SetFileId("b_antilby");
	//	BreakLBYDelta.SetBoundaries(-180, 180);
	//	BreakLBYDelta.SetValue(-90);
	//	aagroup.PlaceLabledControl(1, "Anti-LBY Range", this, &BreakLBYDelta);

		//	freerange.SetFileId("freestanding_range");
		//	freerange.SetBoundaries(0, 90);
		//	freerange.SetValue(35);
		//	aagroup.PlaceLabledControl(1, "Freestanding Value", this, &freerange);

		//preset_aa.SetFileId("preset_aa");
		//aagroup.PlaceLabledControl(1, "Pre-set AntiAim", this, &preset_aa);

		//choked_shot.SetFileId("choke_shot");
		//aagroup.PlaceLabledControl(1, "Choke Shot", this, &choked_shot);
		//-<------------------------------------->-//
	/*FakelagEnab.SetFileId("fakelag_breaklc");
	aagroup.PlaceLabledControl(2, "enable fakelag", this, &FakelagEnab);

	FakelagStand.SetFileId("fakelag_stand_val");
	FakelagStand.SetBoundaries(1, 14);
	FakelagStand.SetValue(1);
	aagroup.PlaceLabledControl(2, "fakelag standing", this, &FakelagStand);

	FakelagMove.SetFileId("fakelag_move_val");
	FakelagMove.SetBoundaries(1, 14);
	FakelagMove.SetValue(1);
	aagroup.PlaceLabledControl(2, "fakelag moving", this, &FakelagMove);

	Fakelagjump.SetFileId("fakelag_jump_val");
	Fakelagjump.SetBoundaries(1, 14);
	Fakelagjump.SetValue(1);
	aagroup.PlaceLabledControl(2, "fakelag jumping", this, &Fakelagjump);*/

/*	fl_spike.SetFileId("fakelag_spike");
	fl_spike.AddItem("default");
	fl_spike.AddItem("enemy sight");
	fl_spike.AddItem("mirror adaptive");
	fl_spike.AddItem("aimware adaptive");
	fl_spike.AddItem("velocity based");
	aagroup.PlaceLabledControl(2, "fakelag type", this, &fl_spike);

	fakelag_key.SetFileId("fakelag_onkey");
	aagroup.PlaceLabledControl(2, "fakelag on key", this, &fakelag_key);*/

	//FakelagBreakLC.SetFileId("fakelag_breaklc");
	//aagroup.PlaceLabledControl(2, "break lag comp", this, &FakelagBreakLC);



	//	auto_fakelag.SetFileId("fakelag_auto");
	//	aagroup.PlaceLabledControl(2, "Dynamic Fakelag", this, &auto_fakelag);

	//randlbyr.SetFileId("b_randlbyr");
	//randlbyr.SetBoundaries(20, 180);
	//randlbyr.SetValue(60);
	//aagroup.PlaceLabledControl(3, "Random Lowerbody Ammount", this, &randlbyr);


	infinite_duck.SetFileId("infinteduck");
	aagroup.PlaceLabledControl(1, "Infinite Duck", this, &infinite_duck);

	fake_crouch.SetFileId("fake_crouch");
	aagroup.PlaceLabledControl(1, "Fake Duck", this, &fake_crouch);

	fake_crouch_key.SetFileId("fake_crouch_key");
	aagroup.PlaceLabledControl(1, "Fake Duck Key", this, &fake_crouch_key);

	//desync_type_stand.SetFileId("desync_type_stand");
	//desync_type_stand.AddItem("Simple");
	//desync_type_stand.AddItem("Balance");
	//desync_type_stand.AddItem("Static");
	//desync_type_stand.AddItem("Relative");
	//desync_type_stand.AddItem("Shuffle");
	//aagroup.PlaceLabledControl(4, "Standing Type", this, &desync_type_stand);

	//	desync_range_stand.SetFileId("desync_range_standing");
	//	desync_range_stand.SetBoundaries(0, 58);
	//	desync_range_stand.SetValue(40);
	//	aagroup.PlaceLabledControl(4, "Standing Range", this, &desync_range_stand);

		//	desync_swapsides_stand.SetFileId("desync_swapsides_stand");
		//	aagroup.PlaceLabledControl(4, "Swap Sides", this, &desync_swapsides_stand);

	//desync_type_move.SetFileId("desync_type_moving");
	//desync_type_move.AddItem("simple");
	//desync_type_move.AddItem("balance");
	//desync_type_move.AddItem("static");
	//desync_type_move.AddItem("relative");
	//desync_type_move.AddItem("shuffle");
	//aagroup.PlaceLabledControl(4, "Moving Type", this, &desync_type_move);

	//	desync_range_move.SetFileId("desync_range_move");
	//	desync_range_move.SetBoundaries(0, 58);
	//	desync_range_move.SetValue(40);
	//	aagroup.PlaceLabledControl(4, "Moving Range", this, &desync_range_move);

//	desync_twist_onshot.SetFileId("desync_twist_onshot");
	//aagroup.PlaceLabledControl(4, "Twist Feet Yaw When Shooting", this, &desync_twist_onshot);

	//fake_crouch.SetFileId("fake_crouch");
	//aagroup.PlaceLabledControl(3, "fake crouch", this, &fake_crouch);

	//fake_crouch_key.SetFileId("fake_crouch_key");
	//aagroup.PlaceLabledControl(3, "fake crouch key", this, &fake_crouch_key);

}
void CLegitBotTab::Setup()
{

	SetTitle("Legit");
	AimbotGroup.SetPosition(-68 + 165 - 21, 83 - 48);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(230, 210);
	RegisterControl(&AimbotGroup);

	Active.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl(1, "Enable", this, &Active);
	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl(1, "Enable Aimbot", this, &AimbotEnable);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl(1, "Aimbot On Key", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl(1, "", this, &AimbotKeyBind);


	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl(1, "Auto Fire", this, &AimbotAutoFire);

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl(1, "Friendly Fire", this, &AimbotFriendlyFire);
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl(1, "Auto Pistol", this, &AimbotAutoPistol);
	legitbacktrack.SetFileId("legit_bt");
	AimbotGroup.PlaceLabledControl(1, "Backtracking", this, &legitbacktrack);

	legitbacktrackticks.SetFileId("legitbacktrackticks");
	legitbacktrackticks.SetBoundaries(0.0f, 12.0f);
	legitbacktrackticks.SetValue(12.0f);
	AimbotGroup.PlaceLabledControl(2, "Tickrate", this, &legitbacktrackticks);

#pragma endregion Aimbot shit

#pragma region Triggerbot
	//	AccGroup.SetPosition(278, 30);
//AccGroup.SetSize(230, 410);
	TriggerGroup.SetPosition(-68 + 165 - 21, 283 - 30);
	TriggerGroup.SetSize(230, 210);
	TriggerGroup.SetText("Triggerbot");
	RegisterControl(&TriggerGroup);

	TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl(1,"Enable", this, &TriggerEnable);

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl(1,"On Key Press", this, &TriggerKeyPress);

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl(1,"Key Bind", this, &TriggerKeyBind);

	TriggerDelay.SetFileId("trig_time");
	TriggerDelay.SetBoundaries(1.f, 1000.f);
	TriggerDelay.SetValue(1.f);
	TriggerGroup.PlaceLabledControl(1,"Delay (ms)", this, &TriggerDelay);

	TriggerRecoil.SetFileId("trig_recoil");
	TriggerGroup.PlaceLabledControl(1,"Recoil", this, &TriggerRecoil);


//	WeaponPistGroup.SetPosition(190 + 20 + 17, 195 + 65);
	//WeaponPistGroup.SetText("Pistols");
	////	WeaponPistGroup.AddTab(CGroupTab("pistols", 1));
	//WeaponPistGroup.SetSize(200, 210);
	//RegisterControl(&WeaponPistGroup);

/*	ActiveLabel3.SetText("pistols");
	TriggerGroup.PlaceLabledControl(2, "pistols", this, &ActiveLabel3);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 3.f);
	WeaponPistSpeed.SetValue(0.3f);
	TriggerGroup.PlaceLabledControl(2, "speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 38.f);
	WeaponPistFoV.SetValue(5.f);
	TriggerGroup.PlaceLabledControl(2, "fov", this, &WeaponPistFoV);


	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("head");
	WeaponPistHitbox.AddItem("neck");
	WeaponPistHitbox.AddItem("chest");
	WeaponPistHitbox.AddItem("stomach");
	TriggerGroup.PlaceLabledControl(2, "hitbox", this, &WeaponPistHitbox);
	WeaponPistRecoil.SetFileId("pist_recoil");
	TriggerGroup.PlaceLabledControl(2, "recoil control", this, &WeaponPistRecoil);*/

	//WeaponSnipGroup.SetPosition(320 + 20 + 17, 195 + 65);
	//WeaponSnipGroup.SetText("Snipers");
	//WeaponSnipGroup.SetSize(200, 210);
	//WeaponSnipGroup.AddTab(CGroupTab("snipers", 1));
	//RegisterControl(&WeaponSnipGroup);

/*ActiveLabel3.SetText("snipers");
	TriggerGroup.PlaceLabledControl(3, "snipers", this, &ActiveLabel3);

	WeaponSnipSpeed.SetFileId("snip_speed");
	WeaponSnipSpeed.SetBoundaries(0.1f, 3.f);
	WeaponSnipSpeed.SetValue(2.0f);
	TriggerGroup.PlaceLabledControl(3, "speed", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("snip_fov");
	WeaponSnipFoV.SetBoundaries(0.1f, 38.f);
	WeaponSnipFoV.SetValue(5.f);
	TriggerGroup.PlaceLabledControl(3, "fov", this, &WeaponSnipFoV);


	WeaponSnipHitbox.SetFileId("snip_hitbox");
	WeaponSnipHitbox.AddItem("head");
	WeaponSnipHitbox.AddItem("neck");
	WeaponSnipHitbox.AddItem("chest");
	WeaponSnipHitbox.AddItem("stomach");
	TriggerGroup.PlaceLabledControl(3, "hitbox", this, &WeaponSnipHitbox);

	WeaponSnipRecoil.SetFileId("snip_recoil");
	TriggerGroup.PlaceLabledControl(3, "recoil control", this, &WeaponSnipRecoil);*/
	
	//WeaponSMGGroup.SetPosition(450 + 20 + 17, 195 + 65);
	//WeaponSMGGroup.SetText("other");
	//WeaponSMGGroup.SetSize(200, 210);
	//WeaponSnipGroup.AddTab(CGroupTab("snipers", 1));
	//RegisterControl(&WeaponSMGGroup);
//
/*	ActiveLabel4.SetText("others");
	TriggerGroup.PlaceLabledControl(4, "others", this, &ActiveLabel4);

	WeaponSMGSpeed.SetFileId("snip_speed");
	WeaponSMGSpeed.SetBoundaries(0.1f, 3.f);
	WeaponSMGSpeed.SetValue(0.3f);
	TriggerGroup.PlaceLabledControl(4, "speed", this, &WeaponSMGSpeed);

	WeaponSMGFoV.SetFileId("snip_fov");
	WeaponSMGFoV.SetBoundaries(0.1f, 38.f);
	WeaponSMGFoV.SetValue(5.f);
	TriggerGroup.PlaceLabledControl(4, "fov", this, &WeaponSMGFoV);


	WeaponSMGHitbox.SetFileId("snip_hitbox");
	WeaponSMGHitbox.AddItem("head");
	WeaponSMGHitbox.AddItem("neck");
	WeaponSMGHitbox.AddItem("chest");
	WeaponSMGHitbox.AddItem("stomach");
	TriggerGroup.PlaceLabledControl(4, "hitbox", this, &WeaponSMGHitbox);

	WeaponSMGRecoil.SetFileId("snip_recoil");
	TriggerGroup.PlaceLabledControl(4, "recoil control", this, &WeaponSMGRecoil);*/

	/*TriggerEnable.SetFileId("trig_enable");
	TriggerGroup.PlaceLabledControl(1, "enable triggerbot", this, &TriggerEnable);

	TriggerKeyPress.SetFileId("trig_onkey");
	TriggerGroup.PlaceLabledControl(1, "on key", this, &TriggerKeyPress);

	TriggerKeyBind.SetFileId("trig_key");
	TriggerGroup.PlaceLabledControl(1, "", this, &TriggerKeyBind);

	TriggerRecoil.SetFileId("trig_recoil");
	TriggerGroup.PlaceLabledControl(1, "recoil control", this, &TriggerRecoil);

	TriggerSmokeCheck.SetFileId("acc_aaa1");
	TriggerGroup.PlaceLabledControl(1, "smoke check", this, &TriggerSmokeCheck);

	TriggerDelay.SetFileId("trig_time");
	TriggerDelay.SetBoundaries(0, 200);
	TriggerDelay.SetValue(1);
	TriggerGroup.PlaceLabledControl(1, "delay", this, &TriggerDelay);*/
#pragma endregion Triggerbot stuff

	WeaponMainGroup.SetText("Rifles");
	WeaponMainGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	WeaponMainGroup.SetSize(240, 210 - 80);
	RegisterControl(&WeaponMainGroup);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 3.f);
	WeaponMainSpeed.SetValue(0.3f);
	WeaponMainGroup.PlaceLabledControl(1, "Speed", this, &WeaponMainSpeed);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.1f, 38.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl(1, "Fov", this, &WeaponMainFoV);


	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl(1, "Hitbox", this, &WeaponMainHitbox);

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainGroup.PlaceLabledControl(1, "Recoil Control", this, &WeaponMainRecoil);


	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48 + 142);
	//WeaponPistGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	WeaponPistGroup.SetSize(240, 210 - 80);
	RegisterControl(&WeaponPistGroup);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 3.f);
	WeaponPistSpeed.SetValue(0.3f);
	WeaponPistGroup.PlaceLabledControl(2, "Speed", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 38.f);
	WeaponPistFoV.SetValue(5.f);
	WeaponPistGroup.PlaceLabledControl(2, "Fov", this, &WeaponPistFoV);


	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl(2, "Hitbox", this, &WeaponPistHitbox);
	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistGroup.PlaceLabledControl(2, "Recoil Control", this, &WeaponPistRecoil);

	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48 + 142 + 142);
	WeaponSnipGroup.SetSize(240, 210 - 80);
	RegisterControl(&WeaponSnipGroup);

	WeaponSnipSpeed.SetFileId("snip_speed");
	WeaponSnipSpeed.SetBoundaries(0.1f, 3.f);
	WeaponSnipSpeed.SetValue(2.0f);
	WeaponSnipGroup.PlaceLabledControl(3, "Speed", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("snip_fov");
	WeaponSnipFoV.SetBoundaries(0.1f, 38.f);
	WeaponSnipFoV.SetValue(5.f);
	WeaponSnipGroup.PlaceLabledControl(3, "Fov", this, &WeaponSnipFoV);


	WeaponSnipHitbox.SetFileId("snip_hitbox");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
	WeaponSnipGroup.PlaceLabledControl(3, "Hitbox", this, &WeaponSnipHitbox);

	WeaponSnipRecoil.SetFileId("snip_recoil");
	WeaponSnipGroup.PlaceLabledControl(3, "Recoil Control", this, &WeaponSnipRecoil); 


#pragma region Main Weapon

#pragma endregion

#pragma region Pistols

#pragma endregion

#pragma region Snipers

#pragma endregion

#pragma region Smg

#pragma endregion

}
void CVisualTab::Setup()
{

	SetTitle("Player");
#pragma region Options
	OptionsGroup.SetText("Options");
	OptionsGroup.SetPosition(-68 + 165 - 21, 83 - 48);
	OptionsGroup.SetSize(230, 410);
	RegisterControl(&OptionsGroup);
	RegisterControl(&Active);

	Active.SetFileId("active");
	OptionsGroup.PlaceLabledControl(1, "Enable Visuals", this, &Active);

	show_team.SetFileId("ftr_enemyonly");
	OptionsGroup.PlaceLabledControl(2, "Show Teammates", this, &show_team);


	BoxCol2.SetFileId(XorStr("player_espbox_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &BoxCol2);
	BoxCol2.SetColor(66, 134, 244, 255);

	OptionsBox.SetFileId("opt_box");
	OptionsBox.AddItem("Off");
	OptionsBox.AddItem("Default");
	OptionsBox.AddItem("Mirror.tk");
	OptionsBox.AddItem("Corners");
	OptionsGroup.PlaceLabledControl(1, "Draw Box", this, &OptionsBox);


	OptionsHealth.SetFileId("opt_hp");
	OptionsHealth.AddItem("off");
	OptionsHealth.AddItem("Default");
	OptionsHealth.AddItem("Battery");
	OptionsHealth.AddItem("Bottom");

	OptionsGroup.PlaceLabledControl(1, "Draw Health", this, &OptionsHealth);

	NameCol2.SetFileId(XorStr("player_espname_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &NameCol2);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl(1, "Draw Name", this, &OptionsName);


	/*OptionsArmor.SetFileId("otr_armor");
	OptionsArmor.AddItem("off");
	OptionsArmor.AddItem("default");
	OptionsArmor.AddItem("battery");
	OptionsArmor.AddItem("bottom");
	OptionsGroup.PlaceLabledControl(1, "armor bar", this, &OptionsArmor); // */

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl(1, "Draw Flags", this, &OptionsInfo);

	Skeleton2.SetFileId(XorStr("player_skeleton_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &Skeleton2);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl(1, "Draw Skeleton", this, &OptionsSkeleton);


	Weapons2.SetFileId(XorStr("player_weapons_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &Weapons2);

	Weapons.SetFileId("kysquecest");
	OptionsGroup.PlaceLabledControl(1, "Draw Weapons", this, &Weapons);


	Ammo2.SetFileId(XorStr("player_ammo_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &Ammo2);
	Ammo2.SetColor(65, 157, 244, 255);

	Ammo.SetFileId("urmomsucksass");
	OptionsGroup.PlaceLabledControl(1, "Draw Ammo Bar", this, &Ammo);


	GlowEnemy2.SetFileId(XorStr("player_glowenemy_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &GlowEnemy2);

	GlowZ.SetFileId("opt_glowz");
	GlowZ.SetValue(0.f);
	GlowZ.SetBoundaries(0.f, 100.f);
	GlowZ.extension = XorStr("%%");
	OptionsGroup.PlaceLabledControl(1, "Enemy Glow", this, &GlowZ);


	GlowTeam2.SetFileId(XorStr("player_glowteam_color"));
	OptionsGroup.PlaceLabledControl(1, XorStr(""), this, &GlowTeam2);
	team_glow.SetFileId("opt_team_glow");
	team_glow.SetValue(0.f);
	team_glow.SetBoundaries(0.f, 100.f);
	team_glow.extension = XorStr("%%");
	OptionsGroup.PlaceLabledControl(1, "Team Glow", this, &team_glow);

	//	OffscreenESP.SetFileId("otr_offscreenESP");
	//	OptionsGroup.PlaceLabledControl(1, "Offscreen ESP", this, &OffscreenESP);



//	FiltersAll.SetFileId("ftr_all");
//	OptionsGroup.PlaceLabledControl(2, "all", this, &FiltersAll);

	//show_players.SetFileId("ftr_players");
	show_players.SetState(true);
	//OptionsGroup.PlaceLabledControl(2, "show enemies", this, &show_players);


	//show_hostage.SetFileId("ftr_hostage");
	//OptionsGroup.PlaceLabledControl(2, "hostage", this, &show_hostage);



	ChamsGroup.SetText("Chams");
	ChamsGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	ChamsGroup.SetSize(230, 410);
	RegisterControl(&ChamsGroup);

	ChamsEnemyVis2.SetFileId(XorStr("player_chamsEVIS_color"));
	ChamsGroup.PlaceLabledControl(1, XorStr(""), this, &ChamsEnemyVis2);
	ChamsEnemyVis2.SetColor(65, 244, 149, 255); // 65, 244, 149, 255
	ChamsEnemyvisible.SetFileId("chams_en_vis");
	ChamsGroup.PlaceLabledControl(1, "Chams Enemy", this, &ChamsEnemyvisible);
	visible_chams_type.SetFileId("otr_visiblechams_type");
	visible_chams_type.AddItem("Texture");
	visible_chams_type.AddItem("Flat"); // like my ex :) //freak trying to be funny with random comments:(
	visible_chams_type.AddItem("Pulse");
	ChamsGroup.PlaceLabledControl(2, "", this, &visible_chams_type);

	ChamsEnemyNotVis2.SetFileId(XorStr("player_chamsENVIS_color"));
	ChamsGroup.PlaceLabledControl(1, XorStr(""), this, &ChamsEnemyNotVis2);
	ChamsEnemyNotVis2.SetColor(66, 134, 244, 255);

	ChamsEnemyinVisible.SetFileId("chams_en_novis");
	ChamsGroup.PlaceLabledControl(1, "Chams Enemy Invisible", this, &ChamsEnemyinVisible); // *1

	invisible_chams_type.SetFileId("otr_invisiblechams_type");
	invisible_chams_type.AddItem("Texture");
	invisible_chams_type.AddItem("Flat"); // i'm still sad about that :(
	invisible_chams_type.AddItem("Pulse");
	ChamsGroup.PlaceLabledControl(2, "", this, &invisible_chams_type);

	ChamsTeamVis2.SetFileId(XorStr("player_ChamsTeamVis"));
	ChamsGroup.PlaceLabledControl(1, XorStr(""), this, &ChamsTeamVis2);

	ChamsTeamVis.SetFileId("ChamsTeamVis");
	ChamsGroup.PlaceLabledControl(1, "Chams Team", this, &ChamsTeamVis);
	//ChamsLocal.SetFileId("chams_local");
	//ChamsGroup.PlaceLabledControl(1, "local chams", this, &ChamsLocal);

	HandChamsCol2.SetFileId(XorStr("handchams_col"));
	ChamsGroup.PlaceLabledControl(2, XorStr(""), this, &HandChamsCol2);

	HandCHAMS.SetFileId("chams_local_hand");
	HandCHAMS.AddItem("Off");
	HandCHAMS.AddItem("Texture");
	HandCHAMS.AddItem("Wireframe");
	HandCHAMS.AddItem("Golden");
	HandCHAMS.AddItem("Glass");
	HandCHAMS.AddItem("Crystal");
	HandCHAMS.AddItem("Pulse");
	ChamsGroup.PlaceLabledControl(1, "Hand Chams", this, &HandCHAMS);
	hand_transparency.SetFileId("esp_hand_transparency");
	hand_transparency.SetBoundaries(0, 100);
	hand_transparency.SetValue(100);
	hand_transparency.extension = XorStr("%%");
	ChamsGroup.PlaceLabledControl(2, "", this, &hand_transparency);

	GunChamsCol2.SetFileId(XorStr("gunchams_col"));
	ChamsGroup.PlaceLabledControl(2, XorStr(""), this, &GunChamsCol2);
	GunCHAMS.SetFileId("chams_local_weapon");
	GunCHAMS.AddItem("Off");
	GunCHAMS.AddItem("Texture");
	GunCHAMS.AddItem("Wireframe");
	GunCHAMS.AddItem("Golden");
	GunCHAMS.AddItem("Glass");
	GunCHAMS.AddItem("Crystal");
	GunCHAMS.AddItem("Pulse");
	ChamsGroup.PlaceLabledControl(1, "Weapon Chams", this, &GunCHAMS);


	gun_transparency.SetFileId("esp_gun_transparency");
	gun_transparency.SetBoundaries(0, 100);
	gun_transparency.SetValue(100);
	gun_transparency.extension = XorStr("%%");
	ChamsGroup.PlaceLabledControl(2, "", this, &gun_transparency);
	scoped_c2.SetFileId(XorStr("scope_c"));
	ChamsGroup.PlaceLabledControl(2, XorStr(""), this, &scoped_c2);
	localmaterial.SetFileId("esp_localscopedmat");
	localmaterial.AddItem("Off");
	localmaterial.AddItem("Clear");
	ChamsGroup.PlaceLabledControl(1, "Scoped Materials", this, &localmaterial);

	transparency.SetFileId("esp_transparency");
	transparency.SetBoundaries(0, 100);
	transparency.SetValue(20);
	transparency.extension = XorStr("%%");
	ChamsGroup.PlaceLabledControl(2, "", this, &transparency);

	// this one is still working you can use it just I dont like this 
	//fakelag_ghost.SetFileId("otr_fakelag_ghost");
	//fakelag_ghost.AddItem("off");
	//fakelag_ghost.AddItem("default");
	//fakelag_ghost.AddItem("pulse");
	//ChamsGroup.PlaceLabledControl(1, "fake lag chams", this, &fakelag_ghost);



	/*GlowLocal2.SetFileId(XorStr("player_glowlocal_color"));
	ChamsGroup.PlaceLabledControl(1, XorStr(""), this, &GlowLocal2);
	Glowz_lcl.SetFileId("opt_glowz_lcl");
	Glowz_lcl.SetValue(0.f);
	Glowz_lcl.SetBoundaries(0.f, 100.f);
	Glowz_lcl.extension = XorStr("%%");
	ChamsGroup.PlaceLabledControl(1, "local glow", this, &Glowz_lcl);*/

	
	// Just no
	//	  I
	//    V
#pragma region I am literally hitler, ruined is 20% gay, DK is a jew and yall can suck it
	
	/*worldgroup.SetText("World");
	worldgroup.AddTab(CGroupTab("Main", 1));
	worldgroup.AddTab(CGroupTab("Mods", 2));
	worldgroup.SetPosition(294, 275);  // 225, 285
	worldgroup.SetSize(260, 165);
	RegisterControl(&worldgroup);

	
	customskies.SetFileId("otr_skycustom");
	customskies.AddItem("Default");
	customskies.AddItem("Night");
	customskies.AddItem("NoSky");
	customskies.AddItem("Cloudy");
	worldgroup.PlaceLabledControl(1, "change sky", this, &customskies);

	ModulateSkyBox.SetFileId(XorStr("sky_box_color_enable"));
	worldgroup.PlaceLabledControl(2, XorStr("enable sky color changer"), this, &ModulateSkyBox);*/



#pragma endregion Setting up the Other controls
}
void CVisual2Tab::Setup()
{
	SetTitle("Visual");
	Main1.SetText("Options");
	Main1.SetPosition(-68 + 165 - 21, 83 - 48);
	Main1.SetSize(230, 410);
	RegisterControl(&Main1);

	spreadcrosscol.SetFileId(XorStr("weapon_spreadcross_col"));
	Main1.PlaceLabledControl(2, XorStr(""), this, &spreadcrosscol);

	SpreadCrosshair.SetFileId(XorStr("v_spreadcrosshair"));
	SpreadCrosshair.AddItem("Off");
	SpreadCrosshair.AddItem("Standard");
	SpreadCrosshair.AddItem("Colour");
	SpreadCrosshair.AddItem("Rainbow");
	SpreadCrosshair.AddItem("Rainbow Rotate");
	Main1.PlaceLabledControl(3, XorStr("Spread Crosshair"), this, &SpreadCrosshair);


	AutowallCrosshair.SetFileId("otr_autowallcross");
	Main1.PlaceLabledControl(3, "Force Crosshair", this, &AutowallCrosshair);

	OtherNoScope.SetFileId("otr_noscope");
	Main1.PlaceLabledControl(3, "Remove Scope", this, &OtherNoScope);

	RemoveZoom.SetFileId("otr_remv_zoom");
	Main1.PlaceLabledControl(3, "Remove Zoom", this, &RemoveZoom);

	OtherNoFlash.SetFileId("otr_noflash");
	Main1.PlaceLabledControl(3, "Remove Flash", this, &OtherNoFlash);

	nosmoke.SetFileId("otr_nosmoke");
	Main1.PlaceLabledControl(3, "Remove Smoke", this, &nosmoke);

	optimize.SetFileId("ftr_optimize");
	Main1.PlaceLabledControl(2, "Disable Post Process", this, &optimize);

	FiltersWeapons.SetFileId("ftr_weaps");
	Main1.PlaceLabledControl(2, "Dropped Weapons", this, &FiltersWeapons);
	FiltersWeapons.SetState(true);

	FiltersWeapons.SetFileId("ftr_weaps_box");
	Main1.PlaceLabledControl(2, "Dropped Weapons Box", this, &FiltersWeaponsBox);

	FiltersNades.SetFileId("ftr_nades");
	Main1.PlaceLabledControl(2, "Grenades", this, &FiltersNades);

	FiltersC4.SetFileId("ftr_c4");
	Main1.PlaceLabledControl(2, "Bomb Timer", this, &FiltersC4);
	FiltersC4.SetState(true);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	Main1.PlaceLabledControl(3, "No Visual Recoil", this, &OtherNoVisualRecoil);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(30.f, 120.f);
	OtherViewmodelFOV.SetValue(60.f);
	Main1.PlaceLabledControl(3, "Viewmodel FOV", this, &OtherViewmodelFOV);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 50.f);
	OtherFOV.SetValue(0.f);
	Main1.PlaceLabledControl(3, "Override FOV", this, &OtherFOV);


	OtherThirdperson.SetFileId("aa_1thirpbind");
	Main1.PlaceLabledControl(0, "Thirdperson", this, &OtherThirdperson);
	ThirdPersonKeyBind.SetFileId("aa_thirpbind");
	Main1.PlaceLabledControl(0, "", this, &ThirdPersonKeyBind);



	/*   */
	Main2.SetText("Misc");
	Main2.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	Main2.SetSize(240, 178);
	RegisterControl(&Main2);


	LBYIndicator.SetFileId("otr_LBYIndicator");
	Main2.PlaceLabledControl(4, "Draw Indicators", this, &LBYIndicator);

	LBYIndicator.SetFileId("otr_LBYIndicator");
	Main2.PlaceLabledControl(4, "Damage Indicators", this, &DamageIndicator);

	logs.SetFileId("otr_skeetpaste");
	Main2.PlaceLabledControl(4, "Event Log", this, &logs);

	SpecList2.SetFileId("otr_spectator");
	Main2.PlaceLabledControl(4, "Spectator List", this, &SpecList2);
	SpecList2.SetState(true);

	cheatinfo.SetFileId("cheatinfox");
	Main2.PlaceLabledControl(4, "Render Info", this, &cheatinfo);


	GlowOtherEnt.SetFileId(XorStr("player_glowother_color"));
	Main2.PlaceLabledControl(1, XorStr(""), this, &GlowOtherEnt);

	OtherEntityGlow.SetFileId("otr_world_ent_glow");
	Main2.PlaceLabledControl(4, "Entity Glow", this, &OtherEntityGlow);

	OtherHitmarker.SetFileId("otr_hitmarker");
	Main2.PlaceLabledControl(4, "Hit marker", this, &OtherHitmarker);

	aspectratio.SetFileId("aspectratio");
	Main2.PlaceLabledControl(3, "Custom Aspect Ratio", this, &aspectratio);

	aspectratiovalue.SetFileId("aspectratiovalue");
	aspectratiovalue.SetBoundaries(0, 200);
	aspectratiovalue.SetValue(50.0);
	Main2.PlaceLabledControl(3, "Custom Aspect Ratio Value", this, &aspectratiovalue);

	//--
	Main3.SetText("World");
	Main3.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48 + 142 + 40 + 5);
	//WeaponPistGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	Main3.SetSize(240, 188);
	RegisterControl(&Main3);

	colmod.SetFileId("night_amm");
	colmod.SetBoundaries(000.000f, 100.00f);
	colmod.extension = XorStr("%%");
	colmod.SetValue(100.0f);
	Main3.PlaceLabledControl(1, "Night Mode", this, &colmod);

	WorldColor.SetFileId("otr_hitmarker");
	Main3.PlaceLabledControl(4, "World Color Changer", this, &WorldColor);

	sky_r.SetFileId("wrld_r");
	sky_r.SetBoundaries(0.f, 100.f);
	sky_r.SetValue(0.0f);
	Main3.PlaceLabledControl(2, "Red", this, &sky_r);

	sky_g.SetFileId("wrld_g");
	sky_g.SetBoundaries(0.f, 100.f);
	sky_g.SetValue(75.0f);
	Main3.PlaceLabledControl(2, "Green", this, &sky_g);

	sky_b.SetFileId("wrld_b");
	sky_b.SetBoundaries(0.f, 100.f);
	sky_b.SetValue(41.0f);
	Main3.PlaceLabledControl(2, "Blue", this, &sky_b);


	colmodupdate.SetFileId("otr_night");
	colmodupdate.SetText(XorStr("Update Materials"));
	Main3.PlaceLabledControl(1, "", this, &colmodupdate); //you could've just made this a button lol // done boss
	colmodupdate.SetCallback(&updatestuff);
}

void CSkinTab::Setup()
{
	SetTitle("Config");

	//ColorsGroup
	knifegroup.SetText("Settings");
	knifegroup.SetPosition(-68 + 165 - 21, 83 - 48);
	knifegroup.SetSize(564 - 89, 400);
	RegisterControl(&knifegroup); 
	
	ConfigListBox.SetHeightInItems(7);
	list_configs();
	knifegroup.PlaceLabledControl(0, XorStr(""), this, &ConfigListBox);
	ConfigListBox.SetSize(175, 310);

	ColorsGroup.SetText("Settings");
	ColorsGroup.SetPosition(-68 + 165 - 21 + 150 + 40, 83 - 48);
	ColorsGroup.SetSize(182 + 133 - 30, 400);
	RegisterControl(&ColorsGroup);

	LoadConfig.SetText(XorStr("Load Config"));
	LoadConfig.SetCallback(&load_callback);
	ColorsGroup.PlaceLabledControl(0, "", this, &LoadConfig);
	SaveConfig.SetText(XorStr("Save Config"));
	SaveConfig.SetCallback(&save_callback);
	ColorsGroup.PlaceLabledControl(0, "", this, &SaveConfig);
	RemoveConfig.SetText(XorStr("Remove Config"));
	RemoveConfig.SetCallback(&remove_config);
	ColorsGroup.PlaceLabledControl(0, "", this, &RemoveConfig);
	ColorsGroup.PlaceLabledControl(0, "", this, &NewConfigName);
	AddConfig.SetText(XorStr("Add Config"));
	AddConfig.SetCallback(&add_config);
	ColorsGroup.PlaceLabledControl(0, "", this, &AddConfig);

	snipergroup.SetText("Misc"); // 173, 116
	snipergroup.SetPosition(278 + 165 + 33 - 173 + 2, 87 + 116 - 20 + 15);
	snipergroup.SetSize(237 - 30, 170 - 15);
	RegisterControl(&snipergroup);
	//	Main2.SetPosition(278 + 165, 83);

	skinwindow.SetFileId("skinwindow");
	snipergroup.PlaceLabledControl(1, "Skinchanger Window", this, &skinwindow);

	plistwindow.SetFileId("espwindow");
	snipergroup.PlaceLabledControl(1, "ESP Preview Window", this, &espwindow);

	espwindow.SetFileId("espwindow");
	snipergroup.PlaceLabledControl(1, "Playerlist Window", this, &plistwindow);

	//logotype.SetFileId("logo_type");
	//logotype.AddItem("icon");
	//logotype.AddItem("text");
	//snipergroup.PlaceLabledControl(1, "menu logo type", this, &logotype);



	/*t_sniperAWP_skin_id.SetFileId("t_AWP_skin");
	t_sniperAWP_skin_id.AddItem("Default");
	t_sniperAWP_skin_id.AddItem("Dragon Lore");
	t_sniperAWP_skin_id.AddItem("Pink DDPAT");
	t_sniperAWP_skin_id.AddItem("Asiimov");
	t_sniperAWP_skin_id.AddItem("Redline");
	t_sniperAWP_skin_id.AddItem("Medusa");
	t_sniperAWP_skin_id.AddItem("Hyper Beast");
	t_sniperAWP_skin_id.AddItem("Whiteout");
	snipergroup.PlaceLabledControl(3, XorStr("Skin"), this, &t_sniperAWP_skin_id);

	t_sniperAWP_wear.SetFileId("t_sniperAWP_wear");
	t_sniperAWP_wear.SetBoundaries(1, 100);
	t_sniperAWP_wear.SetValue(1);
	t_sniperAWP_wear.extension = XorStr("%%");
	snipergroup.PlaceLabledControl(3, XorStr("Wear"), this, &t_sniperAWP_wear); */

	/*enableskins.SetFileId(XorStr(""));
	knifegroup.PlaceLabledControl(0, "enable skins", this, &enableskins);

#pragma region Terrorist ( to be replaced with team based stuff )
	t_knife_index.SetFileId("t_knife_index");
	t_knife_index.AddItem("off");
	t_knife_index.AddItem("bayonet");
	t_knife_index.AddItem("m9 bayonet");
	t_knife_index.AddItem("butterfly");
	t_knife_index.AddItem("flip");
	t_knife_index.AddItem("gut");
	t_knife_index.AddItem("karambit");
	t_knife_index.AddItem("huntsman");
	t_knife_index.AddItem("falchion");
	knifegroup.PlaceLabledControl(0, XorStr("knife model"), this, &t_knife_index);

	t_knife_skin_id.SetFileId("t_knife_skin");
	t_knife_skin_id.AddItem("default");
	t_knife_skin_id.AddItem("ruby");
	t_knife_skin_id.AddItem("sapphire");
	t_knife_skin_id.AddItem("black pearl");
	t_knife_skin_id.AddItem("doppler");
	t_knife_skin_id.AddItem("fade");
	t_knife_skin_id.AddItem("marble fade");
	t_knife_skin_id.AddItem("gamma doppler");
	t_knife_skin_id.AddItem("emerald");
	t_knife_skin_id.AddItem("slaughter");
	t_knife_skin_id.AddItem("whiteout");
	t_knife_skin_id.AddItem("ultraviolet");
	t_knife_skin_id.AddItem("lore (m9)");
	knifegroup.PlaceLabledControl(0, XorStr("paint"), this, &t_knife_skin_id);


	SkinApply.SetText(XorStr("force update"));
	SkinApply.SetCallback(&KnifeApplyCallbk);
	knifegroup.PlaceLabledControl(0, "", this, &SkinApply);

	Msg.SetText(XorStr(" cool weapon skins are set by default, but i'll do combobox for every single weapon ok?"));
	knifegroup.PlaceLabledControl(0, "", this, &Msg);*/


	/*---------------------- COL ----------------------*/
	/*---------------------- COL ----------------------*/
	/*---------------------- COL ----------------------*/




	//Skeletonteam.SetFileId(XorStr("player_skeletonteam_color"));
	//ColorsGroup.PlaceLabledControl(1, XorStr("skeleton team"), this, &Skeletonteam);


	//Weaponsteam.SetFileId(XorStr("player_weapons_color_team"));
	//ColorsGroup.PlaceLabledControl(1, XorStr("weapons team"), this, &Weaponsteam);

	//	Money.SetFileId(XorStr("player_money_color"));
	//	ColorsGroup.PlaceLabledControl(1, XorStr("Money"), this, &Money);


	//	Bullettracer.SetFileId(XorStr("player_beam_color"));
	//	ColorsGroup.PlaceLabledControl(2, XorStr("Bullet tracers"), this, &Bullettracer);


	//misc_lagcomp.SetFileId(XorStr("misc_lagcomp"));
	//misc_lagcomp.SetColor(250, 250, 250, 255);
	//ColorsGroup.PlaceLabledControl(2, XorStr("lag compensation"), this, &misc_lagcomp);

	//misc_lagcompBones.SetFileId(XorStr("misc_lagcompBones"));
	//misc_lagcompBones.SetColor(250, 250, 250, 255);
	//ColorsGroup.PlaceLabledControl(2, XorStr("backtrack bones"), this, &misc_lagcompBones);



	//	SleeveChams_col.SetFileId("player_chams_sleeves_color");
	//	ColorsGroup.PlaceLabledControl(2, XorStr("Sleeve Chams"), this, &SleeveChams_col);

	//Offscreen.SetFileId(XorStr("player_offscreen_color"));
	//ColorsGroup.PlaceLabledControl(2, XorStr("offscreen"), this, &Offscreen);

	//	fakelag_ghost.SetFileId("player_fakelag_ghost");
	//	ColorsGroup.PlaceLabledControl(2, XorStr("Fakelag Ghost"), this, &fakelag_ghost);
		//---

	
	//-----------------
	
	/*snipergroup.SetText("Snipers");
	snipergroup.SetPosition(284, 30);
	snipergroup.AddTab(CGroupTab("Auto", 1));
	snipergroup.AddTab(CGroupTab("Bolt Action", 2));
	snipergroup.SetSize(270, 170);
	RegisterControl(&snipergroup);

	t_sniperSCAR_skin_id.SetFileId("t_scar20_skin");
	t_sniperSCAR_skin_id.AddItem("Default");
	t_sniperSCAR_skin_id.AddItem("Crimson Web");
	t_sniperSCAR_skin_id.AddItem("Splash Jam");
	t_sniperSCAR_skin_id.AddItem("Emerald");
	t_sniperSCAR_skin_id.AddItem("Cardiac");
	t_sniperSCAR_skin_id.AddItem("Cyrex");
	t_sniperSCAR_skin_id.AddItem("Whiteout");
	t_sniperSCAR_skin_id.AddItem("The Fuschia Is Now");
	snipergroup.PlaceLabledControl(1, XorStr("Scar20"), this, &t_sniperSCAR_skin_id);

	t_sniperSCAR_wear.SetFileId("t_sniperSCAR_wear");
	t_sniperSCAR_wear.SetBoundaries(1, 100);
	t_sniperSCAR_wear.SetValue(1);
	t_sniperSCAR_wear.extension = XorStr("%%");
	snipergroup.PlaceLabledControl(1, XorStr("Wear"), this, &t_sniperSCAR_wear);
	*/
	// --



	// --
	
}

void CColorTab::Setup()
{
	SetTitle("Misc");
#pragma region Visual Colors


	//bomb_timer.SetFileId(XorStr("bomb_timer"));
	bomb_timer.SetColor(250, 10, 10, 230);
	//ColorsGroup.PlaceLabledControl(4, XorStr("Bomb Timer"), this, &bomb_timer);



	//	misc_backtrackchams.SetFileId(XorStr("misc_backtrackchams"));
	//	misc_backtrackchams.SetColor(250, 250, 250, 255);
	//	ColorsGroup.PlaceLabledControl(5, XorStr("Backtrack Chams"), this, &misc_backtrackchams);
	// 35 58
	/*---------------------- OTHERS ----------------------*/
	/*---------------------- OTHERS ----------------------*/
	/*---------------------- OTHERS ----------------------*/



	OtherGroup.SetText("Options");
	OtherGroup.SetPosition(-68 + 165 - 21, 83 - 48);
	OtherGroup.SetSize(230, 250);
	RegisterControl(&OtherGroup);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.AddItem("Anti-Untrusted");
	OtherSafeMode.AddItem("Anti Auth Error");
	OtherSafeMode.AddItem("Danger Zone");
	OtherSafeMode.AddItem("Lol");
	OtherSafeMode.AddItem("Off");
	OtherGroup.PlaceLabledControl(0, "Safety Mode", this, &OtherSafeMode);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl(0, "Bunny Hop", this, &OtherAutoJump);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherGroup.PlaceLabledControl(0, "Rage Autostrafer", this, &OtherAutoStrafe);

	//c_changer.SetFileId("clantag_changer");
	//OtherGroup.PlaceLabledControl(0, "clantag spammer", this, &c_changer);

	// 13, 17
	Radar.SetFileId("Radar");
	OtherGroup.PlaceLabledControl(0, "Draw Radar", this, &Radar);
	Radar.SetState(false);

	RadarX.SetFileId("misc_radar_xax1");
	RadarX.SetBoundaries(11, 1716);
	RadarX.SetValue(13);
	OtherGroup.PlaceLabledControl(0, "X position", this, &RadarX);

	RadarY.SetFileId("misc_radar_yax2");
	RadarY.SetBoundaries(26, 875);
	RadarY.SetValue(30);
	OtherGroup.PlaceLabledControl(0, "Y position", this, &RadarY);

	NameChanger.SetFileId("misc_clantagcg");
	NameChanger.AddItem("Off");
	NameChanger.AddItem("GamSens");
	//NameChanger.AddItem("custom");
	OtherGroup.PlaceLabledControl(0, "Clantag Spammer", this, &NameChanger);

	
	hitmarker_sound.SetFileId("hitmarker_sound");
	hitmarker_sound.AddItem("Off");
	hitmarker_sound.AddItem("aimware");
	hitmarker_sound.AddItem("metalic");
	hitmarker_sound.AddItem("bubble");
	hitmarker_sound.AddItem("bameware");
	hitmarker_sound.AddItem("anime");
	hitmarker_sound.AddItem("hitler"); // this is for CruZZ and Crytec. Heil hitler
	hitmarker_sound.AddItem("bell"); // diiiing	
 //	hitmarker_sound.AddItem("Light Switch");
	hitmarker_sound.AddItem("custom (csgo sound folder)");
	OtherGroup.PlaceLabledControl(0, "Hitmarker Sound", this, &hitmarker_sound);



	OtherOptions.SetText("Viewmodel");
	OtherOptions.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48);
	OtherOptions.SetSize(215, 127);
	RegisterControl(&OtherOptions);

	override_viewmodel.SetFileId("otr_override_viewmodel_offset");
	OtherOptions.PlaceLabledControl(3, "Override Viewmodel Offset", this, &override_viewmodel);

	offset_x.SetFileId("otr_offset_x");
	offset_x.SetBoundaries(-12, 12);
	offset_x.SetValue(2.5);
	OtherOptions.PlaceLabledControl(3, "Offset X", this, &offset_x);

	offset_y.SetFileId("otr_offset_Y");
	offset_y.SetBoundaries(-12, 12);
	offset_y.SetValue(2.0);
	OtherOptions.PlaceLabledControl(3, "Offset Y", this, &offset_y);

	offset_z.SetFileId("otr_offset_z");
	offset_z.SetBoundaries(-12, 12);
	offset_z.SetValue(-2.0);
	OtherOptions.PlaceLabledControl(3, "Offset Z", this, &offset_z);


	ConfigGroup.SetText("Legit Bunnyhop");
	ConfigGroup.SetPosition(278 + 165 + 24 - 171 + 16, 83 - 48 + 139);
	ConfigGroup.SetSize(215, 127);
	RegisterControl(&ConfigGroup);

	Legitbhop.SetFileId("misc_legitbhop");
	ConfigGroup.PlaceLabledControl(4, "Legit Bunnyhop", this, &Legitbhop);


	Legitbhophitchance.SetFileId("misc_lbhophitchance");
	Legitbhophitchance.SetBoundaries(0.00f, 100.00f);
	Legitbhophitchance.SetValue(50.0f);
	Legitbhophitchance.extension = XorStr("%%");
	ConfigGroup.PlaceLabledControl(4, "Bunnyhop Hitchance", this, &Legitbhophitchance);

	Legitbhopminhit.SetFileId("misc_legitbhopminhit");
	Legitbhopminhit.SetValue(5.0f);
	Legitbhopminhit.SetBoundaries(0.00f, 11.00f);
	ConfigGroup.PlaceLabledControl(4, "Bunnyhop Min Hops", this, &Legitbhopminhit);

	Legitbhopmaxhit.SetFileId("misc_legitbhopmaxhit");
	Legitbhopmaxhit.SetBoundaries(0.00f, 12.00f);
	Legitbhopmaxhit.SetValue(5.0f);
	ConfigGroup.PlaceLabledControl(4, "Bunnyhop Max Hops", this, &Legitbhopmaxhit);


	OtherOptions2.SetText("Others");

	/*
		TriggerGroup.SetPosition(-68 + 165 - 21, 283 - 30);
	TriggerGroup.SetSize(230, 210);*/
	OtherOptions2.SetPosition(-68 + 165 - 21, 283 - 30 + 40);
	OtherOptions2.SetSize(230, 136);
	RegisterControl(&OtherOptions2);

	unload.SetText("Unload Cheat");
	unload.SetCallback(UnLoadCallbk);
	OtherOptions2.PlaceLabledControl(1, "", this, &unload);

	fcrash.SetText("Force Crash");
	fcrash.SetCallback(fcrash2);
	OtherOptions2.PlaceLabledControl(1, "", this, &fcrash);

	unlockh.SetText("Unlock Hidden Cvars");
	unlockh.SetCallback(updatestuff);
	OtherOptions2.PlaceLabledControl(1, "", this, &unlockh);

	Menu.SetFileId(XorStr("menu_color"));
	Menu.SetColor(255, 146, 1, 255);
	OtherOptions2.PlaceLabledControl(0, XorStr("Menu Color"), this, &Menu);

	//DebugLagComp.SetFileId(XorStr("lagcompensationyes"));
	//OtherGroup.PlaceLabledControl(0, XorStr("draw hit history"), this, &DebugLagComp);

	//BackTrackBones2.SetFileId(XorStr("spookybonesOwOomg"));
	//OtherGroup.PlaceLabledControl(0, XorStr("backtrack skeleton"), this, &BackTrackBones2);

	/*buybot_primary.SetFileId("buybot_primary");
	buybot_primary.AddItem("off");
	buybot_primary.AddItem("scar20/g3sg8");
	buybot_primary.AddItem("ssg08");
	buybot_primary.AddItem("awp");
	buybot_primary.AddItem("ak-47/m4");
	buybot_primary.AddItem("aug/sg553");
	buybot_primary.AddItem("mp9/mac10");
	OtherGroup.PlaceLabledControl(2, "buybot rifles", this, &buybot_primary);

	buybot_secondary.SetFileId("buybot_secondary");
	buybot_secondary.AddItem("off");
	buybot_secondary.AddItem("dual berretas");
	buybot_secondary.AddItem("revolver/desert eagle");
	buybot_secondary.AddItem("fiveseven/cz75");
	OtherGroup.PlaceLabledControl(2, "buybot pistols", this, &buybot_secondary);

	buybot_otr.SetFileId("buybot_other");
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("kevlar")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("hegrenade")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("flashbang")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("smokegrenade")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("molotov")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("zeus")));
	buybot_otr.items.push_back(dropdownboxitem(false, XorStr("defusekit")));
	OtherGroup.PlaceLabledControl(2, "buybot others", this, &buybot_otr);*/


	//DebugLagComp.SetFileId(XorStr("lagcompensationyes"));
	//OtherOptions.PlaceLabledControl(0, XorStr("draw lag compensation"), this, &DebugLagComp);

	//BackTrackBones2.SetFileId(XorStr("spookybonesOwOomg"));
	//OtherOptions.PlaceLabledControl(0, XorStr("backtrack bones"), this, &BackTrackBones2);*/

//	quickstop_speed.SetFileId(XorStr("quickstop_speed"));
//	quickstop_speed.SetBoundaries(1, 40);
//	quickstop_speed.SetValue(30);
//	OtherOptions.PlaceLabledControl(0, XorStr("Quick Stop Speed"), this, &quickstop_speed);
	//	BackTrackBones.SetFileId(XorStr("spookybonesOwO"));
	//	OtherOptions.PlaceLabledControl(0, XorStr("BackTrack Chams"), this, &BackTrackBones);
	// your fps will look beyond the gates of the next life and will raise their middle fingers for having caused their suicide

	//OtherOptions2.SetText("other 2");
	//OtherOptions2.SetPosition(290, 373);
	//OtherOptions2.SetSize(264, 70);
	//RegisterControl(&OtherOptions2);

	//	experimental_backtrack.SetFileId(XorStr("experimental_backtrack"));
	//	OtherOptions2.PlaceLabledControl(0, XorStr("Experimental Position Adjustment"), this, &experimental_backtrack);

	/*ClanTag.SetFileId("otr_clantg");
	//	ClanTag.AddItem("off");
	//	ClanTag.AddItem("Default");
	//	ClanTag.AddItem("FreaK Rats Kids");
	OtherOptions2.PlaceLabledControl(0, XorStr("Clan Tag"), this, &ClanTag); // requested by: https://steamcommunity.com/id/hitoridekun and https://steamcommunity.com/id/123x456x789

	owo_slider.SetFileId("owo_slider");
	owo_slider.SetBoundaries(0, 100);
	owo_slider.SetValue(100);
	owo_slider.extension = XorStr("%%");
	OtherOptions2.PlaceLabledControl(0, XorStr("OwO"), this, &owo_slider);*/
}

void CPlayersTab::Setup() // I just broke it so I deleted everything, but it was working 
{
	SetTitle(XorStr("PLAYERS"));

	PlayerSettingsGroup2.SetText(XorStr("Avalible Players"));
	PlayerSettingsGroup2.SetSize(236, 479);
	PlayerSettingsGroup2.SetPosition(268, -14);
	RegisterControl(&PlayerSettingsGroup2);

	PlayerListControl.SetSize(206, 479);
	PlayerListControl.SetPosition(284, -4);
	PlayerListControl.SetHeightInItems(20);
	RegisterControl(&PlayerListControl);

	PlayerSettingsGroup.SetText(XorStr("Settings"));
	PlayerSettingsGroup.SetSize(236, 479);
	PlayerSettingsGroup.SetPosition(532, -14);
	RegisterControl(&PlayerSettingsGroup);

	PlayerForcePitch_Pitch.AddItem(XorStr("Eye angles"));
	PlayerForcePitch_Pitch.AddItem(XorStr("Up"));
	PlayerForcePitch_Pitch.AddItem(XorStr("Emotion"));

	PlayerForceYaw_Yaw.AddItem(XorStr("Default"));
	PlayerForceYaw_Yaw.AddItem(XorStr("Correction"));
	PlayerForceYaw_Yaw.AddItem(XorStr("Eye angles"));
	PlayerForceYaw_Yaw.AddItem(XorStr("Sideways left"));
	PlayerForceYaw_Yaw.AddItem(XorStr("Sideways right"));
	PlayerForceYaw_Yaw.AddItem(XorStr("180°"));

	PlayerSettingsGroup.PlaceLabledControl(0, XorStr("Priority"), this, &PlayerPriority);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr("Whitelist"), this, &PlayerFriendly);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr("Prioritize body"), this, &PlayerPreferBody);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr("Force pitch"), this, &PlayerForcePitch);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr(""), this, &PlayerForcePitch_Pitch);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr("Force yaw"), this, &PlayerForceYaw);
	PlayerSettingsGroup.PlaceLabledControl(0, XorStr(""), this, &PlayerForceYaw_Yaw);
}


void options::SetupMenu()
{
	menu.Setup();
	GUI.RegisterWindow(&menu);
	GUI.BindWindow(VK_INSERT, &menu);
}
void options::DoUIFrame()
{
	if (menu.ColorsTab.Legitbhop.GetState())
	{
		menu.ColorsTab.OtherAutoJump.SetState(false);
	}
	if (menu.ColorsTab.OtherAutoJump.GetState())
	{
		menu.ColorsTab.Legitbhop.SetState(false);
	}
	if (menu.visuals2_tab.WorldColor.GetState())
	{
		menu.visuals2_tab.colmod.SetValue(100.f);
	}
	GUI.Update();
	GUI.Draw();
	plist.paint();
}


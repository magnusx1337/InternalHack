#pragma once
#include "GUI.h"
#include "Controls.h"

class CAimbotTab : public CTab
{
public:
	void Setup();
	CLabel ActiveLabel;
	CCheckBox Active;
	CComboBoxYeti psilent;
	CSlider randlbyr;
	CSlider randlbyf;
	CGroupBox AimbotGroup;
	CSlider freerange;
	CGroupBox aagroup;
	CKeyBind minimal_walk;
	CCheckBox AimbotEnable;
	CSlider lby1;
	CCheckBox infinite_duck;
	CKeyBind fake_crouch_key;
	CSlider Fakelagjump;
	CSlider FakelagMove;
	CSlider FakelagStand;
	CSlider FakeWalkSpeed;
	CCheckBox lag_pred;
	CCheckBox backtrack;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotSilentAim;
	CCheckBox legit_mode;
	CCheckBox disable_on_dormant;
	CCheckBox legit_trigger;
	CKeyBind legit_trigger_key;
	CCheckBox apply_smooth;
	CCheckBox FakelagEnab;
	CCheckBox FakelagBreakLC;
	CSlider   FakeLagChoke;
	CCheckBox FakelagOnground;
	CKeyBind fw;
	CComboBoxYeti AimbotResolver;
	CSlider AimbotFov;
	//-------------------------
	//--------------------------
	CCheckBox LowerbodyFix;
	CCheckBox PreferBodyAim;
	CCheckBox AWPAtBody;
	CCheckBox QuickStop;
	CSlider BaimIfUnderXHealth;
	CSlider XShots;
	CCheckBox EnginePrediction;
	CCheckBox AimbotAimStep;
	CGroupBox multipoint;
	CCheckBox pointscaleyes;
	CKeyBind fakelag_key;
	CCheckBox Multienable;
	CSlider pointscaleval;
	CCheckBox fake_crouch;
	CSlider Multival;
	CSlider Multival2;
	CSlider MultiVal3;
	CSlider Multival4;
	CCheckBox nospread;
	CSlider AimbotAimStep2;
	CSlider shotlimit;
	CCheckBox AimbotKeyPress;

	CCheckBox baim_fake;
	CCheckBox baim_inair;
	CCheckBox baim_fakewalk;
	CCheckBox baim_lethal;
	CCheckBox baim_muslim;

	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;
	CGroupBox TargetGroup;
	CComboBoxYeti TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBoxYeti TargetHitbox;
	CComboBoxYeti TargetHitscan;
	CComboBoxYeti delay_shot;
	CCheckBox TargetMultipoint;
	CComboBoxYeti fl_spike;
	CSlider   TargetPointscale;
	CSlider   bruteX;
	CSlider   baim;
	CComboBoxYeti desync_type_stand;
	CSlider desync_range_stand;
	CCheckBox desync_swapsides_stand;

	CComboBoxYeti desync_type_move;
	CSlider desync_range_move;
	CCheckBox desync_twist_onshot;
	//--------------//
	CGroupBox weapongroup;

	CSlider hc_auto;
	CSlider hc_scout;
	CSlider hc_awp;
	CSlider hc_pistol;
	CSlider hc_smg;
	CSlider hc_otr;

	CSlider md_auto;
	CSlider md_scout;
	CSlider md_awp;
	CSlider md_pistol;
	CSlider md_smg;
	CSlider md_otr;
		CCheckBox AntiAimEnable;
	CComboBoxYeti AntiAimPitch;
	CComboBoxYeti AntiAimYaw;
	CComboBoxYeti antiaimtype_stand;
	CComboBoxYeti antiaimtype_move;
	CCheckBox desync_aa_stand;
	CCheckBox desync_aa_move;
	CComboBoxYeti AntiAimYaw3;
	CComboBoxYeti AntiAimYawrun;
	// CComboBoxYeti target_auto;
	CComboBoxYeti target_auto;
	CComboBoxYeti target_scout;
	CComboBoxYeti target_awp;
	CComboBoxYeti target_pistol;
	CComboBoxYeti target_smg;
	CComboBoxYeti target_otr;
	CSlider stand_jitter;
	CSlider move_jitter;
	CCheckBox enemyhp_auto;
	CCheckBox enemyhp_scout;
	CCheckBox enemyhp_awp;
	CCheckBox enemyhp_pistol;

	//--------------//

	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;

	CCheckBox AccuracyAutoWall;
	CSlider AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;

	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider   AccuracyHitchance;
	CCheckBox ResolverEnable;
	CComboBoxYeti resolver;

	CComboBoxYeti preso;

	CCheckBox custom_hitscan;

	CComboBoxYeti OverrideMode;
	CKeyBind bigbaim;
	CKeyBind flip180;
	CCheckBox extrapolation;
	CDropBox prefer_head;
	CCheckBox toggledebug;
	CDropBox debug;
};
class CLegitBotTab : public CTab
{
public:
	void Setup();
	// Master Switch
	CLabel ActiveLabel;
	CLabel ActiveLabel2;
	CLabel ActiveLabel3;
	CLabel ActiveLabel4;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox FakeLagFix;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;

	// Main
	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CCheckBox legitbacktrack;
	CSlider legitbacktrackticks;
	CCheckBox TriggerSmokeCheck;
	CSlider   TriggerDelay;
	CSlider   TriggerBreak;
	CCheckBox TriggerRecoil;
	CCheckBox TriggerHead;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerArms;
	CCheckBox TriggerLegs;

	// Main
	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CComboBoxYeti WeaponMainHitbox;

	// Pistol
	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CComboBoxYeti WeaponPistHitbox;

	// Sniper
	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CComboBoxYeti WeaponSnipHitbox;

	CGroupBox WeaponSMGGroup;
	CSlider   WeaponSMGSpeed;
	CSlider   WeaponSMGFoV;
	CCheckBox WeaponSMGRecoil;
	CComboBoxYeti WeaponSMGHitbox;





};
class CVisualTab : public CTab
{
public:
	void Setup();
	CCheckBox2 Invisible1;
	CCheckBox2 Invisible2;
	CCheckBox2 Invisible3;
	CCheckBox2 Invisible4;
	CCheckBox2 Invisible5;


	CColorSelector HandChamsCol2;
	CColorSelector GunChamsCol2;
	CColorSelector BoxColteam2;
	CColorSelector Skeleton2;
	CColorSelector Skeletonteam2;
	CColorSelector GlowEnemy2;
	CColorSelector GlowTeam2;
	CColorSelector GlowLocal2;

	CColorSelector Skyboxcolor2;
	CColorSelector Weapons2;
	CColorSelector Weaponsteam2;
	CColorSelector Ammo2;
	CColorSelector Ammoteam2;
	CColorSelector Money2; //we don't really need to be able to change the color for all the flags it's just retarded
	CColorSelector Offscreen2;
	CColorSelector ChamsLocal2;
	CColorSelector ChamsEnemyVis2;
	CColorSelector ChamsEnemyNotVis2;
	CColorSelector ChamsTeamVis2;
	CColorSelector ChamsTeamNotVis2;
	CColorSelector Bullettracer_local2;
	CColorSelector Bullettracer_enemy2;
	CColorSelector SleeveChams_col2;
	CColorSelector scoped_c2;
	CColorSelector misc_backtrackchams2;
	CColorSelector misc_lagcomp2;
	CColorSelector misc_lagcompChams2;
	CColorSelector misc_lagcompBones2;
	CColorSelector fakelag_ghost2;


	CColorSelector BoxCol2;
	CLabel ActiveLabel;
	CCheckBox Active;
	CCheckBox visualize_desync;
	CGroupBox OptionsGroup;
	CCheckBox OptionsWeapone;
	CComboBoxYeti OptionsBox;
	CCheckBox OptionsName;
	CCheckBox ChamsEnemyvisible;
	CCheckBox ChamsLocal;
	CCheckBox aa_helper;
	CCheckBox ChamsEnemyinVisible;
	CComboBoxYeti helpermat;
	CCheckBox OffscreenESP;
	CComboBoxYeti chamstype;
	CColorSelector urdadyoufaggot;

	CSlider Glowz_lcl;
	CCheckBox BlendIfScoped;
	CSlider BlendValue;

	CComboBoxYeti OptionsChams;
	CComboBoxYeti OptionsArmor;
	CComboBoxYeti OptionsHealth;
	CComboBoxYeti OptionsWeapon;
	CComboBoxYeti manualaa_type;
	CComboBoxYeti HandCHAMS;
	CComboBoxYeti GunCHAMS;
	CCheckBox LCIndicator;
	CCheckBox FakeDuckIndicator;
	CComboBoxYeti OtherThirdpersonAngle;
	CComboBoxYeti WeaponChams;
	CComboBoxYeti fakelag_ghost;
	CComboBoxYeti visible_chams_type;
	CComboBoxYeti invisible_chams_type;

	CCheckBox SleeveChams;
	CCheckBox Weapons;
	CCheckBox ChamsTeamVis;
	CCheckBox ChamsTeamNoVis;
	CCheckBox OptionsGlow_lcl;
	CCheckBox NoGlowIfScoped;
	CCheckBox NoChamsIfScoped;
	CCheckBox armorbar;
	CCheckBox OptionsInfo;
	CCheckBox BulletTrace;
	CCheckBox BulletTrace_enemy;
	CCheckBox ChamsVisibleOnly;
	CCheckBox Ammo;
	CCheckBox GrenadePrediction;
	CCheckBox LocalPlayerESP;
	CCheckBox CanHit;
	CCheckBox OptionsHelmet;
	CCheckBox NightMode;
	CCheckBox OptionsKit;
	CCheckBox IsScoped;
	CCheckBox HasDefuser;
	CCheckBox GrenadeTrace;
	CCheckBox show_hostage;
	CCheckBox DiscoLights;
	CCheckBox Money;
	CCheckBox OptionsDefuse;
	CCheckBox OptionsDefusing;
	CCheckBox SniperCrosshair;
	CCheckBox OptionsSkeleton;
	CCheckBox NightSky;
	CCheckBox hitbone;
	CCheckBox OptionsAimSpot;
	CCheckBox resoinfo;
	CCheckBox killfeed;
	CCheckBox selfglow;
	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox show_players;
	CCheckBox show_team;
	CCheckBox show_local;
	CKeyBind flashlight;
	CCheckBox FiltersChickens;
	CCheckBox FiltersChicken;
	CGroupBox ChamsGroup;
	CComboBoxYeti asus_type;
	CCheckBox ChamsThruWalls;
	CCheckBox ModulateSkyBox;
	CSlider  GlowZ;



	CColorSelector NameCol2;



	CSlider  team_glow;
	CSlider enemy_blend;
	CSlider enemy_blend_invis;
	CCheckBox ChamsPlayers;
	CCheckBox ChamsEnemyOnly;
	CSlider blend_local;
	CGroupBox OtherGroup;
	CCheckBox OptionsGlow;
	CCheckBox EntityGlow;
	CCheckBox OtherRadar;
	CCheckBox OtherAsusWalls;
	CComboBoxYeti OtherNoHands;
	CCheckBox AAIndicators;
	CCheckBox BulletTracers;
	CComboBoxYeti localmaterial;
	CComboBoxYeti scopemat;
	CSlider transparency;
	CSlider hand_transparency;
	CSlider gun_transparency;
	CSlider sleeve_transparency;
};

class CVisual2Tab : public CTab
{
public:
	void Setup();

	CGroupBox Main1;
	CGroupBox Main2;
	CGroupBox Main3;

	CCheckBox optimize;
	CCheckBox cheatinfo;
	CCheckBox logs;
	CSlider asusamount;
	CCheckBox FiltersNades;
	CCheckBox FiltersC4;
	CCheckBox OptionsCompRank;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersWeaponsBox;
	CComboBoxYeti asustype;
	CColorSelector GlowOtherEnt;
	CColorSelector spreadcrosscol;
	CSlider beamtime;
	CCheckBox watermark;
	CSlider beamsize;
	CCheckBox OtherThirdperson;
	CKeyBind ThirdPersonKeyBind;
	CCheckBox OtherHitmarker;
	CCheckBox WorldColor;
	CCheckBox RemoveZoom;
	CComboBoxYeti sound;
	CCheckBox SpreadCross;
	CSlider SpreadCrossSize;
	CCheckBox DamageIndicator;

	CSlider aspectratiovalue;
	CCheckBox aspectratio;

	CSlider OtherViewmodelFOV;


	CComboBoxYeti SpreadCrosshair;
	CSlider OtherFOV;
	CGroupBox worldgroup;
	CButton colmodupdate;
	CSlider colmod;
	CCheckBox OtherEntityGlow;
	CCheckBox DisablePostProcess;
	CCheckBox customskies2;
	CCheckBox LBYIndicator;
	CComboBoxYeti customskies;
	CCheckBox OtherNoScope;
	CComboBoxYeti OtherCrosshair;
	CComboBoxYeti OtherRecoilCrosshair;
	CSlider flashAlpha;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky;
	CCheckBox OtherNoFlash;
	CCheckBox nosmoke;
	CSlider nosmoke_slider;
	CCheckBox SpecList2;
	CCheckBox AutowallCrosshair;
	CSlider sky_r;
	CSlider sky_g;
	CSlider sky_b;

};
class CColorTab : public CTab
{
public:
	void Setup();
	//you pasted the fucking colorselector but didn't use it... man man freak no baka
	//you have no fucking idea how many errors and how much cancer this gave me
	CComboBoxYeti beam_type;
	CCheckBox CompRank;
	CGroupBox ConfigGroup;
	CComboBoxYeti buybot_primary;
	CComboBoxYeti buybot_secondary;
	CGroupBox OtherOptions;
	CGroupBox OtherOptions2;
	CCheckBox HitmarkerSound;
	CComboBoxYeti NameChanger;
	//CGroupBox OtherOptions2;
	CComboBoxYeti autojump_type;
	CCheckBox ClanTag;
	CCheckBox c_changer;
	CCheckBox AutoDefuse;

	CCheckBox blockbot;
	CDropBox buybot_otr;
	CSlider radar_alpha;
	CCheckBox Radar;
	CSlider owo_slider;
	CComboBoxYeti OtherSafeMode;
	CSlider RadarX;
	CSlider RadarY;
	CCheckBox OtherAutoJump;
	CCheckBox OtherAutoStrafe;
	CColorSelector Menu;
	CComboBoxYeti MenuBar;
	CButton unload;
	CButton fcrash;
	CButton unlockh;
	CGroupBox OtherGroup;
	CKeyBind MenuKey;
	CColorSelector bomb_timer;
	CCheckBox override_viewmodel;
	CSlider offset_y;
	CSlider offset_z;
	CSlider offset_x;
	CComboBoxYeti hitmarker_sound;
	CComboBoxYeti chamcount;
	CComboBoxYeti bonecount;
	CComboBoxYeti asus_type;
	CCheckBox Legitbhop;
	CSlider Legitbhophitchance;
	CSlider Legitbhoprestrictedlimit;
	CSlider Legitbhopmaxhit;
	CSlider Legitbhopminhit;
	CCheckBox DebugLagComp;
	CCheckBox BackTrackBones2;
	CCheckBox BackTrackBones;
	CCheckBox ambient;

	CSlider AmbientRed;
	CSlider AmbientGreen;
	CSlider AmbientBlue;


	CGroupBox gcol;
	CSlider outl_r;
	CSlider outl_g;
	CSlider outl_b;

	CSlider inl_r;
	CSlider inl_g;
	CSlider inl_b;

	CSlider inr_r;
	CSlider inr_g;
	CSlider inr_b;


	CSlider outr_r;
	CSlider outr_g;
	CSlider outr_b;

	CSlider cr;
	CSlider cg;
	CSlider cb;

	CCheckBox experimental_backtrack;
	CSlider quickstop_speed;

};
class CMiscTab : public CTab
{
public:
	void Setup();
	CCheckBox DisablePostProcess;
	CComboBoxYeti airduck_type;
	CCheckBox meme;
	CKeyBind Zstrafe;
	CCheckBox freestandtype;
	CKeyBind OtherCircleButton;
	CCheckBox OtherCircleStrafe;
	CCheckBox CircleStrafe;
	CKeyBind CircleStrafeKey;
	CKeyBind OtherCircle;
	CCheckBox choked_shot;
	CTextField CustomClantag;
	CCheckBox CheatsByPass;
	CCheckBox DebugHitbones;
	CCheckBox aa_helper;
	CCheckBox AutoAccept;
	CSlider custom_pitch;
	CCheckBox SniperCrosshair;
	CSlider CircleAmount;
	CKeyBind OtherSlowMotion;
	CKeyBind plugwalk;
	CComboBoxYeti FakeLagTyp;
	CCheckBox autofw;
	CComboBoxYeti FakeYaw;
	CComboBoxYeti FakeYaw2;
	CComboBoxYeti FakeYaw3;
	CCheckBox do_freestanding;
	CKeyBind fake_stand_key;
	CGroupBox AntiAimGroup;
	CGroupBox DesyncGroup;
	CLabel aatext;
	CComboBoxYeti antiaimtype_stand;
	CComboBoxYeti antiaimtype_move;
	CCheckBox desync_aa_stand;
	CCheckBox desync_aa_move;

	CSlider staticr;
	CSlider staticf;
	CSlider ThirdPersonVal;
	CComboBoxYeti AntiAimYaw3;
	CCheckBox OtherTeamChat;
	CSlider ClanTagSpeed;
	CSlider	  OtherChatDelay;
	CCheckBox AutoPistol;
	CCheckBox ClanTag;
	CDropBox killsay;
	CKeyBind  OtherAirStuck;
	CCheckBox OtherSpectators;



	CSlider ThirdPersonValue;
	CCheckBox standing_desync;
	CCheckBox moving_desync;
	CCheckBox air_desync;
	CSlider twitchf;
	CSlider spinf;
	CSlider spinspeed;
	CCheckBox squaredance;
	CComboBoxYeti antilby;
	CCheckBox pitch_up;
	CCheckBox experimental;
	CSlider BreakLBYDelta;
	CSlider BreakLBYDelta2;
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CCheckBox PingSpike;
	CKeyBind LagSpikeKey;
	CComboBoxYeti KnifeModel;
	CButton   SkinApply;
	CCheckBox SkinEnable;
	CCheckBox fl_onshot;
	CCheckBox antilby2;
	CSlider FakeLagChoke2;
	CKeyBind lagkey;
	CComboBoxYeti ConfigBox;
	CGroupBox ConfigGroup;

	CSlider pingspike_val;
	CKeyBind pingspike_key;

};


class CPlayersTab : public CTab
{
public:
	void Setup();
	CListBox PlayerListControl;

	CGroupBox PlayerSettingsGroup;
	CGroupBox PlayerSettingsGroup2;
	CCheckBox PlayerPriority;
	CCheckBox PlayerFriendly;
	CCheckBox PlayerPreferBody;
	CCheckBox PlayerForcePitch;
	CComboBox PlayerForcePitch_Pitch;
	CCheckBox PlayerForceYaw;
	CComboBox PlayerForceYaw_Yaw;
};

class CSkinTab : public CTab
{
public:
	void Setup();
	//--------------------------//
	CGroupBox knifegroup;
	CGroupBoxInvisible ColorsGroup;
	CGroupBox snipergroup;
	CLabel Msg;
	//--------------------------//
	CComboBoxYeti t_knife_index;
	CComboBoxYeti ct_knife_index;

	CButton SkinApply;
	CCheckBox enableskins;
	//--------------------------//
	CSlider t_knife_wear;
	CSlider t_sniperSCAR_wear;
	CSlider t_sniperAWP_wear;

	//--------------------------//
	CComboBoxYeti t_knife_skin_id;
	CComboBoxYeti t_sniperAWP_skin_id;
	CComboBoxYeti t_sniperSCAR_skin_id;

	CCheckBox skinwindow;
	CCheckBox plistwindow;
	CComboBoxYeti logotype;
	CCheckBox espwindow;

	CListBox ConfigListBox;
	CButton SaveConfig;
	CButton RemoveConfig;
	CTextField NewConfigName;
	CButton LoadConfig;
	CButton AddConfig;

};

class mirror_window : public CWindow
{
public:
	void Setup();
	CAimbotTab aimbot_tab;
	CLegitBotTab LegitBotTab;
	CVisualTab visuals_tab;
	CVisual2Tab visuals2_tab;
	CMiscTab MiscTab;
	CSkinTab SkinTab;
	CPlayersTab PlayersTab;
	
	CColorTab ColorsTab;
	CButton   SkinApply;




	CButton SaveButton1;
	CButton test2;
	CButton LoadButton1;
	CButton SaveButton;
	CButton LoadButton;
	CButton UnloadButton;
	CButton PanicButton;
	CButton ThirdButton;
	CButton ByPass;
	CButton FirstButton;
	CComboBox ConfigBox;
};
namespace options
{
	void SetupMenu();
	void DoUIFrame();
	extern mirror_window menu;
};
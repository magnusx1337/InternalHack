#include "SkinChanger.h"
#include "Hacks.h"
#include "Menu.h"

SkinChanger skinchanger;
std::unordered_map<int, SkinStruct>  m_skins;
std::unordered_map<int, const char*> g_ViewModelCFG;
std::unordered_map<const char*, const char*> g_KillIconCfg;

#define iKnife options::menu.SkinTab.t_knife_index.GetIndex() 
void updatestuff2()
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


int SkinChanger::get_skin_id_knife()
{
	int id = options::menu.SkinTab.t_knife_skin_id.GetIndex();

	if (id != 0)
	{
		if (id == 1)
		{
			return 415;
		}

		if (id == 2)
		{
			return 416;
		}

		if (id == 3)
		{
			return 417;
		}

		if (id == 4)
		{
			return 420;
		}

		if (id == 5)
		{
			return 38;
		}

		if (id == 6)
		{
			return 413;
		}

		if (id == 7)
		{
			return 570;
		}

		if (id == 8)
		{
			return 568;
		}

		if (id == 9)
		{
			return 59;
		}

		if (id == 10)
		{
			return 102;
		}

		if (id == 11)
		{
			return 98;
		}

		if (id == 12)
		{
			return 562;
		}
	}
}

void SkinChanger::get_skin_id_sniperAWP()
{
	int id = options::menu.SkinTab.t_sniperAWP_skin_id.GetIndex();

	if (id != 0)
	{
		if (id == 1)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 344; // dragon lore
		}

		if (id == 2)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 84; // pink ddpat
		}

		if (id == 3)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 279; // asiimov
		}

		if (id == 4)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 259; // redline
		}

		if (id == 5)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 446; // medusa
		}

		if (id == 6)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 479; // hyper beast
		}

		if (id == 7)
		{
			m_skins[WEAPON_AWP].nFallbackPaintKit = 102; // whiteout
		}
	}
}


void SkinChanger::get_skin_id_sniperScar()
{
	int id = options::menu.SkinTab.t_sniperSCAR_skin_id.GetIndex();

	if (id != 0)
	{
		if (id == 1)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 12; // crimson web
		}

		if (id == 2)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 165; // splash jam
		}

		if (id == 3)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 196; // emerald 
		}

		if (id == 4)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 391; // cardiac
		}

		if (id == 5)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 312; // cyrex
		}

		if (id == 6)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 102; // whiteout
		}

		if (id == 7)
		{
			m_skins[WEAPON_SCAR20].nFallbackPaintKit = 269; // the fuschia is now
		}

		m_skins[WEAPON_SCAR20].nFallbackStatTrak = 666;
	//	m_skins[WEAPON_SCAR20].flFallbackWear ~ 0.0001;
	}

}

#define iKnifePaintkit get_skin_id_knife()//listbox with knife paintkits tigertooth,doppler,fade etc.//combobox for the knifemodel, you can add the new ones if you wish to as well
#define flKnifeWear options::menu.SkinTab.t_knife_wear.GetValue() / 1000 //slider for the wear
#define iKnifeQuality 1 //combo for quality

void SkinChanger::update_settings()
{
	if (!interfaces::engine->IsConnected() || !interfaces::engine->IsInGame())
		return;
	auto m_local = hackManager.pLocal();
	if (!m_local)
		return;
	if (!m_local->IsAlive())
		return;
	if (!m_local->GetWeapon2())
		return;
	static int last_model;
	static int last_paintkit;
	static float last_wear;
	static int last_quality;
	if (last_paintkit != iKnifePaintkit)
	{
		m_skins[WEAPON_KNIFE].nFallbackPaintKit = iKnifePaintkit;
		m_skins[WEAPON_KNIFE_T].nFallbackPaintKit = iKnifePaintkit;
		last_paintkit = iKnifePaintkit;
	}
	
	if (scar20_paint != m_skins[WEAPON_SCAR20].nFallbackPaintKit)
	{
		get_skin_id_sniperScar();
		scar20_paint = m_skins[WEAPON_SCAR20].nFallbackPaintKit;
	}

	if (awp_paint != m_skins[WEAPON_AWP].nFallbackPaintKit)
	{
		get_skin_id_sniperAWP();
		awp_paint = m_skins[WEAPON_AWP].nFallbackPaintKit;
	}
	
	if (last_model != iKnife)
	{
		std::vector<char*> icons;
		icons.push_back("bayonet");
		icons.push_back("knife_m9_bayonet");
		icons.push_back("knife_butterfly");
		icons.push_back("knife_flip");
		icons.push_back("knife_gut");
		icons.push_back("knife_karambit");
		icons.push_back("knife_tactical");
		icons.push_back("knife_falchion");
		icons.push_back("knife_push");
		icons.push_back("knife_survival_bowie");
		icons.push_back("knife_stiletto");
		g_KillIconCfg["knife_default_ct"] = icons[iKnife - 1];
		g_KillIconCfg["knife_t"] = icons[iKnife - 1];
		int nOriginalKnifeCT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
		int nOriginalKnifeT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		std::vector<char*> models;
		models.push_back("models/weapons/v_knife_bayonet.mdl");
		models.push_back("models/weapons/v_knife_m9_bay.mdl");
		models.push_back("models/weapons/v_knife_butterfly.mdl");
		models.push_back("models/weapons/v_knife_flip.mdl");
		models.push_back("models/weapons/v_knife_gut.mdl");
		models.push_back("models/weapons/v_knife_karam.mdl");
		models.push_back("models/weapons/v_knife_tactical.mdl");
		models.push_back("models/weapons/v_knife_falchion_advanced.mdl");
		models.push_back("models/weapons/v_knife_push.mdl");
		models.push_back("models/weapons/v_knife_survival_bowie.mdl");
		models.push_back("models/weapons/v_knife_stiletto.mdl");
		g_ViewModelCFG[nOriginalKnifeCT] = models[iKnife - 1];
		g_ViewModelCFG[nOriginalKnifeT] = models[iKnife - 1];

		switch (iKnife)
		{
		case 1:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_BAYONET;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_BAYONET;
		}
		break;

		case 2:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_M9_BAYONET;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_M9_BAYONET;
		}
		break;

		case 3:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_BUTTERFLY;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_BUTTERFLY;
		}
		break;

		case 4:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_FLIP;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_FLIP;
		}
		break;

		case 5:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_GUT;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_GUT;
		}
		break;

		case 6:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_KARAMBIT;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_KARAMBIT;
		}
		break;

		case 7:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_TACTICAL;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_TACTICAL;
		}
		break;

		case 8:
		{
			m_skins[WEAPON_KNIFE].nItemDefinitionIndex = WEAPON_KNIFE_FALCHION;
			m_skins[WEAPON_KNIFE_T].nItemDefinitionIndex = WEAPON_KNIFE_FALCHION;
		}
		break;
		}

		last_model = iKnife;
		if (last_wear != flKnifeWear)
		{
			m_skins[WEAPON_KNIFE].flFallbackWear = flKnifeWear;
			m_skins[WEAPON_KNIFE_T].flFallbackWear = flKnifeWear;
			last_wear = flKnifeWear;
		}
		if (last_quality != iKnifeQuality && iKnifeQuality)
		{
			std::vector<int> qualities;
			qualities.push_back(0);
			qualities.push_back(1);
			qualities.push_back(2);
			qualities.push_back(3);
			qualities.push_back(5);
			qualities.push_back(6);
			qualities.push_back(7);
			qualities.push_back(8);
			qualities.push_back(9);
			qualities.push_back(10);
			qualities.push_back(12);
			m_skins[WEAPON_KNIFE].nEntityQuality = qualities[iKnifeQuality];
			m_skins[WEAPON_KNIFE_T].nEntityQuality = qualities[iKnifeQuality];
			interfaces::engine->ClientCmd_Unrestricted("echo [gamsens_sdk] force updating materials...");
			updatestuff2();
			last_quality = iKnifeQuality;
		}
		skinchanger.set_viewmodel();
	}

}
void SkinChanger::set_skins()
{
	m_skins[WEAPON_SCAR20].nFallbackPaintKit = 196;
	m_skins[WEAPON_AWP].nFallbackPaintKit = 279;
	m_skins[WEAPON_AK47].nFallbackPaintKit = 707;
	m_skins[WEAPON_M4A1].nFallbackPaintKit = 695;
	m_skins[WEAPON_M4A1_SILENCER].nFallbackPaintKit = 714;
	m_skins[WEAPON_ELITE].nFallbackPaintKit = 396;
	m_skins[WEAPON_FIVESEVEN].nFallbackPaintKit = 464;
	m_skins[WEAPON_FAMAS].nFallbackPaintKit = 604;
	m_skins[WEAPON_GALILAR].nFallbackPaintKit = 478;
	m_skins[WEAPON_M249].nFallbackPaintKit = 547;
	m_skins[WEAPON_MAC10].nFallbackPaintKit = 246;
	m_skins[WEAPON_P90].nFallbackPaintKit = 359;
	m_skins[WEAPON_UMP45].nFallbackPaintKit = 436;
	m_skins[WEAPON_XM1014].nFallbackPaintKit = 314;
	m_skins[WEAPON_BIZON].nFallbackPaintKit = 508;
	m_skins[WEAPON_MAG7].nFallbackPaintKit = 462;
	m_skins[WEAPON_NEGEV].nFallbackPaintKit = 369;
	m_skins[WEAPON_SAWEDOFF].nFallbackPaintKit = 390;
	m_skins[WEAPON_TEC9].nFallbackPaintKit = 459;
	m_skins[WEAPON_HKP2000].nFallbackPaintKit = 246;
	m_skins[WEAPON_MP7].nFallbackPaintKit = 481;
	m_skins[WEAPON_MP9].nFallbackPaintKit = 482;
	m_skins[WEAPON_NOVA].nFallbackPaintKit = 158;
	m_skins[WEAPON_DEAGLE].nFallbackPaintKit = 37;
	m_skins[WEAPON_DEAGLE].nFallbackStatTrak = 420;
	m_skins[WEAPON_P250].nFallbackPaintKit = 388;
	m_skins[WEAPON_REVOLVER].nFallbackPaintKit = 102;
	m_skins[WEAPON_REVOLVER].nFallbackStatTrak = 666;
	m_skins[WEAPON_GLOCK].nFallbackPaintKit = 38;
	m_skins[WEAPON_G3SG1].nFallbackPaintKit = 511;
	m_skins[WEAPON_G3SG1].nFallbackStatTrak = 1337;
	m_skins[WEAPON_USP_SILENCER].nFallbackPaintKit = 504;
	m_skins[WEAPON_USP_SILENCER].nFallbackStatTrak = 666;
	m_skins[WEAPON_SCAR20].nFallbackPaintKit = 269;
	m_skins[WEAPON_SSG08].nFallbackPaintKit = 269;
	m_skins[WEAPON_SSG08].flFallbackWear = 0.0001;
	m_skins[WEAPON_SG556].nFallbackPaintKit = 39;
	m_skins[WEAPON_AUG].nFallbackPaintKit = 455;
	
	interfaces::engine->ClientCmd_Unrestricted("echo [gamsens_sdk] force updating materials...");
	updatestuff2();
}
void SkinChanger::set_viewmodel()
{
	bool has_model = false;
	if (iKnife)
		has_model = true;
	if (!has_model)
	{
		int nOriginalKnifeCT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
		int nOriginalKnifeT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		g_ViewModelCFG[nOriginalKnifeCT] = "models/weapons/v_knife_default_ct.mdl";
		g_ViewModelCFG[nOriginalKnifeT] = "models/weapons/v_knife_default_t.mdl";
		interfaces::engine->ClientCmd_Unrestricted("echo [gamsens_sdk] force updating materials...");
		updatestuff2();
	}
	else
	{
		int nOriginalKnifeCT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_ct.mdl");
		int nOriginalKnifeT = interfaces::model_info->GetModelIndex("models/weapons/v_knife_default_t.mdl");
		std::vector<char*> models;
		models.push_back("models/weapons/v_knife_bayonet.mdl");
		models.push_back("models/weapons/v_knife_m9_bay.mdl");
		models.push_back("models/weapons/v_knife_butterfly.mdl");
		models.push_back("models/weapons/v_knife_flip.mdl");
		models.push_back("models/weapons/v_knife_gut.mdl");
		models.push_back("models/weapons/v_knife_karam.mdl");
		models.push_back("models/weapons/v_knife_tactical.mdl");
		models.push_back("models/weapons/v_knife_falchion_advanced.mdl");
		models.push_back("models/weapons/v_knife_push.mdl");
		models.push_back("models/weapons/v_knife_survival_bowie.mdl");
		models.push_back("models/weapons/v_knife_stiletto.mdl");
		g_ViewModelCFG[nOriginalKnifeCT] = models[iKnife - 1];
		g_ViewModelCFG[nOriginalKnifeT] = models[iKnife - 1];
	}
}
bool SkinChanger::apply_skins(CBaseAttributableItem* pWeapon, int nWeaponIndex)
{
	if (m_skins.find(nWeaponIndex) == m_skins.end())
		return false;

	*pWeapon->GetFallbackPaintKit() = m_skins[nWeaponIndex].nFallbackPaintKit;
	*pWeapon->GetEntityQuality() = m_skins[nWeaponIndex].nEntityQuality;
	*pWeapon->GetFallbackSeed() = m_skins[nWeaponIndex].nFallbackSeed;
	*pWeapon->GetFallbackStatTrak() = m_skins[nWeaponIndex].nFallbackStatTrak;
	*pWeapon->GetFallbackWear() = m_skins[nWeaponIndex].flFallbackWear;
	if (m_skins[nWeaponIndex].nItemDefinitionIndex)
		*pWeapon->GetItemDefinitionIndex() = m_skins[nWeaponIndex].nItemDefinitionIndex;
	if (m_skins[nWeaponIndex].szWeaponName) {
		sprintf_s(pWeapon->GetCustomName(), 32, "%s", m_skins[nWeaponIndex].szWeaponName);
	}
	*pWeapon->GetItemIDHigh() = -1;
	return true;
}
bool SkinChanger::apply_viewmodel(IClientEntity* pLocal, CBaseAttributableItem* pWeapon, int nWeaponIndex)
{
	CBaseViewModel* pViewModel = (CBaseViewModel*)interfaces::ent_list->GetClientEntityFromHandle(*(HANDLE*)((DWORD)pLocal + 0x32F8));
	if (!pViewModel)
		return false;
	DWORD hViewModelWeapon = pViewModel->GetWeapon();
	CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)interfaces::ent_list->GetClientEntityFromHandle((HANDLE)hViewModelWeapon);
	if (pViewModelWeapon != pWeapon)
		return false;
	int nViewModelIndex = pViewModel->GetModelIndex();
	if (g_ViewModelCFG.find(nViewModelIndex) == g_ViewModelCFG.end())
		return false;
	pViewModel->SetWeaponModel(g_ViewModelCFG[nViewModelIndex], pWeapon);
	return true;
}
bool SkinChanger::apply_killcon(IGameEvent* pEvent)
{
	int nUserID = pEvent->GetInt("attacker");
	if (!nUserID)
		return false;
	if (interfaces::engine->GetPlayerForUserID(nUserID) != interfaces::engine->GetLocalPlayer())
		return false;
	bool head = pEvent->GetBool("headshot");
	bool hitgroup = pEvent->GetInt("hitgroup");
	const char* szWeapon = pEvent->GetString("weapon");
	for (auto ReplacementIcon : g_KillIconCfg)
	{
		if (!strcmp(szWeapon, ReplacementIcon.first))
		{
			pEvent->SetString("weapon", ReplacementIcon.second);
			break;
		}
	}
	return true;
}

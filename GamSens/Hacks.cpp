#define _CRT_SECURE_NO_WARNINGS

#include "Hacks.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "autoaccept.h"
#include "ESP.h"
#include "Visuals.h"
#include "RageBot.h"
#include "legit.h"
#include "MiscHacks.h"

CEsp Esp;
CVisuals Visuals;
CMiscHacks MiscHacks;
CAimbot RageBot;
clegit LegitBot;

void Hacks::SetupHacks()
{
	Esp.Init();
	Esp.Draw();
	Visuals.Init();
	MiscHacks.Init();
	RageBot.Init();
	LegitBot.Init();

	hackManager.RegisterHack(&Esp);
	hackManager.RegisterHack(&Visuals);
	hackManager.RegisterHack(&MiscHacks);
	hackManager.RegisterHack(&RageBot);
	hackManager.RegisterHack(&LegitBot);

	hackManager.Ready();
}

RECT GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	interfaces::engine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}
void SpecList2()
{
	IClientEntity* pLocal = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());

	RECT Viewport = { 0, 0, 0, 0 };
	RECT scrn = GetViewport();
	int ayy = 0;
	int i = 0; i < interfaces::ent_list->GetHighestEntityIndex(); i++;
	IClientEntity* pEntity = interfaces::ent_list->get_client_entity(i);
	HANDLE obs = pEntity->GetObserverTargetHandle();
	Render::rect(scrn.right - 269, (scrn.bottom / 2) - 18 + 2, 264, (16 * ayy) + 20, Color(45, 45, 45, 255));
	Render::outlineyeti(scrn.right - 269, (scrn.bottom / 2) - 18 + 2, 264, (16 * ayy) + 20, Color(1, 1, 1, 255));
	Render::Text(scrn.right - 265 + 90, (scrn.bottom / 2) - 14, Color(255, 255, 255, 255), Render::Fonts::MenuText, "Spectator List");

	// Loop through all active entitys
	for (int i = 0; i < interfaces::ent_list->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity* pEntity = interfaces::ent_list->get_client_entity(i);
		player_info_t pinfo;

		// The entity isn't some laggy peice of shit or something
		if (pEntity && pEntity != pLocal)
		{
			if (interfaces::engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
			{
				HANDLE obs = pEntity->GetObserverTargetHandle();

				if (obs)
				{
					IClientEntity* pTarget = interfaces::ent_list->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{

						if (interfaces::engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{

							char buf[255]; sprintf_s(buf, "%s -> %s", pinfo.name, pinfo2.name);
							RECT TextSize = Render::GetTextSize(Render::Fonts::MenuText, buf);

							Render::rect(scrn.right - 269, (scrn.bottom / 2) + (16 * ayy) + 1, 264, 17, Color(45, 45, 45, 255));

							Render::rect(scrn.right - 267, (scrn.bottom / 2) + (16 * ayy), 260, 16, Color(8, 8, 8, 255));

							Render::TEXTUNICODE(scrn.right - TextSize.right - 4 - 7, (scrn.bottom / 2) + (16 * ayy), buf, Render::Fonts::MenuText, pTarget->GetIndex() == pLocal->GetIndex() ? Color(255, 190, 1, 255) : Color(255, 255, 255, 255));
							ayy++;
						}
					}
				}
			}
		}

	}

}


void Hacks::DrawHacks()
{


	if (!options::menu.visuals_tab.Active.GetState())
		return;


//	if (options::menu.visuals2_tab.CompRank.GetState() && GUI.GetKeyState(VK_TAB))
//	{
	//	GameUtils::ServerRankRevealAll();
	//}

	if (options::menu.visuals2_tab.SpecList2.GetState())
		SpecList2();


	hackManager.Draw();
		
}

void Hacks::MoveHacks(CUserCmd * pCmd, bool & bSendPacket)
{
	Vector origView = pCmd->viewangles;
	IClientEntity *pLocal = hackManager.pLocal();
	hackManager.Move(pCmd, bSendPacket);

}

HackManager hackManager;

void HackManager::RegisterHack(CHack* hake)
{
	Hacks.push_back(hake);
	hake->Init();
}

void HackManager::Draw()
{
	if (!IsReady)
		return;

	pLocalInstance = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Draw();
	}
}

void HackManager::Move(CUserCmd *pCmd,bool &bSendPacket)
{
	if (!IsReady)
		return;

	pLocalInstance = interfaces::ent_list->get_client_entity(interfaces::engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Move(pCmd,bSendPacket); 
	}
}

IClientEntity* HackManager::pLocal()
{
	return pLocalInstance;
}

void HackManager::Ready()
{
	IsReady = true;
}
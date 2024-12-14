
#include <iostream>
#include <thread>
#include "vector.h"
#include "../menu/menu.h"
#include "memory.h"

int ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
int ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;


Vector3 RCSScale = { 0.5f,0.5f };
int RCSBullet = 1;


void Reader::ThreadLoop()
{
	// get client
	if (!reader.client)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(15));

		reader.client = mem.GetBase("client.dll");
		std::cout << "client.dll " << std::hex << reader.client << std::endl;
	}
}


void Reader::Loopcheat() // loop das funcôes criadas no .h e programadas no cpp todas menos o esp que tem que renderizar no Render
{

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(6));
		cheat.Aimbot();
		

	}
}


void Cheat::Aimbot()
{
	//lista de entidades
	uintptr_t entitylist = mem.Read<uintptr_t>(reader.client + offsets::dwEntityList);// lista de entidades na partida
	//if (entitylist == false)
		//std::cout << "entity list not found";

	uintptr_t localplayerpawn = mem.Read<uintptr_t>(reader.client + offsets::dwLocalPlayerPawn); // pare ver o localplayer do player
	//if (localplayerpawn == false)
		//std::cout << "pawn not found";

	uintptr_t listEntry = mem.Read<uintptr_t>(entitylist + 0x10); // list entry para usar no percorrimento
	uintptr_t localteam = mem.Read<uintptr_t>(localplayerpawn + offsets::m_iTeamNum); // para ver se o player e do seu time ou n 
	Vector3 localoriginplayer = mem.Read<Vector3>(localplayerpawn + offsets::m_vOldOrigin);// origem antiga do jogador 
	Vector3 localviewoffset	= mem.Read<Vector3>(localplayerpawn + offsets::m_vecViewOffset); //para ver a posicao do olho do jogador

	Vector3 localeyeview = localoriginplayer + localviewoffset;

	float closest_distance = -1;
	Vector3 enemypos;

	//mouse position
	float TargetX = 0.f; //or int mouse
	float TargetY = 0.f;

	//distance for comparetion para poder escolher o player com a melhor distancia
	//para usar a distancia para renderizar esp/ ou para o aimbot
	Vector3 bestTarget;
	double distance = 1000;  //distancia alta para poder comparar


	for (int i = 0; i < 32; i++)
	{

		if (listEntry == 0)
			continue;


		uintptr_t currentcontroler = mem.Read<uintptr_t>(static_cast<uintptr_t>(listEntry) + static_cast<uintptr_t>(0x78));//para armazenar o controlador de entidades
		if (currentcontroler == 0);
			continue;

		uintptr_t currentcontrolerpawn = mem.Read<uintptr_t>(currentcontroler + offsets::m_hPawn); //verificar todas as entidades
		if (currentcontrolerpawn == 0)
			continue;

		uintptr_t listEntry2 = mem.Read<uintptr_t>(entitylist + 0x8 * ((currentcontrolerpawn & 0x7FFF) >> 9) + 0x10);//percorrimento de entidades

		uintptr_t entitypawn = mem.Read<uintptr_t>(listEntry2 + 0x78 * (currentcontrolerpawn & 0x1FF));
		if (entitypawn == 0);
			continue;

			Vector3 entityeyepos = mem.Read<Vector3>(entitypawn + offsets::m_vOldOrigin) +
				mem.Read<Vector3>(entitypawn + offsets::m_vecViewOffset);

			uint32_t health = mem.Read<uint32_t>(entitypawn + offsets::m_iHealth);
			uint8_t team = mem.Read<uint8_t>(entitypawn + offsets::m_iTeamNum);
			int lifeState = mem.Read<int>(entitypawn + offsets::m_lifeState);


			if (lifeState != 256)
				continue;


			if (team == localteam)
				continue;

			//visible check
			bool spottedState = mem.Read<bool>(entitypawn + (offsets::m_entitySpottedState + offsets::m_bSpotted)); // se a entidade foi avistada e se eu avistei ela

			if (!spottedState)
				continue;


	}

	Vector3 ScreenPos = bestTarget;


	
	if (distance > g.Aimfov)
		return;



	if (ScreenPos.x != ScreenCenterX)
	{
		TargetX = (ScreenPos.x > ScreenCenterX) ? -(ScreenCenterX - ScreenPos.x) : ScreenPos.x - ScreenCenterX;
		TargetX /= g.AimSmooth != 0.0f ? g.AimSmooth : g.AimSmooth;
		TargetX = (TargetX + ScreenCenterX > ScreenCenterX * 2 || TargetX + ScreenCenterX < 0) ? 0 : TargetX;
	}

	if (ScreenPos.y != 0)
	{
		if (ScreenPos.y != ScreenCenterY)
		{
			TargetY = (ScreenPos.y > ScreenCenterY) ? -(ScreenCenterY - ScreenPos.y) : ScreenPos.y - ScreenCenterY;
			TargetY /= g.AimSmooth != 0.0f ? g.AimSmooth : g.AimSmooth;
			TargetY = (TargetY + ScreenCenterY > ScreenCenterY * 2 || TargetY + ScreenCenterY < 0) ? 0 : TargetY;
		}
	}


	if (GetAsyncKeyState(VK_XBUTTON2))
	{
		if (g.AimBot == true)
		{
			mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);
		}
	}
	

}



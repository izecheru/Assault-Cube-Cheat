#pragma once
namespace offsets
{
	constexpr auto ac_localPlayer = 0x187C0C;
	// -------------PLAYER VARIABLES-------------
	constexpr auto ac_name = 0x205;		//char
	constexpr auto ac_ammoMTP = 0x140;//int
	constexpr auto ac_magSizeMTP = 0x11C;//int
	constexpr auto ac_ammoMK = 0x012c;	//int
	constexpr auto ac_health = 0xEC;	//int
	constexpr auto ac_frags = 0x1DC;	//int
	constexpr auto ac_grenades = 0x0144;	//int
	constexpr auto ac_forceAttack = 0x204; //bool
	// -------------PLAYER VARIABLES-------------
	//0x124 mag sizew
	//-------------CHAT-------------
	constexpr auto ac_chat = 0x16C351; //char
	//-------------CHAT-------------

	constexpr auto ac_entityList = 0x187C10;//int*
	//might actually be max players but since the game
	//fills the lobby i dont currently know this
	constexpr auto ac_playerNumber = 0x187C18;//int

	//since the pitch is up and down we also have
	//negative values so must not do uint
	constexpr auto ac_pitch = 0x0038;//float
	constexpr auto ac_yaw = 0x0034;//float
	constexpr auto ac_roll = 0;

	//-------------------------COORDS-------------------------------\\

	/*
	after more research i found some values
	that after changing them i teleport ac might have some console stuff
	what i mean is that i may have found some
	printed values somewhere in the game, 
	not the real ones that are phisically the player's location representation 
	*/

	constexpr auto ac_x = 0x0028;//float
	constexpr auto ac_y = 0x002C;//float
	constexpr auto ac_z = 0x0030;//float

	constexpr auto ac_weird_x = 0x0004;
	constexpr auto ac_weird_y = 0x0008;
	constexpr auto ac_weird_z = 0x000C;
	//-------------------------COORDS-------------------------------
}
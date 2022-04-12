#pragma once
#include <Windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include "../headers/localPlayer.h"

// some retarded ideea that came to my mind
// basically it turns your head in a random
// direction by assigning a rand int value
// to the local player's pitch and yaw
namespace lookAway
{
	void Look(LocalPlayer* player)
	{
		srand(time(NULL));
		float yawTo = (float)(rand() % 100 + 1);
		float pitchTo = (float)(rand() % 100 + 1);

		for (int i = 0; i < yawTo; i++)
		{
			player->yaw +=1.0;
		}

		for (int i = 0; i < pitchTo; i++)
		{
			player->pitch += 1.0;
		}
	}
}
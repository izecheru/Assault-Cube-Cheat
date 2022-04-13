#pragma once
#include"lookAway.h"

// some retarded ideea that came to my mind
// basically it turns your head in a random
// direction by assigning a rand int value
// to the local player's pitch and yaw

void lookAway::Look(PlayerEntity* player)
{
	srand(time(NULL));
	float yawTo = (float)(rand() % 100 + 1);
	float pitchTo = (float)(rand() % 100 + 1);
	player->yaw = yawTo;
	player->pitch = pitchTo;
}

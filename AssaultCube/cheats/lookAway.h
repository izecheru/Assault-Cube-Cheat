#pragma once
#include <Windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "../headers/entity.h"

// some retarded ideea that came to my mind
// basically it turns your head in a random
// direction by assigning a rand int value
// to the local player's pitch and yaw
namespace lookAway
{
	void Look(PlayerEntity* player);
}
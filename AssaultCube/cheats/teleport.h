#pragma once
#include<iostream>

void TeleportTo(float* teleportLocation, float* x, float* y, float* z)
{//coords are x y z in this order
	*x = teleportLocation[0];
	*y = teleportLocation[1];
	*z = teleportLocation[2];
	std::cout << "\nteleported to saved location [" << *x << ", " << *y << ", " << *z << "]\n";
}

void SaveLocation(float* teleportLocation, float* x, float* y, float* z)
{//coords are x y z in this order
	teleportLocation[0] = *x;
	teleportLocation[1] = *y;
	teleportLocation[2] = *z;
	std::cout << "\ncoords saved [" << *x << ", " << *y << ", " << *z << "]\n";
}


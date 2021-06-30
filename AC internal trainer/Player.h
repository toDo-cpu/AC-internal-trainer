#pragma once

#include "memo_tools.h"
#include "Vec3.h"
#include "offsets.h"


class PlayerEntity {
	public:
		
		PlayerEntity(uintptr_t playerBaseAdress)
		{
			this->entityBaseAdress = playerBaseAdress;

			this->health = (int*)FindAdressWithOffsets(playerBaseAdress, healthOffsets);
			this->currentAmmo = (int*)FindAdressWithOffsets(playerBaseAdress, ammoOffsets);

			this->BodyPos = ResolveCoordStruct(BodyCoordXOffsets, BodyCoordYOffsets, BodyCoordZOffsets, playerBaseAdress);
			this->HeadPos = ResolveCoordStruct(HeadCoordXOffsets, HeadCoordYOffsets, HeadCoordZOffsets	, playerBaseAdress);

			this->playerName = (char*)FindAdressWithOffsets(playerBaseAdress, nameOffset);
		}

		uintptr_t entityBaseAdress;

		char* playerName;

		int* health;
		int* currentAmmo;
		
		//Positions
		Vec3 HeadPos;
		Vec3 BodyPos;

};
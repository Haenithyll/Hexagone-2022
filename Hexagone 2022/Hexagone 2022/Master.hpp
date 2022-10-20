#pragma once
#include "Character.hpp"
#include "Activist.hpp"

class Master : Character
{
public:
	void DeliverMessages(Character* activist);
	virtual void Move() override;
};


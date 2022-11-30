#include "Actor.h"
#include "StudentWorld.h"

using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
void Actor::doSomething()
{
}

Actor::~Actor()
{
	// cout << "Actor was destroyed" << endl;
}

Ice::~Ice()
{
	// cout << "Ice was destroyed" << endl;
}

Iceman::~Iceman()
{
	// cout << "Iceman was destroyed" << endl;
}

Boulder::~Boulder()
{

}

Oil::~Oil()
{

}

Gold_Nugget::~Gold_Nugget()
{

}

Sonar_Kit::~Sonar_Kit()
{

}

Water_Pool::~Water_Pool()
{

}

Squirt::~Squirt()
{

}



StudentWorld* Actor::getWorld()
{
	return Sw;
}

bool Actor::living()
{
	return is_alive;
}

void Actor::kill()
{
	is_alive = false;
}
void Actor::revive()
{
	is_alive = true;
}

int Iceman::getGold()
{
	return gold_owned;
}

int Iceman::getSonarCharges()
{
	return sonar_charges;
}

int Sonar_Kit::getTick()
{
	return this->tick;
}

int Regular_Protester::getTick()
{
	return this->tick;
};

int Iceman::getWater()
{
	return this->water_charges;
}

int Iceman::getOilNeeded()
{
	return this->oil_needed;
}

void Iceman::decOil()
{
	this->oil_needed--;
}

void Iceman::setOilNeeded(int oilNeededValue)
{
	oil_needed = oilNeededValue;
}

void Regular_Protester::incTick()
{
	this->tick++;
}


void Sonar_Kit::incTick()
{
	this->tick++;
}

void Regular_Protester::resetTick()
{
	this->tick = 0;
}


void Sonar_Kit::resetTick()
{
	this->tick = 0;
}

void Water_Pool::resetTick()
{
	this->tick = 0;
}

void Water_Pool::incTick()
{
	this->tick++;
}
int Water_Pool::getTick()
{
	return tick;
}

bool Regular_Protester::isGivingUp()
{
	return GivingUp;
}
void Regular_Protester::makeHimGiveUp()
{
	GivingUp = true;
}

void Regular_Protester::decreaseHP(int HPtoDecrease)
{
	HP -= HPtoDecrease;
}

int Regular_Protester::getHP()
{
	return HP;
}

void Iceman::increaseWater()
{
	this->water_charges += 5;
}


void Iceman::increaseGold()
{
	this->gold_owned++;
}

void Iceman::increaseSonarCharges()
{
	this->sonar_charges++;
}

bool Regular_Protester::isAnnoyed()
{
	return Annoyed;
}
void Regular_Protester::Annoy()
{
	Annoyed = true;
}

void Regular_Protester::unAnnoy()
{
	Annoyed = false;
}

void Iceman::TakeDamage(int DamageTaken)
{
	HP -= DamageTaken;
}

int Iceman::getHP()
{
	return HP;
}

void Regular_Protester::setSquarestoMove(int numSquares)
{
	numSquarestoMove = numSquares;
}
void Regular_Protester::decSquarestoMove()
{
	numSquarestoMove--;
}

int Regular_Protester::getSquarestoMove()
{
	return numSquarestoMove;
}






void Iceman::doSomething() // Consult page 30
{
	int ch;

	if (!living())
	{
		return;
	}

	if (getWorld()->getKey(ch) == true)
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			// move player left if not out of bounds or not moving at a boulder
			setDirection(left);
			if (getX() - 1 != -1 && getWorld()->BoulderisNotLeftofIceman())
			{
				moveTo(getX() - 1, getY());
			}
			else if (getX() - 1 == -1)
			{
				moveTo(getX(), getY());
			}
			break;
		case KEY_PRESS_RIGHT:
			// move player right
			setDirection(right);
			if (getX() + 1 != 61 && getWorld()->BoulderisNotRightofIceman())
			{
				moveTo(getX() + 1, getY());
			}
			else if (getX() + 1 == 61)
			{
				moveTo(getX(), getY());
			}
			break;
		case KEY_PRESS_UP:
			// move player UP
			setDirection(up);
			if (getY() + 1 != 61 && getWorld()->BoulderisNotAboveIceman())
			{
				moveTo(getX(), getY() + 1);
			}
			else if (getY() + 1 == 61)
			{
				moveTo(getX(), getY());
			}
			break;
		case KEY_PRESS_DOWN:
			// move player DOWN
			setDirection(down);
			if (getY() - 1 != -1 && getWorld()->BoulderisNotBelowIceman())
			{
				moveTo(getX(), getY() - 1);
			}
			else if (getY() - 1 == -1)
			{
				moveTo(getX(), getY());
			}


			break;
		case KEY_PRESS_SPACE:
			if (this->water_charges > 0)
			{
				 water_charges--;
				getWorld()->SquirtWater();
			}
			break;
		case 122: case 90:  //upper and lower case Zz
			if (this->sonar_charges > 0)
			{
				getWorld()->Sonar_Use();
				sonar_charges--;
				getWorld()->playSound(SOUND_SONAR);
			}
			break;
		case KEY_PRESS_TAB:
			if (gold_owned > 0)
			{
				getWorld()->DropGold();
				gold_owned--;
			}
			break;
		case KEY_PRESS_ESCAPE:
			getWorld()->AbortLevel();
			break;
		}
		// cout << "Iceman Coords: (" << getX() << "," << getY() << ")" << endl;
	}


	// Get Iceman to destroy the ice

	//if (getWorld()->dig(getX(), getY()) == true)
	//{
	//	getWorld()->playSound(SOUND_DIG);

	//}

	// getWorld()->dig(getX(), getY()); This will get iceman to dig, but when executed only once in a single tick, it doesn't function how it should (too slow) 

	while (getWorld()->dig(getX(), getY()) == true) // Doing a loop fixes the issue explained above
	{
		getWorld()->dig(getX(), getY());
		getWorld()->playSound(SOUND_DIG);
		//getWorld()->playSound(SOUND_DIG); // Calling dig multiple times here gives beefier sound.
	}


	 getWorld()->IcemanCrushed();



	if (HP <= 0)
	{
		kill();
	}

	getWorld()->Reveal_Gold_And_Oil();

}


void Boulder::doSomething()
{
	if (!living())
	{
		return;
	}
	else
	{
		if (!getWorld()->iceisBelowBoulder(getX(), getY()))
		{
			tick++;
		}


		if (tick >= 30)
		{
			if (tick == 30)
			{
				getWorld()->playSound(SOUND_FALLING_ROCK);
			}

			if (!getWorld()->iceisBelowBoulder(getX(), getY()))
			{
				moveTo(getX(), getY() - 1);
			}
			else if (getWorld()->iceisBelowBoulder(getX(), getY() == true))
			{
				kill();
			}
		}
	}

}

void Oil::doSomething()
{

	if (!living())
	{
		return;
	}

	//if (getWorld()->getIcemanXPosition() >= this->getX() && getWorld()->getIcemanXPosition() <= this->getX() + 4 &&
	//	getWorld()->getIcemanYPosition() >= this->getY() && getWorld()->getIcemanYPosition() <= this->getY() + 4)
	//{
	//	kill();
	//	getWorld()->playSound(SOUND_FOUND_OIL);
	//	getWorld()->increaseScore(1000);
	//	setVisible(false);
	//}

	getWorld()->collectOil();


}

void Gold_Nugget::doSomething()
{
	if (!living())
	{
		return;
	}

	getWorld()->collectGold();

}


void Sonar_Kit::doSomething()
{
	if (!living())
	{
		return;
	}

	if (getWorld()->getIcemanXPosition() >= this->getX() && getWorld()->getIcemanXPosition() <= this->getX() + 3 &&
		getWorld()->getIcemanYPosition() >= this->getY() && getWorld()->getIcemanYPosition() <= this->getY() + 3)
	{
		kill();
		getWorld()->collectSonarCharge();
		getWorld()->increaseScore(75);
		getWorld()->playSound(SOUND_GOT_GOODIE);
		setVisible(false);
	}
}

void Water_Pool::doSomething()
{
	if (!living())
	{
		return;
	}

	getWorld()->collectWaterPool();
	//if (getWorld()->getIcemanXPosition() >= this->getX() && getWorld()->getIcemanXPosition() <= this->getX() + 3 &&
	//	getWorld()->getIcemanYPosition() >= this->getY() && getWorld()->getIcemanYPosition() <= this->getY() + 3)
	//{
	//	kill();
	//	getWorld()->playSound(SOUND_GOT_GOODIE);
	//	getWorld()->increaseScore(100);
	//	setVisible(false);
	//}

}

void Squirt::doSomething()
{
	if(!living())
	{
		return;
	}
	if (!getWorld()->isNextSpaceEmpty())
		this->kill();



	/*if (getDirection() == GraphObject::right) {
		while(getX() != getWorld()->getIcemanXPosition() + 16)
		{
			moveTo(getX() + 1, getY());
		}
	}
	if (getDirection() == GraphObject::left) {
		while (getX() != getWorld()->getIcemanXPosition() - 16)
		{
			moveTo(getX() - 1, getY());
		}
	}
	if (getDirection() == GraphObject::up) {
		while (getY() != getWorld()->getIcemanYPosition() + 16)
		{
			moveTo(getX(), getY() + 1);
		}
	}
	if (getDirection() == GraphObject::down) {
		while (getY() != getWorld()->getIcemanYPosition() - 16)
		{
			moveTo(getX(), getY() - 1);
		}
	}*/
}


void Regular_Protester::doSomething()
{
	if (!living())
	{
		return;
	}

	if (isGivingUp())
	{
		kill();
	}

	if (!isAnnoyed() && !isGivingUp() && numSquarestoMove <= 0 && !getWorld()->LOS_Of_Protester(this))
	{
		movingUp = false;
		movingDown = false;
		movingLeft = false;
		movingRight = false;

		int chance = rand() % 4 + 1;
		if (chance == 1)
		{
			movingLeft = true;
		}
		if (chance == 2)
		{
			movingRight = true;
		}
		if (chance == 3)
		{
			movingUp = true;
		}
		if (chance == 4)
		{
			movingDown = true;
		}
		numSquarestoMove = rand() % 60 + 8;
	}

	if (!isAnnoyed() && !isGivingUp() && numSquarestoMove > 0 && !getWorld()->LOS_Of_Protester(this))
	{
		if (movingLeft == true)
		{
			numSquarestoMove--;
			getWorld()->ProtesterMoveLeft(this);
		}

		if (movingRight == true)
		{
			numSquarestoMove--;
			getWorld()->ProtesterMoveRight(this);
		}

		if (movingUp == true)
		{
			numSquarestoMove--;
			getWorld()->ProtesterMoveUp(this);
		}

		if (movingDown == true)
		{
			numSquarestoMove--;
			getWorld()->ProtesterMoveDown(this);
		}
		//	cout << this << " " << numSquarestoMove << endl;
	}


	if (getWorld()->ProtesterHitByWater(this) && !isGivingUp())
	{
		getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
		Annoy();
		HP -= 2;
		if (HP <= 0)
		{
			getWorld()->increaseScore(25);
			getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
			makeHimGiveUp();
		}
	}

	if (isGivingUp()) // I give up state is the shortest path to Coordinate (60, 60)
	{

		moveTo(getX(), getY() - 1);
	}

	if (getWorld()->ProtesterCrushed(this))
	{
		decreaseHP(999);
		getWorld()->increaseScore(500);
		if (HP <= 0)
		{
			getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
			makeHimGiveUp();
		}
	}

	if (getWorld()->LOS_Of_Protester(this) && !isGivingUp())
	{

		if (getWorld()->getIcemanXPosition() == this->getX() && getWorld()->getIcemanYPosition() <= this->getY())
		{
			getWorld()->ProtesterMoveDown(this);
		}

		if (getWorld()->getIcemanXPosition() == this->getX() && getWorld()->getIcemanYPosition() >= this->getY())
		{
			getWorld()->ProtesterMoveUp(this);
		}

		if (getWorld()->getIcemanYPosition() == this->getY() && getWorld()->getIcemanXPosition() <= this->getX())
		{
			getWorld()->ProtesterMoveLeft(this);
		}

		if (getWorld()->getIcemanYPosition() == this->getY() && getWorld()->getIcemanXPosition() >= this->getX())
		{
			getWorld()->ProtesterMoveRight(this);
		}
	}
	ForkDecisionCoolDown.increaseTick();

	if (getWorld()->ForkInPath(this) && ForkDecisionCoolDown.gTick >= 200)
	{
		numSquarestoMove = 0;
		int chance = rand() % 2 + 1;
		if (getWorld()->ProtesterCanMoveDown(this) && getWorld()->ProtesterCanMoveLeft(this) && getDirection() == left)
		{
			if (chance == 1)
			{
				moveTo(getX(), getY() - 1);
			}
			if (chance == 2)
			{
				getWorld()->ProtesterMoveDown(this);
			}
			numSquarestoMove = rand() % 60 + 8;
		}

		if (getWorld()->ProtesterCanMoveRight(this) && getWorld()->ProtesterCanMoveDown(this) && getDirection() == right)
		{
			if (chance == 1)
			{
				moveTo(getX() + 1, getY());
			}
			if (chance == 2)
			{
				getWorld()->ProtesterMoveDown(this);
			}
			numSquarestoMove = rand() % 60 + 8;
		}

		if (getWorld()->ProtesterCanMoveLeft(this) && getWorld()->ProtesterCanMoveRight(this) && getDirection() == down)
		{
			if (chance == 1)
			{
				moveTo(getX() - 1, getY());
			}
			if (chance == 2)
			{
				moveTo(getX() + 1, getY());
			}
			numSquarestoMove = rand() % 60 + 8;
		}

		if (getWorld()->ProtesterCanMoveLeft(this) && getWorld()->ProtesterCanMoveRight(this) && getDirection() == up)
		{
			if (chance == 1)
			{
				moveTo(getX() - 1, getY());
			}
			if (chance == 2)
			{
				moveTo(getX() + 1, getY() + 1);
			}
			numSquarestoMove = rand() % 60 + 8;
		}




		ForkDecisionCoolDown.resetTick();
	}


	YellCoolDown.gTick++;

	int term1 = getWorld()->getIcemanXPosition() - this->getX();
	int term2 = getWorld()->getIcemanYPosition() - this->getY();
	double d = sqrt((term1 * term1) + (term2 * term2));

	if (d <= 4.00 && YellCoolDown.gTick >= 15 && !isGivingUp())
	{
		getWorld()->YellAtIceman(); 
		getWorld()->playSound(SOUND_PROTESTER_YELL);
		YellCoolDown.resetTick();
	}



	if (!isGivingUp())
	{
		getWorld()->ProtesterPickUpGold();
	}

}








//if (vSquirt[i] != nullptr)
//{
//	if (vSquirt[i]->getDirection() == GraphObject::right) {
//		if (vSquirt[i]->getX() != getIcemanXPosition() + 16)
//		{
//			vSquirt[i]->moveTo(vSquirt[i]->getX() + 1, vSquirt[i]->getY());
//			vSquirt[i]->kill();
//		}
//	}
//	if (vSquirt[i]->getDirection() == GraphObject::left) {
//		if (vSquirt[i]->getX() != getIcemanXPosition() - 16)
//		{
//			vSquirt[i]->moveTo(vSquirt[i]->getX() - 1, vSquirt[i]->getY());
//			vSquirt[i]->kill();
//		}
//	}
//	if (vSquirt[i]->getDirection() == GraphObject::up) {
//		if (vSquirt[i]->getY() != getIcemanYPosition() + 16)
//		{
//			vSquirt[i]->moveTo(vSquirt[i]->getX(), vSquirt[i]->getY() + 1);
//			vSquirt[i]->kill();
//		}
//	}
//	if (vSquirt[i]->getDirection() == GraphObject::down) {
//		if (vSquirt[i]->getY() != getIcemanYPosition() - 16)
//		{
//			vSquirt[i]->moveTo(vSquirt[i]->getX(), vSquirt[i]->getY() - 1);
//			vSquirt[i]->kill();
//		}
//	}
//}
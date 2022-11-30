#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
using namespace std;
class StudentWorld; // <---BRO

//every actor needs | image ID  | startpositionx | startpositiony | direction | depth | size |  

struct Tick
{
	int gTick = 0;

	Tick()
	{
		gTick = 0;
	}
	void resetTick()
	{
		gTick = 0;
	}
	void increaseTick()
	{
		gTick++;
	}

};

class Actor : public GraphObject {
public:
	//(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
	Actor(int imgId, int startX, int startY, Direction dir, unsigned int depth, double size, StudentWorld* sptr) :
		GraphObject(imgId, startX, startY, dir, size, depth) {
		Sw = sptr;
		is_alive = true;
		setVisible(true);
	}
	~Actor();
	virtual void doSomething();
	virtual bool living();
	virtual void kill();
	virtual void revive();
	StudentWorld* getWorld();


private:
	StudentWorld* Sw;
	bool is_alive;
};
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Ice : public Actor {
public:
	Ice(int startX, int startY, StudentWorld* sptr) : Actor(IID_ICE, startX, startY, right, 3, 0.25, sptr)
	{
		//i_startX = startX;
		//i_startY = startY;
		//setVisible(true);
	}
	~Ice();
	//int getIcePositionX();
	//int getIcePositionY();


private:
	//int i_startX;
	//int i_startY;

};

class Iceman : public Actor {
public:
	Iceman(StudentWorld* sptr) : Actor(IID_PLAYER, 30, 60, right, 0, 1.0, sptr)
	{
		HP = 10;
		water_charges = 5;
		sonar_charges = 1;
		gold_owned = 0;
	}

	~Iceman();
	virtual void doSomething() override;
	int getGold();
	int getSonarCharges();
	int getWater();
	int getOilNeeded();
	int getHP();

	void TakeDamage(int DamageTaken);
	void setOilNeeded(int oilNeededValue);
	void decOil();
	void increaseSonarCharges();
	void increaseGold();
	void increaseWater();

private:
	int HP;
	int water_charges;
	int sonar_charges;
	int gold_owned;
	int oil_needed;
};

class Boulder : public Actor {
public:
	Boulder(StudentWorld* sptr, int startX, int startY) : Actor(IID_BOULDER, startX, startY, down, 1, 1.0, sptr)
	{
		// startX = rand() % 64
		// StartY = rand() % 60
	}
	~Boulder();
	virtual void doSomething() override;


private:
	int tick = 0;

};

class Oil : public Actor
{
public:
	Oil(StudentWorld* sptr, int startX, int startY) : Actor(IID_BARREL, startX, startY, right, 2, 1.0, sptr)
	{
		// startX = rand() % 64
		// startY = rand() % 60
		setVisible(false);
	}
	~Oil();
	virtual void doSomething() override;
private:

};


class Gold_Nugget : public Actor
{
public:
	Gold_Nugget(StudentWorld* sptr, int startX, int startY) : Actor(IID_GOLD, startX, startY, right, 2, 1.0, sptr)
	{
		setVisible(false);
	}
	~Gold_Nugget();
	virtual void doSomething() override;

private:
};

class Sonar_Kit : public Actor
{
public:
	Sonar_Kit(StudentWorld* sptr, int startX, int startY) : Actor(IID_SONAR, startX, startY, right, 2, 1.0, sptr)
	{

	}
	~Sonar_Kit();
	int getTick();
	void incTick();
	void resetTick();
	virtual void doSomething() override;

private:
	int tick = 0;
};


class Water_Pool : public Actor
{
public:
	Water_Pool(StudentWorld* sptr, int startX, int startY) : Actor(IID_WATER_POOL, startX, startY, right, 2, 1.0, sptr)
	{
		//IID_WATER_POOL
	}
	~Water_Pool();
	void incTick();
	void resetTick();
	int getTick();
	virtual void doSomething() override;

private:
	int tick = 0;
};


class Squirt : public Actor
{
public:
	Squirt(StudentWorld* sptr, int startX, int startY, Direction squirtDir) : Actor(IID_WATER_SPURT, startX, startY, squirtDir, 1, 1.0, sptr)
	{
		setVisible(true);
	}
	~Squirt();
	virtual void doSomething() override;
private:

};



class Regular_Protester : public Actor
{
public:
	Regular_Protester(StudentWorld* sptr, int startX, int startY, int IID) : Actor(IID, startX, startY, left, 0, 1.0, sptr)
	{
		Annoyed = false;
		HP = 5;
		GivingUp = false;
		ForkDecisionCoolDown.gTick = 200;
	}

	virtual void doSomething() override;
	int getTick();
	int getHP();


	virtual bool isAnnoyed();
	virtual bool isGivingUp();
	virtual void makeHimGiveUp();
	virtual void decreaseHP(int HPtoDecrease);

	virtual void setSquarestoMove(int numSquares);
	virtual void decSquarestoMove();
	virtual int getSquarestoMove();




	virtual void Annoy();
	virtual void unAnnoy();
	virtual void incTick();
	virtual void resetTick();
private:
	int HP;
	int tick = 0;
	int numSquarestoMove = 0;
	bool Annoyed;
	bool GivingUp;
	bool movingDown = false;
	bool movingUp = false;
	bool movingRight = false;
	bool movingLeft = false;
	Tick YellCoolDown;
	Tick ForkDecisionCoolDown;

};

class Hardcore_Protester : public Regular_Protester
{
public:
	Hardcore_Protester(StudentWorld* sptr, int startX, int startY, int IID) : Regular_Protester(sptr, startX, startY, IID)
	{

	}
private:

};






#endif // ACTOR_H_
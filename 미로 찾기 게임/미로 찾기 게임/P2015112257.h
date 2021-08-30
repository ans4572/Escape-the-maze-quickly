#pragma once
#include "Player.h"

class P2015112257 : public Player
{
public:
	P2015112257();
	void gameStart(Point player, int height, int width);
	Action nextMove();
	void ableToMove(Point point, Point prevPoint);
	void notAbleToMove(Point point);
	~P2015112257();

private:
	Point point;
};
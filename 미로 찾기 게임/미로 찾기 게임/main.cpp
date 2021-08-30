#include "GameManager.h"
#include "P2013111995.h"
#include "P2015112257.h"

int main()
{
	// GameManager 선언
	GameManager gameManager;
	// 게임 초기화
	gameManager.init();
	// 플레이할 플레이어를 동적할당 후 넘김.
	// 다형성을 사용함.
	gameManager.run(new P2015112257());

	return 0;
}
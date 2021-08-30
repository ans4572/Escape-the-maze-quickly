#include "P2015112257.h"
#include "Constants.h"

int **visit;      //방문 안한곳은 0, 방문 한곳은 1, 벽은 2로 표시
int now_x, now_y; //현재 player위치 저장 변수
int *v_stack;     //방문 순서 stack 배열, 배열의 원소가 1이면 up, 2이면 down, 3이면 left, 4이면 right를 했다는것을 표시
int s_index = 0;  //방문 순서 stack 배열에 활용할 index

P2015112257::P2015112257()
{
}

void P2015112257::gameStart(Point player, int height, int width)
{
	//방문 배열 동적할당
	visit = new int*[height];
	for (int i = 0; i < height; i++) {
		visit[i] = new int[width];
	}

	//방문 배열 0으로 초기화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visit[i][j] = 0;
		}
	}

	//stack배열 값들을 0으로 초기화
	v_stack = new int[height*width];
	for (int i = 0; i < height*width; i++)
		v_stack[i] = 0;

	//시작 위치 방문 표시
	now_x = player.getX();
	now_y = player.getY();
	visit[now_x][now_y] = 1;

}

Action P2015112257::nextMove()
{
	if (now_x > 0 && visit[now_x - 1][now_y] == 0) {  //현재 위치의 x값이 0보다 크며(미로 맨 위 X) 
													  //위로 갈 곳이 방문한 곳이 아니라면 위로 이동
		now_x--;  //현재 위치의 x값 변경으로 위로 가는것을 표시
		v_stack[s_index++] = 1; //방문 stack 배열에 위로 간것을 push
		return Action::MOVE_UP;
	}
	else if (now_x < MAZE_HEIGHT-1 && visit[now_x + 1][now_y] == 0) {  //현재 위치의 x값이 20보다 작으며(미로 맨 아래 X) 
															//아래로 갈 곳이 방문한 곳이 아니라면 아래로 이동
		now_x++;  //현재 위치의 x값 변경으로 아래로 가는것을 표시
		v_stack[s_index++] = 2;  //방문 stack 배열에 아래로 간 것을 push
		return Action::MOVE_DOWN;
	}
	else if (now_y > 0 && visit[now_x][now_y - 1] == 0) {  //현재 위치의 y값이 0보다 크며(미로 맨 왼쪽X) 
														   //왼쪽으로 갈 곳이 방문한 곳이 아니라면 왼쪽으로 이동
		now_y--;  //현재 위치의 y값 변경으로 왼쪽으로 가는것을 표시
		v_stack[s_index++] = 3;  //방문 stack 배열에 왼쪽으로 간 것을 push
		return Action::MOVE_LEFT;
	}
	else if (now_y < MAZE_WIDTH-1 && visit[now_x][now_y + 1] == 0) {  //현재 위치의 y값이 50보다 작으며(미로 맨 오른쪽X) 
															//오른쪽으로 갈 곳이 방문한 곳이 아니라면 오른쪽으로 이동
		now_y++;  //현재 위치의 y값 변경으로 왼쪽으로 가는것을 표시
		v_stack[s_index++] = 4;  //방문 stack 배열에 오른쪽으로 간 것을 push
		return Action::MOVE_RIGHT;
	}
	else {  //길을 가다 막히면 다시 돌아가야하는데 이 때 방문 스택 배열 활용 
		if (v_stack[s_index - 1] == 1)  //이전에 위로 올라온거라면
		{
			now_x++;
			s_index--;
			return Action::MOVE_DOWN;
		}
		else if (v_stack[s_index - 1] == 2) {  //이전에 아래로 내려간거라면
			now_x--;
			s_index--;
			return Action::MOVE_UP;
		}
		else if (v_stack[s_index - 1] == 3) {  //이전에 왼쪽으로 갔다면
			now_y++;
			s_index--;
			return Action::MOVE_RIGHT;
		}
		else if (v_stack[s_index - 1] == 4) {  //이전에 오른쪽으로 갔다면
			now_y--;
			s_index--;
			return Action::MOVE_LEFT;
		}

	}
}

void P2015112257::ableToMove(Point point, Point prevPoint)
{
	visit[now_x][now_y] = 1;  //방문 한 곳은 1로 표시
}

void P2015112257::notAbleToMove(Point point)
{
	visit[now_x][now_y] = 2; //벽이므로 2로 표시

	//현재 위치를 돌아온 위치로 바꾸기
	now_x = point.getX();
	now_y = point.getY();

	v_stack[s_index--] = 0;  //못가는 곳이므로 방문 순서 stack 배열에서 pop 
}

P2015112257::~P2015112257() {
	for (int i = 0; i < 20; i++)
		delete[] visit[i];
	delete[] visit;
	delete[] v_stack;
}
#include "P2015112257.h"
#include "Constants.h"

int **visit;      //�湮 ���Ѱ��� 0, �湮 �Ѱ��� 1, ���� 2�� ǥ��
int now_x, now_y; //���� player��ġ ���� ����
int *v_stack;     //�湮 ���� stack �迭, �迭�� ���Ұ� 1�̸� up, 2�̸� down, 3�̸� left, 4�̸� right�� �ߴٴ°��� ǥ��
int s_index = 0;  //�湮 ���� stack �迭�� Ȱ���� index

P2015112257::P2015112257()
{
}

void P2015112257::gameStart(Point player, int height, int width)
{
	//�湮 �迭 �����Ҵ�
	visit = new int*[height];
	for (int i = 0; i < height; i++) {
		visit[i] = new int[width];
	}

	//�湮 �迭 0���� �ʱ�ȭ
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			visit[i][j] = 0;
		}
	}

	//stack�迭 ������ 0���� �ʱ�ȭ
	v_stack = new int[height*width];
	for (int i = 0; i < height*width; i++)
		v_stack[i] = 0;

	//���� ��ġ �湮 ǥ��
	now_x = player.getX();
	now_y = player.getY();
	visit[now_x][now_y] = 1;

}

Action P2015112257::nextMove()
{
	if (now_x > 0 && visit[now_x - 1][now_y] == 0) {  //���� ��ġ�� x���� 0���� ũ��(�̷� �� �� X) 
													  //���� �� ���� �湮�� ���� �ƴ϶�� ���� �̵�
		now_x--;  //���� ��ġ�� x�� �������� ���� ���°��� ǥ��
		v_stack[s_index++] = 1; //�湮 stack �迭�� ���� ������ push
		return Action::MOVE_UP;
	}
	else if (now_x < MAZE_HEIGHT-1 && visit[now_x + 1][now_y] == 0) {  //���� ��ġ�� x���� 20���� ������(�̷� �� �Ʒ� X) 
															//�Ʒ��� �� ���� �湮�� ���� �ƴ϶�� �Ʒ��� �̵�
		now_x++;  //���� ��ġ�� x�� �������� �Ʒ��� ���°��� ǥ��
		v_stack[s_index++] = 2;  //�湮 stack �迭�� �Ʒ��� �� ���� push
		return Action::MOVE_DOWN;
	}
	else if (now_y > 0 && visit[now_x][now_y - 1] == 0) {  //���� ��ġ�� y���� 0���� ũ��(�̷� �� ����X) 
														   //�������� �� ���� �湮�� ���� �ƴ϶�� �������� �̵�
		now_y--;  //���� ��ġ�� y�� �������� �������� ���°��� ǥ��
		v_stack[s_index++] = 3;  //�湮 stack �迭�� �������� �� ���� push
		return Action::MOVE_LEFT;
	}
	else if (now_y < MAZE_WIDTH-1 && visit[now_x][now_y + 1] == 0) {  //���� ��ġ�� y���� 50���� ������(�̷� �� ������X) 
															//���������� �� ���� �湮�� ���� �ƴ϶�� ���������� �̵�
		now_y++;  //���� ��ġ�� y�� �������� �������� ���°��� ǥ��
		v_stack[s_index++] = 4;  //�湮 stack �迭�� ���������� �� ���� push
		return Action::MOVE_RIGHT;
	}
	else {  //���� ���� ������ �ٽ� ���ư����ϴµ� �� �� �湮 ���� �迭 Ȱ�� 
		if (v_stack[s_index - 1] == 1)  //������ ���� �ö�°Ŷ��
		{
			now_x++;
			s_index--;
			return Action::MOVE_DOWN;
		}
		else if (v_stack[s_index - 1] == 2) {  //������ �Ʒ��� �������Ŷ��
			now_x--;
			s_index--;
			return Action::MOVE_UP;
		}
		else if (v_stack[s_index - 1] == 3) {  //������ �������� ���ٸ�
			now_y++;
			s_index--;
			return Action::MOVE_RIGHT;
		}
		else if (v_stack[s_index - 1] == 4) {  //������ ���������� ���ٸ�
			now_y--;
			s_index--;
			return Action::MOVE_LEFT;
		}

	}
}

void P2015112257::ableToMove(Point point, Point prevPoint)
{
	visit[now_x][now_y] = 1;  //�湮 �� ���� 1�� ǥ��
}

void P2015112257::notAbleToMove(Point point)
{
	visit[now_x][now_y] = 2; //���̹Ƿ� 2�� ǥ��

	//���� ��ġ�� ���ƿ� ��ġ�� �ٲٱ�
	now_x = point.getX();
	now_y = point.getY();

	v_stack[s_index--] = 0;  //������ ���̹Ƿ� �湮 ���� stack �迭���� pop 
}

P2015112257::~P2015112257() {
	for (int i = 0; i < 20; i++)
		delete[] visit[i];
	delete[] visit;
	delete[] v_stack;
}
# 미로 탈출 게임

# 1. 목표
시작 지점부터 도착 지점까지 도달하는 것이 목표.


# 2. 조건
-미로의 전체 맵은 주어지지 않음. 따라서 상,하,좌,우로 직접 이동해가면서 도착 지점까지 도달해야 한다.

-플레이 방식은 '턴 방식' 이며, 플레이어는 한 턴에 한 번씩만 이동 가능하다.

-만약 이동하려는 방향에 장애물이 있으면 플레이어에게 이동이 불가능한 것을 알려준다.

-이동하려는 방향으로 이동이 가능한 경우 이동 후의 좌표를 플레이어에게 알려준다.


# 3. 게임 엔진 설명
-GameManager: 게임 전체적인 것을 담당.

-main: 메인 함수, GameManager 호출

-Maze: 게임 중 미로 맵에 대한 구현들을 담당

-Point: 좌표를 담당

-Action: 상 하 좌 우로 이동 할 때의 enum

-MazeGenerator: 미로를 랜덤으로 생성. 출처: https://codereview.stackexchange.com/questions/135443/c-maze-generator


# 4. 플레이어
-Player.h를 상속받아 나만의 플레이어 클래스(myplayer)를 생성 후 메인을 통해 게임 진행


<코드설명>

방문 표시 역할을 하며 , 미로와 같은 사이즈를 가진 2 차원 배열 visit 는 이미 방문한 곳을 길이 막힐 때까지는 다시 가지 않아 이를 활용하여 좀 더 효율적으로 미로를 탈출할 수 있게 만들었고, 방문 순서를 시작위치부터 저장하는 v_stack 배 열은 만약 막히는 곳을 갔다면 이전 에 갈림길로 되돌아가야 하는데 이 때 지나온 길들이 필요하므로 만들었다.
기본적인 움직이는 순서는 각 위치마다 위 아래왼쪽 오른쪽으로 이동할 것이고 v isit 배열과 v_stack 배열을 활용하여 빠르게 미로를 탈출 할 수 있도록 만들었다.


-gameStart():
필요한 배열들을 동적할당 및 초기화를 하며 player의 시작위치를 저장 및 방문표시.


-nextMove():
player의 다음 움직임을 진행하는 함수로 각 위치마다 위, 아래, 왼쪽, 오른쪽 순서대로 조건을 따지며 이동한다. 다음 움직임을 진행하는 조건으로는 1. 방문한 곳이 아니고 2. 미로의 테두리 부분인지를 따지며 이를 만족할 경우 이동하면서 방문 stack배열에 이를 저장한다. 만약 길이 막혔을 경우 방문 stack배열을 이용하여 그 위치를 처음에 어떻게 갔는지 보고 위로 움직여 도착했다면 아래로 움직이고, 아래로 움직여 도착했다면 위로 움직이고 등 이런 식으로 이전 지점으로 돌아간다. 


-ableToMove():
이동이 가능한 곳이라면 그대로 이동을 유지하고 visit방문 배열에 현재 위치를 1로 바꿔 방문 표시를 한다.


-notAbleToMove():
이동한 곳이 벽이라 이동 불가능 하므로 우선 visit방문 배열에 현재 위치를 2로 바꿔 벽이라는 것을 표시하고 player의 현재 위치를 이동하기 전 위치로 바꿔주며 저장했던 방문 순서 v_stack배열의 마지막을 0으로 만들면서 s_index를 1빼며 nextMove()에서 추가했던 방문 순서에서 빼준다. 



# 내 플레이어의 결과


![image](https://user-images.githubusercontent.com/22833414/131271851-651401d4-56db-4414-ae54-ff62bb14e9ff.png)


![image](https://user-images.githubusercontent.com/22833414/131271872-adc35299-c324-4425-b322-49a7e6b0c198.png)


![image](https://user-images.githubusercontent.com/22833414/131271889-ba0652db-825c-47d8-8a98-29f0fc2aabf5.png)

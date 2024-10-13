#pragma once
#include "QList"
#include "QPoint"
#include "QLabel"

#define SNAKE_WIDTH 60 //蛇身宽
#define SNAKE_HIGHT 60 //蛇身高

typedef struct SnakeNode
{
	QLabel* m_pic;
	QPoint m_pos;
}SNAKENODE;


class SnakeCtrl
{
public:
	SnakeCtrl();
	~SnakeCtrl();

public:
	enum MOVE_DIRECTION {
		MOVE_LEFT = 0,
		MOVE_UP,
		MOVE_RIGHT,
		MOVE_DOWN,
	};

	QList<SNAKENODE>	m_snake;
	QList<SNAKENODE>	m_food;
	MOVE_DIRECTION	m_nDirection;  //当前移动方向
};


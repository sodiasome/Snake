#include "SnakeHu.h"
#include <QFile>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QPainter>
#include <ctime>


SnakeHu::SnakeHu(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	InitAll();
}


SnakeHu::~SnakeHu()
{
	ClearSnake();
}

void SnakeHu::DrawSnake()
{
	QList<SNAKENODE>::iterator iter = m_ctrl.m_snake.begin();
	for (; iter != m_ctrl.m_snake.end(); ++iter)
	{
		(*iter).m_pic->setGeometry((*iter).m_pos.x() * SNAKE_WIDTH, (*iter).m_pos.y()*SNAKE_HIGHT, SNAKE_WIDTH, SNAKE_HIGHT);
		(*iter).m_pic->show();
	}
}

void SnakeHu::ChangeSnake()
{
	SNAKENODE head = m_ctrl.m_snake.front();
	int nHeadX = head.m_pos.x();
	int nHeadY = head.m_pos.y();
	switch (m_ctrl.m_nDirection)
	{
	case SnakeCtrl::MOVE_UP:
		--nHeadY;
		break;
	case SnakeCtrl::MOVE_DOWN:
		++nHeadY;
		break;
	case SnakeCtrl::MOVE_LEFT:
		--nHeadX;
		break;
	case SnakeCtrl::MOVE_RIGHT:
		++nHeadX;
		break;
	}

	//头部插入一个
	SNAKENODE newNode;
	newNode.m_pos = QPoint(nHeadX, nHeadY);
	newNode.m_pic = new QLabel(tr(""));
	newNode.m_pic->setParent(this);
	newNode.m_pic->setPixmap(QPixmap::fromImage(QImage(m_strUser)));
	m_ctrl.m_snake.push_front(newNode);

	//尾巴弹出一个
	SNAKENODE snakeTial = m_ctrl.m_snake.back();
	delete snakeTial.m_pic;
	snakeTial.m_pic = NULL;
	m_ctrl.m_snake.pop_back();
}

void SnakeHu::OnFlash()
{
	ui.lbScore->setText(QString("%1").arg(m_ctrl.m_snake.size()));
	DrawBackground();
	if (CheckHitWall())
	{
		if (QMessageBox::Yes == QMessageBox::question(this, QString::fromLocal8Bit("提示"), "游戏结束，是否重新开始？", QMessageBox::Yes | QMessageBox::No))
		{
			InitGame();
		}
		else
		{
			m_timerFlash.stop();
		}
	}
	DrowFood();

	ChangeSnake();
	DrawSnake();
	
	CheckEatFood();
	update();
}

void SnakeHu::OnHuangUser(bool state)
{
	m_strUser = PIC_SNAKE1;
}

void SnakeHu::OnHuUser(bool state)
{
	m_strUser = PIC_SNAKE2;
}

void SnakeHu::ClearSnake()
{
	QList<SNAKENODE>::iterator iter = m_ctrl.m_snake.begin();
	for (; iter != m_ctrl.m_snake.end(); ++iter)
	{
		delete (*iter).m_pic;
		(*iter).m_pic = NULL;
	}
}

void SnakeHu::DrawBackground()
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap("D:\\Src\\pin_bk"));
}

void SnakeHu::DrowFood()
{
	QList<SNAKENODE>::iterator iter = m_ctrl.m_food.begin();
	for (; iter != m_ctrl.m_food.end(); ++iter)
	{
		(*iter).m_pic->setGeometry((*iter).m_pos.x() * SNAKE_WIDTH, (*iter).m_pos.y()*SNAKE_HIGHT, SNAKE_WIDTH, SNAKE_HIGHT);
		(*iter).m_pic->show();
	}
}

void SnakeHu::CheckEatFood()
{
	SNAKENODE head = m_ctrl.m_snake.front();
	QList<SNAKENODE>::iterator iter = m_ctrl.m_food.begin();
	QList<SNAKENODE>::iterator snakeIter;
	int nNewFoodX, nNewFoodY;
	bool nIsOnSnake;

	for (; iter != m_ctrl.m_food.end(); ++iter)
	{
		if (head.m_pos.x() == (*iter).m_pos.x() && head.m_pos.y() == (*iter).m_pos.y())
		{
			//判断食物是否在蛇身上
			do 
			{
				nNewFoodX = qrand() % WIN_WIDTH;
				nNewFoodY = qrand() % WIN_HEGHT;
				nIsOnSnake = false;
				snakeIter = m_ctrl.m_snake.begin();
				for (; snakeIter != m_ctrl.m_snake.end(); ++snakeIter)
				{
					if ((*snakeIter).m_pos.x() == nNewFoodX && (*snakeIter).m_pos.y() == nNewFoodY)
					{
						nIsOnSnake = true;
						break;
					}

				}
			} while (nIsOnSnake);
			//更新食物坐标
			(*iter).m_pos = QPoint(nNewFoodX, nNewFoodY);
			
			//蛇尾增加一个
			SNAKENODE tial = m_ctrl.m_snake.back();
			int nNewTialX, nNewTialY;
			switch (m_ctrl.m_nDirection)
			{
			case SnakeCtrl::MOVE_UP:
				nNewTialX = tial.m_pos.x();
				nNewTialY = tial.m_pos.y() + 1;
				break;
			case SnakeCtrl::MOVE_DOWN:
				nNewTialX = tial.m_pos.x();
				nNewTialY = tial.m_pos.y() - 1;
				break;
			case SnakeCtrl::MOVE_LEFT:
				nNewTialX = tial.m_pos.x() + 1;
				nNewTialY = tial.m_pos.y();
				break;
			case SnakeCtrl::MOVE_RIGHT:
				nNewTialX = tial.m_pos.x() - 1;
				nNewTialY = tial.m_pos.y();
				break;
			}
			SNAKENODE newNode;
			newNode.m_pos = QPoint(nNewTialX, nNewTialY);
			newNode.m_pic = new QLabel(tr(""));
			newNode.m_pic->setParent(this);
			newNode.m_pic->setPixmap(QPixmap::fromImage(QImage(m_strUser)));
			m_ctrl.m_snake.push_back(newNode);
		}
	}
}

bool SnakeHu::CheckHitWall()
{
	SNAKENODE head = m_ctrl.m_snake.front();
	if (head.m_pos.x() > WIN_WIDTH || head.m_pos.y() > WIN_HEGHT 
		|| head.m_pos.x() < 0 || head.m_pos.y() < 0)
	{
		return true;
	}
	return false;
}

void SnakeHu::InitAll()
{
	qsrand(time(NULL));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	//定时器 刷新蛇身移动
	m_timerFlash.setInterval(500);
	connect(&m_timerFlash, SIGNAL(timeout()), this, SLOT(OnFlash()));

	//勾选
	m_strUser = PIC_SNAKE1;
	connect(ui.cbHuangdatian, &QCheckBox::clicked, [=](bool state)
	{
		if (state)
			m_strUser = PIC_SNAKE2;
	});
	connect(ui.cbHuwanqing, &QCheckBox::clicked, [=](bool state)
	{
		if (state)
			m_strUser = PIC_SNAKE1;
	});

	InitGame();
}

void SnakeHu::InitGame()
{
	//加载音乐
	OnBtnLoadMusic();

	m_ctrl.m_snake.clear();
	m_ctrl.m_food.clear();
	m_ctrl.m_nDirection = SnakeCtrl::MOVE_RIGHT;

	//初始化蛇头
	SNAKENODE snakeHead;
	snakeHead.m_pic = new QLabel(tr(""));
	snakeHead.m_pic->setPixmap(QPixmap::fromImage(QImage(m_strUser)));
	snakeHead.m_pic->setGeometry(2, 2, SNAKE_WIDTH, SNAKE_HIGHT);
	snakeHead.m_pic->setParent(this);
	snakeHead.m_pos = QPoint(2, 2);
	m_ctrl.m_snake.push_back(snakeHead);

	//食物
	SNAKENODE food;
	food.m_pic = new QLabel(tr(""));
	food.m_pic->setPixmap(QPixmap::fromImage(QImage(PIC_FOOD1)));
	food.m_pic->setParent(this);
	food.m_pos = QPoint(qrand() % 5, qrand() % 5);
	m_ctrl.m_food.push_back(food);

	m_timerFlash.start();
}

void SnakeHu::OnBtnLoadMusic()
{
	QString strMusicPath = "D:\\Src\\lively.mp3";
	QMediaPlayer *player = new QMediaPlayer;
	//播放进度的信号提示

	connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(OnMusicPosChaged(qint64)));
	player->setMedia(QUrl::fromLocalFile(strMusicPath));
	player->setVolume(50); //0~100音量范围,默认是100
	player->play();
}

void SnakeHu::OnMusicPosChaged(qint64 nPos)
{
	//ui.proBarMusic->setValue(nPos);
}

void SnakeHu::keyPressEvent(QKeyEvent *event)
{
	int nAscii = event->key();
	switch (nAscii)
	{
	case 'w':
	case 'W':
		m_ctrl.m_nDirection = SnakeCtrl::MOVE_UP;
		break;
	case 's':
	case 'S':
		m_ctrl.m_nDirection = SnakeCtrl::MOVE_DOWN;
		break;
	case 'a':
	case 'A':
		m_ctrl.m_nDirection = SnakeCtrl::MOVE_LEFT;
		break;
	case 'd':
	case 'D':
		m_ctrl.m_nDirection = SnakeCtrl::MOVE_RIGHT;
		break;
	default:
		QWidget::keyPressEvent(event);
		break;
	}
}

void SnakeHu::paintEvent(QPaintEvent *event)
{
	QPainter paint;   //创建画家对象；
	paint.begin(this);  //指定当前窗口为绘图设备；
	//外边框
	QPen pen;
	pen.setWidth(5);
	pen.setColor(QColor(255, 0, 0));
	pen.setStyle(Qt::DashDotLine);

	paint.setPen(pen);

	//创建画刷
	QBrush brush;
	brush.setColor(Qt::black);
	brush.setStyle(Qt::Dense6Pattern);

	paint.setBrush(brush);

	// 画矩形；
	paint.drawRect(0, 0, SNAKE_WIDTH*9 , SNAKE_HIGHT*8);
}

#pragma once
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets/QDialog>
#include "ui_SnakeHu.h"
#include <QKeyEvent>
#include "QTimer"
#include "SnakeCtrl.h"

#define PIC_SNAKE1 ".\\src\\snake\\snake1.jpg"
#define PIC_SNAKE2 ".\\src\\snake\\snake2.jpg"
#define PIC_FOOD1 ".\\src\\snake\\food1.png"

#define WIN_WIDTH 7
#define WIN_HEGHT 6

class SnakeHu : public QDialog
{
    Q_OBJECT

public:
    SnakeHu(QWidget *parent = nullptr);
    ~SnakeHu();

	SnakeCtrl m_ctrl;
	QTimer m_timerFlash;	//刷新
	QString m_strUser;
	void DrawSnake();
	void ClearSnake();		//释放内存
	void DrawBackground();
	void DrowFood();
	void CheckEatFood();	//检测是否迟到食物
	bool CheckHitWall();	//判断是否撞墙
	void InitAll();
	void InitGame();
	void ChangeSnake();

private:
    Ui::SnakeHuClass ui;

public slots:
	void OnBtnLoadMusic();
	void OnMusicPosChaged(qint64 nPos);

	void OnFlash();
	void OnHuangUser(bool state);
	void OnHuUser(bool state);
protected:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void paintEvent(QPaintEvent *event);
};

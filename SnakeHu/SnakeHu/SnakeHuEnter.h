#pragma once
#include <QtWidgets/QDialog>
#include "Ui_SnakeHuEnter.h"

#define PIC_ENTER ".\\src\\snake\\enter_bk.png"

class SnakeHuEnter :
	public QDialog
{
	Q_OBJECT
public:
	SnakeHuEnter(QWidget *parent = nullptr);
	~SnakeHuEnter();
private:
	Ui::SnakeHuEnter ui;
	void Init();

public slots:
	void OnClickedEnter();
};


#include "SnakeHuEnter.h"
#include "QIcon"
#include "QPainter"

SnakeHuEnter::SnakeHuEnter(QWidget *parent /*= nullptr*/)
	: QDialog(parent)
{
	ui.setupUi(this);
	Init();
	connect(ui.btnEnter, &QPushButton::clicked, this, &SnakeHuEnter::OnClickedEnter);
}

SnakeHuEnter::~SnakeHuEnter()
{

}

void SnakeHuEnter::Init()
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	QPalette palette;
	palette.setBrush(backgroundRole(), QBrush(QPixmap(PIC_ENTER).scaled(this->size())));
	setPalette(palette);
}

void SnakeHuEnter::OnClickedEnter()
{
	accept();
}
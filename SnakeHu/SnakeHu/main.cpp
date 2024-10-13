#include "SnakeHu.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "SnakeHuEnter.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	

	SnakeHuEnter gameEnter;
	SnakeHu game;

	//if (gameEnter.exec() == QDialog::Accepted)
	{
		QPalette palette(game.palette());
		palette.setColor(QPalette::Background, QColor(78,238,148));
		game.setAutoFillBackground(true);
		game.setPalette(palette);
		game.show();
		return a.exec();
	}
	//else
	//	return 0;
   
}

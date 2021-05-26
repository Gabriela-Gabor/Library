#pragma once
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qmessagebox.h>
#include<qpainter.h>
#include<qimage.h>



class CosRead :public QWidget, public Observer
{
public:
	CosRead(Service& serv) :srv{ serv }
	{
		srv.addObserver(this);
		this->setStyleSheet("background-color: #d6cbf5;font-family:Comic Sans MS, cursive, sans-serif;font-weight:bold;");

	}
private:

	Service& srv;
	
	void update() override
	{
		this->repaint();
	}
    void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		
		for (int i=0;i<srv.Cos().size();i++)
		{
			int x = rand() % (width() - 60);
			int y = rand() % (height() - 60);
			QRectF rectangle(x, y, 60.0, 40.0);
			p.drawRect(rectangle);
			p.fillRect(rectangle, Qt::blue);
		}
	
    }


};
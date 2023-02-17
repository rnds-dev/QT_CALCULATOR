#pragma once

#include <qwidget.h>
#include <qapplication.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QKeyEvent>
#include <qcheckbox.h>
#include <qgridlayout.h>
#include <QPushButton>
#include <qstyle.h>
#include "parser/parser.h"

class Interface : public QWidget {
public: 
	Interface(QWidget * parent = 0);

private:
	QLineEdit* input;
	QPushButton* ans;

	QPushButton* type;
	QCheckBox* theme;
	QString style, styleBtn;
	QGridLayout* gridBtn;
	QList<QPushButton*>* buttons = new QList<QPushButton*>();
	bool isSimple; int heightBtn, widthBtn;

	void act();
	void changeType();
	void changeTheme(int);
	void ansToInput();
	void startAnimation();
};
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

class calculator:public QWidget
{
	Q_OBJECT;
public:
	calculator(QWidget* parent = 0);

protected:
	void act();
	void changeType();
	void changeTheme(int);
	void history();
	void ansToInput();

private:
	QLineEdit* input;
	QPushButton* ans;

	QPushButton* type, *hstLineBtn, * hstAnsBtn;
	QCheckBox* theme;
	QString style, styleBtn;
	QGridLayout* gridBtn, *gridHst;
	QList<QPushButton*>* buttons = new QList<QPushButton*>();
	bool isSimple; int heightBtn, widthBtn;
};


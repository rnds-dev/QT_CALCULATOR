#include "Interface.h"
#include "parser/parser.h"
#include "Style.h"
#include <QPropertyAnimation>

TParser parser;

Interface::Interface(QWidget* parent) {
	int width = 350, height = 600,
		widthMax = 1920, heightMax = 1080;

	QFont	inputfont("Montserrat SemiBold", 20),
		ansfont("Montserrat", 14),
		buttonfont("Montserrat SemiBold", 11);

	type = new QPushButton("");
	type->setFont(ansfont);
	type->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	type->setMinimumSize(width, height / 15);
	type->setMaximumSize(widthMax, height / 15);
	connect(type, &QPushButton::clicked, this, &Interface::changeType);

	input = new QLineEdit();
	input->setFont(inputfont);
	input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	input->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	input->setMinimumSize(width, height / 4);
	input->setMaximumSize(widthMax, heightMax / 4);

	ans = new QPushButton("");
	ans->setFont(ansfont);
	ans->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ans->setMinimumSize(width, height / 8);
	ans->setMaximumSize(widthMax, heightMax / 8);
	connect(ans, &QPushButton::clicked, this, &Interface::ansToInput);

	theme = new QCheckBox("Dark theme");
	connect(theme, &QCheckBox::stateChanged, this, &Interface::changeTheme);

	QGridLayout* gridInterface = new QGridLayout(this);
	QGridLayout* gridMain = new QGridLayout(this);
	gridBtn = new QGridLayout(this);

	gridBtn->setSpacing(0);
	gridMain->setSpacing(0);

	gridMain->addWidget(type, 0, 0);
	gridMain->addWidget(input, 1, 0);
	gridMain->addWidget(ans, 2, 0);
	gridMain->addLayout(gridBtn, 3, 0);
	gridMain->addWidget(theme, 4, 0);

	gridInterface->addLayout(gridMain, 0, 0);


	gridInterface->setContentsMargins(0, 0, 0, 0);

	input->setFocus();
	type->click();
	theme->click();
	setLayout(gridMain);
};

void Interface::act() {
	QString buttonText;
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	buttonText = buttonSender->text();

	if (buttonText == "=") {
		ans->setFont(QFont("Montserrat", 14));
		QString str = input->text(), hstLine = str, hstAns;
		QByteArray byteData = str.toLocal8Bit();
		char* s = byteData.data();

		try
		{
			parser.Compile(s);
			parser.Evaluate();
			ans->setText(QString::number(parser.GetResult()));
		}
		catch (TError error)
		{
			ans->setFont(QFont("Montserrat", 8));
			ans->setText(error.error + QString(" at position ") + QString::number(error.pos));
		}
	}
	else if (buttonText == "C") {
		input->clear();
	}
	else if (buttonText == "<") {
		input->backspace();
	}
	else {
		input->insert(buttonText);
	}
	input->setFocus();
};

void Interface::changeType() {
	startAnimation();

	isSimple = !isSimple;

	QFont buttonfont("Montserrat SemiBold", 11);
	int p;
	QList<QString> vals;

	p = 0;
	if (buttons->size())
		for (int i = 0; i < heightBtn; i++)
			for (int j = 0; j < widthBtn; j++)
			{
				gridBtn->removeWidget(buttons->at(p));
				buttons->at(p)->deleteLater();
				p++;
			}
	buttons->clear();

	if (isSimple) {
		type->setText("Simple");
		heightBtn = 5, widthBtn = 4;
		vals = {
			"C",		"<",		"^",		"sqrt()",
			"7",		"8",		"9",		"/",
			"4",		"5",		"6",		"*",
			"1",		"2",		"3",		"-",
			"0",		".",		"=",		"+" };//5x4
	}
	else {
		type->setText("Scientific");
		heightBtn = 8, widthBtn = 5;
		vals = {
		"sin()",	"cos()",	"tg()",		"ctg()",	"^",
		"arcsin()",	"arccos()",	"arctg()",  "arcctg()",	"sqrt()",
		"sh()",		"ch()",		"th()",		"cth()",	"1/x",
		"C",		"<",		"",			"",			"",
		"lg()",		"7",		"8",		"9",		"/",
		"ln()",		"4",		"5",		"6",		"*",
		"pi",		"1",		"2",		"3",		"-",
		"e",		"0",		".",		"=",		"+" };
	}

	p = 0;
	for (int i = 0; i < heightBtn; i++)
		for (int j = 0; j < widthBtn; j++) {

			QPushButton* btn = new QPushButton(vals[p], this);
			btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			btn->setMinimumSize(70, 50);
			btn->setFont(buttonfont);
			if (vals[p] == "=") btn->setDefault(1);
			buttons->append(btn);

			if (i >= heightBtn - 4) {
				btn->setFont(buttonfont);
				btn->setStyleSheet(styleBtn);
				btn->setMinimumSize(70, 50);
			}
			else {
				btn->setFont(QFont("Montserrat", 9));
				btn->setStyleSheet(style);
				btn->setMinimumSize(70, 40);

			}

			if (vals[p] == '=') btn->setShortcut(tr("RETURN"));
			gridBtn->addWidget(btn, i, j);
			connect(buttons->at(p), &QPushButton::clicked, this, &Interface::act);
			p++;
		}

	input->setFocus();
}

void Interface::changeTheme(int state) {
	setWindowOpacity(0);
	QString nameTheme;
	if (state == Qt::Checked) {
		nameTheme = "Dark";
	}
	else {
		nameTheme = "White";
	}
	useStyle(type,	"Button", nameTheme);
	useStyle(input, "Input", nameTheme);
	useStyle(ans,	"Answer", nameTheme);
	useStyle(theme, "Button", nameTheme);

	for (int i = 0; i < heightBtn * widthBtn; i++) {
		if (i >= heightBtn * widthBtn - 4 * widthBtn)
			useStyle(buttons->at(i), "Button", nameTheme);
		else useStyle(buttons->at(i), "Answer", nameTheme);
	}

	startAnimation();
	input->setFocus();
}

void Interface::ansToInput() {
	input->setText(ans->text());
	ans->setText("");
	input->setFocus();
}

void Interface::startAnimation() {
	QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(200);
	animation->setStartValue(0);
	animation->setEndValue(0.98);
	animation->start();
};
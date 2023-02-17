#pragma once

#include <qstring.h>
#include <qwidget.h>

void useStyle(QWidget* object, QString type, QString theme) {
	QString style;
	QFont font;

	if (theme == "Dark") {
		style = (
			"background-color: #202020;"
			"color: #ffffff;"
			"padding: 10px;"
			"border-radius: 0;");
	}
	else {
		style = ("background-color:#ffffff;"
			"color: #202020;"
			"padding: 10px;"
			"border-radius: 0;");
	}
	/************************************************/
	if (type == "Button") {
		font.setFamily("Montserrat SemiBold");
		font.setPointSize(11);
	}
	else if (type == "Input") {
		font.setFamily("Montserrat SemiBold");
		font.setPointSize(20);

	}
	else if (type == "Answer") {
		font.setFamily("Montserrat");
		font.setPointSize(14);
	}

	object->setStyleSheet(style);
	object->setFont(font);
}
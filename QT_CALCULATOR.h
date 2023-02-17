#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_CALCULATOR.h"

class QT_CALCULATOR : public QMainWindow
{
    Q_OBJECT

public:
    QT_CALCULATOR(QWidget *parent = Q_NULLPTR);

private:
    Ui::QT_CALCULATORClass ui;
};

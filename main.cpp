#include "QT_CALCULATOR.h"
#include <QtWidgets/QApplication>
#include "calculator.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator w;
    w.setWindowOpacity(0.98); 
    w.setWindowTitle("Calculator");
    w.setWindowIcon(QIcon("D:/Files/Windows/Customization/Icons/Lumicons/Mono/Maximize Plus.ico"));
    w.setAutoFillBackground(1);
    
    w.show();
    return a.exec();
}
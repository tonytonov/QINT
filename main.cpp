#include "QintGUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    RInside R(argc, argv);
    QApplication app(argc, argv);
    QIntGUI ui(R);
    
    return app.exec();
}

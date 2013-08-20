#include "qintanalysis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    RInside R(argc, argv);
    QApplication app(argc, argv);
    QIntAnalysis qint(R);
    
    return app.exec();
}

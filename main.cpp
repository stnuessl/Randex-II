#include "randex.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Randex w;
    w.show();
    
    return a.exec();
}

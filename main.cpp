#include "text_search.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Text_Search w;
    w.show();
    return a.exec();
}

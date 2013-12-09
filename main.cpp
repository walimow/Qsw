#include <QtWidgets//QApplication>
#include "QswShell.h"

using namespace qstepwork;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QswShell foo;
    foo.show();
    return app.exec();
}

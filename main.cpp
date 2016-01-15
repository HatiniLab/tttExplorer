#include "tttexplorermainwindow.h"
#include <QApplication>
extern int qInitResources_icons();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle("fusion");

    qInitResources_icons();

    tttExplorerMainWindow w;
    w.show();

    return a.exec();
}

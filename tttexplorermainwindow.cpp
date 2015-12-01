#include "tttexplorermainwindow.h"
#include "ui_tttexplorermainwindow.h"

tttExplorerMainWindow::tttExplorerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tttExplorerMainWindow)
{
    ui->setupUi(this);
}

tttExplorerMainWindow::~tttExplorerMainWindow()
{
    delete ui;
}

#ifndef TTTEXPLORERMAINWINDOW_H
#define TTTEXPLORERMAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>


#include "tttlayermanager.h"
#include "tttDataset.h"
namespace Ui {

class tttExplorerMainWindow;
}

class tttExplorerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tttExplorerMainWindow(QWidget *parent = 0);
    ~tttExplorerMainWindow();

private slots:
    //1. Project based slots
    void    actionOpenDatasetTriggered();
    void    actionNewDatasetTriggered();
    void    actionCloseDatasetTriggered();
signals:

    void datasetChanged();
    void datasetClosed();

private:
    Ui::tttExplorerMainWindow *m_pUI;

    //Rendering engine
    //Main application renderer
    vtkSmartPointer<vtkRenderer>     m_Renderer;
    //Main renderWindow;
    vtkSmartPointer<vtkRenderWindow>    m_RenderWindow;
    //Main
    vtkSmartPointer<vtkRenderWindowInteractor> m_RenderWindowInteractor;
    //add Signal mapper


    tttLayerManager * m_pLayerManager;
    Dataset m_Dataset;
};

#endif // TTTEXPLORERMAINWINDOW_H

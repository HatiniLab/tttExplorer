#ifndef TTTEXPLORERMAINWINDOW_H
#define TTTEXPLORERMAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkEventQtSlotConnect.h>


#include "tttlayermanager.h"
#include "tttDataset.h"
#include "ttttimelapsemanager.h"
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

    void datasetChanged(const ttt::Dataset::Pointer&);
    void datasetClosed();
    void frameChanged(unsigned long);

private:
    Ui::tttExplorerMainWindow *m_pUI;

    //Rendering engine
    //Main application renderer
    vtkSmartPointer<vtkRenderer>     m_Renderer;
    //Main renderWindow;
    vtkSmartPointer<vtkRenderWindow>    m_RenderWindow;
    //Main RenderWindowInteractor
    vtkSmartPointer<QVTKInteractor> m_RenderWindowInteractor;
    //Signal mapper
	vtkSmartPointer<vtkEventQtSlotConnect> m_QtToVTKConnections;

    tttLayerManager * m_pLayerManager;

    tttTimelapseManager * m_pTimelapseManager;
    ttt::Dataset::Pointer m_Dataset;

    QString m_DatasetPath;

    unsigned long m_CurrentFrame;
};

#endif // TTTEXPLORERMAINWINDOW_H

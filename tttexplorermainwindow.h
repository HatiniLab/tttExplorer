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
/**
 * TODO
 */
class tttExplorerMainWindow;
}
/**
 * TODO
 */
class tttExplorerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	 * TODO
	 */
    explicit tttExplorerMainWindow(QWidget *parent = 0);
    /**
     * TODO
     */
    ~tttExplorerMainWindow();
private:
    /**
     * TODO
     */
    void	setupUI();

private slots:
	/**
	 * TODO
	 */
	void	actionTimesliderMoved(int);

	/**
	 * TODO
	 */
    void    actionOpenDatasetTriggered();
    /**
     * TODO
     */
    void    actionNewDatasetTriggered();
    /**
     * TODO
     */
    void    actionCloseDatasetTriggered();
    /**
     * TODO
     */
    void	actionNewLayerTriggered();

    /**
     *
     *
     */
    void	actionRemoveLayerTriggered();
    /**
     * TODO
     */
    void	actionAddFrameTriggered();
    /**
     * TODO
     */
    void	actionRemoveFrameTriggered();

    /**
     * TODO
     */
    void 	actionExitTriggered();
    /**
     * TODO
     */
    void slotDatasetChanged(const ttt::Dataset::Pointer&);

    /**
     * TODO
     */
    void slotSelectedLayerChanged(const ttt::Dataset::LayerHandlerType & layer);

    void slotSelectedLayerCleared(const ttt::Dataset::LayerHandlerType & layer);


    void slotCurrentFrameChanged(unsigned long);

signals:
	/**
	 * TODO
	 */
    void datasetChanged(const ttt::Dataset::Pointer&);
    /**
     * TODO
     */
    void datasetClosed();
    /**
     * TODO
     */
    //void frameChanged(unsigned long);

private:
    /**
     * TODO
     */
    Ui::tttExplorerMainWindow *m_pUI;

    //Rendering engine
    //Main application renderer
    /**
     * TODO
     */
    vtkSmartPointer<vtkRenderer>     m_Renderer;
    //Main renderWindow;
    /**
     * TODO
     */
    vtkSmartPointer<vtkRenderWindow>    m_RenderWindow;
    //Main RenderWindowInteractor
    /**
     * TODO
     */
    vtkSmartPointer<QVTKInteractor> m_RenderWindowInteractor;
    //Signal mapper
    /**
     * TODO
     */
	vtkSmartPointer<vtkEventQtSlotConnect> m_QtToVTKConnections;
	/**
	 * TODO
	 */
    tttLayerManager * m_pLayerManager;
    /**
     * TODO
     */
    tttTimelapseManager * m_pTimelapseManager;
    /**
     * TODO
     */
    ttt::Dataset::Pointer m_Dataset;
    /**
     * TODO
     */
    QString m_DatasetPath;
    /**
     * TODO
     */
    unsigned long m_CurrentFrame;
};

#endif // TTTEXPLORERMAINWINDOW_H

#ifndef TTTLAYERMANAGER_H
#define TTTLAYERMANAGER_H

//#include "layerdrawer.h"
#include <QDockWidget>
#include <tttDataset.h>
#include <tttLayer.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include "tttlayermodel.h"
#include "tttDrawer.h"
namespace Ui {

class tttLayerManager;
}
class tttLayerManager : public QDockWidget
{
    Q_OBJECT
public:
    explicit tttLayerManager(QWidget *parent = 0,const vtkSmartPointer<vtkRenderer> & renderer =0,const vtkSmartPointer<vtkRenderWindow> & renderWindow=0 );

signals:

    void layerDeleted();
    void newLayer();
    void layerVisibilityChanged(bool);
    void selectedLayerChanged(const ttt::Dataset::LayerHandlerType &);
    void selectedLayerCleared(const ttt::Dataset::LayerHandlerType &);
    //..
public slots:
    void currentFrameChanged(unsigned long);
    void datasetChanged(const ttt::Dataset::Pointer&);
    void datasetClosed();
    void drawLayer();
    void eraseLayer();
    void showLayer(ttt::Dataset::LayerHandlerType &);
    void hideLayer(ttt::Dataset::LayerHandlerType &);

    void addLayer();
    void removeLayer();
    void setPickable();
private slots:
	void rowChanged(const QModelIndex & current , const QModelIndex & previous);

private:
    ttt::Dataset::Pointer m_Dataset;
    vtkSmartPointer<vtkRenderWindow> m_RenderWindow;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    unsigned long m_CurrentFrame;

    Ui::tttLayerManager * m_pUI;
    //std::list<LayerDrawer> m_Drawers;



    tttLayerModel * m_LayerModel;


    std::map<ttt::Layer::LayerHandlerType,ttt::Drawer::Pointer> m_Drawers;
};

#endif // TTTLAYERMANAGER_H

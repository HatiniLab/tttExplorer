#ifndef TTTLAYERMANAGER_H
#define TTTLAYERMANAGER_H

//#include "layerdrawer.h"
#include <QDockWidget>
#include <tttDataset.h>

#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
namespace Ui {

class tttLayerManager;
}
class tttLayerManager : public QDockWidget
{
    Q_OBJECT
public:
    explicit tttLayerManager(QObject *parent = 0,const vtkSmartPointer<vtkRenderer> & renderer=0 );

signals:

    void layerDeleted();
    void newLayer();
    void layerVisibilityChanged(bool);
    //..
public slots:
    void currentFrameChanged(unsigned long);
    void datasetChanged(const ttt::Dataset::Pointer&);
    void datasetClosed();
    void drawLayer();
    void eraseLayer();
    void showLayer();
    void hideLayer();
    void addLayer();
    void removeLayer();
    void setPickable();

private:
    ttt::Dataset::Pointer m_Dataset;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    unsigned long m_CurrentFrame;

    Ui::tttLayerManager * m_pUI;
    //std::list<LayerDrawer> m_Drawers;
};

#endif // TTTLAYERMANAGER_H

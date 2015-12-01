#ifndef TTTLAYERMANAGER_H
#define TTTLAYERMANAGER_H

#include "layerdrawer.h"

class tttLayerManager : public QObject
{
    Q_OBJECT
public:
    explicit tttLayerManager(QObject *parent = 0);

signals:

    void layerDeleted();
    void newLayer();
    void layerVisibilityChanged(bool);
    //..
public slots:
    void currentFrameChanged();
    void datasetChanged();
    void datasetClosed();
    void drawLayer();
    void eraseLayer();
    void showLayer();
    void hideLayer();
    void addLayer();
    void removeLayer();
    void setPickable();

private:
    std::list<LayerDrawer> m_Drawers;
};

#endif // TTTLAYERMANAGER_H

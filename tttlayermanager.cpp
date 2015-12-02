#include "tttlayermanager.h"
#include "ui_tttlayermanager.h"
tttLayerManager::tttLayerManager(QObject *parent,const vtkSmartPointer<vtkRenderer> & renderer ) :
		QDockWidget(parent),
		m_Renderer(renderer),
		m_pUI( new Ui::tttLayerManager)
{
	m_pUI->setupUi(this);


}

void tttLayerManager::currentFrameChanged(unsigned long frame) {
	m_CurrentFrame = frame;

}
void tttLayerManager::datasetChanged(const ttt::Dataset::Pointer& dataset) {
	m_Dataset = dataset;
}
void tttLayerManager::datasetClosed() {
	m_Dataset = 0;
}
void tttLayerManager::drawLayer() {

}
void tttLayerManager::eraseLayer() {

}
void tttLayerManager::showLayer() {

}
void tttLayerManager::hideLayer() {

}

void tttLayerManager::addLayer() {

}

void tttLayerManager::removeLayer() {

}
void tttLayerManager::setPickable() {

}

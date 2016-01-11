#include "tttlayermanager.h"
#include "ui_tttlayermanager.h"
#include <tttMinMaxVolumeDrawer.h>
tttLayerManager::tttLayerManager(QObject *parent,const vtkSmartPointer<vtkRenderer> & renderer,const vtkSmartPointer<vtkRenderWindow> & renderWindow ) :
		QDockWidget(parent),
		m_Renderer(renderer),
		m_RenderWindow(renderWindow),
		m_pUI( new Ui::tttLayerManager)
{
	m_pUI->setupUi(this);
	m_LayerModel= new tttLayerModel(this);

	this->m_pUI->layersTableView->setModel(m_LayerModel);

	connect(this->m_LayerModel,SIGNAL(showLayer(ttt::Dataset::LayerHandlerType &)),this,SLOT(showLayer(ttt::Dataset::LayerHandlerType &)));
	connect(this->m_LayerModel,SIGNAL(hideLayer(ttt::Dataset::LayerHandlerType &)),this,SLOT(hideLayer(ttt::Dataset::LayerHandlerType &)));
}

void tttLayerManager::currentFrameChanged(unsigned long frame) {
	std::cout << "tttLayerManager->currentFrameChanged " << frame << std::endl;

	m_CurrentFrame = frame;
	m_LayerModel->frameChanged(frame);

	auto resultset = m_Dataset->GetFramesAtTimestamp(frame);

	for(auto itDrawers =  m_Drawers.begin();itDrawers!=m_Drawers.end();++itDrawers){
		itDrawers->second->Reset();
	}
	for(auto resultIt = resultset.first;resultIt!=resultset.second;++resultIt ){
		auto layerHandler =resultIt->GetLayerHandler();
		auto layer = m_Dataset->GetLayer(layerHandler);

		if(m_Drawers.find(layerHandler)==m_Drawers.end()){

			if(layer.GetLayerType()==ttt::Layer::IMAGE){
				m_Drawers[layerHandler]=ttt::MinMaxVolumeDrawer<ttt::Dataset::FloatImageType>::New();
				m_Drawers[layerHandler]->SetRenderer(m_Renderer);
			}
		}


		if(layer.GetLayerType()==ttt::Layer::IMAGE){
			itk::ImageFileReader<ttt::Dataset::FloatImageType>::Pointer source = resultIt->GetFrameSource<itk::ImageFileReader<ttt::Dataset::FloatImageType>>();
			source->Update();

			ttt::MinMaxVolumeDrawer<ttt::Dataset::FloatImageType>::Pointer drawer = std::dynamic_pointer_cast<ttt::MinMaxVolumeDrawer<ttt::Dataset::FloatImageType>>(m_Drawers[layerHandler]);
			drawer->SetImage(source->GetOutput());
		}

		m_Drawers[layerHandler]->Draw();
		m_Drawers[layerHandler]->SetVisibility(m_LayerModel->getVisibility(layerHandler));

	}
	this->m_RenderWindow->Render();
}

void tttLayerManager::datasetChanged(const ttt::Dataset::Pointer& dataset) {
	std::cout << "tttLayerManager->datasetChanged " <<std::endl;

	m_Dataset = dataset;
	m_LayerModel->datasetChanged(m_Dataset);
}

void tttLayerManager::datasetClosed() {
	m_Dataset = 0;
}

void tttLayerManager::drawLayer() {

}

void tttLayerManager::eraseLayer() {

}

void tttLayerManager::showLayer(ttt::Dataset::LayerHandlerType & layer) {
	m_Drawers[layer]->Show();
	this->m_RenderWindow->Render();

}

void tttLayerManager::hideLayer(ttt::Dataset::LayerHandlerType & layer) {
	m_Drawers[layer]->Hide();
	this->m_RenderWindow->Render();

}

void tttLayerManager::addLayer() {

}

void tttLayerManager::removeLayer() {

}
void tttLayerManager::setPickable() {

}

#include "tttaddlayerdialog.h"
#include "ui_tttaddlayerdialog.h"

tttAddLayerDialog::tttAddLayerDialog(const ttt::Dataset::Pointer & dataset,QWidget *parent) :
    QDialog(parent),
	m_Dataset(dataset),
	m_pUI(new Ui::tttAddLayerDialog)
{
	m_pUI->setupUi(this);

}

tttAddLayerDialog::~tttAddLayerDialog()
{
    delete m_pUI;
}



void tttAddLayerDialog::accept(){
	ttt::Layer::LayerHandlerType layerHandler=m_pUI->nameLineEdit->text().toStdString();
	std::string description = m_pUI->descriptionTextEdit->toPlainText().toStdString();
	ttt::Layer::LayerType layerType = ttt::Layer::IMAGE;
	ttt::Layer newLayer(
			layerHandler,
			description,
			layerType
			);
	m_Dataset->AddLayer(newLayer);
	emit datasetChanged(m_Dataset);
	QDialog::accept();
}

void tttAddLayerDialog::reject(){
	QDialog::reject();
}


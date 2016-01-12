#include "tttaddimagelayerdialog.h"
#include "ui_tttaddimagelayerdialog.h"

tttAddImageLayerDialog::tttAddImageLayerDialog(QWidget *parent) :
    QDialog(parent),
	m_pUI(new Ui::tttAddImageLayerDialog)
{
	m_pUI->setupUi(this);

}

tttAddImageLayerDialog::~tttAddImageLayerDialog()
{
    delete m_pUI;
}



void tttAddImageLayerDialog::accept(){
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

void tttAddImageLayerDialog::reject(){
	QDialog::reject();
}


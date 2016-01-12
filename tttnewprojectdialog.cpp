#include "tttnewprojectdialog.h"
#include "ui_tttnewprojectdialog.h"

tttNewProjectDialog::tttNewProjectDialog(QWidget *parent) :
    QDialog(parent),
	m_pUI(new Ui::tttNewProjectDialog)
{
	m_pUI->setupUi(this);
}

tttNewProjectDialog::~tttNewProjectDialog()
{
    delete m_pUI;
}

void tttNewProjectDialog::accept(){
	m_Dataset= ttt::Dataset::New();
	m_Dataset->SetDatasetName(m_pUI->nameLineEdit->text().toStdString());
	m_Dataset->SetDatasetDescription(m_pUI->descriptionTextEdit->toPlainText().toStdString());
	m_Dataset->SetPath(m_pUI->directoryLineEdit->text().toStdString());

	emit datasetChanged(m_Dataset);

	QDialog::accept();

}

#include "tttnewprojectdialog.h"
#include "ui_tttnewprojectdialog.h"
#include <QFileDialog>
tttNewProjectDialog::tttNewProjectDialog(QWidget *parent) :
    QDialog(parent),
	m_pUI(new Ui::tttNewProjectDialog)
{
	m_pUI->setupUi(this);


	connect(this->m_pUI->directoryButton,SIGNAL(clicked()),this,SLOT(selectDirectory()));
}
void tttNewProjectDialog::selectDirectory(){
    QFileDialog fileDialog(this);

    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);
    if(fileDialog.exec()){
    	this->m_pUI->directoryLineEdit->setText(fileDialog.selectedFiles().first());
    }
}
tttNewProjectDialog::~tttNewProjectDialog()
{
    delete m_pUI;
}

void tttNewProjectDialog::accept(){
	m_Dataset= ttt::Dataset::New();
	m_Dataset->SetPath(m_pUI->directoryLineEdit->text().toStdString());
	m_Dataset->SetDatasetName(m_pUI->nameLineEdit->text().toStdString());
	m_Dataset->SetDatasetDescription(m_pUI->descriptionTextEdit->toPlainText().toStdString());


	emit datasetChanged(m_Dataset);

	QDialog::accept();

}

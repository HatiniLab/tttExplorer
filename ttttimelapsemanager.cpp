#include "ttttimelapsemanager.h"
#include "ui_ttttimelapsemanager.h"
tttTimelapseManager::tttTimelapseManager(QWidget *parent) :
	QDockWidget(parent),
	m_pUI(new Ui::tttTimelapseManager)
{
	m_pUI->setupUi(this);

	connect(this->m_pUI->actionForward,SIGNAL(triggered()),SLOT(forward()));
	connect(this->m_pUI->actionBackward,SIGNAL(triggered()),SLOT(backward()));
	connect(this->m_pUI->actionFirst,SIGNAL(triggered()),SLOT(first()));
	connect(this->m_pUI->actionLast,SIGNAL(triggered()),SLOT(last()));
}
void tttTimelapseManager::updateControls(){

	m_pUI->actionBackward->setEnabled(m_CurrentFrame!=m_Dataset->GetFirstTimestamp());
	m_pUI->actionFirst->setEnabled(m_CurrentFrame!=m_Dataset->GetFirstTimestamp());
	m_pUI->firstButton->setEnabled(m_CurrentFrame!=m_Dataset->GetFirstTimestamp());
	m_pUI->backwardButton->setEnabled(m_CurrentFrame!=m_Dataset->GetFirstTimestamp());

	m_pUI->actionForward->setEnabled(m_CurrentFrame!=m_Dataset->GetLastTimestamp());
	m_pUI->actionLast->setEnabled(m_CurrentFrame!=m_Dataset->GetLastTimestamp());
	m_pUI->lastButton->setEnabled(m_CurrentFrame!=m_Dataset->GetLastTimestamp());
	m_pUI->forwardButton->setEnabled(m_CurrentFrame!=m_Dataset->GetLastTimestamp());
}
void tttTimelapseManager::forward(){
	m_CurrentFrame++;
	emit currentFrameChanged(m_CurrentFrame);
	this->updateControls();
}

void tttTimelapseManager::backward(){
	m_CurrentFrame--;
	emit currentFrameChanged(m_CurrentFrame);
	this->updateControls();
}

void tttTimelapseManager::first(){
	m_CurrentFrame =m_Dataset->GetFirstTimestamp();
	emit currentFrameChanged(m_CurrentFrame);
	this->updateControls();

}

void tttTimelapseManager::last(){

	m_CurrentFrame =m_Dataset->GetLastTimestamp();
	emit currentFrameChanged(m_CurrentFrame);
	this->updateControls();
}

void tttTimelapseManager::slotCurrentFrameChanged(unsigned long frame){
	m_CurrentFrame=frame;
	emit currentFrameChanged(m_CurrentFrame);
	this->updateControls();
}
void tttTimelapseManager::datasetChanged(const ttt::Dataset::Pointer & dataset){
	m_Dataset=dataset;
	this->first();
}

void tttTimelapseManager::datasetClosed(){
	m_Dataset=0;
}

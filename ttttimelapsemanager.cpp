#include "ttttimelapsemanager.h"
#include "ui_ttttimelapsemanager.h"
tttTimelapseManager::tttTimelapseManager(QObject *parent) :
	QDockWidget(parent),
	m_pUI(new Ui::tttTimelapseManager)
{
	m_pUI->setupUi(this);

	connect(this->m_pUI->actionForward,SIGNAL(triggered()),SLOT(forward()));
	connect(this->m_pUI->actionBackward,SIGNAL(triggered()),SLOT(backward()));
	connect(this->m_pUI->actionFirst,SIGNAL(triggered()),SLOT(first()));
	connect(this->m_pUI->actionLast,SIGNAL(triggered()),SLOT(last()));
}

void tttTimelapseManager::forward(){
	m_CurrentFrame++;
	emit currentFrameChanged(m_CurrentFrame);
}

void tttTimelapseManager::backward(){
	m_CurrentFrame--;
	emit currentFrameChanged(m_CurrentFrame);
}

void tttTimelapseManager::first(){
	m_CurrentFrame =m_Dataset->GetFirstTimestamp();
	emit currentFrameChanged(m_CurrentFrame);

}

void tttTimelapseManager::last(){

	m_CurrentFrame =m_Dataset->GetLastTimestamp();
	emit currentFrameChanged(m_CurrentFrame);
}

void tttTimelapseManager::datasetChanged(const ttt::Dataset::Pointer & dataset){
	m_Dataset=dataset;
}

void tttTimelapseManager::datasetClosed(){
	m_Dataset=0;
}

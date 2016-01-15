#include "tttexplorermainwindow.h"
#include "ui_tttexplorermainwindow.h"
#include "tttnewprojectdialog.h"
#include "tttaddlayerdialog.h"
#include "tttaddframedialog.h"
#include <QFileDialog>
#include <QMessageBox>
tttExplorerMainWindow::tttExplorerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::tttExplorerMainWindow)
{
	m_pUI->setupUi(this);

	m_Renderer=vtkSmartPointer<vtkRenderer>::New();


	m_RenderWindow =this->m_pUI->centralQVTKWidget->GetRenderWindow();
	m_RenderWindow->AddRenderer(this->m_Renderer);
	m_RenderWindow->SetAlphaBitPlanes(1); //enable usage of alpha channel


	this->m_RenderWindowInteractor=this->m_pUI->centralQVTKWidget->GetInteractor();
	this->m_RenderWindowInteractor->SetDesiredUpdateRate(1.0);

	//LAYER MANAGER
	m_pLayerManager= new tttLayerManager(this,m_Renderer,m_RenderWindow);
    this->m_pLayerManager->setHidden(false);
    this->m_pLayerManager->setEnabled(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pLayerManager);
    this->m_pUI->menuWindow->addAction(this->m_pLayerManager->toggleViewAction());

    //TIMELAPSE MANAGER
	m_pTimelapseManager=new tttTimelapseManager(this);
    this->m_pTimelapseManager->setHidden(false);
    this->m_pTimelapseManager->setEnabled(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pTimelapseManager);
    this->m_pUI->menuWindow->addAction(this->m_pTimelapseManager->toggleViewAction());

    connect(this->m_pLayerManager,SIGNAL(selectedLayerChanged(const ttt::Dataset::LayerHandlerType &)),this,SLOT(slotSelectedLayerChanged(const ttt::Dataset::LayerHandlerType & )));
    connect(this->m_pLayerManager,SIGNAL(selectedLayerCleared(const ttt::Dataset::LayerHandlerType &)),this,SLOT(slotSelectedLayerCleared(const ttt::Dataset::LayerHandlerType & )));

	connect(this->m_pUI->actionOpenDataset,SIGNAL(triggered()),SLOT(actionOpenDatasetTriggered()));
	connect(this->m_pUI->actionNewDataset,SIGNAL(triggered()),SLOT(actionNewDatasetTriggered()));
	connect(this->m_pUI->actionCloseDataset,SIGNAL(triggered()),SLOT(actionCloseDatasetTriggered()));
	connect(this->m_pUI->actionAddLayer,SIGNAL(triggered()),SLOT(actionNewLayerTriggered()));
	connect(this->m_pUI->actionRemoveLayer,SIGNAL(triggered()),SLOT(actionRemoveLayerTriggered()));

	connect(this->m_pUI->actionAddFrame,SIGNAL(triggered()),SLOT(actionAddFrameTriggered()));

	connect(this->m_pUI->actionRemoveFrame,SIGNAL(triggered()),SLOT(actionRemoveFrameTriggered()));

	connect(this->m_pUI->actionExit,SIGNAL(triggered()),this,SLOT(actionExitTriggered()));

	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pLayerManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pTimelapseManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this,SLOT(slotDatasetChanged(ttt::Dataset::Pointer)));

	connect(this,SIGNAL(datasetClosed()),this->m_pLayerManager,SLOT(datasetClosed()));
	connect(this,SIGNAL(datasetClosed()),this->m_pTimelapseManager,SLOT(datasetClosed()));

	connect(this->m_pUI->timeSlider,SIGNAL(valueChanged(int)),this,SLOT(actionTimesliderMoved(int)));

	connect(this->m_pTimelapseManager,SIGNAL(currentFrameChanged(unsigned long)),this->m_pLayerManager,SLOT(currentFrameChanged(unsigned long)));
	connect(this->m_pTimelapseManager,SIGNAL(currentFrameChanged(unsigned long)),this,SLOT(slotCurrentFrameChanged(unsigned long)));


}

void tttExplorerMainWindow::slotSelectedLayerChanged(const ttt::Dataset::LayerHandlerType & layer){
	this->m_pUI->actionRemoveLayer->setEnabled(true);
	this->m_pUI->actionRemoveFrame->setEnabled(true);
}

void tttExplorerMainWindow::slotSelectedLayerCleared(const ttt::Dataset::LayerHandlerType & layer){
	this->m_pUI->actionRemoveLayer->setEnabled(false);
	this->m_pUI->actionRemoveFrame->setEnabled(false);
}

void tttExplorerMainWindow::slotCurrentFrameChanged(unsigned long frame){
	this->m_pUI->timeSlider->blockSignals(true);

	this->m_pUI->timeSlider->setValue(frame);
	this->m_pUI->timeSlider->blockSignals(false);

}

void tttExplorerMainWindow::slotDatasetChanged(const ttt::Dataset::Pointer & dataset){
	m_Dataset=dataset;
	this->setupUI();
}


void tttExplorerMainWindow::actionTimesliderMoved(int value){
	this->m_pTimelapseManager->slotCurrentFrameChanged((unsigned long) value);
}

void tttExplorerMainWindow::actionExitTriggered(){
    QApplication::quit();
}

tttExplorerMainWindow::~tttExplorerMainWindow()
{
    delete m_pUI;
}

void tttExplorerMainWindow::actionAddFrameTriggered(){
	this->m_pUI->statusBar->showMessage(tr("New Frame..."));
	tttAddFrameDialog dialog(m_Dataset,this);
	//dialog.setDataset(m_Dataset);
	connect(&dialog, &tttAddFrameDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	dialog.exec();
	disconnect(&dialog, &tttAddFrameDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	this->m_pUI->statusBar->showMessage(tr("Ready"));
}

void tttExplorerMainWindow::actionRemoveFrameTriggered(){
	this->m_pUI->statusBar->showMessage(tr("Removing Frame..."));

	QMessageBox  msgBox(this);
	msgBox.setText("This will remove permanently the selected frame from the dataset. Do you really want to proceed?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	msgBox.setIcon(QMessageBox::Warning);
	//m_pLayerManager->removeSelectedLayer();
	int ret = msgBox.exec();

	if(ret==QMessageBox::Ok){
		std::cout << "Ok" << std::endl;
	}else if(ret==QMessageBox::Cancel){
		std::cout << "Cancel" << std::endl;
	}

	this->m_pUI->statusBar->showMessage(tr("Ready"));

}
void tttExplorerMainWindow::actionNewLayerTriggered(){
	this->m_pUI->statusBar->showMessage(tr("New layer..."));
	tttAddLayerDialog dialog(m_Dataset,this);
	//dialog.setDataset(m_Dataset);
	connect(&dialog, &tttAddLayerDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	dialog.exec();
	disconnect(&dialog, &tttAddLayerDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	this->m_pUI->statusBar->showMessage(tr("Ready"));
}

void tttExplorerMainWindow::actionRemoveLayerTriggered(){
	this->m_pUI->statusBar->showMessage(tr("New layer..."));

	QMessageBox  msgBox(this);
	msgBox.setText("This will remove permanently the selected layer from the dataset. Do you really want to proceed?");
	msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	msgBox.setIcon(QMessageBox::Warning);
	//m_pLayerManager->removeSelectedLayer();
	int ret = msgBox.exec();

	if(ret==QMessageBox::Ok){
		std::cout << "Ok" << std::endl;
	}else if(ret==QMessageBox::Cancel){
		std::cout << "Cancel" << std::endl;
	}
	this->m_pUI->statusBar->showMessage(tr("Ready"));
}

void tttExplorerMainWindow::actionNewDatasetTriggered(){
	this->m_pUI->statusBar->showMessage(tr("New dataset..."));
	tttNewProjectDialog dialog(this);
	connect(&dialog, &tttNewProjectDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	dialog.exec();
	disconnect(&dialog, &tttNewProjectDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	this->m_pUI->statusBar->showMessage(tr("Ready"));
}

void tttExplorerMainWindow::setupUI(){

	this->m_pUI->timeSlider->setMinimum(m_Dataset->GetFirstTimestamp());
	this->m_pUI->timeSlider->setMaximum(m_Dataset->GetLastTimestamp());
	this->m_pUI->timeSlider->setEnabled(true);
	this->m_pUI->centralQVTKWidget->setEnabled(true);

	this->m_pLayerManager->setEnabled(true);
	this->m_pUI->actionAddLayer->setEnabled(true);
	this->m_pUI->actionAddFrame->setEnabled(true);

	this->m_pTimelapseManager->setEnabled(true);

	this->m_pUI->actionCloseDataset->setEnabled(true);
}
void tttExplorerMainWindow::actionOpenDatasetTriggered(){

    QFileDialog fileDialog(this);

    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);


    if(fileDialog.exec()){
        this->m_DatasetPath=fileDialog.selectedFiles().first();

        std::cout << this->m_DatasetPath.toStdString() << std::endl;

        this->m_Dataset = ttt::Dataset::New();
        this->m_Dataset->SetPath(this->m_DatasetPath.toStdString());
        if(this->m_Dataset->Load()){
        	emit datasetChanged(m_Dataset);
        	this->setupUI();
            this->m_CurrentFrame=0;
            this->m_pTimelapseManager->slotCurrentFrameChanged(this->m_CurrentFrame);
            //emit frameChanged(this->m_CurrentFrame);

        }else{

            QMessageBox errorMessage(this);
            errorMessage.setText("Unable to Open Project");
            errorMessage.setInformativeText("Please check the selected directory contains a valid project and try again");
            errorMessage.setIcon(QMessageBox::Critical);
            errorMessage.exec();

        }
        //C

        //
    }

}
void tttExplorerMainWindow::actionCloseDatasetTriggered(){

	emit datasetClosed();

	this->m_pUI->timeSlider->setEnabled(false);
	this->m_pUI->centralQVTKWidget->setEnabled(false);

	this->m_pLayerManager->setEnabled(false);
	this->m_pUI->actionAddLayer->setEnabled(false);
	this->m_pUI->actionAddFrame->setEnabled(false);

	this->m_pTimelapseManager->setEnabled(false);

	this->m_pUI->actionCloseDataset->setEnabled(false);
}

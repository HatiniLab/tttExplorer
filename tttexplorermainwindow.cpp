#include "tttexplorermainwindow.h"
#include "ui_tttexplorermainwindow.h"
#include <QFileDialog>
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


	m_pLayerManager= new tttLayerManager(this);
    this->m_pLayerManager->setHidden(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pLayerManager);

	m_pTimelapseManager=new tttTimelapseManager(this);

    this->m_pTimelapseManager->setHidden(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pTimelapseManager);

	connect(this->m_pUI->actionOpenDataset,SIGNAL(triggered()),SLOT(actionOpenDatasetTriggered()));
	connect(this->m_pUI->actionNewDataset,SIGNAL(triggered()),SLOT(actionNewDatasetTriggered()));

	connect(this,SIGNAL(frameChanged(unsigned long)),this->m_pLayerManager,SLOT(currentFrameChanged(unsigned long)));
	connect(this->m_pTimelapseManager,SIGNAL(currentFrameChanged(unsigned long)),this->m_pLayerManager,SLOT(currentFrameChanged(unsigned long)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pLayerManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pTimelapseManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));



}

tttExplorerMainWindow::~tttExplorerMainWindow()
{
    delete m_pUI;
}

void tttExplorerMainWindow::actionNewDatasetTriggered(){

	emit datasetChanged(m_Dataset);
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
            this->m_CurrentFrame=0;
            emit frameChanged(this->m_CurrentFrame);
#if 0
            this->DrawFrame(0);
            this->m_pUI->actionOpenFile->setEnabled(false);
            this->m_pUI->visualizationDock->setEnabled(true);

            this->m_pUI->frameSlider->blockSignals(true);
            this->m_pUI->frameSlider->setEnabled(true);
            this->m_pUI->frameSlider->setMinimum(0);
            this->m_pUI->frameSlider->setMaximum(this->m_Project.GetNumberOfFrames()-1);
            this->m_pUI->frameSlider->setValue(0);
            this->m_pUI->frameSlider->setTickInterval(1);
            this->m_pUI->frameSlider->blockSignals(false);

            this->m_pUI->actionDetectVertices->setEnabled(true);

            this->m_pUI->actionSelectVertex->setEnabled(true);
            this->m_pUI->actionAddVertices->setEnabled(true);

            this->m_pUI->actionSelectEdge->setEnabled(true);
            this->m_pUI->actionAddEdge->setEnabled(true);

            this->m_pUI->actionTrackVertices->setEnabled(true);
            this->m_pUI->actionVertexMolecularDistribution->setEnabled(true);
            this->m_pUI->actionEdgeMolecularDistribution->setEnabled(true);
            this->m_pUI->statusbar->showMessage(tr("Ready"));


            this->m_pGraphPlotterDockWidget->SetLength(m_Project.GetNumberOfFrames());
#endif

        }else{
#if 0

            std::cout << "Error: " << std::endl;
            QMessageBox errorMessage(this);
            errorMessage.setText("Unable to Open Project");
            errorMessage.setInformativeText("Please check the selected directory contains a valid project and try again");
            errorMessage.setIcon(QMessageBox::Critical);
            errorMessage.exec();
#endif
        }
        //C

        //
    }

}
void tttExplorerMainWindow::actionCloseDatasetTriggered(){

	emit datasetClosed();
}

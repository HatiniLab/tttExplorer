#include "tttexplorermainwindow.h"
#include "ui_tttexplorermainwindow.h"
#include "tttnewprojectdialog.h"
#include "tttaddimagelayerdialog.h"
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


	m_pLayerManager= new tttLayerManager(this,m_Renderer,m_RenderWindow);
    this->m_pLayerManager->setHidden(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pLayerManager);

	m_pTimelapseManager=new tttTimelapseManager(this);

    this->m_pTimelapseManager->setHidden(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pTimelapseManager);

	connect(this->m_pUI->actionOpenDataset,SIGNAL(triggered()),SLOT(actionOpenDatasetTriggered()));
	connect(this->m_pUI->actionNewDataset,SIGNAL(triggered()),SLOT(actionNewDatasetTriggered()));

	connect(this->m_pUI->actionAddLayer,SIGNAL(triggered()),SLOT(actionNewLayerTriggered()));
	connect(this->m_pUI->actionShowLayers,SIGNAL(toggled(bool)),SLOT(actionShowLayersChanged(bool)));

	connect(this,SIGNAL(frameChanged(unsigned long)),this->m_pLayerManager,SLOT(currentFrameChanged(unsigned long)));
	connect(this->m_pTimelapseManager,SIGNAL(currentFrameChanged(unsigned long)),this->m_pLayerManager,SLOT(currentFrameChanged(unsigned long)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pLayerManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this->m_pTimelapseManager,SLOT(datasetChanged(ttt::Dataset::Pointer)));
	connect(this,SIGNAL(datasetChanged(const ttt::Dataset::Pointer&)),this,SLOT(slotDatasetChanged(ttt::Dataset::Pointer)));
	connect(this->m_pUI->timeSlider,SIGNAL(valueChanged(int)),this,SLOT(actionTimesliderMoved(int)));


}

void tttExplorerMainWindow::slotDatasetChanged(const ttt::Dataset::Pointer & dataset){
	m_Dataset=dataset;
}

void tttExplorerMainWindow::actionShowLayersChanged(bool){
    this->m_pLayerManager->setHidden(false);
    this->addDockWidget(Qt::RightDockWidgetArea,this->m_pLayerManager);

}
void tttExplorerMainWindow::actionTimesliderMoved(int value){
	emit frameChanged((unsigned long) value);
}

tttExplorerMainWindow::~tttExplorerMainWindow()
{
    delete m_pUI;
}

void tttExplorerMainWindow::actionAddFrameTriggered(){
#if 0
	QStringList files = wizard.getSelectedFiles();

	typedef itk::ImageFileReader<ttt::Dataset::FloatImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();

		Layer newLayer("RawImage","",Layer::IMAGE);
		ttt::Dataset::LayerHandlerType layer = m_Dataset.AddLayer(newLayer);
		for(QStringList::Iterator it = files.begin();it!=files.end();++it){
			reader->SetFileName((*it).toStdString());
			Frame newFrame = m_Dataset.NewFrame(,);

		}
#endif
}
void tttExplorerMainWindow::actionNewLayerTriggered(){
	tttAddImageLayerDialog dialog(this);
	dialog.setDataset(m_Dataset);
	connect(&dialog, &tttAddImageLayerDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);
	dialog.exec();
	disconnect(&dialog, &tttAddImageLayerDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);


}
void tttExplorerMainWindow::actionNewDatasetTriggered(){
	tttNewProjectDialog dialog(this);
	connect(&dialog, &tttNewProjectDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);

	dialog.exec();

	disconnect(&dialog, &tttNewProjectDialog::datasetChanged, this, &tttExplorerMainWindow::datasetChanged);

}

void tttExplorerMainWindow::setupUI(){

	this->m_pUI->timeSlider->setMinimum(m_Dataset->GetFirstTimestamp());
	this->m_pUI->timeSlider->setMaximum(m_Dataset->GetLastTimestamp());
	this->m_pUI->timeSlider->setEnabled(true);
	this->m_pUI->centralQVTKWidget->setEnabled(true);
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

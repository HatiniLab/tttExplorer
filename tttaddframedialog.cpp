#include "tttaddframedialog.h"
#include "ui_tttaddframedialog.h"
#include <QDoubleSpinBox>
#include <itkImageFileWriter.h>
tttAddFrameDialog::tttAddFrameDialog(const ttt::Dataset::Pointer & dataset,QWidget *parent) :
    QDialog(parent),
	m_Dataset(dataset),
	m_pUI(new Ui::tttAddFrameDialog)
{
	m_pUI->setupUi(this);
	int k=0;

	for(auto it = m_Dataset->BeginLayerHandlers();it!=m_Dataset->EndLayerHandlers();++it){
		this->m_pUI->layerComboBox->insertItem(k,QString::fromStdString(*it));
		k++;
	}
	connect(this->m_pUI->addFilesButton,SIGNAL(clicked()),SLOT(addFile()));

	 QStringList tableHeader;
	 tableHeader << "Name"<<"Timestamp"<<"Size X"<<"Size Y" << "Size Z" << "Spacing X" << "Spacing Y" << "Spacing Z";
	 this->m_pUI->selectedFilesWidget->setHorizontalHeaderLabels(tableHeader);
}

tttAddFrameDialog::~tttAddFrameDialog()
{
    delete m_pUI;
}
void tttAddFrameDialog::addFile(){


	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
    //fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(dialog.exec()){
    	//typedef itk::ImageFileReader<ttt::Dataset::FloatImageType> ReaderType;
    	//ReaderType::Pointer reader = ReaderType::New();
    	typedef itk::MetaImageIO IOType;

    	IOType::Pointer imageIO = IOType::New();
    	QStringList selectedFiles = dialog.selectedFiles();

    	for(QStringList::iterator it = selectedFiles.begin();it!=selectedFiles.end();++it){
    		this->m_pUI->selectedFilesWidget->setRowCount(this->m_pUI->selectedFilesWidget->rowCount()+1);

    		int row = this->m_pUI->selectedFilesWidget->rowCount()-1;

    		QTableWidgetItem * fileItem = new QTableWidgetItem(*it);
    		this->m_pUI->selectedFilesWidget->setItem(row,0,fileItem);

    		QTableWidgetItem * timestampItem = new QTableWidgetItem("1");
    		this->m_pUI->selectedFilesWidget->setItem(row,1,timestampItem);

    		imageIO->SetFileName((*it).toStdString());
    		imageIO->ReadImageInformation();

    		QTableWidgetItem * dimX = new QTableWidgetItem(tr("%1").arg(imageIO->GetDimensions(0)));
    		this->m_pUI->selectedFilesWidget->setItem(row, 2, dimX);

    		QTableWidgetItem * dimY = new QTableWidgetItem(tr("%1").arg(imageIO->GetDimensions(1)));
    		this->m_pUI->selectedFilesWidget->setItem(row, 3, dimY);

    		QTableWidgetItem * dimZ = new QTableWidgetItem(tr("%1").arg(imageIO->GetDimensions(2)));
    		this->m_pUI->selectedFilesWidget->setItem(row, 4, dimZ);

    		QDoubleSpinBox * spacingX = new QDoubleSpinBox(this);//new QTableWidgetItem(tr("%1").arg(imageIO->GetSpacing(0)));
    		spacingX->setDecimals(6);
    		spacingX->setValue(imageIO->GetSpacing(0));


    		this->m_pUI->selectedFilesWidget->setCellWidget(row, 5, spacingX);

    	    QDoubleSpinBox * spacingY = new QDoubleSpinBox(this);//new QTableWidgetItem(tr("%1").arg(imageIO->GetSpacing(0)));
    	    spacingY->setDecimals(6);
    	    spacingY->setValue(imageIO->GetSpacing(1));

    	    this->m_pUI->selectedFilesWidget->setCellWidget(row, 6, spacingY);

    	    QDoubleSpinBox * spacingZ = new QDoubleSpinBox(this);//new QTableWidgetItem(tr("%1").arg(imageIO->GetSpacing(0)));
    	    spacingZ->setDecimals(6);
    	    spacingZ->setValue(imageIO->GetSpacing(2));

    	    this->m_pUI->selectedFilesWidget->setCellWidget(row, 7, spacingZ);
    	}
    }
}

void tttAddFrameDialog::accept(){

	typedef itk::ImageFileReader<ttt::Dataset::FloatImageType> ReaderType;
	ReaderType::Pointer reader = ReaderType::New();

	typedef itk::ImageFileWriter<ttt::Dataset::FloatImageType> WriterType;


	for(int r=0;r<this->m_pUI->selectedFilesWidget->rowCount();r++){
		reader->SetFileName(this->m_pUI->selectedFilesWidget->item(r,0)->text().toStdString());
		long timestamp = this->m_pUI->selectedFilesWidget->item(r,1)->text().toLong();
		ttt::Layer::LayerHandlerType layerHandler = this->m_pUI->layerComboBox->currentText().toStdString();
		ttt::Frame newFrame = m_Dataset->NewFrame(timestamp,layerHandler);

		WriterType::Pointer writer = newFrame.GetFrameSink<WriterType>();

		writer->SetInput(reader->GetOutput());
		writer->Update();
	}
	emit datasetChanged(m_Dataset);
	QDialog::accept();
}


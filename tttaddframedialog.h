#ifndef TTTADDFRAMEDIALOG_H
#define TTTADDFRAMEDIALOG_H

#include <QDialog>
#include "tttDataset.h"
#include "tttLayer.h"
#include <QFileDialog>
#include <itkMetaImageIO.h>
namespace Ui {
class tttAddFrameDialog;
}

class tttAddFrameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tttAddFrameDialog(const ttt::Dataset::Pointer & dataset,QWidget *parent = 0);
    ~tttAddFrameDialog();

    inline void setDataset(const ttt::Dataset::Pointer & dataset){
    	m_Dataset=dataset;
    }

private slots:
    void addFile();

public slots:
	void accept();

signals:
	void datasetChanged(const ttt::Dataset::Pointer &);

private:
    Ui::tttAddFrameDialog *m_pUI;

    ttt::Dataset::Pointer m_Dataset;

};

#endif // TTTADDFRAMEDIALOG_H

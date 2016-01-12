#ifndef ADDIMAGELAYERDIALOG_H
#define ADDIMAGELAYERDIALOG_H

#include <QDialog>
#include "tttLayer.h"
#include "tttDataset.h"

namespace Ui {
class tttAddImageLayerDialog;
}

class tttAddImageLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tttAddImageLayerDialog(QWidget *parent = 0);
    ~tttAddImageLayerDialog();

    inline void setDataset(ttt::Dataset::Pointer & dataset){
    	m_Dataset=dataset;
    }

public slots:
	virtual void accept();
	virtual void reject();
signals:
	void datasetChanged(const ttt::Dataset::Pointer & dataset);

private:
    Ui::tttAddImageLayerDialog *m_pUI;
    ttt::Dataset::Pointer  m_Dataset;

};

#endif // ADDIMAGELAYERDIALOG_H

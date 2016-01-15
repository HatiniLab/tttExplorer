#ifndef ADDIMAGELAYERDIALOG_H
#define ADDIMAGELAYERDIALOG_H

#include <QDialog>
#include "tttLayer.h"
#include "tttDataset.h"

namespace Ui {
class tttAddLayerDialog;
}

class tttAddLayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tttAddLayerDialog(const ttt::Dataset::Pointer & dataset,QWidget *parent = 0);
    ~tttAddLayerDialog();

public slots:
	virtual void accept();
	virtual void reject();
signals:
	void datasetChanged(const ttt::Dataset::Pointer & dataset);

private:
    Ui::tttAddLayerDialog *m_pUI;
    ttt::Dataset::Pointer  m_Dataset;

};

#endif // ADDIMAGELAYERDIALOG_H

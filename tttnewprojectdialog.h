#ifndef TTTNEWPROJECTDIALOG_H
#define TTTNEWPROJECTDIALOG_H

#include <QDialog>
#include "tttDataset.h"
namespace Ui {
class tttNewProjectDialog;
}

class tttNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tttNewProjectDialog(QWidget *parent = 0);
    ~tttNewProjectDialog();

public slots:
	virtual void accept();

signals:

	void datasetChanged(const ttt::Dataset::Pointer & dataset);

private:
    Ui::tttNewProjectDialog *m_pUI;
    ttt::Dataset::Pointer m_Dataset;
};

#endif // TTTNEWPROJECTDIALOG_H

#ifndef TTTTIMELAPSEMANAGER_H
#define TTTTIMELAPSEMANAGER_H

#include <QDockWidget>
#include "tttDataset.h"
namespace Ui {

class tttTimelapseManager;

}

class tttTimelapseManager : public QDockWidget
{
    Q_OBJECT
public:
    explicit tttTimelapseManager(QObject *parent = 0);

signals:
    void currentFrameChanged(unsigned long);
public slots:
    void datasetClosed();
    void datasetChanged(const ttt::Dataset::Pointer & );
    void forward();
    void backward();
    void first();
    void last();
    //void play();
    //void pause();
private:
    unsigned long m_CurrentFrame;
    ttt::Dataset::Pointer m_Dataset;
    Ui::tttTimelapseManager * m_pUI;
};

#endif // TTTTIMELAPSEMANAGER_H

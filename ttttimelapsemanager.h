#ifndef TTTTIMELAPSEMANAGER_H
#define TTTTIMELAPSEMANAGER_H


class tttTimelapseManager : public QObject
{
    Q_OBJECT
public:
    explicit tttTimelapseManager(QObject *parent = 0);

signals:
    void currentFrameChanged();
public slots:
    void datasetClosed();
    void datasetChanged();
    void forward();
    void backward();
    void play();
    void pause();
};

#endif // TTTTIMELAPSEMANAGER_H

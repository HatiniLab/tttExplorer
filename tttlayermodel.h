/*
 * tttLayerModel.h
 *
 *  Created on: Dec 3, 2015
 *      Author: morgan
 */

#ifndef TTTLAYERMODEL_H_
#define TTTLAYERMODEL_H_
#include <QAbstractTableModel>
#include <tttDataset.h>
#include <tttLayer.h>
class tttLayerModel: public QAbstractTableModel {
Q_OBJECT
public:
	explicit tttLayerModel(QObject * parent = 0);
	virtual ~tttLayerModel();
	/**
	 * Get the number of layers at the current frame
	 */
	int rowCount(const QModelIndex &parent = QModelIndex()) const {
		return m_Layers.size();

	}
	/**
	 * Return the number of columns - 3
	 */
	int columnCount(const QModelIndex &parent = QModelIndex()) const {
		return 2;
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			if(orientation==Qt::Horizontal){
				switch (section) {
				case 0:
					return QString("Show");
					break;
				case 1:
					return QString("Name");
					break;
				}
			}else{
					return QVariant(section+1);
			}
		}
		return QVariant();
	}
	/**
	 * Return the contents
	 */
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			if (index.column() == 1) {
				//return QString::fromStdString(static_cast<std::string>(m_Layers[index.row()]));
				return QString::fromStdString(m_Layers[index.row()]);
			} else {
				return QVariant();
			}
		}
		if (role == Qt::CheckStateRole) {  // this shows the checkbox
			if (index.column() == 0) {
				ttt::Dataset::LayerHandlerType layer = m_Layers[index.row()];
				if (m_ShowLayer.at(layer))
					return Qt::Checked;
				else
					return Qt::Unchecked;
			}
			return QVariant();
		}
		if(role == Qt::TextAlignmentRole	){
			if(index.column()==0){
				return Qt::AlignCenter;
			}else{
				return Qt::AlignLeft;
			}
		}
		return QVariant();
	}

	Qt::ItemFlags flags(const QModelIndex & index) const {
		if (!index.isValid()){
			return Qt::ItemIsEnabled;
		}else{
			if (index.column() == 0) {
				return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable /*| Qt::ItemIsEditable */ ;
			}else{
				return QAbstractItemModel::flags(index)	;
			}

		 }


	}

	bool setData(const QModelIndex &index,const QVariant &value, int role = Qt::EditRole)
	{
	    if ( index.isValid() && role == Qt::CheckStateRole) {
	    	if(index.column()==0){
	    		auto layer = m_Layers[index.row()];
	    		m_ShowLayer[layer]=value.toBool();

	    		if(value.toBool()){
	    			emit showLayer(layer);
	    		}else{
	    			emit hideLayer(layer);
	    		}

	    	}
	        emit dataChanged(index, index);
	        return true;
	    }
	    return false;
	}

public slots:
	/**
	 * Update information about the current frame
	 */
	void frameChanged(unsigned long frame) {
		m_CurrentFrame = frame;

		auto resultSet = m_Dataset->GetFramesAtTimestamp(frame);
		m_Layers.clear();

		for (auto frameIt = resultSet.first; frameIt != resultSet.second; ++frameIt) {
			m_Layers.push_back(frameIt->m_LayerHandler);
		}
		emit layoutChanged();
	}
	/**
	 * Update the dataset
	 */
	void datasetChanged(ttt::Dataset::Pointer & dataset) {

		m_Dataset = dataset;
	}
	/**
	 * Close the dataset
	 */
	void datasetClosed() {
		m_Dataset = 0;
		m_Layers.clear();
		m_ShowLayer.clear();
	}

	bool getVisibility(const ttt::Dataset::LayerHandlerType & layer ){
		return m_ShowLayer[layer];
	}
	ttt::Dataset::LayerHandlerType getLayerAtRow(int row){
		return m_Layers[row];
	}
signals:
	void showLayer(ttt::Dataset::LayerHandlerType &);
	void hideLayer(ttt::Dataset::LayerHandlerType &);

private:
	ttt::Dataset::Pointer m_Dataset;

	std::vector<ttt::Dataset::LayerHandlerType> m_Layers;
	int m_CurrentFrame;

    std::map<ttt::Dataset::LayerHandlerType,bool> m_ShowLayer;

};

#endif /* TTTLAYERMODEL_H_ */

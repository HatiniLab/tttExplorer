/*
 * tttLayerModel.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: morgan
 */

#include "tttlayermodel.h"

tttLayerModel::tttLayerModel(QObject * parent) : QAbstractTableModel(parent) {
	m_CurrentFrame=0;
}

tttLayerModel::~tttLayerModel() {

}


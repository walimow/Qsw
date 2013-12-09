/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef QSTWENVIRONMENTDATA_H
#define QSTWENVIRONMENTDATA_H

#include <QtCore/QObject>
#include <QVariant>
#include <QPointer>


namespace qstepwork{

class QstwEnvironmentData : public QObject
{
    Q_OBJECT
    QVariant	m_variant;
    QPointer<QObject>	m_oPtr;
public:
    QstwEnvironmentData(QObject* parent=nullptr);
    QstwEnvironmentData(QVariant var, QObject* parent=nullptr);
    void setObject(QObject*p){m_oPtr=p;}
    QObject* getObject(){ return m_oPtr;}
    QVariant& data(){return m_variant;}
    
private:

};

}

#endif // QSTWENVIRONMENTDATA_H

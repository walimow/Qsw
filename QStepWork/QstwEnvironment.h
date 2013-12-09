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

#ifndef QSTWENVIRONMENT_H
#define QSTWENVIRONMENT_H

#include <QObject>
#include <QSharedDataPointer>
#include <QPointer>
#include <set>
#include <QStepWalk.h>
#include <QVariant>
#include <QUuid>
#include <QString>

#include <QstwForward.h>

namespace qstepwork {

///DataEnvironment, can be bound in a hierarchy

///MsgEnvironment

///Context, where an StepBaseObject is instanciated in


class QstwEnvironment :  public QObject, public IEnvironment
{
    QPointer<QstwEnvironment>  m_oSuper;
    QString _envTitel;
    QUuid   _uuid;
    
    Q_OBJECT
   
   
    Q_PROPERTY(QString envTitel READ envTitel )
    Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid )
public:


    QstwEnvironment();
    explicit QstwEnvironment(QObject* parent);
    ~QstwEnvironment();
    QString envTitel() const {
        return _envTitel;
    }

    QUuid  uuid() const {
        return _uuid;
    }
    void setUuid(QUuid uuid) {
        _uuid=uuid;
    }

    unsigned int  size() override {
        return m_entries.size();
    }
    void  clearEnvironment() override  {
        m_entries.clear();
    }



    struct Entry: public IEntry
    {
        int option=0;
        QVariant 		m_varData;
        QPointer<QObject>  m_oPtr;
        QString  m_sName;

        struct Less: std::binary_function<Entry,Entry,bool>
        {
            bool operator() ( const Entry&o1,const  Entry& o2 ) const
            {
                return o1.name()<o2.name();
            };
        };

        const QString& name()const override {
            return m_sName;
        }

        void assignData(const QVariant&v)override {
            m_varData=v;
        };
        QVariant&  data() override	{
            return m_varData;
        }
        QObject* obj() override {
            return m_oPtr;
        }
        void setObj(QObject*p)override {
            m_oPtr=p;
        }
    };
    bool hasEntry(const QString& name, bool bHier);
    const Entry&	getEntry(const QString& name, bool bHier=true, const Entry&  _default=nullEntry);
///IEnvironment

    bool hasEntry(const std::string&, bool bHierarch=false)override;
    IEnvironment::IEntry& entry(const std::string&, bool bHierarch=false)override;
    IEnvironment::IEntry& operator[](const std::string&)override;
    IEnvironment* superEnvironment()override;

    template<typename T>
    IEnvironment::IEntry&  setEntry(const std::string& sName_, const T& value) {
        Entry e;
        e.m_sName=   sName_.c_str();
        e.m_varData = value;
        return (IEnvironment::IEntry&)*m_entries.insert(e).first;
    }

    static QstwEnvironment * createEnvironment( QstwDataForm& list, const QString& s, QstwEnvironment *pSuper);

signals:
    void beforeEnterInstance( IStepSupport*);  //proto?
    void onEnterInstance( IStepSupport*);	//object
    void beforeLeaveInstance( IStepSupport*);

private:
    static  Entry nullEntry;
    std::set<Entry, Entry::Less>	m_entries;

};



}

#endif // QSTWENVIRONMENT_H

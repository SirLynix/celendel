#include "TableEditor.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QScrollArea>

TableLine::TableLine(const QString& s1, const QString& s2, QWidget* par) : QWidget(par)
{
        m_l1 = new QLineEdit(this);
        m_l1->setText(s1);
        m_l1->setPlaceholderText(tr("Index..."));

        m_l2 = new QLineEdit(this);
        m_l2->setText(s2);
        m_l2->setPlaceholderText(tr("Donnée..."));

        m_delete = new QPushButton(tr("X"), this);
        connect(m_delete, SIGNAL(pressed()), this, SIGNAL(suicide()));

        QHBoxLayout* lay = new QHBoxLayout;
        lay->addWidget(m_l1);
        lay->addWidget(m_l2);
        lay->addWidget(m_delete);
        setLayout(lay);
}

QStringPair TableLine::getPair() const
{
    return qMakePair(m_l1->text(),m_l2->text());
}


TableEditor::TableEditor(QWidget* par, const QStringPairList& list) : QDialog(par)
{
    QVBoxLayout* lay = new QVBoxLayout;
    setLayout(lay);
    QScrollArea* scrll=new QScrollArea(this);
    scrll->setWidgetResizable(true);
    lay->addWidget(scrll);
    QWidget* wscrll=new QWidget(scrll);
    wscrll->setMinimumSize(300,100);
    scrll->setWidget(wscrll);
    m_layout=new QVBoxLayout;
    m_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    wscrll->setLayout(m_layout);

    m_newLine = new QPushButton(tr("Nouvelle ligne"), this);
    connect(m_newLine, SIGNAL(pressed()), this, SLOT(newLine()));
    lay->addWidget(m_newLine);

    m_ok = new QPushButton(tr("Valider"), this);
    connect(m_ok, SIGNAL(pressed()), this, SLOT(accept()));
    lay->addWidget(m_ok);

    if(!list.isEmpty())
        setList(list);
    else
        newLine();
}

QStringPairList TableEditor::getList() const
{
    QStringPairList ret;
    for(int i=0,m=m_list.size();i<m;++i)
        ret.append(m_list[i]->getPair());
    return ret;
}

void TableEditor::setList(const QStringPairList& list)
{
    for(int i=0,m=m_list.size();i<m;++i)
        delete m_list[i];

    m_list.clear();

    for(int i=0,m=list.size();i<m;++i)
        addLine(list[i].first,list[i].second);
}

void TableEditor::newLine()
{
    addLine();
}

void TableEditor::deleteLine()
{
    TableLine* li = qobject_cast<TableLine*>(sender());
    m_list.removeAll(li);
    delete li;
}

void TableEditor::addLine(const QString& s1, const QString& s2)
{
    TableLine* li = new TableLine(s1,s2,this);
    connect(li, SIGNAL(suicide()), this, SLOT(deleteLine()));
    m_list.append(li);
    m_layout->addWidget(li);
}

QStringPairList TableEditor::editList(QWidget* parent,const QStringPairList& list, bool* ok)
{
    bool b=false;
    if(ok==0)
        ok=&b;

    *ok=false;

    TableEditor t(parent, list);
    if(t.exec() == QDialog::Accepted)
        *ok=true;

    return t.getList();
}


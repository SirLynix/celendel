#include <QLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <limits>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerlua.h>

#include "EntityMaker.h"
#include "../Shared/LuaSystem/ScriptedEntity.h"
#include "TableEditor.h"

Line::Line(QWidget* par) : QWidget(par)
{
    m_b=false;

    QHBoxLayout* lay=new QHBoxLayout;

    m_name = new QLineEdit(this);
    lay->addWidget(m_name);
    m_shownName = new QLineEdit(this);
    lay->addWidget(m_shownName);
    m_comboBox = new QComboBox(this);
    {QStringList l;l<<tr("String")<<tr("Nombre")<<tr("Table");m_comboBox->addItems(l);}
    connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(cbChngd(int)));
    lay->addWidget(m_comboBox);

    m_string=new QLineEdit(this);
    m_string->setPlaceholderText(tr("Texte..."));
    lay->addWidget(m_string);
    m_editList=new QPushButton(tr("Editer la table"), this);
    connect(m_editList, SIGNAL(pressed()), this, SLOT(tableEditor()));
    lay->addWidget(m_editList);
    m_number=new QDoubleSpinBox(this);
    m_number->setRange(std::numeric_limits<double>::min(),std::numeric_limits<double>::max());
    lay->addWidget(m_number);

    m_delete=new QPushButton(tr("X"), this);
    m_delete->setWhatsThis(tr("Supprimer la ligne"));
    connect(m_delete, SIGNAL(pressed()), this, SIGNAL(suicide()));
    lay->addWidget(m_delete);

    setLayout(lay);

    setMinimumSize(100,50);
    setWindowTitle(tr("Créateur d'entitées"));

    setData(QString());
}

void Line::tableEditor()
{
    bool b=false;
    QStringPairList r=TableEditor::editList(this, m_list, &b);
    if(!b)
        return;

    m_list = r;
}

void Line::cbChngd(int i)
{
    m_b=true;
    if(i==0)
        setData(m_string->text());
    else if(i==1)
        setData(m_number->value());
    else if(i==2)
        setData(m_list);
}

void Line::setName(const QString& s)
{
    m_name->setText(s);
}

void Line::setShownName(const QString& s)
{
    m_shownName->setText(s);
}

void Line::setData(const QString& s)
{
    if(!m_b)
        m_comboBox->setCurrentIndex(0);

    m_b=false;

    m_number->hide();
    m_editList->hide();
    m_string->show();
    m_string->setText(s);
}

void Line::setData(double d)
{
    if(!m_b)
        m_comboBox->setCurrentIndex(1);

    m_b=false;

    m_number->show();
    m_editList->hide();
    m_string->hide();
    m_number->setValue(d);
}

void Line::setData(const QStringPairList& l)
{
    if(!m_b)
        m_comboBox->setCurrentIndex(2);

    m_b=false;

    m_number->hide();
    m_editList->show();
    m_string->hide();
    m_list=l;
}

QString Line::toScript() const
{
    QString t;
    if(m_name->text().isEmpty())
        return QString();
    QString sn=m_shownName->text();
    if(sn.isEmpty())
        sn=m_name->text();

    t+="data[\""+m_name->text()+"\"]=\""+sn+"\";\n";
    t+=m_name->text()+"=";
    if(m_number->isVisible())
        t+=QString::number(m_number->value())+'\n';
    else if(m_string->isVisible())
        t+="\"" + m_string->text() + "\"\n";
    else if(m_editList->isVisible())
    {
        t+="{}\n";
        for(int i=0,m=m_list.size();i<m;++i)
            t+=m_name->text()+"[\""+m_list[i].first+"\"]=\""+m_list[i].second+"\"\n";
    }
    else
        t+="nil\n";
    t+='\n';
    return t;
}

EntityMaker::EntityMaker(QWidget* par) : QDialog(par)
{
    QHBoxLayout* lay=new QHBoxLayout;
    setLayout(lay);

    m_editor = new QsciScintilla(this);
	m_editor->setLexer(new QsciLexerLua);
	m_editor->setMarginLineNumbers(1,true);
    m_editor->setUtf8(true);


    lay->addWidget(m_editor);

    m_toEdi=new QPushButton(tr("<<"),this);
    connect(m_toEdi, SIGNAL(pressed()), this, SLOT(toEdi()));
    m_fromEdi=new QPushButton(tr(">>"),this);
    connect(m_fromEdi, SIGNAL(pressed()), this, SLOT(fromEdi()));
    m_newLine=new QPushButton(tr("Nouvelle ligne"), this);
    connect(m_newLine, SIGNAL(pressed()), this, SLOT(newLine()));
    m_scriptName=new QLineEdit(this);
    m_scriptName->setPlaceholderText(tr("Nom du script..."));
    m_sendScript=new QPushButton(tr("Envoyer au serveur"), this);
    connect(m_sendScript, SIGNAL(pressed()), this, SLOT(sndScrpt()));
    {
    QVBoxLayout *vl=new QVBoxLayout;
    vl->addWidget(m_scriptName);
    vl->addWidget(m_sendScript);
    vl->addWidget(m_toEdi);
    vl->addWidget(m_fromEdi);
    vl->addWidget(m_newLine);
    lay->addLayout(vl);
    }

    QScrollArea* scrll=new QScrollArea(this);
    scrll->setWidgetResizable(true);
    lay->addWidget(scrll);
    QWidget* wscrll=new QWidget(scrll);
    wscrll->setMinimumSize(300,100);
    scrll->setWidget(wscrll);
    m_layout=new QVBoxLayout();
    m_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    wscrll->setLayout(m_layout);
    newLine();
}

void EntityMaker::sndScrpt()
{
    emit sendScript(m_scriptName->text(), m_editor->text());
}

void EntityMaker::newLine()
{
    Line* li=new Line(this);
    m_lines.append(li);
    m_layout->addWidget(li);
    connect(li, SIGNAL(suicide()),this,SLOT(deleteLine()));
}

void EntityMaker::addLine(const QString& name, const EntityData& ent)
{
    Line* li=new Line(this);

    li->setName(name);
    li->setShownName(ent.shownName);

    if(ent.isString())
        li->setData(ent.getString());
    else if(ent.isNumber())
        li->setData(ent.getNumber());
    else if(ent.isStringPairList())
        li->setData(ent.getStringPairList());
    else
    {
        delete li;
        return;
    }

    m_layout->addWidget(li);

    m_lines.append(li);

    connect(li, SIGNAL(suicide()),this,SLOT(deleteLine()));
}

void EntityMaker::deleteLine()
{
    Line* li=qobject_cast<Line*>(sender());
    if(li==0)
        return;

    m_lines.removeAll(li);
    li->deleteLater();
}

QString EntityMaker::getScriptName() const
{
    return m_scriptName->text();
}

QString EntityMaker::getScript() const
{
    return m_editor->text();
}

void EntityMaker::setScript(const QString& s)
{
    m_editor->setText(s);
    fromEdi();
}

void EntityMaker::setScriptName(const QString& s)
{
    m_scriptName->setText(s);
}


void EntityMaker::toEdi()
{
    QString t;

    t+="data={}\n\n";

    for(int i=0,m=m_lines.size();i<m;++i)
    {
        t+=m_lines[i]->toScript();
    }

    t+="\n\nfunction once() end\nfunction onInit() end\nfunction onUpdate() end\nfunction onDeath() end\n";
    m_editor->setText(t);
}

void EntityMaker::fromEdi()
{
    ScriptedEntity sc; bool b=false;
    QString err = sc.pushCode(m_editor->text(),&b);
    if(!b)
    {
        QMessageBox::critical(this,tr("Erreur de script"),tr("Erreur : %1").arg(err));
        return;
    }

    for(int i=0,m=m_lines.size();i<m;++i)
        delete m_lines[i];
    m_lines.clear();

    QMap<QString, EntityData> mp = sc.getData();
    for(QMap<QString, EntityData>::const_iterator i=mp.constBegin();i!=mp.constEnd();++i)
    {
        addLine(i.key(),i.value());
    }
}


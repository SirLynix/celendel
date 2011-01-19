#include "Translator.h"
#include <QFile>
#include <qDebug>
#include "..\Shared\Constants.h"

Translator::Translator(){}

QList<QPair<QString, QString> > Translator::getLanguages() const
{
    QList<QPair<QString, QString> > l;
    QMap<QString, QString>::const_iterator i = m_languages.constBegin();
    while (i != m_languages.constEnd())
    {
        l.append(qMakePair(i.key(),i.value()));
        ++i;
    }

    return l;
}

int getSum(const QString& str)
{
    int r=0,m=str.size();
    for(int i=0;i<m;++i)
        r+=static_cast<int>(str[i].unicode());

    return r;
}

bool isSpecialChar(const QString& str)
{
    if(str.size()>1)
        return false;
    return !str[0].isLetterOrNumber();
}

void Translator::reset()
{
    m_languages->clear();
    m_dictionaries->clear();
}

QString Translator::translate(const QString& text, const QString& language, int prct)
{
    if(prct<0)
        prct=0;
    else if(prct>100)
        prct=100;

    QStringList l=text.split(' ', QString::SkipEmptyParts);
    QString out;

    int m=l.size();
    for(int i=0; i<m; ++i)
    {
        if(alea(0,100)>prct&&!isSpecialChar(l[i]))
            out+=getWord(language, l[i].size()+1, getSum(l[i]))+' ';
        else
            out+=l[i]+' ';
    }

    return out.simplified();
}


QString Translator::getWord(const QString& language, int size, int sum)
{
    if(!m_languages.contains(language)||size<0)
        return QString();

    QList<QStringList>& d = m_dictionaries[m_languages[language]];
    int m=d.size();

    if(m<2)
        return QString();

    qDebug() << size << m << sum;

    if(size==0)
        size=m-1;

    if(size>=m)
        return getWord(language, m-1, sum);

    int ms=d[size].size();
    if(ms==0)
        return getWord(language, size-1, sum);
    return d[size][sum%ms];
}

QStringList Translator::getDictionariesList() const
{
    return m_dictionaries.uniqueKeys();
}

bool Translator::removeDictionary(const QString& name)
{
    if(!m_languages.keys(name).isEmpty())
        return true;

    if(!m_dictionaries.remove(name))
        return true;

    return false;
}

bool Translator::openDictionary(const QString& name)
{
    QString fileName=DICTIONARIES_FOLDER_PATH + name + DICTIONARIES_EXTENSION;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Dictionary not found : " << fileName;
        return true;
    }

    return loadDictionary(name, file.readAll());
}

bool Translator::loadDictionary(const QString& name, const QString& content)
{
    if(m_dictionaries.contains(name))
        return true;

    QStringList list = content.split('\n', QString::SkipEmptyParts);
    for(int i=0, m=list.size();i<m;++i)
    {
        QString line=list[i].simplified(); line.remove(' ');

        int size=line.size()+1;

        if(size>1)
        {
            QList<QStringList>& d=m_dictionaries[name];

            if(size>=d.size())
                resize(d, size+1);

            d[size].append(line);
        }
    }

    return false;
}

bool Translator::loadLanguage(const QString& name, const QString& dico)
{
    if(m_languages.contains(name))
        return true;

    if(!m_dictionaries.contains(dico))
    {
        QString fileName=DICTIONARIES_FOLDER_PATH + dico + DICTIONARIES_EXTENSION;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug() << "FAILLURE : " << fileName;
            return true;
        }

        while(!file.atEnd()) //Althought this method is dangerous with STL-files, Qt's one is saffer.
        {
            QString line=file.readLine().simplified(); line.remove(' ');
            int size=line.size()+1;

            if(size>1)
            {
                QList<QStringList>& d=m_dictionaries[dico];

                if(size>=d.size())
                    resize(d, size+1);

                d[size].append(line);
            }
        }
    }
    if(m_dictionaries.contains(dico))
        m_languages[name]=dico;

    return false;
}


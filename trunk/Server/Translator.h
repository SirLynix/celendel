#ifndef DEF_TRANSLATOR
#define DEF_TRANSLATOR

#include <QStringList>
#include <QMap>
#include <QPair>

class Translator
{
    public:
    Translator();

    bool loadLanguage(const QString& name, const QString& dico);

    QString translate(const QString& text, const QString& language, int prct);

    QList<QPair<QString, QString> > getLanguages() const;
    QStringList getDictionariesList() const;

    bool removeDictionary(const QString& name);

    bool loadDictionary(const QString& name, const QString& content);
    bool openDictionary(const QString& name);

    void reset();

    private:

    QString getWord(const QString& language, int size, int sum=-1);

    QMap<QString, QString> m_languages;
    QMap<QString, QList<QStringList> > m_dictionaries; //First is dictonary filename, second is a list classed by words lenght

};

#endif

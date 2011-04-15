#ifndef SCRIPTSANDBOX_H
#define SCRIPTSANDBOX_H

#include <QObject>
#include "luaHeader.h"

class ScriptSandbox : public QObject
{
    Q_OBJECT
    public:
        ScriptSandbox();

        bool isError() const { return m_error; }
        QString errorString() const { return m_errorTxt; }

    public slots:
        bool pushCode(const QString& code);

    private:
        Lua_State m_state;
        bool m_error;
        QString m_errorTxt;
};

#endif // SCRIPTSANDBOX_H

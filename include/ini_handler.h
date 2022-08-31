#ifndef INI_HANDLER_H
#define INI_HANDLER_H

#include <QString>
#include <QSettings>

class INIHandler {
    INIHandler(QString f_ini_fullpath);

private :
    QSettings m_char_ini;
};

#endif // INI_HANDLER_H

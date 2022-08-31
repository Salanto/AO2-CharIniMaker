#ifndef INI_HANDLER_H
#define INI_HANDLER_H

#include <QString>
#include <QSettings>
#include <ao2_character_data.h>

class INIHandler {
public:
    INIHandler(QString f_ini_fullpath);
    ~INIHandler();

    CharacterOptions loadOptions();

    void saveOptions(const CharacterOptions f_options);

private :
    QSettings *m_char_ini;
};

#endif // INI_HANDLER_H

#ifndef INI_HANDLER_H
#define INI_HANDLER_H

#include <QString>
#include <QSettings>
#include <ao2_character_data.h>


/**
 * @brief The INIHandler class responsible for loading and saving to char.ini
 *
 * @details The INIHandler is a mostly portable char.ini loader/saver implementation, able to load
 * the group segements of char.ini in blocks and save back to it.
 */
class INIHandler {
public:
    INIHandler(QString f_ini_fullpath);
    ~INIHandler();

    CharacterOptions loadOptions();
    void saveOptions(const CharacterOptions f_options);

    QList<AnimationData> loadEmotions();
    void saveEmotions(const Emotions f_emotions);

private :
    QSettings *m_char_ini;
};

#endif // INI_HANDLER_H

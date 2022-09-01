#include "ini_handler.h"

#include <QDebug>

INIHandler::INIHandler(QString f_ini_fullpath)
{
    if (f_ini_fullpath.isEmpty()) {
        qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                   << "error : empty path passed during config loading.";
        return;
    }

    m_char_ini = new QSettings(f_ini_fullpath, QSettings::IniFormat);
    if (m_char_ini->status() != QSettings::NoError) {
        switch (m_char_ini->status()) {
        case QSettings::AccessError:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: failed to open file; aborting (" << m_char_ini->fileName() << ")";
            break;

        case QSettings::FormatError:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: file is malformed; aborting (" << m_char_ini->fileName() << ")";
            break;

        default:
            qWarning() << "[INIHANDLER]:[CONSTRUCT]"
                       << "error: some error; aborting; aborting (" << m_char_ini->fileName() << ")"
                       << "error code:" << m_char_ini->status();
            break;
        }
    }
}

INIHandler::~INIHandler()
{
    m_char_ini->deleteLater();
}

CharacterOptions INIHandler::loadOptions()
{
    CharacterOptions l_options;
    m_char_ini->beginGroup("Options");
    l_options.name = m_char_ini->value("name","").toString();
    l_options.showname = m_char_ini->value("showname","").toString();
    l_options.side = m_char_ini->value("side","def").toString();
    l_options.blips = m_char_ini->value("blips","").toString();
    if (l_options.blips.isEmpty()) l_options.blips = m_char_ini->value("gender","").toString();
    l_options.category = m_char_ini->value("category", "").toString();
    l_options.chat = m_char_ini->value("chat", "default").toString();
    l_options.chat_size = m_char_ini->value("chat_size", 8).toInt();
    l_options.effects = m_char_ini->value("effects", "").toString();
    l_options.realization = m_char_ini->value("realization","").toString();
    l_options.scaling = m_char_ini->value("scaling", "fast").toString();
    m_char_ini->endGroup();

    return l_options;
}

void INIHandler::saveOptions(const CharacterOptions f_options)
{
    // We version the char.ini. Since this tool currently mimics current AO2 .ini
    // files it is a version 1.
    m_char_ini->setValue("version/major", 1);

    m_char_ini->beginGroup("Options");
    m_char_ini->setValue("name", f_options.name);
    if (!f_options.showname.isEmpty())
        m_char_ini->setValue("showname", f_options.showname);
    m_char_ini->setValue("side", f_options.side);
    if (!f_options.blips.isEmpty())
        m_char_ini->setValue("blips", f_options.blips);
    else
        m_char_ini->setValue("blips", "male");
    if (!f_options.category.isEmpty()) m_char_ini->setValue("category", f_options.category);
    if (!f_options.chat.isEmpty()) m_char_ini->setValue("chat", f_options.chat);
    if (!f_options.chat_font.isEmpty()) m_char_ini->setValue("chat_font", f_options.chat_font.isEmpty());
    m_char_ini->setValue("chat_size", f_options.chat_size);
    if (!f_options.effects.isEmpty()) m_char_ini->setValue("effects", f_options.effects);
    if (!f_options.realization.isEmpty()) m_char_ini->setValue("realization", f_options.realization);

    m_char_ini->endGroup();
    m_char_ini->sync();
}

QList<AnimationData> INIHandler::loadEmotions()
{
    m_char_ini->beginGroup("Emotions");
    int l_emotions_count = m_char_ini->value("number", 0).toInt();

    QList<AnimationData> l_animations;
    for (int i = 1; i <= l_emotions_count; i++) {
        QStringList l_animation_segments = m_char_ini->value(QString::number(i)).toString().split("#");
        AnimationData l_animation;

        if (l_animation_segments.size() < 4) {
            qWarning() << "[INIHANDLER]:[READ_EMOTION]"
                       << "error : emotion data at " + QString::number(i)
                       << " is too small to load. Adding default entry.";
            l_animations.append(l_animation);
            continue;
        }

        if (l_animation_segments.size() == 4) {
            qWarning() << "[INIHANDLER]:[READ_EMOTION]"
                       << "waring : missing deskmod entry at " + QString::number(i)
                       << ". Adding default deskmod of 0.";
            l_animation.comment = l_animation_segments.at(0);
            l_animation.preAnim = l_animation_segments.at(1);
            l_animation.Anim = l_animation_segments.at(2);
            l_animation.modifier = l_animation_segments.at(3).toInt();
            l_animation.deskmod = 0;
            continue;
        }

        l_animation.comment = l_animation_segments.at(0);
        l_animation.preAnim = l_animation_segments.at(1);
        l_animation.Anim = l_animation_segments.at(2);
        l_animation.modifier = l_animation_segments.at(3).toInt();
        l_animation.deskmod = l_animation_segments.at(4).toInt();
        }

    return l_animations;
}

void INIHandler::saveEmotions(const Emotions f_emotions)
{
    m_char_ini->beginGroup("Emotions");
    m_char_ini->setValue("number", f_emotions.number);
}

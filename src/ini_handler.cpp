#include "ini_handler.h"
#include "ao2_character_data.h"

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
    l_options.stretch = m_char_ini->value("stretch", false).toBool();
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
    m_char_ini->setValue("stretch", f_options.stretch);

    m_char_ini->endGroup();
    m_char_ini->sync();
}

QList<AnimationData> INIHandler::loadEmotions()
{
    m_char_ini->beginGroup("Emotions");
    int l_emotions_count = m_char_ini->value("number", 0).toInt();

    QList<AnimationData> l_animations;
    for (int emote_index = 1; emote_index <= l_emotions_count; emote_index++) {
        QStringList l_animation_segments = m_char_ini->value(QString::number(emote_index)).toString().split("#");
        AnimationData l_animation;

        if (l_animation_segments.size() < 4) {
            qWarning() << "[INIHANDLER]:[READ_EMOTION]"
                       << "error : emotion data at " + QString::number(emote_index)
                       << " is too small to load. Adding default entry.";
            l_animations.append(l_animation);
            continue;
        }

        if (l_animation_segments.size() == 4) {
            qWarning() << "[INIHANDLER]:[READ_EMOTION]"
                       << "waring : missing deskmod entry at " + QString::number(emote_index)
                       << ". Adding default deskmod of 0.";
            l_animation.comment = l_animation_segments.at(0);
            l_animation.preAnim = l_animation_segments.at(1);
            l_animation.Anim = l_animation_segments.at(2);
            l_animation.modifier = l_animation_segments.at(3).toInt();
            l_animation.deskmod = 0;
            l_animations.append(l_animation);
            continue;
        }

        l_animation.comment = l_animation_segments.at(0);
        l_animation.preAnim = l_animation_segments.at(1);
        l_animation.Anim = l_animation_segments.at(2);
        l_animation.modifier = l_animation_segments.at(3).toInt();
        l_animation.deskmod = l_animation_segments.at(4).toInt();
        l_animations.append(l_animation);
    }
    m_char_ini->endGroup();

    return l_animations;
}

void INIHandler::saveEmotions(const Emotions f_emotions)
{
    m_char_ini->beginGroup("Emotions");
    m_char_ini->setValue("number", f_emotions.number);

    int l_emote_index = 1;
    for (AnimationData l_animation_data: f_emotions.emotions) {
      QString l_emote_entry = QString("%1#%2#%3#%4#%5").arg(l_animation_data.comment, l_animation_data.preAnim,
                                                            l_animation_data.Anim,
                                                            QString::number(l_animation_data.modifier),
                                                            QString::number(l_animation_data.deskmod));
      m_char_ini->setValue(QString::number(l_emote_index), l_emote_entry);
      l_emote_index++;
    }
    m_char_ini->endGroup();
}

QList<SoundData> INIHandler::loadSounds()
{
    QList<SoundData> l_sounds;
    // Cross-group reading/writing is kinda cringe, but AO2 has forced my hand.
    int l_sound_count = m_char_ini->value("Emotions/number", 0).toInt();

    for (int sound_index = 1; sound_index <= l_sound_count; sound_index++) {
        SoundData l_sound;
        l_sound.sfx = m_char_ini->value("SoundN/" + QString::number(sound_index), "NO-SFX").toString();
        l_sound.ticks = m_char_ini->value("SoundT/" + QString::number(sound_index), 0).toInt();
        l_sound.loop = m_char_ini->value("SoundL/" + QString::number(sound_index), 0).toBool();
        l_sounds.append(l_sound);
    }
    return l_sounds;
}

void INIHandler::saveSounds(const QList<SoundData> f_sounds)
{
    int l_sound_index = 1;
    for (const SoundData &l_sound_data : f_sounds) {
        m_char_ini->setValue("SoundN/" + QString::number(l_sound_index), l_sound_data.sfx);
        m_char_ini->setValue("SoundT/" + QString::number(l_sound_index), l_sound_data.ticks);
        m_char_ini->setValue("SoundL/" + QString::number(l_sound_index), int(l_sound_data.loop));
        l_sound_index++;
    }
}

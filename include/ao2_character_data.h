#ifndef AO2_CHARACTER_DATA_H
#define AO2_CHARACTER_DATA_H

#include <QString>
#include <QList>
// Char.ini internal datastructure represented as structs

/**
 * @brief The CharacterOptions class
 *
 * @details The character Options group is meta-data group, containing filesystem relevant entries.
 *
 * #name - The folder and character name.
 * name = Larry - /base/characters/Larry/
 *
 * #showname - The display name of the character.
 * Folder names can be ugly. The showname is a user friendly name which is not unique.
 *
 * #side - The 'side' of the character.
 * The side decides which background and desk the client shows.
 *
 * #blips - The audio that plays during a chat tick.
 * Blips are a visual novel trope to emulate speaking while being too cheap to hire a voice actor.
 *
 * #category - Sorts the characters in the serverlist by the category.
 *
 * #chat - The characters chatbox.
 * Chatboxes for characters can be disabled in the settings.
 * If custom_chatbox is disabled, only the themes default chatbox will be used.
 *
 * #chat_font
 * The font the character uses. If the font file is missing, the clients default font is used.
 *
 * #chat_size
 * Sets the characters font size. I have never seen this set.
 *
 * #effects
 * EVIL.
 *
 * #realization
 * Specifies a custom realization sound to be played.
 *
 * #scaling
 * Defines the characters scaling mode. Some may look better using smooth scaling, like HD chars.
 */
struct CharacterOptions {
    QString name;
    QString showname;
    QString side;
    QString blips;
    QString category;
    QString chat;
    QString chat_font;
    int chat_size;
    QString effects;
    QString realization;
    QString scaling;
    bool stretch;
};

/**
 * @brief The AnimationData class
 *
 * @details The emote information is limited using the pound (#) symbol.
 *
 */
struct AnimationData {
  QString comment = "normal";
  QString preAnim = "-";
  QString Anim = "normal";
  int modifier = 0;
  int deskmod = 0;
};

struct Emotions {
    int number;
    QList<AnimationData> emotions;
};

/**
 * @brief The SoundData struct.
 *
 * @details The sound information is split into two groups in the ini.
 * [SoundN] contains the index of the emote and the sfx filename.
 * 1 = dubstep
 *
 * [SoundT] contains the index of the emote and the delay in ticks (60ms).
 * 1 = 0
 *
 * As you may have noticed this structure makes no sense and is stupid.
 */
struct SoundData {
  QString sfx = "NO-SFX";
  int ticks = 0;
  bool loop = false;
};

enum FrameType{
    SFX,
    REALIZATION,
    SHAKE
};

struct FrameFXEntry {
  QString emote;
  FrameType type;
  QList<int> frames;
};

#endif // AO2_CHARACTER_DATA_H

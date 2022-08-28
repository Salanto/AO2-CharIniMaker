#ifndef AO2_CHARACTER_DATA_H
#define AO2_CHARACTER_DATA_H

#include <QString>
#include <QList>
// Char.ini internal datastructure represented as structs

/**
 * @brief The AnimationData class
 *
 * @details The emote information is delimited using the pound (#) symbol.
 *
 */
struct AnimationData {
  QString comment = "normal";
  QString preAnim = "-";
  QString Anim = "normal";
  int modifier = 0;
  int deskmod = 1;
};

/**
 * @brief The SoundData class
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

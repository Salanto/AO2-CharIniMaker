#ifndef AO2_EMOTE_H
#define AO2_EMOTE_H

#include <QList>
#include <QString>

#include "ao2_character_data.h"

/**
 * @brief The AO2Emote class represents an Attorney Online 2 emotion with all
 * related substructures.
 *
 * @details Unlike any sane datastructure AO2's char.ini relates several
 * behaviour modifiers across multiple INI groups. This class aims to to
 * consolidate them into a single place.
 */
class AO2Emote {
 public:
    AnimationData animationData() const;
    void setAnimationData(AnimationData f_animation);
    void setComment(const QString f_comment);
    void setPreAnim(QString f_pre_anim);
    void setAnim(QString f_anim);
    void setModifier(int f_modifier);
    void setDeskmod(int f_deskmod);

 private:
  /**
   * @brief Contains the files used to play this emote.
   *
   * @details AnimationData also contain meta-data, like the name of the emote.
   * This is used to identify the emote in the UI by name. Many people just use the index though.
   */
  AnimationData m_animation;
};

#endif  // AO2_EMOTE_H

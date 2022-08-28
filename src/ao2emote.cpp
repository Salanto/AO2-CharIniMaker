#include "ao2emote.h"

AnimationData AO2Emote::animationData() const
{
    return m_animation;
}

void AO2Emote::setComment(QString f_comment)
{
    m_animation.comment = f_comment;
}

void AO2Emote::setPreAnim(QString f_pre_anim)
{
    m_animation.preAnim = f_pre_anim;
}

void AO2Emote::setAnim(QString f_anim)
{
    m_animation.Anim = f_anim;
}

void AO2Emote::setModifier(int f_modifier)
{
    m_animation.modifier = f_modifier;
}

void AO2Emote::setDeskmod(int f_deskmod)
{
    m_animation.deskmod = f_deskmod;
}

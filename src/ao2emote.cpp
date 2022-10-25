#include "ao2emote.h"

AnimationData AO2Emote::animationData() const
{
    return m_animation;
}

void AO2Emote::setAnimationData(AnimationData f_animation)
{
    m_animation = f_animation;
}

void AO2Emote::setComment(const QString f_comment)
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

SoundData AO2Emote::soundData() const
{
    return m_sound;
}

void AO2Emote::setSoundData(SoundData f_sound)
{
    m_sound = f_sound;
}

void AO2Emote::setSFX(QString f_sfx_name)
{
    m_sound.sfx = f_sfx_name;
}

void AO2Emote::setTicks(int f_ticks)
{
    m_sound.ticks = f_ticks;
}

void AO2Emote::setLoop(bool f_loop)
{
    m_sound.loop = f_loop;
}

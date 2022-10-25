#include "ao2charmaker.h"
#include "ao2_character_data.h"
#include "ui_ao2charmaker.h"

void AO2CharMaker::setEmoteRowText(int f_index, bool add_entry) {
    AnimationData l_animation_data = m_emotions.at(f_index).animationData();
    QString l_display_text =
        QString("%6 = %1#%2#%3#%4#%5")
            .arg(l_animation_data.comment, l_animation_data.preAnim,
                 l_animation_data.Anim,
                 QString::number(l_animation_data.modifier),
                 QString::number(l_animation_data.deskmod),
                 QString::number(f_index + 1));
    if (add_entry)
        ui->emote_listview->addItem(l_display_text);
    else
        ui->emote_listview->currentItem()->setText(l_display_text);
}

void AO2CharMaker::setSoundRowText(int f_index, bool add_entry)
{
    SoundData l_sound_data = m_emotions.at(f_index).soundData();
    QString l_display_text =
            QString("%3 = %1 | %2 ticks").arg(l_sound_data.sfx,
                                         QString::number(l_sound_data.ticks),
                                         QString::number(f_index + 1));
    if (l_sound_data.loop) {
        l_display_text.append(" | Loop");
    }
    else {
        l_display_text.append(" | No Loop");
    }

    if (add_entry)
        ui->sound_listview->addItem(l_display_text);
    else
        ui->sound_listview->currentItem()->setText(l_display_text);
}

void AO2CharMaker::setEmoteEditMenu(int f_index) {
  AnimationData l_anim_data = m_emotions.at(f_index).animationData();
  ui->emote_comment_lineedit->setText(l_anim_data.comment);
  ui->emote_preanim_lineedit->setText(l_anim_data.preAnim);
  ui->emote_anim_lineedit->setText(l_anim_data.Anim);

  int modifier_index =
      ui->emote_modifier_combobox->findData(l_anim_data.modifier);
  if (modifier_index != -1)
    ui->emote_modifier_combobox->setCurrentIndex(modifier_index);
  else
    ui->emote_modifier_combobox->setCurrentIndex(0);

  int deskmod_index =
      ui->emote_modifier_combobox->findData(l_anim_data.modifier);
  if (deskmod_index != -1)
    ui->emote_deskmod_combobox->setCurrentIndex(modifier_index);
  else
      ui->emote_deskmod_combobox->setCurrentIndex(1);

  if (f_index == 0) {
    //We need to disable up for sure.
    ui->emote_up_button->setEnabled(false);
    if (f_index != m_emotions.size() -1) {
        //We have an entry after this one. Enable down button.
        ui->emote_down_button->setEnabled(true);
    }
  }

  if (f_index != 0 && f_index != m_emotions.size() -1) {
      //Entry is not at the end or beginning. Enable both.
      ui->emote_down_button->setEnabled(true);
      ui->emote_up_button->setEnabled(true);
  }

  if (f_index == m_emotions.size() -1 && f_index != 0) {
      //We are at the end of the list and NOT the first entry.
    ui->emote_up_button->setEnabled(true);
    ui->emote_down_button->setEnabled(false);
  }

}

void AO2CharMaker::setSoundEditMenu(int f_index)
{
  SoundData l_sound_data = m_emotions.at(f_index).soundData();
  ui->sound_sfx_lineedit->setText(l_sound_data.sfx);
  ui->sound_tick_spinbox->setValue(l_sound_data.ticks);
  ui->sound_loop_checkbox->setChecked(l_sound_data.loop);
}

void AO2CharMaker::setOptionsTab(CharacterOptions f_options)
{
    ui->name_lineedit->setText(f_options.name);
    ui->showname_lineedit->setText(f_options.showname);

    int l_side = ui->side_combobox->findText(f_options.side);
    if (l_side != -1) ui->side_combobox->setCurrentIndex(l_side);
    else ui->side_combobox->setCurrentIndex(0);

    ui->blips_lineedit->setText(f_options.blips);
    ui->category_lineedit->setText(f_options.category);
    ui->chat_lineedit->setText(f_options.chat);
    ui->chat_front_lineedit->setText(f_options.chat_font);
    ui->chat_size_spinbox->setValue(f_options.chat_size);
    ui->effects_lineedit->setText(f_options.effects);
    ui->realization_lineedit->setText(f_options.realization);

    int l_scaling = ui->scaling_combobox->findText(f_options.scaling);
    if (l_scaling != -1) ui->scaling_combobox->setCurrentIndex(l_scaling);
    else ui->scaling_combobox->setCurrentIndex(0);

    ui->stretch_checkbox->setChecked(f_options.stretch);
}

void AO2CharMaker::setEmotionsTab(QList<AnimationData> f_emotions)
{
    // We are loading in a foreign char.ini. The widget items have become obsolete.
    // The signal firing needs to be disabled as clear would set the current row to -1
    ui->emote_listview->blockSignals(true);
    ui->emote_listview->clear();
    m_emotions.clear();

    int l_row = 0;
    for (const AnimationData &l_animation : f_emotions) {
        AO2Emote l_emote;
        l_emote.setAnimationData(l_animation);
        m_emotions.append(l_emote);
        setEmoteRowText(l_row, true);
        l_row++;
    }

    ui->emote_listview->blockSignals(false);
    if (ui->emote_listview->count() > 0) {
        ui->emote_listview->setCurrentRow(0);
        ui->emote_input_groupbox->setEnabled(true);
    }
    else {
        ui->emote_input_groupbox->setEnabled(false);
    }
}

void AO2CharMaker::setSoundTab(QList<SoundData> f_sounds)
{
    // We are loading in a foreign char.ini. The widget items have become obsolete.
    // The signal firing needs to be disabled as clear would set the current row to -1
    ui->sound_listview->blockSignals(true);
    ui->sound_listview->clear();

    int l_row = 0;
    for (const SoundData &l_sound : f_sounds) {
        m_emotions[l_row].setSoundData(l_sound);
        setSoundRowText(l_row, true);
        l_row++;
    }

    ui->sound_listview->blockSignals(false);
    if(ui->sound_listview->count() > 0) {
        ui->sound_listview->setCurrentRow(0);
        ui->sound_input_groupbox->setEnabled(true);
    }
    else {
        ui->sound_input_groupbox->setEnabled(false);
    }
}

void AO2CharMaker::redrawUI()
{
    QList<AnimationData> l_emotions;
    QList<SoundData> l_sounds;
    for (const AO2Emote &l_emote : qAsConst(m_emotions)) {
        l_emotions.append(l_emote.animationData());
        l_sounds.append(l_emote.soundData());
    }
    setEmotionsTab(l_emotions);
    setSoundTab(l_sounds);
}

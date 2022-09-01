#include "ao2charmaker.h"
#include "ao2_character_data.h"
#include "ui_ao2charmaker.h"
#include "ini_handler.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

void AO2CharMaker::on_load_button_pressed()
{
    QString l_ini_fullname = QFileDialog::getOpenFileName(this,
        tr("Open char.ini"), root_path, tr("Character File (char.ini)"));

    if(l_ini_fullname.isEmpty())
        return;

    INIHandler* l_handler = new INIHandler(l_ini_fullname);

    setOptionsTab(l_handler->loadOptions());
    setEmotionsTab(l_handler->loadEmotions());
    setSoundTab(l_handler->loadSounds());

    delete l_handler;
}

void AO2CharMaker::on_save_button_pressed() {
  if (ui->name_lineedit->text().isEmpty()) {
    QMessageBox::question(
        this, "Please name the character.",
        "Please enter a character name before saving the character.",
        QMessageBox::StandardButton::Ok);
    return;
  }

  INIHandler l_handler(root_path + "/" + ui->name_lineedit->text() + "/char.ini");

  CharacterOptions l_options;
  l_options.name = ui->name_lineedit->text();
  l_options.showname = ui->showname_lineedit->text();
  l_options.side = ui->side_combobox->currentText();
  l_options.blips = ui->blips_lineedit->text();
  l_options.category = ui->category_lineedit->text();
  l_options.chat = ui->chat_lineedit->text();
  l_options.chat_font = ui->chat_front_lineedit->text();
  l_options.chat_size = ui->chat_size_spinbox->value();
  l_options.effects = ui->effects_lineedit->text();
  l_options.realization = ui->realization_lineedit->text();
  l_options.scaling = ui->scaling_combobox->currentText();
  l_options.stretch = ui->stretch_checkbox->isChecked();

  l_handler.saveOptions(l_options);

  Emotions l_emotions;
  l_emotions.number = m_emotions.size();
  QList<AnimationData> l_emote_entries;
  for (const AO2Emote &l_emote : qAsConst(m_emotions)) {
      l_emote_entries.append(l_emote.animationData());
  }
  l_emotions.emotions = l_emote_entries;

  l_handler.saveEmotions(l_emotions);

  QList<SoundData> l_sound_entries;
  for (const AO2Emote &l_emote : qAsConst(m_emotions)) {
      l_sound_entries.append(l_emote.soundData());
  }
  l_handler.saveSounds(l_sound_entries);
}

void AO2CharMaker::on_add_emote_pressed() {
  ui->emote_input_groupbox->setEnabled(true);
  ui->sound_input_groupbox->setEnabled(true);
  AO2Emote l_new_emotion;
  m_emotions.append(l_new_emotion);

  int l_emote_index = m_emotions.size() - 1;
  setEmoteRowText(l_emote_index, true);
  setSoundRowText(l_emote_index, true);
  ui->emote_listview->setCurrentRow(l_emote_index);
  setEmoteEditMenu(l_emote_index);
  setSoundEditMenu(l_emote_index);
}

void AO2CharMaker::on_comment_lineedit_edited(QString f_text) {
  int l_currently_selected = ui->emote_listview->currentRow();
  m_emotions[l_currently_selected].setComment(f_text);
  setEmoteRowText(l_currently_selected);
}

void AO2CharMaker::on_preanim_lineedit_edited(QString f_text) {
  int l_currently_selected = ui->emote_listview->currentRow();
  m_emotions[l_currently_selected].setPreAnim(f_text);
  setEmoteRowText(l_currently_selected);
}

void AO2CharMaker::on_animation_lineedit_edited(QString f_text) {
  int l_currently_selected = ui->emote_listview->currentRow();
  m_emotions[l_currently_selected].setAnim(f_text);
  setEmoteRowText(l_currently_selected);
}

void AO2CharMaker::on_modifier_combobox_item_selected(QString f_modifier_text) {
  int l_currently_selected = ui->emote_listview->currentRow();
  m_emotions[l_currently_selected].setModifier(f_modifier_text.toInt());
  setEmoteRowText(l_currently_selected);
}

void AO2CharMaker::on_deskmod_combobox_item_selected(QString f_deskmod_text) {
  int l_currently_selected = ui->emote_listview->currentRow();
  m_emotions[l_currently_selected].setDeskmod(f_deskmod_text.toInt());
  setEmoteRowText(l_currently_selected);
}

void AO2CharMaker::on_sfx_name_edited(QString f_text)
{
  int l_currently_selected = ui->sound_listview->currentRow();
  m_emotions[l_currently_selected].setSFX(f_text);
  setSoundRowText(l_currently_selected);
}

void AO2CharMaker::on_sfx_ticks_changed(int f_ticks)
{
    int l_currently_selected = ui->sound_listview->currentRow();
    m_emotions[l_currently_selected].setTicks(f_ticks);
    setSoundRowText(l_currently_selected);
}

void AO2CharMaker::on_create_folder_pressed() {
  if (ui->name_lineedit->text().isEmpty()) {
    QMessageBox::question(
        this, "Please name the character.",
        "Please enter a character name before creating its folder.",
        QMessageBox::StandardButton::Ok);
    return;
  }

  if (ui->create_a_folder->isChecked()) createFolder("(a)");
  if (ui->create_b_folder->isChecked()) createFolder("(b)");
  if (ui->create_button_folder->isChecked()) createFolder("emotions");
  if (ui->create_anim_folder->isChecked()) createFolder("anim");
  if (ui->create_custom_folder->isChecked()) createFolder("custom");
  if (ui->create_shouts_folder->isChecked()) createFolder("shouts");
}

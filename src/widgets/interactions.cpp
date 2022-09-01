#include "ao2charmaker.h"
#include "ao2_character_data.h"
#include "ui_ao2charmaker.h"
#include "ini_handler.h"

#include <QFileDialog>

void AO2CharMaker::on_load_button_pressed()
{
    QString l_ini_fullname = QFileDialog::getOpenFileName(this,
        tr("Open char.ini"), root_path, tr("Character File (char.ini)"));

    if(l_ini_fullname.isEmpty())
        return;

    INIHandler l_handler(l_ini_fullname);

    setOptionsTab(l_handler.loadOptions());
}

void AO2CharMaker::on_add_emote_pressed() {
  ui->emote_input_groupbox->setEnabled(true);
  AO2Emote empty;
  m_emotions.append(empty);

  int l_emote_index = m_emotions.size() - 1;
  setEmoteRowText(l_emote_index, true);
  ui->emote_listview->setCurrentRow(l_emote_index);
  setEmoteEditMenu(l_emote_index);
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

void AO2CharMaker::on_save_button_pressed() {
  if (ui->name_lineedit->text().isEmpty()) {
    QMessageBox::question(
        this, "Please name the character.",
        "Please enter a character name before saving the character.",
        QMessageBox::StandardButton::Ok);
    return;
  }
  QSettings char_ini = QSettings(resolvePath("char.ini"), QSettings::IniFormat);
  char_ini.setIniCodec("UTF-8");
  char_ini.clear();

  writeOptions(&char_ini);
  writeEmotions(&char_ini);
}

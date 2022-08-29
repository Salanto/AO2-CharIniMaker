#include "ao2charmaker.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QDir>
#include <QMessageBox>
#include <QSettings>

#include "ui_ao2charmaker.h"

AO2CharMaker::AO2CharMaker(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::AO2CharMaker) {
  ui->setupUi(this);
  connect(ui->build_folders, &QPushButton::pressed, this,
          &AO2CharMaker::on_create_folder_pressed);
  connect(ui->control_buttons, &QDialogButtonBox::accepted, this,
          &AO2CharMaker::on_save_button_pressed);
  connect(ui->emote_add_button, &QPushButton::pressed, this,
          &AO2CharMaker::on_add_emote_pressed);
  connect(ui->emote_listview, &QListWidget::currentRowChanged, this,
          &AO2CharMaker::setEmoteEditMenu);
  connect(ui->emote_comment_lineedit, &QLineEdit::textEdited, this,
          &AO2CharMaker::on_comment_lineedit_edited);
  connect(ui->emote_preanim_lineedit, &QLineEdit::textEdited, this,
          &AO2CharMaker::on_preanim_lineedit_edited);
  connect(ui->emote_anim_lineedit, &QLineEdit::textEdited, this,
          &AO2CharMaker::on_animation_lineedit_edited);
  connect(ui->emote_deskmod_combobox, &QComboBox::currentTextChanged, this,
          &AO2CharMaker::on_deskmod_combobox_item_selected);
  connect(ui->emote_modifier_combobox, &QComboBox::currentTextChanged, this,
          &AO2CharMaker::on_modifier_combobox_item_selected);
  ui->emote_input_groupbox->setEnabled(false);
}

AO2CharMaker::~AO2CharMaker() { delete ui; }

QString AO2CharMaker::resolvePath(QString f_path) {
  return QString("%1/%2/%3").arg(root_path, ui->name_lineedit->text(), f_path);
}

void AO2CharMaker::createFolder(QString f_name) {
  QDir().mkpath(resolvePath(f_name));
}

void AO2CharMaker::writeOptions(QSettings* char_ini) {
  // We version the char.ini. Since this tool currently mimics current AO2 .ini
  // files it is a version 1.
  char_ini->setValue("version/major", 1);

  char_ini->beginGroup("Options");
  char_ini->setValue("name", ui->name_lineedit->text());

  QString showname = ui->showname_lineedit->text();
  if (!showname.isEmpty())
    char_ini->setValue("showname", ui->showname_lineedit->text());

  char_ini->setValue("pos", ui->side_combobox->currentText());

  QString blips = ui->blips_lineedit->text();
  if (!blips.isEmpty())
    char_ini->setValue("blips", blips);
  else
    char_ini->setValue("blips", "male");

  QString chat = ui->chat_lineedit->text();
  if (!chat.isEmpty()) char_ini->setValue("chat", chat);

  QString chat_font = ui->chat_front_lineedit->text();
  if (!chat_font.isEmpty()) char_ini->setValue("chat_font", chat_font);

  int chat_size = ui->chat_size_spinbox->value();
  char_ini->setValue("chat_size", chat_size);

  QString effects = ui->effects_lineedit->text();
  if (!effects.isEmpty()) char_ini->setValue("effects", effects);

  QString realization = ui->realization_lineedit->text();
  if (!realization.isEmpty()) char_ini->setValue("realization", realization);

  char_ini->endGroup();
  char_ini->sync();
}

void AO2CharMaker::writeEmotions(QSettings* char_ini) {
  char_ini->beginGroup("Emotions");
  char_ini->setValue("numbers", m_emotions.size());

  int l_emote_index = 1;
  for (AO2Emote emotion : m_emotions) {
    AnimationData l_animation_data = emotion.animationData();
    QString l_emote_entry = QString("%1#%2#%3#%4#%5").arg(l_animation_data.comment, l_animation_data.preAnim,
                                                          l_animation_data.Anim,
                                                          QString::number(l_animation_data.modifier),
                                                          QString::number(l_animation_data.deskmod));
    char_ini->setValue(QString::number(l_emote_index), l_emote_entry);
    l_emote_index++;
  }
}

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
    ui->emote_deskmod_combobox->setCurrentIndex(0);
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

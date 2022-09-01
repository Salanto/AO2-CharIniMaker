#include "ao2charmaker.h"
#include "ui_ao2charmaker.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>

#include "ini_handler.h"

AO2CharMaker::AO2CharMaker(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::AO2CharMaker) {
  ui->setupUi(this);
  connect(ui->build_folders, &QPushButton::pressed, this,
          &AO2CharMaker::on_create_folder_pressed);
  connect(ui->control_save_button, &QPushButton::pressed, this,
          &AO2CharMaker::on_save_button_pressed);
  connect(ui->control_load_button, &QPushButton::pressed, this, &AO2CharMaker::on_load_button_pressed);
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

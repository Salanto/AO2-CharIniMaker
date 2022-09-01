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

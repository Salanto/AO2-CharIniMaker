#include "ao2charmaker.h"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QDialogButtonBox>

#include "ui_ao2charmaker.h"

AO2CharMaker::AO2CharMaker(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AO2CharMaker) {
  ui->setupUi(this);
  connect(ui->build_folders, &QPushButton::pressed, this,
          &AO2CharMaker::on_create_folder_pressed);
  connect(ui->control_buttons, &QDialogButtonBox::accepted,
          this, &AO2CharMaker::on_save_button_pressed);
}

AO2CharMaker::~AO2CharMaker() { delete ui; }

QString AO2CharMaker::resolvePath(QString f_path) {
  return QString("%1/%2/%3").arg(root_path, ui->name_lineedit->text(), f_path);
}

void AO2CharMaker::createFolder(QString f_name) {
    QDir().mkpath(resolvePath(f_name));
}

void AO2CharMaker::writeOptions()
{
    QSettings char_ini = QSettings(resolvePath("char.ini"), QSettings::IniFormat);
    char_ini.setIniCodec("UTF-8");
    char_ini.clear();

    // We version the char.ini. Since this tool currently mimics current AO2 .ini files
    // it is a version 1.
    char_ini.setValue("version/major", 1);

    char_ini.beginGroup("options");
    char_ini.setValue("name", ui->name_lineedit->text());

    QString showname = ui->showname_lineedit->text();
    if (!showname.isEmpty())
        char_ini.setValue("showname", ui->showname_lineedit->text());

    char_ini.setValue("pos", ui->side_combobox->currentText());

    QString blips = ui->blips_lineedit->text();
    if (!blips.isEmpty())
        char_ini.setValue("blips", blips);
    else
        char_ini.setValue("blips", "male");

    QString chat = ui->chat_lineedit->text();
    if (!chat.isEmpty())
        char_ini.setValue("chat", chat);

    QString chat_font = ui->chat_front_lineedit->text();
    if (!chat_font.isEmpty())
        char_ini.setValue("chat_font", chat_font);

    int chat_size = ui->chat_size_spinbox->value();
    char_ini.setValue("chat_size", chat_size);

    QString effects = ui->effects_lineedit->text();
    if (!effects.isEmpty())
        char_ini.setValue("effects", effects);

    QString realization = ui->realization_lineedit->text();
    if (!realization.isEmpty())
        char_ini.setValue("realization", realization);

    char_ini.endGroup();
    char_ini.sync();
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

void AO2CharMaker::on_save_button_pressed()
{
    if (ui->name_lineedit->text().isEmpty()) {
      QMessageBox::question(
          this, "Please name the character.",
          "Please enter a character name before saving the character.",
          QMessageBox::StandardButton::Ok);
      return;
    }
    writeOptions();
}

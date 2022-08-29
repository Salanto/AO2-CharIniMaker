#ifndef AO2CHARMAKER_H
#define AO2CHARMAKER_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QVector>
#include <QSettings>

#include "ao2emote.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AO2CharMaker;
}
QT_END_NAMESPACE

class AO2CharMaker : public QMainWindow {
  Q_OBJECT

 public:
  AO2CharMaker(QWidget *parent = nullptr);
  ~AO2CharMaker();

 private:
  Ui::AO2CharMaker *ui;

  /**
   * @brief The root directory that contains our character folder.
   *
   * @details Most commonly this will be /base/characters
   */
  QString root_path = QCoreApplication::applicationDirPath() + "/characters";

  /**
   * @brief Resolves the path given in relation to the characters folders root and character
   * @param Path/File we want to resolve.
   * @return Returns an absolute path to the asset we want to locate.
   */
  QString resolvePath(QString f_path);

  // Filesystem handler functions.

  /**
   * @brief Creates a folder and required root directories.
   * @param Name of the folder we want to create.
   */
  void createFolder(QString f_name);

  /**
   * @brief Writes the Options data in the char.ini
   */
  void writeOptions(QSettings *char_ini);

  /**
   * @brief Writes the Emotions data in the char.ini
   */
  void writeEmotions(QSettings *char_ini);

  /**
   * @brief Sets the ListWidget text according to the emote data provided.
   * @param f_index
   */
  void setEmoteRowText(int f_index, bool add_entry = false);

  /**
   * @brief Sets the emote component fields according to the emote data at the index.
   * @param f_index
   */
  void setEmoteEditMenu(int f_index);

  /**
   * @brief Shares storage between widget pages to save emotes.
   */
  QVector<AO2Emote> m_emotions;

 private slots:
  /**
   * @brief We want to create a folder structure.
   *
   * @details AO2-Client and by extension WebAO allow content to be foldered.
   * The creation of folders is a convenience to the user. It serves no function
   * in the creation of a char.ini
   */
  void on_create_folder_pressed();

  /**
   * @brief We want to save this char.ini
   *
   * @details Converting our widget data has to happen in multiple steps.
   *
   * Normally you would split configurations in seperate files for logical seperation.
   * Char.ini forces it all into a single file with improper structure. Ain't that grand?
   */
  void on_save_button_pressed();

  /**
   * @brief Adds an emote to the internal QVector of emotes.
   */
  void on_add_emote_pressed();


  void on_comment_lineedit_edited(QString f_text);

  void on_preanim_lineedit_edited(QString f_text);

  void on_animation_lineedit_edited(QString f_text);

  void on_modifier_combobox_item_selected(QString f_modifier_text);

  void on_deskmod_combobox_item_selected(QString f_deskmod_text);
};
#endif  // AO2CHARMAKER_H

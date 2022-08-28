#ifndef AO2CHARMAKER_H
#define AO2CHARMAKER_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QVector>

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
   * @brief Writes the Options data in our char.ini
   */
  void writeOptions();

  // Char.ini internal datastructure represented as structs

  /**
   * @brief The AnimationData class
   *
   * @details The emote information is delimited using the pound (#) symbol.
   *
   */
  struct AnimationData {
    QString comment;
    QString preAnim;
    QString Anim;
    int modifier;
    int deskmod;
  };

  /**
   * @brief The SoundData class
   *
   * @details The sound information is split into two groups in the ini.
   * [SoundN] contains the index of the emote and the sfx filename.
   * 1 = dubstep
   *
   * [SoundT] contains the index of the emote and the delay in ticks (60ms).
   * 1 = 0
   *
   * As you may have noticed this structure makes no sense and is stupid.
   */
  struct SoundData {
    int id = 0;
    QString sfx = "NO-SFX";
    int ticks = 0;
  };

  enum FrameType{
      SFX,
      REALIZATION,
      SHAKE
  };

  struct FrameFXEntry {
    QString emote;
    FrameType type;
    QList<int> frames;
  };

  // How tf does this work.
  struct FrameData {
      QList<FrameFXEntry> frameFX;
  };

  struct EmoteData {
    AnimationData emote;
    SoundData sound;
    FrameData frame_sfx;
  };

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
};
#endif  // AO2CHARMAKER_H

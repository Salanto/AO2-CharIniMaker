#ifndef AO2CHARMAKER_H
#define AO2CHARMAKER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AO2CharMaker; }
QT_END_NAMESPACE

class AO2CharMaker : public QMainWindow
{
    Q_OBJECT

public:
    AO2CharMaker(QWidget *parent = nullptr);
    ~AO2CharMaker();

private:
    Ui::AO2CharMaker *ui;
};
#endif // AO2CHARMAKER_H

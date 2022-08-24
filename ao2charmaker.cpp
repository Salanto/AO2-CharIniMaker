#include "ao2charmaker.h"
#include "ui_ao2charmaker.h"

AO2CharMaker::AO2CharMaker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AO2CharMaker)
{
    ui->setupUi(this);
}

AO2CharMaker::~AO2CharMaker()
{
    delete ui;
}


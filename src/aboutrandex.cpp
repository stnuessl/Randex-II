#include "aboutrandex.h"
#include "ui_aboutrandex.h"

#include <QtGui>

AboutRandex::AboutRandex(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::AboutRandex)
{
    _ui->setupUi(this);
    _ui->tabWidget->setTabText(0, QString("Readme"));
    _ui->tabWidget->setTabText(1, QString("License"));

    _ui->textEditReadme->setReadOnly(true);
    _ui->textEditLicense->setReadOnly(true);

    this->setWindowTitle(QString("About Randex"));

    QObject::connect(_ui->pushButtonQuit, &QPushButton::clicked, this, &AboutRandex::close);
}

AboutRandex::~AboutRandex()
{
    delete _ui;
}

#include "randex.h"
#include "ui_randex.h"
#include "scheduleview.h"

#include <QtGui>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

Randex::Randex(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Randex), _scheduleView(0)
{
    _ui->setupUi(this);

    _ui->spinBoxPositions->setRange(1, 10);

    _setupFileDialog();
    _setupWidgetAboutRandex();
    _setStatusTips();
    _connect();
}

Randex::~Randex()
{
    delete _ui;
    delete _widgetAboutRandex;

    if(_scheduleView)
        delete _scheduleView;
}
void Randex::_setupWidgetAboutRandex()
{
    QTabWidget *tabWidget;
    QPushButton *pushButtonOk;
    QSpacerItem *spacerItemLeft, *spacerItemRight;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;

    spacerItemLeft  = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum);
    spacerItemRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum);

    tabWidget = new QTabWidget();
    tabWidget->addTab(_widgetReadme(), "Readme");
    tabWidget->addTab(_widgetLicense(), "License");

    pushButtonOk = new QPushButton("&0k");

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->addItem(spacerItemLeft);
    hBoxLayout->addWidget(pushButtonOk);
    hBoxLayout->addItem(spacerItemRight);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(tabWidget);
    vBoxLayout->addLayout(hBoxLayout);

    _widgetAboutRandex = new QWidget();
    _widgetAboutRandex->setWindowTitle(QString("About Randex-II"));
    _widgetAboutRandex->setLayout(vBoxLayout);
    _widgetAboutRandex->resize(650, 400);

    QObject::connect(pushButtonOk, &QPushButton::clicked, _widgetAboutRandex, &QWidget::close);
}

QWidget *Randex::_widgetReadme(void)
{
    QWidget *widgetReadme;
    QTextEdit *textEditReadme;
    QString readme;

    readme.append("Lurchis gotta work to do.\n");

    textEditReadme = new QTextEdit();
    textEditReadme->setText(readme);
    textEditReadme->setReadOnly(true);

    widgetReadme = new QWidget();
    widgetReadme->setLayout(new QVBoxLayout());
    widgetReadme->layout()->addWidget(textEditReadme);

    return widgetReadme;
}

QWidget *Randex::_widgetLicense(void)
{
    QWidget *widgetLicense;
    QTextEdit *textEditLicense;
    QString license;

    license.append(QString("The MIT License (MIT)\n"));
    license.append(QString("Copyright (c) 2013 Patrick Hiemeyer, Steffen Nuessle\n"));
    license.append(QString("\n"));
    license.append(QString("Permission is hereby granted, free of charge, to any person obtaining a copy\n"));
    license.append(QString("of this software and associated documentation files (the \"Software\"), to deal in\n"));
    license.append(QString("the Software without restriction, including without limitation the rights to use,\n"));
    license.append(QString("copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the\n"));
    license.append(QString("Software, and to permit persons to whom the Software is furnished to do so,\n"));
    license.append(QString("subject to the following conditions:\n"));
    license.append(QString("\n"));
    license.append(QString("The above copyright notice and this permission notice shall be included in all\n"));
    license.append(QString("copies or substantial portions of the Software.\n"));
    license.append(QString("\n"));
    license.append(QString("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY\n"));
    license.append(QString("KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE\n"));
    license.append(QString("WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR\n"));
    license.append(QString("PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS\n"));
    license.append(QString("OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n"));
    license.append(QString("OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR\n"));
    license.append(QString("OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE\n"));
    license.append(QString("SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n"));

    textEditLicense = new QTextEdit();
    textEditLicense->setText(license);
    textEditLicense->setReadOnly(true);

    widgetLicense = new QWidget();
    widgetLicense->setLayout(new QVBoxLayout());
    widgetLicense->layout()->addWidget(textEditLicense);

    return widgetLicense;
}

void Randex::_setupFileDialog(void)
{
    _fileDialog = new QFileDialog(this);
    _fileDialog->setDirectory(QDir::homePath());
    _fileDialog->setViewMode(QFileDialog::List);
    _fileDialog->setNameFilter("Text Files (*.txt)");
    _fileDialog->setWindowModality(Qt::WindowModal);

}

void Randex::_setStatusTips(void)
{
    _ui->actionQuit->setStatusTip(QString("Close this application."));
    _ui->actionCreate_Schedule->setStatusTip(QString("Create the schedule table for current identifiers."));
    _ui->actionAbout_Randex->setStatusTip(QString("Get information about Randex-II."));

    _ui->lineEditIdentifiers->setStatusTip(QString("Add new identifiers."));
    _ui->spinBoxPositions->setStatusTip(QString("Enter the number of positions to fill."));

    _ui->pushButtonClearLast->setStatusTip(QString("Delete the last added identifier."));
    _ui->pushButtonClearAll->setStatusTip(QString("Delete all added identifiers."));
    _ui->pushButtonSave->setStatusTip(QString("Save the current identifiers."));
    _ui->pushButtonLoad->setStatusTip(QString("Load a identifier list"));
    _ui->pushButtonCreateSchedule->setStatusTip(QString("Create the schedule table for current identifiers."));
}

void Randex::_connect(void)
{
    QObject::connect(_ui->actionCreate_Schedule, &QAction::triggered, this, &Randex::_createScheduleTriggered);
    QObject::connect(_ui->actionQuit,            &QAction::triggered, this, &Randex::_quitTriggered);
    QObject::connect(_ui->actionAbout_Randex,    &QAction::triggered, this, &Randex::_aboutRandexTriggered);

    QObject::connect(_ui->pushButtonClearLast, &QPushButton::clicked, this, &Randex::_clearLastClicked);
    QObject::connect(_ui->pushButtonClearAll,  &QPushButton::clicked, this, &Randex::_clearAllClicked);
    QObject::connect(_ui->pushButtonSave,      &QPushButton::clicked, this, &Randex::_saveClicked);
    QObject::connect(_ui->pushButtonLoad,      &QPushButton::clicked, this, &Randex::_loadClicked);
    QObject::connect(_ui->pushButtonCreateSchedule, &QPushButton::clicked, this, &Randex::_createScheduleClicked);

    QObject::connect(_ui->lineEditIdentifiers, &QLineEdit::returnPressed, this, &Randex::_lineEditEnterPressed);
}


unsigned int Randex::_randomUInt(unsigned int min, unsigned int max)    const
{
    return qrand() % ((max + 1) - min) + min;
}

unsigned int Randex::_validRandomUInt(unsigned int min, unsigned int max, QList<unsigned int> listInvalids) const
{
    unsigned int ret;

    while(1) {
        ret = _randomUInt(min, max);

        if(listInvalids.count(ret) == 0)
            break;
    }

    return ret;
}

void Randex::_createSchedule(void)
{
    unsigned int val, minGap, maxGap, randGap;
    int positionCount;
    QList<unsigned int> listInvalids;
    QTableWidgetItem *item;
    QTableWidget *tableWidget;

    positionCount = _ui->spinBoxPositions->value();

    if(_ui->listWidgetIdentifiers->count() < (positionCount << 1)) {
        _ui->labelErrorMessage->setText(QString("Not enough identifiers defined."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    tableWidget = new QTableWidget(positionCount + 1, _ui->listWidgetIdentifiers->count());

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i)
        tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString("%1").arg(i + 1)));

    for(int i = 0; i < positionCount; ++i)
        tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString("Position %1").arg(i + 1)));

    tableWidget->setVerticalHeaderItem(positionCount, new QTableWidgetItem(QString("Comments")));

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i) {
        val = _validRandomUInt(0, _ui->listWidgetIdentifiers->count() - 1, listInvalids);
        listInvalids.append(val);

        item = new QTableWidgetItem(_ui->listWidgetIdentifiers->item(val)->text());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);

        tableWidget->setItem(0, i, item);
    }

    if(positionCount > 1) {
        minGap = 2;
        maxGap = (_ui->listWidgetIdentifiers->count() / (positionCount - 1)) - 1;

        for(int i = 1; i < positionCount; ++i) {
            randGap = _randomUInt(minGap, maxGap);

            for(int j = 0; j < _ui->listWidgetIdentifiers->count(); ++j)
                tableWidget->setItem(i, (j + randGap) % _ui->listWidgetIdentifiers->count(), tableWidget->item(i - 1, j)->clone());
        }
    }

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i) {
        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable);

        tableWidget->setItem(positionCount, i, item);
    }

    if(_scheduleView)
        delete _scheduleView;

    _scheduleView = new ScheduleView(0, tableWidget);
    _scheduleView->show();
}

void Randex::_createScheduleTriggered(void)
{
    _createSchedule();
}

void Randex::_quitTriggered(void)
{
    this->close();
}

void Randex::_aboutRandexTriggered(void)
{
    _widgetAboutRandex->show();
}

void Randex::_clearLastClicked(void)
{
    delete _ui->listWidgetIdentifiers->takeItem(_ui->listWidgetIdentifiers->count() - 1);
}

void Randex::_clearAllClicked(void)
{
    _ui->listWidgetIdentifiers->clear();
}

void Randex::_saveClicked(void)
{
    QStringList fileNames;
    QFile file;
    QTextStream out;

    _fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    _fileDialog->setFileMode(QFileDialog::AnyFile);

    if(_fileDialog->exec() != 1) {
        _ui->labelErrorMessage->setText(QString("File dialog failed."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    fileNames = _fileDialog->selectedFiles();

    if(fileNames.size() != 1) {
        _ui->labelErrorMessage->setText(QString("Too many files selected."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    file.setFileName(fileNames.first());

    if(file.open(QIODevice::WriteOnly | QIODevice::Text) != true) {
        _ui->labelErrorMessage->setText(QString("Opening file failed."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    out.setDevice(&file);

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i)
        out << _ui->listWidgetIdentifiers->item(i)->text().append(QString("\n"));
}

void Randex::_loadClicked(void)
{
    QStringList fileNames;
    QFile file;
    QTextStream in;

    _fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    _fileDialog->setFileMode(QFileDialog::ExistingFile);

    if(_fileDialog->exec() != 1) {
        _ui->labelErrorMessage->setText(QString("File dialog failed."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    fileNames = _fileDialog->selectedFiles();

    if(fileNames.size() != 1) {
        _ui->labelErrorMessage->setText(QString("Too many files selected."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    file.setFileName(fileNames.first());

    if(file.open(QIODevice::ReadOnly | QIODevice::Text) != true) {
        _ui->labelErrorMessage->setText(QString("Opening file failed."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    in.setDevice(&file);

    while(!in.atEnd())
        _ui->listWidgetIdentifiers->addItem(in.readLine());

    _ui->listWidgetIdentifiers->setStatusTip(QString("%1 identifiers.").arg(_ui->listWidgetIdentifiers->count()));
}

void Randex::_createScheduleClicked(void)
{
    _createSchedule();
}

void Randex::_lineEditEnterPressed(void)
{
    _ui->listWidgetIdentifiers->addItem(_ui->lineEditIdentifiers->text());

    _ui->lineEditIdentifiers->clear();

    _ui->listWidgetIdentifiers->setStatusTip(QString("%1 identifiers.").arg(_ui->listWidgetIdentifiers->count()));
}

#include "randex.h"
#include "ui_randex.h"

#include <QtGui>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

Randex::Randex(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::Randex), _scheduleTable(0), _aboutRandex(new AboutRandex())
{
    _ui->setupUi(this);
    _ui->spinBoxPositions->setRange(1, 10);

    _setupFileDialog();
    _setStatusTips();
    _connect();
}

Randex::~Randex()
{
    delete _ui;
    delete _aboutRandex;

    if(_scheduleTable)
        delete _scheduleTable;
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
    QTableWidget tableWidget;

    positionCount = _ui->spinBoxPositions->value();

    if(_ui->listWidgetIdentifiers->count() < (positionCount << 1)) {
        _ui->labelErrorMessage->setText(QString("Not enough identifiers defined."));
        return;
    } else {
        _ui->labelErrorMessage->clear();
    }

    tableWidget.setRowCount(positionCount + 1);
    tableWidget.setColumnCount(_ui->listWidgetIdentifiers->count());

    for(int i = 0; i < positionCount; ++i)
        tableWidget.setVerticalHeaderItem(i, new QTableWidgetItem(QString("Position %1").arg(i + 1)));

    tableWidget.setVerticalHeaderItem(positionCount, new QTableWidgetItem(QString("Comments")));

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i) {
        val = _validRandomUInt(0, _ui->listWidgetIdentifiers->count() - 1, listInvalids);
        listInvalids.append(val);

        item = new QTableWidgetItem(_ui->listWidgetIdentifiers->item(val)->text());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);

        tableWidget.setItem(0, i, item);
    }

    if(positionCount > 1) {
        minGap = 2;
        maxGap = (_ui->listWidgetIdentifiers->count() / (positionCount - 1)) - 1;

        for(int i = 1; i < positionCount; ++i) {
            randGap = _randomUInt(minGap, maxGap);

            for(int j = 0; j < _ui->listWidgetIdentifiers->count(); ++j)
                tableWidget.setItem(i, (j + randGap) % _ui->listWidgetIdentifiers->count(), tableWidget.item(i - 1, j)->clone());
        }
    }

    for(int i = 0; i < _ui->listWidgetIdentifiers->count(); ++i) {
        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable);

        tableWidget.setItem(positionCount, i, item);
    }

    if(_scheduleTable)
        delete _scheduleTable;

    _scheduleTable = new ScheduleTable(0, tableWidget);
    _scheduleTable->show();
}

QString Randex::_getFileName(void)
{
    QStringList stringList;

    if(_fileDialog->exec() != 1) {
        _ui->labelErrorMessage->setText(QString("File dialog failed."));
        return QString();
    } else {
        _ui->labelErrorMessage->clear();
    }

    stringList = _fileDialog->selectedFiles();

    if(stringList.size() != 1) {
        _ui->labelErrorMessage->setText(QString("Too many files selected."));
        return QString();
    } else {
        _ui->labelErrorMessage->clear();
    }

    return stringList.takeFirst();
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
    _aboutRandex->show();
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
    QFile file;
    QTextStream out;

    _fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    _fileDialog->setFileMode(QFileDialog::AnyFile);

    file.setFileName(_getFileName());

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
    QFile file;
    QTextStream in;

    _fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    _fileDialog->setFileMode(QFileDialog::ExistingFile);

    file.setFileName(_getFileName());

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

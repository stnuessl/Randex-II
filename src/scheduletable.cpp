#include "scheduletable.h"
#include "ui_scheduletable.h"

#include <QTableWidget>

ScheduleTable::ScheduleTable(QWidget *parent, const QTableWidget &tableWidget) :
    QWidget(parent),
    _ui(new Ui::ScheduleTable)
{
    _ui->setupUi(this);

    this->setWindowTitle("Schedule Table");

    _ui->tableWidget->setRowCount(tableWidget.rowCount());
    _ui->tableWidget->setColumnCount(tableWidget.columnCount());

    for(int i = 0; i < tableWidget.rowCount(); ++i)
        _ui->tableWidget->setVerticalHeaderItem(i, tableWidget.verticalHeaderItem(i)->clone());

    for(int i = 0; i < tableWidget.rowCount(); ++i) {
        for(int j = 0; j < tableWidget.columnCount(); ++j)
            _ui->tableWidget->setItem(i, j, tableWidget.item(i, j)->clone());
    }

    this->resize(_ui->tableWidget->columnWidth(0) * _ui->tableWidget->columnCount() + 100,
                 _ui->tableWidget->rowHeight(0)   * (_ui->tableWidget->rowCount() + 1) + 50);

    QObject::connect(_ui->pushButtonDone, &QPushButton::clicked, this, &QWidget::close);
}

ScheduleTable::~ScheduleTable()
{
    delete _ui;
}

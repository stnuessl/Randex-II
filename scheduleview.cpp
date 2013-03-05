#include "scheduleview.h"

#include <QLayout>

ScheduleView::ScheduleView(QWidget *parent, QTableWidget *tableWidget) :
    QWidget(parent), _tableWidgetSchedule(tableWidget)
{
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;

    _spacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum);
    _pushButtonClose = new QPushButton("&Close");

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->addItem(_spacerItem);
    hBoxLayout->addWidget(_pushButtonClose);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(_tableWidgetSchedule);
    vBoxLayout->addLayout(hBoxLayout);

    this->setLayout(vBoxLayout);
    this->setWindowTitle(QString("Schedule Table"));
    this->resize(_tableWidgetSchedule->columnWidth(0) * _tableWidgetSchedule->columnCount() + 100,
                 _tableWidgetSchedule->rowHeight(0)   * (_tableWidgetSchedule->rowCount() + 1) + 50);

    QObject::connect(_pushButtonClose, &QPushButton::clicked, this, &ScheduleView::close);
}

ScheduleView::~ScheduleView()
{

}

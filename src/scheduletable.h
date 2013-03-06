#ifndef SCHEDULETABLE_H
#define SCHEDULETABLE_H

#include <QWidget>
#include <QtGui>
#include <QTableWidget>

namespace Ui {
class ScheduleTable;
}

class ScheduleTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScheduleTable(QWidget *parent = 0, const QTableWidget &tableWidget = QTableWidget());
    ~ScheduleTable();
    
private:
    Ui::ScheduleTable *_ui;
};

#endif // SCHEDULETABLE_H

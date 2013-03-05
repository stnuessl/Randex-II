#ifndef SCHEDULEVIEW_H
#define SCHEDULEVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QSpacerItem>

class ScheduleView : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleView(QWidget *parent = 0, QTableWidget *tableWidget = 0);
    ~ScheduleView();
signals:
    
public slots:
private:
    QTableWidget *_tableWidgetSchedule;
    QPushButton *_pushButtonClose;
    QSpacerItem *_spacerItem;
    
};

#endif // SCHEDULEVIEW_H

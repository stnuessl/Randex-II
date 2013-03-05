#ifndef RANDEX_H
#define RANDEX_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>

#include "scheduleview.h"

namespace Ui {
class Randex;
}

class Randex : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Randex(QWidget *parent = 0);
    ~Randex();
    
private:
    Ui::Randex   *_ui;
    ScheduleView *_scheduleView;
    QWidget      *_widgetAboutRandex;
    QFileDialog  *_fileDialog;

    void _setupWidgetAboutRandex(void);
    QWidget *_widgetReadme(void);
    QWidget *_widgetLicense(void);

    void _setupFileDialog(void);
    void _setStatusTips(void);
    void _connect(void);


    unsigned int _randomUInt(unsigned int min, unsigned int max)    const;
    unsigned int _validRandomUInt(unsigned int min,
                                  unsigned int max,
                                  QList<unsigned int> listInvalids)     const;
    void _createSchedule(void);

private slots:
    /* action handles */
    void _createScheduleTriggered(void);
    void _quitTriggered(void);
    void _aboutRandexTriggered(void);

    /* button handles */
    void _clearLastClicked(void);
    void _clearAllClicked(void);
    void _saveClicked(void);
    void _loadClicked(void);
    void _createScheduleClicked(void);

    /* line edit handles */
    void _lineEditEnterPressed(void);
};

#endif // RANDEX_H

#ifndef RANDEX_H
#define RANDEX_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>

#include "scheduletable.h"
#include "aboutrandex.h"

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
    Ui::Randex    *_ui;
    ScheduleTable *_scheduleTable;
    AboutRandex   *_aboutRandex;
    QFileDialog   *_fileDialog;


    void _setupFileDialog(void);
    void _setStatusTips(void);
    void _connect(void);


    unsigned int _randomUInt(unsigned int min, unsigned int max)    const;
    unsigned int _validRandomUInt(unsigned int min,
                                  unsigned int max,
                                  QList<unsigned int> listInvalids)     const;
    void _createSchedule(void);

    QString _getFileName(void);

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

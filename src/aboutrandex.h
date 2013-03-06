#ifndef ABOUTRANDEX_H
#define ABOUTRANDEX_H

#include <QWidget>

namespace Ui {
class AboutRandex;
}

class AboutRandex : public QWidget
{
    Q_OBJECT
    
public:
    explicit AboutRandex(QWidget *parent = 0);
    ~AboutRandex();
    
private:
    Ui::AboutRandex *_ui;
};

#endif // ABOUTRANDEX_H

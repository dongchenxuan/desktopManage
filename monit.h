#ifndef MONIT_H
#define MONIT_H

#include <QWidget>
#include <QProgressBar>
#include <QTimer>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <QLabel>
#include <QMovie>

#include "monitcpu.h"
#include "monitram.h"

class Monit : public QWidget
{
    Q_OBJECT
public:
    explicit Monit(QWidget *parent = nullptr);
    QFrame *frame;
    QLabel *label;
    QMovie *movie;
public:
    monitCPU* cpuWin;
    monitRAM* ramWin;
    //添加鼠标事件
    bool moveWindows = true;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

private:
    void initMonit();
    QPoint getQScreenSize();
    QLabel * bglabel;
    QPoint clickPos;
protected:
    bool eventFilter(QObject *watched, QEvent *evt);

public slots:
};

#endif // MONIT_H

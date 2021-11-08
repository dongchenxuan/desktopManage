#ifndef COMMEMORIAL_H
#define COMMEMORIAL_H

#include <QWidget>
#include <ActiveQt/QAxWidget>
#include <QString>
#include <QFrame>
#include <QMouseEvent>
#include <QPoint>
#include <QMovie>

#include <todo.h>

class comMemorial : public QWidget
{
    Q_OBJECT
public:
    explicit comMemorial(QWidget *parent = nullptr);

signals:

public:
    todo* todoWin;
public:
    QAxWidget* axWidget;
    QFrame* weather;
    QFrame* calendar;
    QMovie* movie;
public:
    //添加鼠标事件
    bool moveWindows = true;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void initTodoWin();    // 初始化备忘录
    void onLookupHost();   // 检查网络连接状态
    //设置要打开的网页
    QString webpath=QString("http://api.xuanzhe.club/weather/");
    QPoint clickPos;
public slots:
};

#endif // COMMEMORIAL_H

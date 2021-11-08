#include "commemorial.h"

#include <ActiveQt/QAxWidget>
#include <ActiveQt/qaxbase.h>
#include <QVBoxLayout>

comMemorial::comMemorial(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500,520);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setWindowOpacity(0.5);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    /*
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                        "background-position:center;"
                        "background-repeat:no-repeat;");*/
    /*
    weather = new QFrame(this);
    weather->setFrameShape(QFrame::HLine);
    weather->setFrameShadow(QFrame::Sunken);
    weather->setStyleSheet("QFrame{border:2px; "
                           "solid #014F84;"
                           "background:transparent;"
                           "border:1px solid #9900FF;}");
    weather->setGeometry(QRect(0,0,280,150));
    weather->setParent(this);;
    */
    axWidget = new QAxWidget(this);

    //注册组件ID
    axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    //不显示警告信息
    axWidget->setProperty("DisplayAlerts",false);
    //不显示滚动条
    axWidget->setProperty("DisplayScrollBars",false);
    //显示网页
    axWidget->dynamicCall("Navigate(const QString&)",webpath);
    axWidget->setGeometry(QRect(240,0,260,120));
    axWidget->setParent(this);
    /*
    QVBoxLayout * weatherMain = new QVBoxLayout;
    weatherMain->addWidget(axWidget);
    weatherMain->setParent(weather);
    */

    initTodoWin();

    QLabel* label = new QLabel(this);
    label->setGeometry(QRect(0,0,210,130));
    label->setParent(this);
    label->setStyleSheet("QLabel{"
                         "background:transparent;}");
    movie = new QMovie(":/images/gif/bkg2.gif");
    label->setMovie(movie);
    movie->start();
}

void comMemorial::mousePressEvent(QMouseEvent *event)
{
    clickPos = event->globalPos() - this->pos();
}

void comMemorial::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons()==Qt::LeftButton) && (clickPos!=QPoint()) && (!this->isMaximized())){
        move(event->globalPos() - clickPos);
    }
}

void comMemorial::mouseReleaseEvent(QMouseEvent *event)
{
    clickPos = QPoint();
}


void comMemorial::initTodoWin(){
    todoWin = new todo;
    todoWin->setGeometry(QRect(0,130,500,400));
    todoWin->setParent(this);
}

void comMemorial::onLookupHost()
{

}


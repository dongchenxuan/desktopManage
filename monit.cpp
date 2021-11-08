#include "monit.h"

#include <QScreen>
#include <QApplication>
#include <QMouseEvent>


Monit::Monit(QWidget *parent) : QWidget(parent)
{
    this->initMonit();

}
void Monit::initMonit(){
    this->setFixedSize(350, 130);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);



    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                        "background-position:center;"
                        "background-repeat:no-repeat;");


    QPoint point=getQScreenSize();
    this->move(point.x()-360,point.y()-200);

    cpuWin = new monitCPU;
    cpuWin->setParent(this);
    cpuWin->setGeometry(QRect(0,0,130,130));
    cpuWin->show();

    ramWin = new monitRAM;
    ramWin->setParent(this);
    ramWin->setGeometry(QRect(220,0,130,130));
    ramWin->show();

    /*
    lattice = new QFrame(this);
    lattice->setFrameShape(QFrame::HLine);
    lattice->setFrameShadow(QFrame::Sunken);
    lattice->setGeometry(QRect(0,40,350,320));
    lattice->setStyleSheet("QFrame{"
                           "border:2px; "
                           "solid #014F84;"
                           "background:transparent;"
                           "border:1px solid #9933FF;}");
    */
    frame = new QFrame(this);
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setGeometry(QRect(130,0,90,130));
    frame->setStyleSheet("QFrame{"
                         "border:2px; "
                         "solid #014F84;"
                         "background:transparent}");
    label = new QLabel(this);
    label->setGeometry(QRect(0,0,210,130));
    label->setParent(frame);
    label->setStyleSheet("QLabel{"
                         "background:transparent;}");
    movie = new QMovie(":/images/gif/bkg1.gif");
    label->setMovie(movie);
    movie->start();
}

QPoint Monit::getQScreenSize(){
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();

    return QPoint(desktop_width,desktop_height);
}

bool Monit::eventFilter(QObject *watched, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();

            return true;
        } else {
            exit(0);
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            if(moveWindows == true){
                this->move(event->globalPos() - mousePoint);
                return true;
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void Monit::mousePressEvent(QMouseEvent *event)
{
    clickPos = event->globalPos() - this->pos();
}

void Monit::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons()==Qt::LeftButton) && (clickPos!=QPoint()) && (!this->isMaximized())){
        move(event->globalPos() - clickPos);
    }
}

void Monit::mouseReleaseEvent(QMouseEvent *event)
{
    clickPos = QPoint();
}

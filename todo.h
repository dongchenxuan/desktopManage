#ifndef TODO_H
#define TODO_H

#include <QWidget>
#include <QFrame>
#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QPoint>
#include <Windows.h>
#include <QScreen>
#include <QPainter>
#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <qmenu>
#include <QCloseEvent>
#include <QIcon>
#include <QApplication>
#include <qDebug>
#include <QLabel>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QTableView>
#include <signal.h>
#include <QSplitter>
#include <qpushbutton.h>

class todo : public QWidget
{
    Q_OBJECT

public:
    explicit todo(QWidget *parent = nullptr);
    ~todo();
public:
//    QFrame *frame;
    QStandardItemModel *ItemModel;
    QListWidget *list;
    QLineEdit *daiban;
    QPushButton *addbutton;
    QPushButton *delbutton;
    QMenu* popMenu;
    QAction *del,*add;
    void init();
    void Addkongjian();
    void contextMenuEvent( QContextMenuEvent * event ) ;
    void show_menu(const QPoint pos);

signals:

public slots:
    void addbutton_clicked();
    void delbutton_clicked();


};

#endif // TODO_H

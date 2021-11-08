#ifndef SKINWINDOW_H
#define SKINWINDOW_H

#include <QtWidgets/QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QSystemTrayIcon>

class filewindow : public QWidget
{
    Q_OBJECT
public:
    explicit filewindow(QWidget *parent = nullptr);
public:
    QFrame* mainframe;
    QStringListModel *Model;
    QStandardItemModel *ItemModel;
    QVBoxLayout *mainLayout;
    QListWidget *listview;
    QStringList *strList;
    QPushButton *delButton;
    QPushButton *addButton;
private slots:
    void delButtonClicked();
    void selectClicked(QListWidgetItem * item);
    void addButtonClicked(int sel);
private:
    void initSkinwindow();    // 初始化
    QSystemTrayIcon *trayIcon;
    void closeEvent(QCloseEvent *event);
    void readFile(QString path);
    void writeFile(QString path);
public:
    void receiveFilepath(QString str); //接受传递来的目录
    QString getfilepath();             //获得目录文件名
private:
    QString path;
};

#endif // SKINWINDOW_H

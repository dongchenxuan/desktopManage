#ifndef MONITCPU_H
#define MONITCPU_H

#include <QWidget>
#include <QProgressBar>
#include <QTimer>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <QMutex>


class monitCPU : public QWidget
{
    Q_OBJECT
public:
    explicit monitCPU(QWidget *parent = nullptr);
protected:
    //页面重绘事件
    void paintEvent(QPaintEvent *event);
private:
    void initMonit();
    QPoint getQScreenSize();
    int get_CpuUsage();
    void drawBackGround(QPainter* painter);
    void drawWaterWave(QPainter* painter);
    void drawText(QPainter* painter);
    /*
    void drawCPUBackGround(QPainter* painter);
    void drawCPUWaterWave(QPainter* painter);
    void drawCPUText(QPainter* painter);
    void drawRAMBackGround(QPainter* painter);
    void drawRAMWaterWave(QPainter* painter);
    void drawRAMText(QPainter* painter);
    */
private:
    int m_iBorderWidth;//边框厚度
    int m_iValue;//当前进度条进度
    double m_dOffset;//水波偏移量
    QColor m_waterColor;//水波颜色
    QColor m_backgroundColor;//背景颜色
    QColor m_borderColor;//边框颜色
    QColor m_textColor;//文本颜色
    QTimer *m_timer;//控制水波移动的定时器
    QTimer *getCPU;//控制获取CPU占用率，避免资源消耗过多
    qreal cpuUsagePercentageInTime(const qint64 &msecs);

private:
    int cpuPercent;
signals:

public slots:


};

#endif // MONITCPU_H

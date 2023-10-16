#ifndef SONWIDGET_H
#define SONWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include "singlewidget.h"


class sonwidget : public QWidget
{
    Q_OBJECT
public:
    explicit sonwidget(QWidget *parent = nullptr);
    singlewidget * get_FCFS(){ return FCFS; }
    singlewidget * get_SSTF(){ return SSTF; }
    singlewidget * get_SCAN(){ return SCAN; }
    singlewidget * get_LOOK(){ return LOOK; }

signals:    //信号

private:
    singlewidget * FCFS;        //先到先服务算法
    singlewidget * SSTF;        //最短查找时间优先算法
    singlewidget * SCAN;        //扫描算法
    singlewidget * LOOK;        //电梯算法
    QGridLayout * gridLayout;   //网格布局
};

#endif // SONWIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include<QFormLayout>
#include<QPushButton>
#include<QDebug>
#include"sonwidget.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initWidge();                                                                   //初始化

    //获取表单提交数据
    int get_number(){ return number_input->toInt(); }                                   //磁道序列数
    double get_across_Time(){ return across_Time_input->toDouble(); }                     //跨越1个磁道所用时间（单位：毫秒）
    double get_start_Time(){ return start_Time_input->toDouble(); }                       //启动时间（单位：毫秒）
    double get_rotate_Speed(){ return rotate_Speed_input->toDouble(); }                   //磁盘转速（单位：转/分钟）
    int get_tracksector_Number(){ return tracksector_Number_input->toInt(); }           //每磁道扇区数
    int get_sector_Bytes_Number_input(){ return sector_Bytes_Number_input->toInt(); }   //磁头移动法方向（0：向内，1：向外）
    int get_direction(){ return direction_input->toInt(); }

    //设置算法坐标以绘制折线图
    void set_FCFS_point(QVector<double> x,QVector<int> y,QVector<int> select){ sonwindow->get_FCFS()->setpoint_out(x,y,select); }
    void set_SSTF_point(QVector<double> x,QVector<int> y,QVector<int> select){ sonwindow->get_SSTF()->setpoint_out(x,y,select); }
    void set_SCAN_point(QVector<double> x,QVector<int> y,QVector<int> select){ sonwindow->get_SCAN()->setpoint_out(x,y,select); }
    void set_LOOK_point(QVector<double> x,QVector<int> y,QVector<int> select){ sonwindow->get_LOOK()->setpoint_out(x,y,select); }

    //设置文本输出数据
    void set_FCFS_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat){
        sonwindow->get_FCFS()->set_data(position,sq,os,sum,seek,at,art,tt,tat);
    }
    void set_SSTF_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat){
        sonwindow->get_SSTF()->set_data(position,sq,os,sum,seek,at,art,tt,tat);
    }
    void set_SCAN_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat){
        sonwindow->get_SCAN()->set_data(position,sq,os,sum,seek,at,art,tt,tat);
    }
    void set_LOOK_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat){
        sonwindow->get_LOOK()->set_data(position,sq,os,sum,seek,at,art,tt,tat);
    }

signals:
    void after_submit();
public slots:
    void run();
private:
    //标签
    QLabel * number_L;                          //磁道序列数
    QLabel * across_Time_L;                     //跨越1个磁道所用时间（单位：毫秒）
    QLabel * start_Time_L;                      //启动时间（单位：毫秒）
    QLabel * rotate_Speed_L;                    //磁盘转速（单位：转/分钟）
    QLabel * tracksector_Number_L;              //每磁道扇区数
    QLabel * sector_Bytes_Number_L;             //每扇区字节数
    QLabel * direction_L;                       //磁头移动法方向（0：向内，1：向外）

    //文本输入框
    QLineEdit * number_T;
    QLineEdit * across_Time_T;
    QLineEdit * start_Time_T;
    QLineEdit * rotate_Speed_T;
    QLineEdit * tracksector_Number_T;
    QLineEdit * sector_Bytes_Number_T;
    QLineEdit * direction_T;

    //记录表单数据
    QString * number_input;
    QString * across_Time_input;
    QString * start_Time_input;
    QString * rotate_Speed_input;
    QString * tracksector_Number_input;
    QString * sector_Bytes_Number_input;
    QString * direction_input;

    QPushButton * submit;                       //提交按钮
    QFormLayout * layout;                       //表单布局分布
    sonwidget * sonwindow;                      //子窗口

};
#endif // WIDGET_H

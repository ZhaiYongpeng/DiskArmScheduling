#ifndef SINGLEWIDGET_H
#define SINGLEWIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QVector>
#include <QDebug>
#include <QtCharts/QValueAxis>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QtWidgets/QScrollBar>
#include <QLineEdit>
#include <QTextEdit>

class singlewidget : public QWidget
{
    Q_OBJECT
public:
    explicit singlewidget(QWidget *parent = nullptr);
    ~singlewidget();
    void initWidge();                                                             //初始化
    QPushButton * get_button(){ return start; }                                   //获取开始按钮
    void setchartitle(QString title){ chart->setTitle(title);}                    //设置折线图标题
    void setpoint_out(QVector<double> x_gather,QVector<int> y_gather,QVector<int> select);             //设置points坐标和输出文本
    void set_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat);//设置文本输出数据
signals:

public slots:
    void run();                 //计时器启动，开始画折线图
    void slider(int value);     //滑动条
    void timerEvent();                                                //画折线图
private:
    int currentIndex = 0;
    QLineSeries * series;       //折线图
    QChart *chart;              //折线图
    QChartView * chartView;     //折线图

    QValueAxis *xAxis;          //x坐标轴
    QValueAxis *yAxis;          //y坐标轴
    double interval_x = 1500;      //x轴最大间隔
    int interval_y = 200;       //y轴最大间隔
    double m_x = 0;              //x坐标轴最大值
    double low_x;                //x坐标轴最小值

    QPushButton * start;        //开始按钮
    QScrollBar *scrollBar;      //滑动条
    QTextEdit * outPutText;     //输出文本
    QVBoxLayout * verticalLayout;//垂直布局
    QHBoxLayout * levellayout;  //水平布局

    //画动态折线图
    QVector<QPointF> * points;  //存储坐标
    QTimer * timer;              //定时器
    int position;               //当前坐标

    QPointF startPoint;         // 初始化起始坐标
    QPointF endPoint;           // 初始化终点坐标
    int stepCount;              // 动画分为多少步
    int currentStep;            //当前步
    QVector<int> select_out;    //输出文本

    int currentTrack;           //当前磁头位置
    QVector<int> sequence;      //随机生成的磁道访问序列
    QVector<int> orderedSequence;//引臂移动序列
    int sumOfArmMovement;       //引臂移动总量
    double  seekTime;            //寻道时间
    double averageTime;         //平均寻道时间
    double averageRotationDelayTime;//平均旋转延迟时间
    double transferTime;        //传输时间
    double totalAccessTime;     //所有访问处理时间
};

#endif // SINGLEWIDGET_H

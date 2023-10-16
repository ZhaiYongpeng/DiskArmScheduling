#include "singlewidget.h"

singlewidget::singlewidget(QWidget *parent)
    : QWidget{parent}
{
    this->initWidge();
}

void singlewidget::initWidge(){

    start = new QPushButton("start",this);
//    start->setFixedWidth(100);
    start->show();

    // 创建折线图数据系列
    series = new QLineSeries();

    // 创建图表并将数据系列添加到图表中
    chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();                          //隐藏图例
    chart->createDefaultAxes();

    // 创建图表视图
    chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿效果
    chartView->show();

    // 创建横坐标轴和纵坐标轴
    xAxis = new QValueAxis;
    xAxis->setRange(0, interval_x); // 设置横坐标范围
    xAxis->setTitleText("时间(毫秒)"); // 设置横坐标标题
    chart->setAxisX(xAxis, series); // 将横坐标轴与系列关联

    yAxis = new QValueAxis;
    yAxis->setRange(0, interval_y); // 设置纵坐标范围
    yAxis->setTitleText("磁道"); // 设置纵坐标标题
    chart->setAxisY(yAxis, series); // 将纵坐标轴与系列关联

    // 初始化数据点集合
    points = new QVector<QPointF>();

    // 创建定时器，用于动画绘制
    timer = new QTimer(this);

    //拖动条
    // 创建拖动条控件
    scrollBar = new QScrollBar(Qt::Horizontal,this);
//    scrollBar->setRange(0, m_x-interval_x); // 设置范围为数据总数减去每页显示的数据个数
//    scrollBar->setStyleSheet("QScrollBar:horizontal { width: 300; height:10;}");
//    scrollBar->setVisible(false);//显示按钮

    outPutText = new QTextEdit();
    outPutText->setReadOnly(true);

    verticalLayout = new QVBoxLayout();         //垂直布局
    levellayout = new QHBoxLayout();            //水平布局
    verticalLayout->addWidget(chartView,10);    //添加图标
    verticalLayout->addWidget(scrollBar,1);     //添加拖动条
    verticalLayout->addWidget(start,1);         //添加按钮
    levellayout->addLayout(verticalLayout,3);     //添加垂直布局
    levellayout->addWidget(outPutText,1);         //添加输出文本
    setLayout(levellayout);                       //放置进容器

    // 连接拖动条的值改变信号到自定义的槽函数
    QObject::connect(scrollBar, &QScrollBar::valueChanged,this,&singlewidget::slider);
    //连接按钮的点击信号到定时器的开始
    connect(start,&QPushButton::clicked,this,&singlewidget::run);
    // 连接定时器的timeout信号到画折线图
    connect(timer, &QTimer::timeout, this, &singlewidget::timerEvent);
}

void singlewidget::setpoint_out(QVector<double> x_gather,QVector<int> y_gather,QVector<int> select){
    for(int i = 0;i < x_gather.size();i++){
        points->append(QPointF(x_gather[i],y_gather[i]));
    }
    select_out = select;
}
void singlewidget::set_data(int position,QVector<int> sq,QVector<int> os,int sum,double seek,double at,double art,double tt,double tat){
    currentTrack = position;           //当前磁头位置
    sequence = sq;              //随机生成的磁道访问序列
    orderedSequence = os;       //引臂移动序列
    sumOfArmMovement = sum;       //引臂移动总量
    seekTime = seek;            //寻道时间
    averageTime = at;         //平均寻道时间
    averageRotationDelayTime = art;//平均旋转延迟时间
    transferTime = tt;        //传输时间
    totalAccessTime = tat;     //所有访问处理时间
    points->append(QPointF(0,currentTrack));
}

void singlewidget::run(){
    low_x = 0;      //x坐标轴最小值
    position = 0;   //当前坐标
    startPoint = (*points)[position]; // 初始化起始坐标
    endPoint = (*points)[++position];// 初始化终点坐标
    stepCount = 200; // 动画分为多少步
    currentStep = 0; //当前步
    timer->setInterval((endPoint.x() - startPoint.x())/stepCount); // 设置定时器间隔时间

    //文本输出
    outPutText->append("当前磁头位于磁道:" + QString::number(currentTrack));
    outPutText->append("随机生成的磁道访问序列为:");
    for(int i = 0;i < sequence.size();i++){
        outPutText->append(QString::number(sequence[i]));
    }

    timer->start();// 启动定时器
}

void singlewidget::timerEvent(){

    if (currentStep < stepCount) {
        //获取最新坐标
        qreal x = startPoint.x() + (endPoint.x() - startPoint.x()) * (currentStep + 1) / stepCount;
        qreal y = startPoint.y() + (endPoint.y() - startPoint.y()) * (currentStep + 1) / stepCount;

        // 清空数据系列
        series->clear();

        //添加已经输出的坐标
        for(int i = 0;i < position;i++){
            series->insert(i,(*points)[i]);
        }
        // 添加起始点和当前点
        series->append(startPoint);
        series->append(QPointF(x, y));

        if(x - low_x > interval_x){
            low_x = x - interval_x;
            xAxis->setRange(low_x,x);
        }
        scrollBar->setRange(0, x-interval_x); // 设置范围为数据总数减去每页显示的数据个数  关于滑动条

        // 刷新图表
        chartView->repaint();

        currentStep++;
    } else {
        currentStep = 0; //重置部署
        if(position < points->size() - 1){
            if((select_out)[position-1] == 0){
                outPutText->append("正在移动磁头到磁道" + QString::number((*points)[position].y()));
            }
            if((select_out)[position-1] == 1){
                outPutText->append("正在定位到" + QString::number((*points)[position].y()) + "磁道的扇区...");
            }
            if((select_out)[position-1] == 2){
                outPutText->append("正在读写数据...");
            }

            startPoint = (*points)[position];
            endPoint = (*points)[++position];
            timer->setInterval((endPoint.x() - startPoint.x())/stepCount); // 设置定时器间隔时间
        }
        else{
            if((select_out)[position-1] == 0){
                outPutText->append("正在移动磁头到磁道" + QString::number((*points)[position].y()));
            }
            if((select_out)[position-1] == 1){
                outPutText->append("正在定位到" + QString::number((*points)[position].y()) + "磁道的扇区...");
            }
            if((select_out)[position-1] == 2){
                outPutText->append("正在读写数据...");
            }

            // 清空数据系列
            series->clear();
            //添加已经输出的坐标
            for(int i = 0;i < position + 1;i++){
                series->insert(i,(*points)[i]);
            }
            if((*points)[points->size()- 1].x()>interval_x){
                low_x = (*points)[points->size()- 1].x() - interval_x;
                xAxis->setRange(low_x,(*points)[points->size()- 1].x());
                scrollBar->setRange(0,(*points)[points->size()- 1].x()-interval_x); // 设置范围为数据总数减去每页显示的数据个数  关于滑动条
            }
            else{
                xAxis->setRange(low_x,interval_x);
                scrollBar->setRange(0,0); // 设置范围为数据总数减去每页显示的数据个数  关于滑动条
            }

            // 刷新图表
            chartView->repaint();
            timer->stop(); // 动画结束，停止定时器

            outPutText->append("产生的引臂移动序列为:");
            for(int i = 0;i < orderedSequence.size();i++){
                outPutText->append(QString::number(orderedSequence[i]));
            }
            outPutText->append("引臂移动总量为:" + QString::number(sumOfArmMovement));
            outPutText->append("寻道时间为:" + QString::number(seekTime) + "ms");
            outPutText->append("平均寻道时间为:" + QString::number(averageTime) + "ms");
            outPutText->append("平均旋转延迟时间为:" + QString::number(averageRotationDelayTime) + "ms");
            outPutText->append("传输时间为:" + QString::number(transferTime) + "ms");
            outPutText->append("所有访问处理时间为:" + QString::number( totalAccessTime) + "ms");


        }
    }
}

//拖动条
void singlewidget::slider(int value){
    double viewportRange = interval_x; // 视口范围，即当前显示的数据范围
    // 根据拖动条的值计算视口范围的起始索引
    double startIndex = value;
    double endIndex = value + viewportRange + 1;
    // 重新设置图表视图的范围
    qreal minX = startIndex;
    qreal maxX = endIndex;
    chartView->chart()->axisX()->setRange(minX, maxX);
    chartView->chart()->axisX(series)->setRange(minX,maxX);

}

singlewidget::~singlewidget()
{
}

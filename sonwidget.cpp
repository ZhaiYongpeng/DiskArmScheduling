#include "sonwidget.h"

sonwidget::sonwidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("子窗口");

    FCFS = new singlewidget();//先到先服务算法
    SSTF = new singlewidget();//最短查找时间优先算法
    SCAN = new singlewidget();//扫描算法
    LOOK = new singlewidget();//电梯算法

    FCFS->setchartitle("先到先服务算法");
    SSTF->setchartitle("最短查找时间优先算法");
    SCAN->setchartitle("扫描算法");
    LOOK->setchartitle("电梯算法");

    // 创建网格布局
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(FCFS,0,0);
    gridLayout->addWidget(SSTF,0,1);
    gridLayout->addWidget(SCAN,1,0);
    gridLayout->addWidget(LOOK,1,1);
    setLayout(gridLayout);

}

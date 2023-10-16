#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->initWidge();

}
void Widget::initWidge(){
    setWindowTitle("原神,启动!");
    resize(400,400);

    submit = new QPushButton("提交",this);
    submit->move(150,300);

    //标签
    number_L = new QLabel("磁道序列数:",this);
    across_Time_L = new QLabel("跨越1个磁道所用时间(单位：毫秒):",this);
    start_Time_L = new QLabel("启动时间(单位：毫秒):",this);
    rotate_Speed_L = new QLabel("磁盘转速(单位:转/分钟):",this);
    tracksector_Number_L = new QLabel("每磁道扇区数:",this);
    sector_Bytes_Number_L = new QLabel("每扇区字节数:",this);
    direction_L = new QLabel("磁头移动法方向(0：向内，1：向外):",this);
    //文本框
    number_T = new QLineEdit("20",this);
    across_Time_T = new QLineEdit("1",this);
    start_Time_T = new QLineEdit("1",this);
    rotate_Speed_T = new QLineEdit("1000",this);
    tracksector_Number_T = new QLineEdit("2",this);
    sector_Bytes_Number_T = new QLineEdit("2",this);
    direction_T = new QLineEdit("1",this);

    //表单布局分布
    layout = new QFormLayout();
    layout->addRow(number_L,number_T);
    layout->addRow(across_Time_L,across_Time_T);
    layout->addRow(start_Time_L,start_Time_T);
    layout->addRow(rotate_Speed_L,rotate_Speed_T);
    layout->addRow(tracksector_Number_L,tracksector_Number_T);
    layout->addRow(sector_Bytes_Number_L,sector_Bytes_Number_T);
    layout->addRow(direction_L,direction_T);
    layout->setAlignment(Qt::AlignHCenter); // 设置水平居中对齐
    setLayout(layout);

    connect(submit,&QPushButton::clicked,this,&Widget::run);

}

void Widget::run(){
    number_input = new QString(number_T->text());
    across_Time_input = new QString(across_Time_T->text());
    start_Time_input = new QString(start_Time_T->text());
    rotate_Speed_input = new QString(rotate_Speed_T->text());
    tracksector_Number_input = new QString(tracksector_Number_T->text());
    sector_Bytes_Number_input = new QString(sector_Bytes_Number_T->text());
    direction_input = new QString(direction_T->text());

    sonwindow = new sonwidget();
    sonwindow->showMaximized();//子窗口最大化
    sonwindow->show();
    emit after_submit();


}


Widget::~Widget()
{
}


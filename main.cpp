#include "widget.h"
#include "DiskArmScheduling.h"

#include <QApplication>
#include <QDebug>

template <typename T>
QVector<T> toQVector(const std::vector<T>& stdVector){
    QVector<T> * qVector = new QVector<T>();

    for (const T& element : stdVector) {
        qVector->append(element);
    }

    return *qVector;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QWidget::connect(&w,&Widget::after_submit,[&](){
        std::vector<int> sequence;
        srand(time(0));
        for (int i = 0; i < w.get_number(); i++) {
            sequence.push_back(rand() % 200);
        }
        // 定义要生成的范围
        int lower_bound = 75;
        int upper_bound = 125;
        int random = rand() % (upper_bound - lower_bound + 1) + lower_bound;


        DiskArmScheduling* fcfs = new FCFS
            (random, sequence, w.get_across_Time(), w.get_start_Time(), w.get_rotate_Speed(), w.get_tracksector_Number(), w.get_sector_Bytes_Number_input(), w.get_direction());
        DiskArmScheduling* sstf = new SSTF
            (random, sequence, w.get_across_Time(), w.get_start_Time(), w.get_rotate_Speed(), w.get_tracksector_Number(), w.get_sector_Bytes_Number_input(), w.get_direction());
        DiskArmScheduling* scan = new SCAN
            (random, sequence, w.get_across_Time(), w.get_start_Time(), w.get_rotate_Speed(), w.get_tracksector_Number(), w.get_sector_Bytes_Number_input(), w.get_direction());
        DiskArmScheduling* look = new LOOK
            (random, sequence, w.get_across_Time(), w.get_start_Time(), w.get_rotate_Speed(), w.get_tracksector_Number(), w.get_sector_Bytes_Number_input(), w.get_direction());

        fcfs->Scheduling();
        sstf->Scheduling();
        scan->Scheduling();
        look->Scheduling();

        w.set_FCFS_data(fcfs->getCurrentTrack(),
                        toQVector(fcfs->getSequence()),
                        toQVector(fcfs->getOrderedSequence()),
                        fcfs->getSumOfArmMovement(),
                        fcfs->getSeekTime(),
                        double(fcfs->getSeekTime())/fcfs->getOrderedSequence().size(),
                        fcfs->getAverageRotationDelayTime(),
                        fcfs->getTransferTime(),
                        fcfs->getTotalAccessTime());
        w.set_SSTF_data(sstf->getCurrentTrack(),
                        toQVector(sstf->getSequence()),
                        toQVector(sstf->getOrderedSequence()),
                        sstf->getSumOfArmMovement(),
                        sstf->getSeekTime(),
                        double(sstf->getSeekTime())/sstf->getOrderedSequence().size(),
                        sstf->getAverageRotationDelayTime(),
                        sstf->getTransferTime(),
                        sstf->getTotalAccessTime());
        w.set_SCAN_data(scan->getCurrentTrack(),
                        toQVector(scan->getSequence()),
                        toQVector(scan->getOrderedSequence()),
                        scan->getSumOfArmMovement(),
                        scan->getSeekTime(),
                        double(scan->getSeekTime())/scan->getOrderedSequence().size(),
                        scan->getAverageRotationDelayTime(),
                        scan->getTransferTime(),
                        scan->getTotalAccessTime());
        w.set_LOOK_data(look->getCurrentTrack(),
                        toQVector(look->getSequence()),
                        toQVector(look->getOrderedSequence()),
                        look->getSumOfArmMovement(),
                        look->getSeekTime(),
                        double(look->getSeekTime())/look->getOrderedSequence().size(),
                        look->getAverageRotationDelayTime(),
                        look->getTransferTime(),
                        look->getTotalAccessTime());

        w.set_FCFS_point(toQVector(fcfs->getTime_sequence()),
                         toQVector(fcfs->getTrack_sequence()),
                         toQVector(fcfs->getPrint_sequence()));
        w.set_SSTF_point(toQVector(sstf->getTime_sequence()),
                         toQVector(sstf->getTrack_sequence()),
                         toQVector(sstf->getPrint_sequence()));
        w.set_SCAN_point(toQVector(scan->getTime_sequence()),
                         toQVector(scan->getTrack_sequence()),
                         toQVector(scan->getPrint_sequence()));
        w.set_LOOK_point(toQVector(look->getTime_sequence()),
                         toQVector(look->getTrack_sequence()),
                         toQVector(look->getPrint_sequence()));
    });

    w.show();

    return a.exec();
}

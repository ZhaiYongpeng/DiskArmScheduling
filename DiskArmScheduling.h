#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>

class DiskArmScheduling {
protected:
    int track[200] = { 0 };//磁道号数组
    int currentTrack;//当前磁道
    std::vector<int> sequence;//磁道访问序列
    double perTime;//跨越1个磁道所用时间
    double startTime;//启动时间
    double rotationalSpeed;//磁盘转速
    int sectorsPerTrack;//每磁道扇区数
    int bytesPerSector;//每扇区字节数
    int direction;//磁头移动方向（0：向内，1：向外）

    std::vector<double> time_sequence;//x坐标
    std::vector<int> track_sequence;//y坐标
    std::vector<int> print_sequence;//打印内容(0移动，1定位，2读写)

    int sumOfArmMovement;//引臂移动总量
    std::vector<int> orderedSequence;//引臂移动序列
    double seekTime;//寻道时间
    double averageRotationDelayTime;//平均旋转延迟时间
    double RotationDelayTime;//旋转延迟时间
    double transferTimePerByte;//每字节传输时间
    double transferTime;//传输时间
    double totalAccessTime;//所有访问处理时间

public:
    DiskArmScheduling(int ct, std::vector<int> sq, double pt, double st, double rs, int spt, int bps, int dr) {
        currentTrack = ct;
        sequence = sq;
        for (int temp : sq) {
            track[temp] += 1;
        }
        perTime = pt;
        startTime = st;
        rotationalSpeed = rs;
        sectorsPerTrack = spt;
        bytesPerSector = bps;
        direction = dr;
    }
    virtual ~DiskArmScheduling() {}
    virtual void Scheduling() = 0;//调度算法接口

    //getter
    inline int getCurrentTrack() {
        return currentTrack;
    }
    inline std::vector<int> getSequence(){
        return sequence;
    }

    inline std::vector<double> getTime_sequence() {
        return time_sequence;
    }
    inline std::vector<int> getTrack_sequence() {
        return track_sequence;
    }
    inline std::vector<int> getPrint_sequence() {
        return print_sequence;
    }

    inline int getSumOfArmMovement() {
        return sumOfArmMovement;
    }
    inline std::vector<int> getOrderedSequence() {
        return orderedSequence;
    }
    inline double getSeekTime() {
        return seekTime;
    }
    inline double getAverageRotationDelayTime() {
        return averageRotationDelayTime;
    }
    inline double getRotationDelayTime() {
        return RotationDelayTime;
    }
    inline double getTransferTimePerByte() {
        return transferTimePerByte;
    }
    inline double getTransferTime() {
        return transferTime;
    }
    inline double getTotalAccessTime() {
        return totalAccessTime;
    }
};

class FCFS :public DiskArmScheduling {
public:
    FCFS(int ct, std::vector<int> sq, double pt, double st, double rs, int spt, int bps, int dr) :
        DiskArmScheduling(ct, sq, pt, st, rs, spt, bps, dr) {}
    virtual ~FCFS() {}

    virtual void Scheduling();
};

class SSTF :public DiskArmScheduling {
public:
    SSTF(int ct, std::vector<int> sq, double pt, double st, double rs, int spt, int bps, int dr) :
        DiskArmScheduling(ct, sq, pt, st, rs, spt, bps, dr) {}
    virtual ~SSTF() {}

    virtual void Scheduling();
};

class SCAN :public DiskArmScheduling {
public:
    SCAN(int ct, std::vector<int> sq, double pt, double st, double rs, int spt, int bps, int dr) :
        DiskArmScheduling(ct, sq, pt, st, rs, spt, bps, dr) {}
    virtual ~SCAN() {}

    virtual void Scheduling();
};

class LOOK :public DiskArmScheduling {
public:
    LOOK(int ct, std::vector<int> sq, double pt, double st, double rs, int spt, int bps, int dr) :
        DiskArmScheduling(ct, sq, pt, st, rs, spt, bps, dr) {}
    virtual ~LOOK() {}

    virtual void Scheduling();
};

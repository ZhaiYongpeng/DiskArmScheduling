#include "DiskArmScheduling.h"

void FCFS::Scheduling() {
    //   std::cout << "FCFS" << std::endl;
    //   std::cout << "当前磁头位于磁道" << currentTrack << std::endl;
    //std::cout << "随机生成的磁道访问序列为:" << std::endl;
    //   for (int temp : sequence) {
    //	std::cout << temp << " ";
    //}
    //   std::cout << std::endl << std::endl;

    sumOfArmMovement = 0;//引臂移动总量
    seekTime = 0;//寻道时间
    averageRotationDelayTime = 1 / (2 * rotationalSpeed / 60000);//平均旋转延迟时间
    RotationDelayTime = 0;//旋转延迟时间
    transferTimePerByte = 1 / averageRotationDelayTime * double(sectorsPerTrack * bytesPerSector);//每字节传输时间
    transferTime = 0;//传输时间
    totalAccessTime = 0;//所有访问处理时间

    orderedSequence = sequence;
    int tempCurrentTrack = currentTrack;

    for (int temp : orderedSequence) {
        if (tempCurrentTrack != temp) {
            //std::cout << "正在移动磁头到磁道" << temp << "..." << std::endl;
            if (time_sequence.empty()) {
                time_sequence.push_back(startTime + perTime * abs(temp - tempCurrentTrack));
            }
            else {
                time_sequence.push_back(time_sequence.back() + startTime + perTime * abs(temp - tempCurrentTrack));
            }
            track_sequence.push_back(temp);
            print_sequence.push_back(0);
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds
        //((int)(startTime + perTime * abs(temp - tempCurrentTrack))));
        sumOfArmMovement += abs(temp - tempCurrentTrack);
        seekTime += startTime + perTime * abs(temp - tempCurrentTrack);
        tempCurrentTrack = temp;
        //std::cout << "正在定位到" << tempCurrentTrack << "磁道的扇区..." << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(int(averageRotationDelayTime)));
        if (time_sequence.empty()) {
            time_sequence.push_back(averageRotationDelayTime);
        }
        else {
            time_sequence.push_back(time_sequence.back() + averageRotationDelayTime);
        }
        track_sequence.push_back(tempCurrentTrack);
        print_sequence.push_back(1);
        RotationDelayTime += averageRotationDelayTime;
        //std::cout << "正在读取数据..." << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(int(transferTimePerByte)));
        if (time_sequence.empty()) {
            time_sequence.push_back(transferTimePerByte);
        }
        else {
            time_sequence.push_back(time_sequence.back() + transferTimePerByte);
        }
        track_sequence.push_back(tempCurrentTrack);
        print_sequence.push_back(2);
        transferTime += transferTimePerByte;
    }
    totalAccessTime = seekTime + RotationDelayTime + transferTime;
    //std::cout << std::endl;

    //std::cout << "用FCFS产生的引臂移动序列为:" << std::endl;
    //for (int temp : orderedSequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "引臂移动总量为:" << std::endl;
    //std::cout << sumOfArmMovement << std::endl;
    //std::cout << "寻道时间为:" <<  std::endl;
    //std::cout << seekTime << "ms" << std::endl;
    //std::cout << "平均寻道时间为:" << std::endl;
    //std::cout << double(seekTime) / orderedSequence.size() << "ms" << std::endl;
    //std::cout << "平均旋转延迟时间为:"  << std::endl;
    //std::cout << averageRotationDelayTime << "ms" << std::endl;
    //std::cout << "传输时间为:" << std::endl;
    //std::cout << transferTime << "ms" << std::endl;
    //std::cout << "所有访问处理时间为:" << std::endl;
    //std::cout << totalAccessTime << "ms" << std::endl;
    //std::cout << std::endl;
    return;
}

void SSTF::Scheduling(){
    //std::cout << "SSTF" << std::endl;
    //std::cout << "当前磁头位于磁道" << currentTrack << std::endl;
    //std::cout << "随机生成的磁道访问序列为:" << std::endl;
    //for (int temp : sequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl << std::endl;

    sumOfArmMovement = 0;//引臂移动总量
    seekTime = 0;//寻道时间
    averageRotationDelayTime = 1 / (2 * rotationalSpeed / 60000);//平均旋转延迟时间
    RotationDelayTime = 0;//旋转延迟时间
    transferTimePerByte = 1 / averageRotationDelayTime * double(sectorsPerTrack * bytesPerSector);//每字节传输时间
    transferTime = 0;//传输时间
    totalAccessTime = 0;//所有访问处理时间

    int temp = currentTrack;
    int tempCurrentTrack = currentTrack;
    std::vector<int> tempSequence = sequence;

    while (tempSequence.size() != 0) {
        int min = INT_MAX;
        int minIndex = 0;
        for (int i = 0; i < tempSequence.size(); i++) {
            if (abs(tempSequence[i] - temp) < min) {
                min = abs(tempSequence[i] - temp);
                minIndex = i;
            }
        }
        temp = tempSequence[minIndex];
        orderedSequence.push_back(temp);
        for (int t : tempSequence) {
            if (t == temp) {
                tempSequence.erase(std::find(tempSequence.begin(), tempSequence.end(), t));
            }
        }
    }

    std::unique(orderedSequence.begin(), orderedSequence.end());

    for (int temp : orderedSequence) {
        //if (tempCurrentTrack != temp)std::cout << "正在移动磁头到磁道" << temp << "..." << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds
        //((int)(startTime + perTime * abs(temp - tempCurrentTrack))));
        if (time_sequence.empty()) {
            time_sequence.push_back(startTime + perTime * abs(temp - tempCurrentTrack));
        }
        else {
            time_sequence.push_back(time_sequence.back() + startTime + perTime * abs(temp - tempCurrentTrack));
        }
        track_sequence.push_back(temp);
        print_sequence.push_back(0);
        sumOfArmMovement += abs(temp - tempCurrentTrack);
        seekTime += startTime + perTime * abs(temp - tempCurrentTrack);
        tempCurrentTrack = temp;
        for (int i = 0; i < track[temp]; i++) {
            //std::cout << "正在定位到" << tempCurrentTrack << "磁道的扇区..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(averageRotationDelayTime)));
            if (time_sequence.empty()) {
                time_sequence.push_back(averageRotationDelayTime);
            }
            else {
                time_sequence.push_back(time_sequence.back() + averageRotationDelayTime);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(1);
            RotationDelayTime += averageRotationDelayTime;
            //std::cout << "正在读取数据..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(transferTimePerByte)));
            if (time_sequence.empty()) {
                time_sequence.push_back(transferTimePerByte);
            }
            else {
                time_sequence.push_back(time_sequence.back() + transferTimePerByte);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(2);
            transferTime += transferTimePerByte;
        }
    }
    totalAccessTime = seekTime + RotationDelayTime + transferTime;
    //std::cout << std::endl;

    //std::cout << "用SSTF产生的引臂移动序列为:" << std::endl;
    //for (int temp : orderedSequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "引臂移动总量为:" << std::endl;
    //std::cout << sumOfArmMovement << std::endl;
    //std::cout << "寻道时间为:" << std::endl;
    //std::cout << seekTime << "ms" << std::endl;
    //std::cout << "平均寻道时间为:" << std::endl;
    //std::cout << double(seekTime) / orderedSequence.size() << "ms" << std::endl;
    //std::cout << "平均旋转延迟时间为:" << std::endl;
    //std::cout << averageRotationDelayTime << "ms" << std::endl;
    //std::cout << "传输时间为:" << std::endl;
    //std::cout << transferTime << "ms" << std::endl;
    //std::cout << "所有访问处理时间为:" << std::endl;
    //std::cout << totalAccessTime << "ms" << std::endl;
    //std::cout << std::endl;
    return;
}

void SCAN::Scheduling(){
    //std::cout << "SCAN" << std::endl;
    //std::cout << "当前磁头位于磁道" << currentTrack << std::endl;
    //std::cout << "当前磁头移动方向为" << (direction ? "向外" : "向内") << std::endl;
    //std::cout << "随机生成的磁道访问序列为:" << std::endl;
    //for (int temp : sequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl << std::endl;

    sumOfArmMovement = 0;//引臂移动总量
    seekTime = 0;//寻道时间
    averageRotationDelayTime = 1 / (2 * rotationalSpeed / 60000);//平均旋转延迟时间
    RotationDelayTime = 0;//旋转延迟时间
    transferTimePerByte = 1 / averageRotationDelayTime * double(sectorsPerTrack * bytesPerSector);//每字节传输时间
    transferTime = 0;//传输时间
    totalAccessTime = 0;//所有访问处理时间

    int temp = currentTrack;
    int tempCurrentTrack = currentTrack;

    if (direction) {//向外
        for (int i = currentTrack; i < 200; i++) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
        if (track[199] == 0) {
            orderedSequence.push_back(199);
        }
        for (int i = currentTrack - 1; i >= 0; i--) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
    }
    else {//向内
        for (int i = currentTrack; i >= 0; i--) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
        if (track[0] == 0) {
            orderedSequence.push_back(0);
        }
        for (int i = currentTrack + 1; i < 200; i++) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
    }

    std::unique(orderedSequence.begin(), orderedSequence.end());

    for (int temp : orderedSequence) {
        //if (tempCurrentTrack != temp)std::cout << "正在移动磁头到磁道" << temp << "..." << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds
        //((int)(startTime + perTime * abs(temp - tempCurrentTrack))));
        if (time_sequence.empty()) {
            time_sequence.push_back(startTime + perTime * abs(temp - tempCurrentTrack));
        }
        else {
            time_sequence.push_back(time_sequence.back() + startTime + perTime * abs(temp - tempCurrentTrack));
        }
        track_sequence.push_back(temp);
        print_sequence.push_back(0);
        sumOfArmMovement += abs(temp - tempCurrentTrack);
        seekTime += startTime + perTime * abs(temp - tempCurrentTrack);
        tempCurrentTrack = temp;
        for (int i = 0; i < track[temp]; i++) {
            //std::cout << "正在定位到" << tempCurrentTrack << "磁道的扇区..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(averageRotationDelayTime)));
            if (time_sequence.empty()) {
                time_sequence.push_back(averageRotationDelayTime);
            }
            else {
                time_sequence.push_back(time_sequence.back() + averageRotationDelayTime);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(1);
            RotationDelayTime += averageRotationDelayTime;
            //std::cout << "正在读取数据..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(transferTimePerByte)));
            if (time_sequence.empty()) {
                time_sequence.push_back(transferTimePerByte);
            }
            else {
                time_sequence.push_back(time_sequence.back() + transferTimePerByte);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(2);
            transferTime += transferTimePerByte;
        }
    }
    totalAccessTime = seekTime + RotationDelayTime + transferTime;
    //std::cout << std::endl;

    //std::cout << "用SCAN产生的引臂移动序列为:" << std::endl;
    //for (int temp : orderedSequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "引臂移动总量为:" << std::endl;
    //std::cout << sumOfArmMovement << std::endl;
    //std::cout << "寻道时间为:" << std::endl;
    //std::cout << seekTime << "ms" << std::endl;
    //std::cout << "平均寻道时间为:" << std::endl;
    //std::cout << double(seekTime) / orderedSequence.size() << "ms" << std::endl;
    //std::cout << "平均旋转延迟时间为:" << std::endl;
    //std::cout << averageRotationDelayTime << "ms" << std::endl;
    //std::cout << "传输时间为:" << std::endl;
    //std::cout << transferTime << "ms" << std::endl;
    //std::cout << "所有访问处理时间为:" << std::endl;
    //std::cout << totalAccessTime << "ms" << std::endl;
    //std::cout << std::endl;
    return;
}

void LOOK::Scheduling(){
    //std::cout << "LOOK" << std::endl;
    //std::cout << "当前磁头位于磁道" << currentTrack << std::endl;
    //std::cout << "当前磁头移动方向为" << (direction ? "向外" : "向内") << std::endl;
    //std::cout << "随机生成的磁道访问序列为:" << std::endl;
    //for (int temp : sequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl << std::endl;

    sumOfArmMovement = 0;//引臂移动总量
    seekTime = 0;//寻道时间
    averageRotationDelayTime = 1 / (2 * rotationalSpeed / 60000);//平均旋转延迟时间
    RotationDelayTime = 0;//旋转延迟时间
    transferTimePerByte = 1 / averageRotationDelayTime * double(sectorsPerTrack * bytesPerSector);//每字节传输时间
    transferTime = 0;//传输时间
    totalAccessTime = 0;//所有访问处理时间

    int temp = currentTrack;
    int tempCurrentTrack = currentTrack;

    if (direction) {//向外
        for (int i = currentTrack; i < 200; i++) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
        for (int i = currentTrack - 1; i >= 0; i--) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
    }
    else {//向内
        for (int i = currentTrack; i >= 0; i--) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
        for (int i = currentTrack + 1; i < 200; i++) {
            if (track[i] > 0) {
                orderedSequence.push_back(i);
            }
        }
    }

    std::unique(orderedSequence.begin(), orderedSequence.end());

    for (int temp : orderedSequence) {
        //if (tempCurrentTrack != temp)std::cout << "正在移动磁头到磁道" << temp << "..." << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds
        //((int)(startTime + perTime * abs(temp - tempCurrentTrack))));
        if (time_sequence.empty()) {
            time_sequence.push_back(startTime + perTime * abs(temp - tempCurrentTrack));
        }
        else {
            time_sequence.push_back(time_sequence.back() + startTime + perTime * abs(temp - tempCurrentTrack));
        }
        track_sequence.push_back(temp);
        print_sequence.push_back(0);
        sumOfArmMovement += abs(temp - tempCurrentTrack);
        seekTime += startTime + perTime * abs(temp - tempCurrentTrack);
        tempCurrentTrack = temp;
        for (int i = 0; i < track[temp]; i++) {
            //std::cout << "正在定位到" << tempCurrentTrack << "磁道的扇区..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(averageRotationDelayTime)));
            if (time_sequence.empty()) {
                time_sequence.push_back(averageRotationDelayTime);
            }
            else {
                time_sequence.push_back(time_sequence.back() + averageRotationDelayTime);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(1);
            RotationDelayTime += averageRotationDelayTime;
            //std::cout << "正在读取数据..." << std::endl;
            //std::this_thread::sleep_for(std::chrono::milliseconds(int(transferTimePerByte)));
            if (time_sequence.empty()) {
                time_sequence.push_back(transferTimePerByte);
            }
            else {
                time_sequence.push_back(time_sequence.back() + transferTimePerByte);
            }
            track_sequence.push_back(tempCurrentTrack);
            print_sequence.push_back(2);
            transferTime += transferTimePerByte;
        }
    }
    totalAccessTime = seekTime + RotationDelayTime + transferTime;
    //std::cout << std::endl;

    //std::cout << "用SCAN产生的引臂移动序列为:" << std::endl;
    //for (int temp : orderedSequence) {
    //    std::cout << temp << " ";
    //}
    //std::cout << std::endl;
    //std::cout << "引臂移动总量为:" << std::endl;
    //std::cout << sumOfArmMovement << std::endl;
    //std::cout << "寻道时间为:" << std::endl;
    //std::cout << seekTime << "ms" << std::endl;
    //std::cout << "平均寻道时间为:" << std::endl;
    //std::cout << double(seekTime) / orderedSequence.size() << "ms" << std::endl;
    //std::cout << "平均旋转延迟时间为:" << std::endl;
    //std::cout << averageRotationDelayTime << "ms" << std::endl;
    //std::cout << "传输时间为:" << std::endl;
    //std::cout << transferTime << "ms" << std::endl;
    //std::cout << "所有访问处理时间为:" << std::endl;
    //std::cout << totalAccessTime << "ms" << std::endl;
    //std::cout << std::endl;
    return;
}

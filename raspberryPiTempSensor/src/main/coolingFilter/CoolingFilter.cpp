//
// Created by David Halonen on 2/15/21.
//

#include <climits>
#include <iostream>
#include <vector>

#include "CoolingFilter.h"

bool CoolingFilter::accept(
    time_t const * const time,
    int const temp
) {
    double delta = difftime(*time, lastTime);
    if((int)(delta - 300) > 0)  //greater than 5 min
    {
       accept(temp);
       lastTime = *time;
    }
    if(tooEarlyInDay() && isCooling())
    {
        return false;
    }
    return true;
}

bool CoolingFilter::tooEarlyInDay(
){
    struct tm *timeInfo = localtime(&lastTime);
    int currentMinutes = timeInfo->tm_hour * 60 + timeInfo->tm_min;
    if(currentMinutes < earlyMinutesThreshold)
    {
        return true;
    }
    return false;
}

void CoolingFilter::accept(
        const int temp
) {
    lastTemps[currentHead] = temp;
    currentHead++;
    if(currentHead == lastTemps.size())
    {
        currentHead = 0;
    }
//    std::cout << "\n";
}

bool CoolingFilter::isCooling(
) {
//    std::cout << "Array dump";
//    for(int item : lastTemps)
//    {
//        std::cout << item << " ";
//    }
//    std::cout << "\n end of dump\n";
    cooling = true;
    if(currentHead == 0)
    {
        int lastValue = INT_MAX;
        for(int item : lastTemps)
        {
//            std::cout << item << "_";
            if(item <= lastValue)
            {
                lastValue = item;
            } else
            {
                cooling = false;
                break;
            }
        }
//        std::cout << "\n";
    } else {
        int lastValue = lastTemps[currentHead];
        for (std::vector<int>::size_type i = currentHead; i < lastTemps.size(); i++) {
//            std::cout << lastTemps[i] << " ";
            if(lastTemps[i] <= lastValue)
            {
                lastValue = lastTemps[i];
            } else
            {
                cooling = false;
                break;
            }
        }
        if(cooling)
        {
            for (std::vector<int>::size_type i = 0; i < currentHead; i++) {
//                std::cout << lastTemps[i] << " ";
                if(lastTemps[i] < lastValue)
                {
                    lastValue = lastTemps[i];
                } else
                {
                    cooling = false;
                    break;
                }
            }
        }
//        std::cout << "\n";
    }
    return cooling;
}

void CoolingFilter::enable(
) {
    enabled = true;
}

void CoolingFilter::disable(
){
    enabled = false;
}

bool CoolingFilter::isEnabled(
) const {
    return enabled;
}
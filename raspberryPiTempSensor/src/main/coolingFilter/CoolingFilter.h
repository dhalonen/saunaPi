//
// Created by David Halonen on 2/15/21.
//
//A circular ring of temperature values (int).
//Track last 1/2 hr of values, whereby each value is 5 minutes apart from the previous.

#ifndef RASPBERRYPITEMPSENSOR_COOLINGFILTER_H
#define RASPBERRYPITEMPSENSOR_COOLINGFILTER_H


class CoolingFilter {
public:
    explicit CoolingFilter(
            bool enabled = true,
            bool cooling = false
    ) :
    enabled(enabled),
    cooling(cooling)
    {}

    //accept temp, regardless of time interval. Used primarily for dev of circular ring.
    void accept(int temp);

    bool isCooling();

    void enable();
    void disable();
    bool isEnabled() const;

private:
    std::vector<int> lastTemps = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int>::size_type currentHead = 0;    //Next location to write temp
    bool cooling;         //We are in the "cooling" state
    bool enabled;
};


#endif //RASPBERRYPITEMPSENSOR_COOLINGFILTER_H

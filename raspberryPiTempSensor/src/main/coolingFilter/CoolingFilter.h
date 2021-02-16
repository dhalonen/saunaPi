//
// Created by David Halonen on 2/15/21.
//
//A circular ring of temperature values (int).
//Track last 1/2 hr of values, whereby each value is at least 5 minutes apart from the previous.

#ifndef RASPBERRYPITEMPSENSOR_COOLINGFILTER_H
#define RASPBERRYPITEMPSENSOR_COOLINGFILTER_H

class CoolingFilter {
public:
    explicit CoolingFilter(
        bool cooling = false,
        bool enabled = true,
        int earlyHour = 6,
        int earlyMinute = 0
    ) :
        cooling(cooling),
        enabled(enabled)
    {
        lastTime = time(&lastTime);
        //If early in day, use this to drop cooling data
        earlyMinutesThreshold = earlyHour * 60 + earlyMinute;
    }

    bool accept(
        time_t const *time,
        int temp);

    bool isCooling();

    void enable();
    void disable();
    bool isEnabled() const;

private:
    std::vector<int> lastTemps = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int>::size_type currentHead = 0;    //Next location to write temp
    bool cooling;         //We are in the "cooling" state
    bool enabled;
    time_t lastTime;        //The filter manages it's time.
    int earlyMinutesThreshold;
    bool tooEarlyInDay();
    //accept temp, regardless of time interval. Used primarily for dev of circular ring.
    void accept(
            int temp);

};
#endif //RASPBERRYPITEMPSENSOR_COOLINGFILTER_H

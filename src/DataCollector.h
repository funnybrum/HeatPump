#pragma once

#include "InfluxDBCollector.h"

class DataCollector: public InfluxDBCollector {
    public:
        DataCollector();
        bool shouldCollect();
        void collectData();
        void beforePush();
        void afterPush();
        bool shouldPush();
};

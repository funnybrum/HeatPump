#pragma once

#include "InfluxDBCollector.h"

class DataCollector: public InfluxDBCollector {
    public:
        DataCollector();
        bool shouldCollect();
        void collectData();
        void onPush();
        bool shouldPush();
};

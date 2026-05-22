#pragma once
#include "system_monitor/system_monitor.hpp"
#include "frontend_bridge/frontend_bridge.hpp"
#include "serializer/serializer.hpp"

class StatUpdater {
    SystemMonitor monitor_;  
    FrontendBridge& frontend_bridge_;
    bool running_ = true;

public:
    StatUpdater(FrontendBridge& bridge);

    void update();
};
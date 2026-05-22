#include "stat_updater.hpp"
#include "system_monitor/system_snapshot.hpp"
#include "defines.hpp"

#include <thread>

void StatUpdater::update() {
    while (running_) {
        auto snapshot = monitor_.collect();
        auto json = Serializer::serialize(snapshot);

        frontend_bridge_.send(json);
        std::this_thread::sleep_for(UPDATE_PERIOD);
    }
}
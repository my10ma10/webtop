#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

#include <webui.hpp>

#include "frontend_bridge/frontend_bridge.hpp"
#include "serializer/serializer.hpp"
#include "system_monitor/system_monitor.hpp"

std::atomic<bool> frontend_ready = false;

int main() {
    try {
        webui::set_default_root_folder("frontend");

        webui::window window;

        window.bind("frontend_ready", [&](webui_event_t*) {
            std::cout << "Frontend is ready\n";
            frontend_ready = true;
        });

        window.show_browser("index.html", Firefox);

        FrontendBridge bridge(window);

        std::thread sender([&]() {

            // ждём frontend один раз
            while (!frontend_ready) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            SystemMonitor monitor;

            while (true) {

                auto snapshot = monitor.collect();
                auto json = Serializer::serialize(snapshot);

                bridge.send(json);

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });

        webui::wait();

        sender.join();
        return 0;

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
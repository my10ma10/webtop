#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <webui.hpp>

#include "frontend_bridge/frontend_bridge.hpp"
#include "serializer/serializer.hpp"
#include "system_monitor/system_monitor.hpp"

int main() {
    try {

        webui::set_default_root_folder("frontend");
        webui::set_config(multi_client, true);

        webui::window main_window;

        main_window.show_browser(
            "index.html",
            Firefox
        );

        FrontendBridge bridge(main_window);

        std::mutex mutex;

        std::string latest_json;

        bool running = true;

        /*
         * Thread #1
         * Collect data
         */
        std::thread collector([&]() {

            SystemMonitor monitor;

            while (running) {

                auto snapshot = monitor.collect();

                auto json =
                    Serializer::serialize(snapshot);

                {
                    std::lock_guard lock(mutex);
                    latest_json = json;
                }

                std::this_thread::sleep_for(
                    std::chrono::seconds(1)
                );
            }
        });
        
        std::thread sender([&]() {

            std::this_thread::sleep_for(
                std::chrono::seconds(2)
            );

            while (running) {

                std::string json;

                {
                    std::lock_guard lock(mutex);
                    json = latest_json;
                }

                if (!json.empty()) {

                    bridge.send(json);

                    std::cout
                        << "JSON SENT\n";
                }

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(500)
                );
            }
        });

        
        webui::wait();

        running = false;

        collector.join();
        sender.join();

        return 0;
    }
    catch (const std::exception& ex) {

        std::cout
            << ex.what()
            << std::endl;
    }
}
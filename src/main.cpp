#include <webui.hpp>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

#include "system_monitor/system_monitor.hpp"
#include "serializer/serializer.hpp"

int main() {
    try {
        // webui::window my_window;

        // webui::set_config(multi_client, true);

        // my_window.show_browser(
        //     "html/index.html",
        //     Firefox
        // );
        SystemMonitor monitor;

        // std::thread([&](){
            while (true) {
                auto system_snapshot = monitor.collect();
                std::cout << Serializer::serialize(system_snapshot) << std::endl;

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        // }).detach();

        // webui::wait();
        return 0;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
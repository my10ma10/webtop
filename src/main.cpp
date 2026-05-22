#include <webui.hpp>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>

#include "system_monitor/system_monitor.hpp"

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
                monitor.collect();
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
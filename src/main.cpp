#include <thread>
#include <stdexcept>
#include <iostream>

#include "stat_updater/stat_updater.hpp"

int main() {
    try {
        // webui::window my_window;

        // webui::set_config(multi_client, true);

        // my_window.show_browser(
        //     "html/index.html",
        //     Firefox
        // );
        
        StatUpdater updater;
        std::thread([&]() {
            updater.update();
        }).detach();

        // webui::wait();
        return 0;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
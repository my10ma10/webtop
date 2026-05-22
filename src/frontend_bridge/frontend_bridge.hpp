#pragma once
#include <string>
#include <webui.hpp>

/**
 * @brief Мост между фронтендом и бэкендом, основанный на webui
 */
class FrontendBridge {
    webui::window window_;
public:
    void send(const std::string& json);
};
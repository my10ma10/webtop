#pragma once
#include <string>
#include <webui.hpp>

/**
 * @brief Мост между фронтендом и бэкендом, основанный на webui
 */
class FrontendBridge {
    webui::window& window_;
    
public:
    FrontendBridge(webui::window& window);

    /**
     * @brief Отправить JSON на frontend
     */
    void send(const std::string& json);
};
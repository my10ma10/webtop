#include "frontend_bridge.hpp"

FrontendBridge::FrontendBridge(webui::window& window)
    : window_(window)
{
}

void FrontendBridge::send(const std::string& json) {
    window_.run(
        "window.onBackendMessage(" + json + ");"
    );
}
// #define WSL_DEV
#ifdef WSL_DEV

#include <webui.h>
#include <cstdio>

void my_handler(webui_event_t *e) {

}

int main() {
    auto win = webui_new_window();
    
    // Запускаем только сервер, без авто-открытия браузера
    const char* url = webui_start_server(win, "html/index.html");

    webui_set_config(multi_client, true);
    webui_set_config(use_cookies, false);
    
    if (url) {
        printf("Откройте в браузере Windows: %s\n", url);
        webui_open_url(url);
    }
    
    webui_wait();
    return 0;
}

#else
#include <webui.hpp>

int main() {

    webui::window my_window;

    webui::set_config(multi_client, true);

    my_window.show_browser(
        "html/index.html",
        Firefox
    );

    webui::wait();

    return 0;
}

#endif // WSL_DEV
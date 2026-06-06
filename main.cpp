#include <filesystem>

#include "app/App.h"



int main() {
    // Инициализация терминала (автоматически восстановит настройки при выходе)
    App app = App();
    app.start();


    return 0;
}
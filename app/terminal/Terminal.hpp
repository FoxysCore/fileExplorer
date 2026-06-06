#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <utility>

class Terminal {
private:
    struct termios orig_termios;

public:
    Terminal() {
        // Сохраняем текущие настройки терминала
        tcgetattr(STDIN_FILENO, &orig_termios);
        struct termios raw = orig_termios;

        // Переводим терминал в сырой режим:
        // Отключаем эхо (ECHO), канонический режим ввода по строкам (ICANON),
        // обработку сигналов Ctrl+C/Ctrl+Z (ISIG) и расширенный ввод (IEXTEN)
        raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

        // Отключаем программное управление потоком Ctrl+S/Ctrl+Q (IXON)
        // и конвертацию возврата каретки (ICRNL)
        raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);

        // Отключаем постобработку вывода (OPOST)
        // Важно: при отключенном OPOST символ '\n' больше не делает возврат каретки,
        // поэтому для перехода на новую строку нужно будет выводить "\r\n"
        raw.c_oflag &= ~(OPOST);

        raw.c_cflag |= (CS8);

        // Настраиваем read() на ожидание ровно 1 символа
        raw.c_cc[VMIN] = 1;
        raw.c_cc[VTIME] = 0;

        // Применяем новые настройки
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    ~Terminal() {
        // Обязательно возвращаем терминал в нормальное состояние при уничтожении объекта
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    // Возвращает размер терминала в виде пары {ширина (columns), высота (rows)}
    std::pair<int, int> getSize() const {
        struct winsize ws;
        // Используем ioctl для запроса TIOCGWINSZ (Get WINdow SiZe)
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            return {0, 0}; // В случае ошибки возвращаем нули
        }
        return {ws.ws_col, ws.ws_row};
    }

    // Возвращает ASCII код нажатой кнопки
    int getButton() const {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1) {
            return -1; // Ошибка чтения
        }
        return static_cast<int>(c);
    }
};
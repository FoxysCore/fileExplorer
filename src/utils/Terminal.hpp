#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <utility>

class Terminal {
private:
    static termios orig_termios;
    static Terminal instance;

    Terminal() {}
    ~Terminal() {}

    public:

        static void setNormalMode() {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &Terminal::orig_termios);
        }

        static void setRawMode() {
            termios origin = {};

            tcgetattr(STDIN_FILENO, &origin);
            //orig_termios = origin;
            struct termios raw = origin;
            raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
            raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
            raw.c_oflag &= ~(OPOST);

            raw.c_cflag |= (CS8);
            raw.c_cc[VMIN] = 1;
            raw.c_cc[VTIME] = 0;

            tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        }

        static std::pair<int, int> getSize() {
            winsize ws{};
            if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
                return {0, 0};
            }
            return {ws.ws_col, ws.ws_row};
        }

        static int getButton() {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1) {
            return -1;
        }
        return static_cast<int>(c);
    }

        static void drawLine(int x, int y, int color, bool invert, int width, const std::string& content) {
            std::cout << "\033[" << y << ";" << x << "H";
            std::cout << "\033[" << color << "m";
            if (invert) {
                std::cout << "\033[7m";
            }
            std::cout << content.substr(0, width);
            std::cout << "\033[0m" << std::flush;
        }

        static void clearScreen() {
            std::cout << "\033[2J\033[H" << std::flush;
        }
};
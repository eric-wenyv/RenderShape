// Written by AI
#include "PlatformInput.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#endif

namespace PlatformInput
{

#ifdef _WIN32
    bool kbhit()
    {
        return _kbhit();
    }

    char getch()
    {
        return _getch();
    }

    void init()
    {
    }

    void cleanup()
    {
    }

#else
    // Linux 实现
    static struct termios old_termios;
    static bool initialized = false;

    void init()
    {
        if (initialized)
            return;

        // 获取当前终端设置
        tcgetattr(STDIN_FILENO, &old_termios);

        // 设置新的终端模式
        struct termios new_termios = old_termios;
        new_termios.c_lflag &= ~(ICANON | ECHO); // 禁用缓冲和回显
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

        // 设置非阻塞模式
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        initialized = true;
    }

    void cleanup()
    {
        if (!initialized)
            return;

        // 恢复原始终端设置
        tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

        // 恢复阻塞模式
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);

        initialized = false;
    }

    bool kbhit()
    {
        if (!initialized)
            init();

        fd_set readfds;
        struct timeval timeout;

        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout) > 0;
    }

    char getch()
    {
        if (!initialized)
            init();

        char ch;
        while (read(STDIN_FILENO, &ch, 1) != 1)
        {
            // 等待输入
        }
        return ch;
    }

#endif

}

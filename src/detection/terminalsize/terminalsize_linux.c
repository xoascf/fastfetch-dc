#include "terminalsize.h"
#include "common/io/io.h"

#include <sys/ioctl.h>
#include <unistd.h>

bool ffDetectTerminalSize(FFTerminalSizeResult* result)
{
    struct winsize winsize = {};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);

    if (winsize.ws_row == 0 || winsize.ws_col == 0)
        ffGetTerminalResponse("\033[18t", "\033[8;%hu;%hut", &winsize.ws_row, &winsize.ws_col);

    if (winsize.ws_ypixel == 0 || winsize.ws_xpixel == 0)
        ffGetTerminalResponse("\033[14t", "\033[4;%hu;%hut", &winsize.ws_ypixel, &winsize.ws_xpixel);

    if (winsize.ws_row == 0 && winsize.ws_col == 0)
        return false;

    result->rows = winsize.ws_row;
    result->columns = winsize.ws_col;
    result->width = winsize.ws_xpixel;
    result->height = winsize.ws_ypixel;
    return true;
}

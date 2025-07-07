#pragma once

namespace PlatformInput {
    // 检查是否有键盘输入（非阻塞）
    bool kbhit();
    
    // 获取按键字符（阻塞）
    char getch();
    
    // 初始化输入系统（Linux 需要）
    void init();
    
    // 清理输入系统（Linux 需要）
    void cleanup();
}

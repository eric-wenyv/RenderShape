# RenderShape

A console-based 3D ASCII renderer supporting real-time rotation and depth perception.
基于控制台的3D ASCII渲染器，支持实时旋转和深度感知。

## Features

- Load 3D models from CSV files
  从CSV文件加载3D模型
- Real-time rotation and rendering
  实时旋转和渲染
- Depth-based ASCII symbol rendering
  基于深度的ASCII字符渲染
- Double buffering for smooth display
  双缓冲技术保证流畅显示

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./RenderShape
```

- Press q to quit
  按`q`键退出程序

## Dependencies

- C++11 or higher
  C++11或更高版本
- Windows only (uses _kbhit() and _getch())
  仅支持Windows环境（使用`_kbhit()`和`_getch()`）
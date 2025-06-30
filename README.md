# RenderShape

A console-based 3D ASCII renderer supporting real-time rotation and depth perception.  
_基于控制台的3D ASCII渲染器，支持实时旋转和深度感知。_

## Features

- Load 3D models from CSV files  
  _从CSV文件加载3D模型_
- Real-time rotation and rendering  
  _实时旋转和渲染_
- Depth-based ASCII symbol rendering  
  _基于深度的ASCII字符渲染_
- Double buffering for smooth display  
  _双缓冲技术保证流畅显示_

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./RenderShape
```

- Press q to quit  
  _按`q`键退出程序_

## Dependencies

- C++11 or higher  
  _C++11或更高版本_
- Windows only (uses _kbhit() and _getch())  
  _仅支持Windows环境（使用`_kbhit()`和`_getch()`）_
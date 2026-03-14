# MC_CN-OS 操作系统

一个基于OSASK修改的32位微型操作系统，包含内核、API库、应用程序和文件管理器功能。

## 系统概述

MC_CN-OS是一个学习用操作系统，基于《30天自制操作系统》中的OSASK系统修改而来。本系统包含：

- **内核**：负责内存管理、任务调度、文件系统、图形界面等核心功能
- **API库**：提供应用程序开发接口
- **应用程序**：包括文件管理器、游戏、工具等多种应用
- **工具链**：编译和构建所需的工具集合

## 目录结构

```
MCOS/
├── haribote/           # 内核源代码
│   ├── bootpack.c      # 内核主程序
│   ├── bootpack.h      # 内核头文件
│   ├── graphic.c       # 图形处理
│   ├── dsctbl.c        # GDT/IDT设置
│   ├── int.c           # 中断处理
│   ├── fifo.c          # FIFO缓冲区
│   ├── memory.c        # 内存管理
│   ├── timer.c         # 定时器
│   ├── mtask.c         # 多任务
│   ├── file.c          # 文件系统
│   ├── console.c       # 控制台
│   ├── window.c        # 窗口管理
│   └── api*.c          # API函数实现
├── apilib/             # API库源代码
│   └── apilib.asm      # API汇编实现
├── stdlib/             # 标准库
│   └── stdlib.c        # 标准C库函数
├── filemgr/            # 文件管理器
│   └── filemgr.c       # 文件管理器主程序
├── hello*/             # Hello World示例程序
├── winhelo*/           # 窗口示例程序
├── stars*/             # 星空演示程序
├── lines/              # 线条绘制程序
├── walk/               # 动画演示程序
├── noodle/             # 计时器程序
├── beepdown/           # 蜂鸣器程序
├── color*/             # 色彩演示程序
├── sosu*/              # 素数计算程序
├── type/               # 文件查看程序
├── tview/              # 文本查看器
├── calc/               # 计算器
├── invader/            # 太空侵略者游戏
├── bball/              # 弹球游戏
├── notrec/             # 非矩形窗口演示
├── mmlplay/            # MML音乐播放器
├── gview/              # 图片查看器
├── mmldata/            # MML音乐文件
├── pictdata/           # 图片文件
├── nihongo/            # 日文字体
├── tolset/             # 工具链
│   └── z_tools/        # 编译工具
├── Makefile            # 主Makefile
├── make.bat            # Windows编译脚本
└── haribote.img        # 生成的系统镜像
```

## 文件说明

### 内核文件 (haribote/)

| 文件 | 说明 |
|------|------|
| bootpack.c | 内核入口，初始化所有组件 |
| bootpack.h | 内核头文件，定义结构体和常量 |
| graphic.c | 图形绘制函数（点、线、框、文字） |
| dsctbl.c | GDT（全局描述符表）和IDT（中断描述符表）设置 |
| int.c | 中断处理程序（键盘中断、定时器中断等） |
| fifo.c | FIFO缓冲区实现，用于任务间通信 |
| memory.c | 内存管理（分配、释放、4KB页管理） |
| timer.c | 定时器管理 |
| mtask.c | 多任务调度 |
| file.c | FAT12文件系统实现 |
| console.c | 控制台窗口实现 |
| window.c | 窗口管理系统 |
| api*.c | 系统API函数实现 |
| ipl10.nas | 启动引导程序（汇编） |
| asmhead.nas | 汇编头文件 |

### API库 (apilib/)

提供应用程序调用的系统API：

| API函数 | 功能 |
|---------|------|
| api_putchar | 输出字符到控制台 |
| api_putstr0 | 输出字符串到控制台 |
| api_openwin | 打开窗口 |
| api_putstrwin | 在窗口中显示字符串 |
| api_boxfilwin | 在窗口中绘制填充矩形 |
| api_point | 在窗口中绘制点 |
| api_linewin | 在窗口中绘制线 |
| api_refreshwin | 刷新窗口显示 |
| api_getkey | 获取键盘输入 |
| api_initmalloc | 初始化内存分配 |
| api_malloc | 分配内存 |
| api_free | 释放内存 |
| api_fopen | 打开文件 |
| api_fclose | 关闭文件 |
| api_fread | 读取文件 |
| api_fsize | 获取文件大小 |
| api_cmdline | 获取命令行参数 |

### 文件管理器 (filemgr/)

图形化文件管理器，功能包括：

- 显示文件列表（文件名、扩展名、大小）
- 支持键盘导航（↑↓选择，Enter运行）
- 支持多种文件类型（HRB、MML、JPG、BMP、TXT）
- 窗口大小：240x240像素

操作方式：
- ↑↓：选择文件
- Enter：运行选中的程序
- Q/ESC：退出

## 编译系统

### 环境要求

- Windows操作系统
- Git（用于版本控制）
- 工具链已包含在 `tolset/z_tools/` 目录中

### 编译步骤

1. **克隆仓库**
   ```bash
   git clone https://github.com/zskbtkf/MC_CN-OS.git
   cd MC_CN-OS
   ```

2. **编译整个系统**
   ```bash
   make.bat
   ```
   或
   ```bash
   ..\z_tools\make.exe
   ```

3. **编译单个应用程序**
   ```bash
   cd filemgr
   make.bat
   ```

4. **生成的文件**
   - `haribote.img` - 系统镜像文件（软盘镜像）
   - `haribote.sys` - 内核文件
   - `*.hrb` - 应用程序文件

## 运行系统

### 使用QEMU运行

```bash
cd tolset\z_tools\qemu
qemu-win.bat ..\..\..\haribote.img
```

### 使用VMware运行

1. 打开VMware Workstation
2. 创建新虚拟机
3. 选择"稍后安装操作系统"
4. 操作系统类型选择"其他"
5. 完成虚拟机创建
6. 编辑虚拟机设置
7. 删除硬盘，保留软盘驱动器
8. 软盘驱动器选择"使用软盘映像文件"
9. 选择 `haribote.img`
10. 启动虚拟机

## 制作应用程序

### 应用程序结构

```c
#include "apilib.h"

void HariMain(void)
{
    // 应用程序代码
    api_end();  // 结束应用程序
}
```

### 示例：Hello World

```c
#include "apilib.h"

void HariMain(void)
{
    api_putstr0("Hello, World!\n");
    api_end();
}
```

### 示例：窗口程序

```c
#include "apilib.h"

void HariMain(void)
{
    char *buf;
    int win;
    
    api_initmalloc();
    buf = api_malloc(150 * 50);  // 分配窗口缓冲区
    win = api_openwin(buf, 150, 50, -1, "hello");
    
    api_putstrwin(win, 28, 28, 0, 12, "hello, world");
    
    for (;;) {
        if (api_getkey(1) == 0x0a) {  // 回车键退出
            break;
        }
    }
    
    api_end();
}
```

### 编译应用程序

1. 创建应用程序目录
   ```bash
   mkdir myapp
   cd myapp
   ```

2. 创建源代码文件 `myapp.c`

3. 创建Makefile
   ```makefile
   APP = myapp
   
   include ../Makefile.app
   ```

4. 编译
   ```bash
   make.bat
   ```

5. 将生成的 `.hrb` 文件复制到系统镜像
   ```bash
   copy myapp.hrb ..\haribote.img
   ```

### Makefile模板

**应用程序Makefile (Makefile.app)**

```makefile
# 应用程序Makefile模板

CC = ../../z_tools/cc1.exe
GAS2NASK = ../../z_tools/gas2nask.exe
NASK = ../../z_tools/nask.exe
OBJ2BIM = ../../z_tools/obj2bim.exe
BIM2HRB = ../../z_tools/bim2hrb.exe
BIM2BIN = ../../z_tools/bim2bin.exe
MAKEFONT = ../../z_tools/makefont.exe
BIN2OBJ = ../../z_tools/bin2obj.exe

CFLAGS = -I../../z_tools/haribote/ -I../ -Os -Wall -quiet

$(APP).hrb : $(APP).bim
	$(BIM2HRB) $(APP).bim $(APP).org 0k
	$(BIM2BIN) -osacmp in:$(APP).org out:$(APP).hrb
	rm $(APP).org

$(APP).bim : $(APP).obj
	$(OBJ2BIM) @../haribote.rul out:$(APP).bim map:$(APP).map stack:4k \
		$(APP).obj ../apilib/apilib.lib ../stdlib/stdlib.lib

$(APP).obj : $(APP).nas
	$(NASK) $(APP).nas $(APP).obj $(APP).lst

$(APP).nas : $(APP).gas
	$(GAS2NASK) -a $(APP).gas $(APP).nas

$(APP).gas : $(APP).c
	$(CC) $(CFLAGS) -o $(APP).gas $(APP).c

clean :
	-rm $(APP).gas
	-rm $(APP).nas
	-rm $(APP).obj
	-rm $(APP).bim
	-rm $(APP).map
	-rm $(APP).hrb
```

## 系统架构

### 内存布局

```
0x00000000 - 0x000fffff : 启动时使用的临时区域（1MB）
0x00100000 - 0x001fffff : 软盘镜像缓存（1MB）
0x00200000 - 0x00267fff : 空（416KB）
0x00268000 - 0x0026f7ff : 空（30KB）
0x0026f800 - 0x0026ffff : IDT（2KB）
0x00270000 - 0x0027ffff : GDT（64KB）
0x00280000 - 0x002fffff : bootpack.hrb（512KB）
0x00300000 - 0x003fffff : 栈及其他（1MB）
0x00400000 - ...       : 应用程序可用内存
```

### 文件系统

- 使用FAT12文件系统
- 软盘镜像格式
- 根目录最多224个文件
- 文件信息存储在0x00102600处

### 任务管理

- 支持多任务
- 时间片轮转调度
- 每个任务有独立的栈和上下文

## 开发指南

### 添加新功能

1. **修改内核**：在 `haribote/` 目录下添加或修改代码
2. **添加API**：在 `haribote/api*.c` 中添加API实现，在 `apilib/apilib.asm` 中添加API接口
3. **创建应用**：参考现有应用程序创建新的 `.c` 文件
4. **更新Makefile**：将新应用程序添加到主Makefile

### 调试技巧

1. 使用 `api_putstr0()` 输出调试信息到控制台
2. 使用QEMU运行便于调试
3. 检查编译错误信息
4. 确保内存分配正确

## 许可证

本项目基于OSASK系统修改，遵循原项目的许可证。

## 参考资料

- 《30天自制操作系统》- 川合秀实
- OSASK官方网站

## 贡献者

- 原作者：川合秀实
- 修改者：zskbtkf

---

如有问题，请提交Issue或Pull Request。
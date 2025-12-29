# STM32F103-LAB 实践项目（CMake + GCC + OpenOCD）

面向 STM32F103（Cortex-M3）的入门学习项目，使用 GNU Arm Embedded Toolchain、CMake 构建，并通过 OpenOCD + ST-Link 进行烧录。

## 功能概览
- 基于标准外设库（StdPeriph）与 CMSIS。
- 生成 `elf`、`hex`、`bin` 三种产物。
- 提供 VS Code 任务，一键构建与烧录。

## 目录结构
- `src/`：核心与示例源代码（`core/`、`driver/`、`gpio_demo/`）。
- `include/`：对应头文件（含 `driver/`、`gpio_demo/`）。
- `lib/`：`CMSIS` 与 `STM32F10x_StdPeriph_Driver`。 
- `openocd/`：调试器与目标芯片配置（`interface/`、`target/`）。
- `svd/`：设备描述文件。
- `build/`：构建输出目录（由 CMake 生成）。
- `STM32F103C8Tx_FLASH.ld`：链接脚本。
- `CMakeLists.txt`：项目构建脚本。

## 环境要求
- GNU Arm Embedded Toolchain（`arm-none-eabi-gcc` 等）
- CMake ≥ 3.20
- OpenOCD
- ST-Link 驱动（如使用 ST-Link V2）

安装完成后，确保 `arm-none-eabi-*`、`cmake`、`openocd` 可在终端直接调用。

## 快速开始
### 方式一：VS Code 任务
已在工作区配置以下任务，可通过 “Terminal → Run Task” 或命令面板运行：
- `clean`：清理构建输出（删除 `./build`）。
- `cmake build`：生成构建目录与工程文件（`-S . -B ./build`）。
- `cmake生成bin`：编译工程并生成 `elf/hex/bin`。
- `openocd烧录`：将 `build/stm32f103c8t6.elf` 烧录到目标板并校验、复位、退出。

### 方式二：命令行
```powershell
# 1. 生成构建目录
cmake -S . -B ./build

# 2. 编译生成 elf/hex/bin
cmake --build ./build

# 3. 烧录（ST-Link + STM32F1）
openocd -f openocd/interface/stlink.cfg -f openocd/target/stm32f1x.cfg -c "program build/stm32f103c8t6.elf verify reset exit"
```

### 构建类型（可选）
支持指定构建类型以控制优化与调试信息：
```powershell
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug  # 或 Release / RelWithDebInfo / MinSizeRel
cmake --build ./build
```

## 产物说明
CMake 默认在 `build/` 下生成：
- `stm32f103c8t6.elf`：可执行镜像（用于调试与烧录）。
- `stm32f103c8t6.bin`：二进制镜像。
- `stm32f103c8t6.hex`：Intel HEX 格式镜像。
- `stm32f103c8t6.map`：链接映射（内存占用等信息）。

## 常见问题
- 找不到 `arm-none-eabi-gcc`：请将 GNU Arm 工具链的 `bin` 目录加入环境变量 `PATH`。
- OpenOCD 无法连接：检查 ST-Link 驱动是否安装、连线是否正确、目标板是否供电。
- 构建失败：确认 CMake 版本、工具链安装完整；可尝试先运行 `clean` 任务后重新生成。

## 参考
- CMSIS 与 STM32 标准外设库文档。
- OpenOCD 官方文档。

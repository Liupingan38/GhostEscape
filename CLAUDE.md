# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在此仓库中工作时提供指引。

## 构建命令

```powershell
# 配置（首次或修改 CMakeLists.txt 后执行）
cmake -B build

# Debug 构建
cmake --build build --config Debug

# Release 构建
cmake --build build --config Release
```

可执行文件输出到项目根目录：`GhostEscape-Windows.exe`。  
也可直接用 Visual Studio 打开 `build/GhostEscape.sln`。

本项目无测试套件。

## 依赖库

所有依赖通过 CMake 的 `find_package()` 引入：

- **SDL3** — 窗口、渲染器、输入、主循环
- **SDL3_image** — 纹理加载
- **SDL3_mixer** — 音频（BGM + 音效）
- **SDL3_ttf** — 字体渲染
- **glm** — 数学库（vec2、clamp 等）

## 架构

引擎以 **Scene → Object 层级结构**为核心，由 Game 单例驱动。

```
Game（单例）
├── AssetStore          — 按路径懒加载并缓存纹理/音频/字体
├── Scene（当前场景）   — 相机、世界尺寸、更新/渲染循环
│   ├── screenChildren_ — ObjectScreen 列表（UI/HUD，屏幕坐标）
│   └── worldChildren_  — ObjectWorld 列表（游戏对象，世界坐标）
```

**对象继承链：**
```
Object → ObjectScreen → ObjectWorld → Actor → Player
```

各层新增能力：
- `ObjectScreen` — 屏幕空间 2D 位置
- `ObjectWorld` — 世界空间位置，渲染时相对相机偏移
- `Actor` — 速度、`maxSpeed`（500 px/s）、阻尼衰减
- `Player` — WASD 输入，边界限制到世界尺寸

**生命周期方法**（虚函数，每帧由场景调用）：
`init()` → `handleEvents()` → `update(dt)` → `render()` → `clean()`

**游戏循环：** 目标 120 FPS；`dt` 以纳秒计算后转为 `float` 秒传入 `update()`。

**相机：** 存在于 `Scene` 中，跟随玩家；所有 `ObjectWorld` 的渲染坐标均偏移相机位置。

**资源加载：** 始终通过 `AssetStore`（`game_.getAssetStore()`）访问，以文件路径为键，返回原始 SDL 指针（SDL_Texture*、Mix_Music* 等）。

## 关键文件

| 文件 | 职责 |
|------|------|
| `src/main.cpp` | 入口点 — 创建 Game，设置 1920×1280 窗口 |
| `src/core/game.h/cpp` | SDL 初始化、主循环、事件泵、渲染器 |
| `src/core/scene.h/cpp` | 场景基类：相机、子对象列表、坐标系 |
| `src/core/object.h/cpp` | 所有实体的生命周期接口基类 |
| `src/core/assetStore.h/cpp` | 资源缓存 |
| `src/sceneMain.h/cpp` | 主游戏场景，含网格背景 |
| `src/player.h/cpp` | 玩家移动与输入处理 |

`src/main1.cpp` 是旧的 SDL3 API 测试文件，不参与最终构建。

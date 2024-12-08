#pragma once
//===============================================
//
// プリコンパイル済みヘッダー
//  ここに書いたものは初回のみ解析されるため、コンパイル時間が高速になる。
//  全てのcppからインクルードされる必要がある。
//
//===============================================


//===============================================
//
// 基本
//
//===============================================
#pragma comment(lib,"winmm.lib")

#define NOMINMAX
#include <windows.h>
#include <stdio.h>

#include <wrl/client.h>

//===============================================
//
// STL
//
//===============================================
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>
#include <direct.h>
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <sstream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <optional>
#include <random>

//===============================================
//
// Direct3D11
//
//===============================================
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <d3dcommon.h>
#include <dxgi.h>
#include <d3d11_1.h>

#include <DirectXMath.h>
#include <DirectXCollision.h>

// DirectX Tool Kit
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DirectXTKAudioWin8.lib")
#include <SimpleMath.h>
#include <Audio.h>

// DirectX Tex
#pragma comment(lib, "DirectXTex.lib")
#include <DirectXTex.h>

//===============================================
//
// imgui
//
//===============================================
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

//===============================================
// 文字コード変換
//===============================================
#include "strconv.h"

//===============================================
//
// 自作System
//
//===============================================
#include "System/KdSystem.h"
//CustomLib
#include "Data/Classes/Header/Button.h"
#include "Data/Classes/Header/Menu.h"
#include "Data/Classes/Header/Item.h"
#include "Data/Classes/Header/KeyEvent.h"
#include "Data/Classes/Header/WindowsControlData.h"
#include "Data/Classes/Header/DrawTextureData.h"
#include "Data/Classes/Header/SceneControlData.h"
#include "Data/Classes/Header/Block.h"
#include "Data/Classes/Header/Player.h"
#include "Data/Classes/Header/TerrainObject.h"
#include "Data/Classes/Header/PC.h"
#include "Data/Classes/Header/Stage.h"
#include "Data/Classes/Header/Enemy.h"
#include "Data/Classes/Header/Spawner.h"



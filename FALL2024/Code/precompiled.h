#pragma once

// windows headers
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <shellapi.h> 

// cleanup Window's preprocessor footprint
#undef near
#undef far
#undef GetObject

// c++ std library headers
#include <algorithm>
#include <atomic>
#include <any>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <thread>
#include <typeindex>
#include <unordered_map>
#include <variant>
#include <vector>

#include "fmod.hpp"
#include <fmod_errors.h>
#include "document.h"
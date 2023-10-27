include(FetchContent)

FetchContent_Declare(
  nanogui
  GIT_REPOSITORY https://github.com/wjakob/nanogui.git
  GIT_TAG        e9ec8a1a9861cf578d9c6e85a6420080aa715c03
  GIT_PROGRESS TRUE
)

set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(NANOGUI_BUILD_PYTHON OFF CACHE BOOL "" FORCE)
set(NANOGUI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(NANOGUI_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(nanogui)
FetchContent_GetProperties(nanogui SOURCE_DIR nanogui_SRC_DIR BINARY_DIR nanogui_BIN_DIR)

add_definitions(${NANOGUI_EXTRA_DEFS})
include_directories(${nanogui_SRC_DIR}/include)
include_directories(${NANOGUI_EXTRA_INCS})
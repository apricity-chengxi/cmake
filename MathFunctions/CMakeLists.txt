# 创建链接库
add_library(MathFunctions mysqrt.cxx MathFunctions.cxx)

# target_include_directories 的三个参数含义
# PUBLIC 本目标需要用,依赖这个目标的其他目标也需要用
# INTERFACE 本目标不需要,依赖本目标的其他目标需要
# PRIVATE 本目标需要,依赖这个目标的其他目标不需要
target_include_directories(
    MathFunctions
    INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

message(STATUS
    "MathFunctions --- "
    "CMAKE_CURRENT_SOURCE_DIR = "
        "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(
    MathFunctions
    PUBLIC
    tutorial_compiler_flags
)
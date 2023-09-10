# 定义最低 cmake版本
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(Tutorial VERSION 1.0)

# 设定cpp标准
# set(CMAKE_CXX_STANDARD 11)
# 是否允许使用之前的cpp标准
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# 利用接口库设置cpp标准
add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(
    tutorial_compiler_flags
    INTERFACE
    cxx_std_17
)

# 生成器表达式 $<condition:true_string>
# 当condition非0时,该表达式为后面的字符串
# 当condition为0时,该表达式为空
# 生成器表达式因为是在生成阶段可用,所以不能在配置阶段进行输出,可用下面方式调试
add_custom_target(ged COMMAND ${CMAKE_COMMAND} -E echo "$<1:test>")
# 观察命令
#   make ged
#   cmake --build . --target ged

# 输出 compile_commands.json 文件(用于clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(test_string "hello world")
set(test_cmakedefine_0 0)
set(test_cmakedefine_1 1)

# 用 option 创建一个变量 USE_MYMATH 默认值设为 ON/OFF TRUE/FALSE
# option 会存储在CMakeCache.txt中. 等价于缓存变量(=set)作用
#   定义: option(<variable> "<help_text>" [value])
#       variable    选项名
#       help_text   描述、解释、备注
#       value       选项初始化值(除ON而外全为OFF)
#   1.不初始化或赋为非ON的值,全部视为OFF
#   2.在定义语句执行后才有效:在定义之前均视为未定义(除过在CMake命令中通过-D预定义)
#   3.如果出现同名的变量(普通或缓存变量或-D预设变量),则option会被忽略
option(USE_MYMATH "use my math?" ON)
message(STATUS USE_MYMATH = ${USE_MYMATH})

# 用 configure_file 复制 TutorialConfig.h.in
#   生成TutorialConfig.h
configure_file(
    TutorialConfig.h.in
    TutorialConfig.h
)

if(USE_MYMATH)
    # 用 add_subdirectory() 把 (目录名)MathFunctions 添加到项目中
    add_subdirectory(MathFunctions)
    # 用 list 添加(APPEND) MathFunctions 到 EXTRA_LIBS 中
    list(APPEND EXTRA_LIBS MathFunctions)
endif()


# 生成 Tutorial 可执行文件
add_executable(Tutorial Tutorial.cxx)

# 用 target_link_libraries 向可执行文件中添加链接库
# 等价与 -lMathFunctions
target_link_libraries(
    Tutorial
    PUBLIC
    ${EXTRA_LIBS}
    tutorial_compiler_flags
)

# 用 target_include_directories
#   添加头文件搜索目录 ${PROJECT_BINARY_DIR}
# PUBLIC PRIVATE INTERFACE
# 添加双引号来防止目录中有空格
target_include_directories(
    Tutorial
    PUBLIC
    "${PROJECT_BINARY_DIR}"
) 

# 输出信息
message(STATUS "${Tutorial_VERSION_MAJOR}")
message(STATUS "${Tutorial_VERSION_MINOR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")


# 学习的视频链接 
#【【文档向】CMake基础知识】 
# https://www.bilibili.com/video/BV1hz4y1H7YA/?share_source=copy_web&vd_source=046aacfd7f86f3fae1039836c3ba3196
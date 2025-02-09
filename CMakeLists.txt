# 标题
cmake_minimum_required(VERSION 3.5.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)

# 查找并载入Cmake预设
find_package(SDL2 REQUIRED)

# 添加可执行文件
add_executable(SDLShooter main.cpp)

# 链接库
target_link_libraries(SDLShooter 
                        SDL2::SDL2 
                        SDL2::SDL2main)
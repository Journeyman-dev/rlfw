# SPDX-FileCopyrightText: 2023 Daniel Aimé Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

# Copyright (c) 2023 Daniel Aimé Valcour
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.25)

project(rlfw
        VERSION 0.0.0.0
        DESCRIPTION "The roguelike framework."
)
Include(FetchContent)
FetchContent_Declare(
    rlm
    GIT_REPOSITORY https://github.com/Journeyman-dev/rlm
    GIT_TAG        v0.3.0
)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(rlm glfw)
add_library(rlfw STATIC "")
add_library(rlfw::rlfw ALIAS rlfw)
add_subdirectory(src)
target_link_libraries(rlfw
	PUBLIC
		rlm::rlm
		glfw
)
target_include_directories(rlfw
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set_target_properties(rlfw
    PROPERTIES
    OUTPUT_NAME "rlfw"
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
add_subdirectory(sandbox)

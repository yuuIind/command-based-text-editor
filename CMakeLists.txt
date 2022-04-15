cmake_minimum_required(VERSION 3.21)
project(TermProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(TermProject
        .idea/.gitignore
        .idea/modules.xml
        .idea/TermProject.iml
        .idea/workspace.xml
        main.cpp txtEditor.cpp txtEditor.h stringSLList.cpp stringSLList.h textStack.cpp textStack.h)

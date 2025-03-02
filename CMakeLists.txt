cmake_minimum_required(VERSION 3.10)
project(DynamicProject)
#find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB CPP_FILES "*.cpp")


set(SQLITE3_PATH "./sqlite3")  
add_library(SQLite3 STATIC ${SQLITE3_PATH}/sqlite3.c)

foreach(SOURCE ${CPP_FILES})
    file(READ ${SOURCE} CONTENTS)
    if (CONTENTS MATCHES "int main[ \t\n\r]*\\(")
        get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)

        
        add_executable(${EXECUTABLE_NAME} ${SOURCE} Database.cpp)

        
        target_link_libraries(${EXECUTABLE_NAME} SQLite3)
        target_include_directories(${EXECUTABLE_NAME} PRIVATE ${SQLITE3_PATH})

        # Σύνδεση του Qt5 Widgets
        #target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets)

        # Αν το project περιέχει το Qt Designer, μπορείς να προσθέσεις και άλλες εξαρτήσεις Qt αν χρειάζεται
        #target_include_directories(${EXECUTABLE_NAME} PRIVATE ${Qt5Widgets_INCLUDE_DIRS})

        message(STATUS "Created target: ${EXECUTABLE_NAME} from ${SOURCE}")
    endif()
endforeach()

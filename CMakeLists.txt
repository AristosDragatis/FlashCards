cmake_minimum_required(VERSION 3.10)
project(DynamicProject)

# Αναζήτηση όλων των .cpp αρχείων στον φάκελο
file(GLOB CPP_FILES "*.cpp")


set(SQLITE3_PATH "./sqlite3")  
add_library(SQLite3 STATIC ${SQLITE3_PATH}/sqlite3.c)

foreach(SOURCE ${CPP_FILES})
    # Διαβάζουμε το αρχείο και ελέγχουμε αν περιέχει τη συνάρτηση main()
    file(READ ${SOURCE} CONTENTS)
    if (CONTENTS MATCHES "int main[ \t\n\r]*\\(")
        get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
        add_executable(${EXECUTABLE_NAME} ${SOURCE})
	target_link_libraries(${EXECUTABLE_NAME} SQLite3)
	target_include_directories(${EXECUTABLE_NAME} PRIVATE ${SQLITE3_PATH})
        message(STATUS "Created target: ${EXECUTABLE_NAME} from ${SOURCE}")
    endif()
endforeach()

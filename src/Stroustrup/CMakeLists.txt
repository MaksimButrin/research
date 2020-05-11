project (Stroustrup) # Project name

# Here the project files
file(GLOB HDR *.h)
file(GLOB SRC *.cpp)
file(GLOB UI *.ui)
file(GLOB RC *.rc)
file(GLOB QRC *.qrc)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX ${SRC_GROUP_PREFIX} FILES ${SRC})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX ${HDR_GROUP_PREFIX} FILES ${HDR})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX ${UI_GROUP_PREFIX} FILES ${UI})

add_executable(${PROJECT_NAME} WIN32 ${SRC} ${HDR} ${UI} ${RC} ${QRC}) #THE MAIN
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Applications)

# Here connected dynamic library
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Charts)

message("Create project '" ${PROJECT_NAME} "' is done")

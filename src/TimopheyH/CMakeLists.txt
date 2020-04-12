project (TimopheyH) # Project name

# Here the project files
file(GLOB HDR *.h)
file(GLOB SRC *.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX ${SRC_GROUP_PREFIX} FILES ${SRC})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX ${HDR_GROUP_PREFIX} FILES ${HDR})

add_executable(${PROJECT_NAME} ${SRC} ${HDR} ) #THE MAIN
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Applications)

# Here connected dynamic library
target_link_libraries(${PROJECT_NAME} Qt5::Core)

message("Create project '" ${PROJECT_NAME} "' is done")

cmake_minimum_required(VERSION 3.20)
project(dinosaur_clone)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(LIBRARIES_SOURCE
	libraries/src/glad/glad.c
	libraries/src/stb/stb_image.cpp
	libraries/src/imgui/imgui.cpp
	libraries/src/imgui/imgui_draw.cpp
	libraries/src/imgui/imgui_widgets.cpp
	libraries/src/imgui/imgui_tables.cpp
	libraries/src/imgui/imgui_impl_glfw.cpp
	libraries/src/imgui/imgui_impl_opengl3.cpp
)
set(ENGINE_SOURCE
	engine/renderer/window.hpp
	engine/renderer/window.cpp
	engine/renderer/mesh.hpp
	engine/renderer/mesh.cpp
	engine/renderer/shader.hpp
	engine/renderer/shader.cpp
	engine/renderer/texture.hpp
	engine/renderer/texture.cpp
	engine/math/transform.hpp
	engine/math/transform.cpp
	engine/tool/resource_manager.hpp
	engine/tool/resource_manager.cpp
	engine/gui/gui_manager.hpp
	engine/gui/gui_manager.cpp
	engine/collision/collision_data.hpp
	engine/collision/collision_manager.hpp
	engine/collision/collision_manager.cpp
)
set(MODULE_SOURCE
	source/module/scene/camera.hpp
	source/module/scene/camera.cpp
	source/module/gui/menu.hpp
	source/module/gui/menu.cpp
	source/module/gui/debug_console.hpp
	source/module/gui/debug_console.cpp
	source/module/entity/dinosaur.hpp
	source/module/entity/dinosaur.cpp
	source/module/input/input_dinosaur.hpp
	source/module/input/input_handler.hpp
	source/module/input/input_handler.cpp
	source/module/scene/ground.hpp
	source/module/scene/ground.cpp
	source/module/entity/obstacle.hpp
	source/module/entity/obstacle.cpp
)
set(CORE_SOURCE
	source/core/game.hpp
	source/core/game.cpp
	source/core/main.cpp
)
add_executable(${PROJECT_NAME}
	${LIBRARIES_SOURCE}
	${ENGINE_SOURCE}
	${MODULE_SOURCE}
	${CORE_SOURCE}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	libraries/include
	libraries/include/stb
	libraries/include/imgui
)

if(WIN32)
	target_link_libraries(${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/libraries/lib/windows/glfw3.lib
	opengl32.lib
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
	target_link_libraries(${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/libraries/lib/linux/libglfw3.a
	GL
	X11
	pthread
	dl
	)
elseif(APPLE)
	target_link_libraries(${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/libraries/lib/macos/libglfw3.a
	-framework OpenGL
	-framework Cocoa
	-framework IOKit
	)
endif()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/resources
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
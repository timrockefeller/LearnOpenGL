GET_DIR_NAME(DIRNAME)
set(FOLDER_NAME ${DIRNAME})

set(TARGET_NAME "${TARGET_PREFIX}${DIRNAME}")
#多个源文件用 [空格] 分隔
#如：set(STR_TARGET_SOURCES "main.cpp src_2.cpp")
file(GLOB ALL_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.vs"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.gs"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.fs"
)
set(STR_TARGET_SOURCES "")
foreach(SOURCE ${ALL_SOURCES})
	set(STR_TARGET_SOURCES "${STR_TARGET_SOURCES} ${SOURCE}")
endforeach(SOURCE ${ALL_SOURCES})

# set(STR_TARGET_LIBS "glfw3.lib glad Glfw Operation Config EventManager opengl32.lib")

set(STR_TARGET_LIBS "glfw3.lib glad Operation Glfw File Shader Image Texture Camera EventListener VAO opengl32.lib")
SETUP_PROJECT(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})

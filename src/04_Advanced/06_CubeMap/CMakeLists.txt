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
set(STR_TARGET_LIBS "glfw3.lib glad Operation EventListener Glfw File VAO Shader Image Texture Camera FBO opengl32.lib assimp.lib Model")

SETUP_PROJECT(${MODE} ${TARGET_NAME} ${STR_TARGET_SOURCES} ${STR_TARGET_LIBS})

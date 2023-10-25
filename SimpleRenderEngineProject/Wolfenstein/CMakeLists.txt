# Game Only

file(GLOB_RECURSE Wolfenstein-src "*.h" "*.cpp")


add_executable(Wolfenstein ${Wolfenstein-src})

target_include_directories(Wolfenstein PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(Wolfenstein MyEngine ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)
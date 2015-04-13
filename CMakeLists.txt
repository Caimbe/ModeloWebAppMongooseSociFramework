project(ModeloAPP)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem system thread program_options )

include_directories(src)
aux_source_directory(src SRC)
aux_source_directory(src/model MODEL)
aux_source_directory(src/view VIEW)
aux_source_directory(src/control CONTROL)
aux_source_directory(src/entity ENTITY)
aux_source_directory(src/repository REPOSITORY)
list(APPEND FULL_SRC
    ${SRC}
    ${ENTITY}
    ${MODEL}
    ${VIEW}
    ${CONTROL}
    ${REPOSITORY} )
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif()

include_directories(${Boost_INCLUDE_DIRS}) 

add_executable(${PROJECT_NAME} ${FULL_SRC})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} _mongoose jsoncpp htmlcxx soci_mysql soci_core mysql psapi)
if(UNIX)
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)
else()
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ws2_32)
endif()


# install
install (DIRECTORY WebContent/ DESTINATION WebContent)
install (TARGETS ${PROJECT_NAME} DESTINATION bin)

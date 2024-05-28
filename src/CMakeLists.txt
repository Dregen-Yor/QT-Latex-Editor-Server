file(GLOB_RECURSE DIR_LIB_SRCS "*.cpp" "*.h" "*.hpp")
add_executable(${PROJECT_NAME} ${DIR_LIB_SRCS})
target_link_libraries(${PROJECT_NAME} PUBLIC proxygen::proxygen proxygen::proxygenhttpserver
mvfst::mvfst_transport
mvfst::mvfst_client
mvfst::mvfst_server
nlohmann_json::nlohmann_json /usr/local/lib/mariadb/libmariadbcpp.so)

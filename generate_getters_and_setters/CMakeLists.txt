set(ARTICLE_NAME generate_getters_and_setters)
add_executable(${ARTICLE_NAME} field.h main.cpp)
set_target_properties(${ARTICLE_NAME} PROPERTIES CXX_STANDARD 11)
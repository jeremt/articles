set(ARTICLE_NAME some_cpp11_function_tricks)
add_executable(${ARTICLE_NAME} Callable.h Function.h main.cpp)
set_target_properties(${ARTICLE_NAME} PROPERTIES CXX_STANDARD 11)
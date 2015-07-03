set(ARTICLE_NAME the_property_class)
add_executable(${ARTICLE_NAME} PropertyBase.h PropertyPointer.h CounterProperty.h main.cpp)
set_target_properties(${ARTICLE_NAME} PROPERTIES CXX_STANDARD 11)
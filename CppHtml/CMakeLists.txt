add_executable (CppHtml "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppHtml PROPERTY CXX_STANDARD 20)
endif()
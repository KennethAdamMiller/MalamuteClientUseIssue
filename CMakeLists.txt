cmake_minimum_required (VERSION 2.8.11)
project (Broker)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++" )

INCLUDE_DIRECTORIES(
  "include"
)


set(BROKER_TEST_SRC
  "main.cpp"
)


add_executable(RunTests ${BROKER_TEST_SRC})
target_link_libraries(RunTests zmq czmq mlm)
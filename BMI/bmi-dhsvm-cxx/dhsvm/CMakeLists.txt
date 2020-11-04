cmake_minimum_required(VERSION 3.0)

set (DHSVM_VERSION 0.2)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/dhsvmcxx.pc.cmake
                ${CMAKE_BINARY_DIR}/dhsvmcxx.pc)

set(bmi_dhsvm_lib_SRCS bmi_dhsvm.cxx dhsvm.cxx)
if(WIN32)
  add_library(bmidhsvmcxx ${bmi_dhsvm_lib_SRCS})
else()
  add_library(bmidhsvmcxx SHARED ${bmi_dhsvm_lib_SRCS})
endif()

add_executable(run_bmidhsvmcxx bmi_main.cxx bmi_dhsvm.cxx dhsvm.cxx)

install(
  TARGETS run_bmidhsvmcxx
  RUNTIME DESTINATION bin
)
install(
  TARGETS bmidhsvmcxx
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)
install(
  FILES bmi_dhsvm.hxx dhsvm.hxx
  DESTINATION include
)
install(
  FILES ${CMAKE_BINARY_DIR}/dhsvmcxx.pc
  DESTINATION lib/pkgconfig
)

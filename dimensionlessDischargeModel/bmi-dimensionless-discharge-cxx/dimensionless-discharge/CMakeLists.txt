cmake_minimum_required(VERSION 3.0)

set (DIMENSIONLESS_DISCHARGE_VERSION 0.2)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/dimensionlessdischargecxx.pc.cmake
                ${CMAKE_BINARY_DIR}/dimensionlessdischargecxx.pc)

set(bmi_dimensionless_discharge_lib_SRCS bmi_dimensionless_discharge.cxx dimensionless_discharge.cxx)
if(WIN32)
  add_library(bmidimensionlessdischargecxx ${bmi_dimensionless_discharge_lib_SRCS})
else()
  add_library(bmidimensionlessdischargecxx SHARED ${bmi_dimensionless_discharge_lib_SRCS})
endif()

add_executable(run_bmidimensionlessdischargecxx bmi_main.cxx bmi_dimensionless_discharge.cxx dimensionless_discharge.cxx)

install(
  TARGETS run_bmidimensionlessdischargecxx
  RUNTIME DESTINATION bin
)
install(
  TARGETS bmidimensionlessdischargecxx
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)
install(
  FILES bmi_dimensionless_discharge.hxx dimensionless_discharge.hxx
  DESTINATION include
)
install(
  FILES ${CMAKE_BINARY_DIR}/dimensionlessdischargecxx.pc
  DESTINATION lib/pkgconfig
)

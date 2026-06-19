# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appHotel_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appHotel_autogen.dir\\ParseCache.txt"
  "appHotel_autogen"
  )
endif()

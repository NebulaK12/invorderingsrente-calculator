# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Invrenteberekenen_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Invrenteberekenen_autogen.dir\\ParseCache.txt"
  "Invrenteberekenen_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/QTSampleApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QTSampleApp_autogen.dir/ParseCache.txt"
  "QTSampleApp_autogen"
  )
endif()

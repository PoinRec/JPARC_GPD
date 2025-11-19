cmake_minimum_required(VERSION 3.16...3.27)

project(JPARC_E16_GPD)

find_package(Geant4 REQUIRED ui_all vis_all)

set(E16_GEANT4 "/data/tools/geant4/geant4-install/include/Geant4") # for CLHEP

# ROOT
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(jparc jparc.cc ${sources} ${headers})
target_link_libraries(jparc ${Geant4_LIBRARIES} ROOT::Core ROOT::RIO ROOT::Tree)

add_custom_target(JPARC_E16_GPD DEPENDS jparc)
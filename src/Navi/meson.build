# Define movie using function library()

inc = include_directories('.')

place = library('place', sources: ['Place.hpp']) 
place_dep = declare_dependency(include_directories: inc, link_with: place)

navi = library('navi', sources: ['Navi.hpp'], dependencies: [place_dep])
navi_dep = declare_dependency(include_directories: inc, link_with: navi)
# Define actor using function library()

inc = include_directories('.')

disjoint = library('disjoint', sources: ['disjoint.hpp']) 

disjoint_dep = declare_dependency(include_directories: inc, link_with: disjoint)
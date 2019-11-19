# Define actor using function library()

inc = include_directories('.')

actor = library('actor', sources: ['actor.hpp', 'actor.cpp']) 

actor_dep = declare_dependency(include_directories: inc,
  link_with: actor)
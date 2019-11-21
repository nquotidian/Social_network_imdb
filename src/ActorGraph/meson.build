# Define ActorGraph using function library()
subdir('MovieNode')
subdir('ActorNode')

inc = include_directories('.')

actor_graph = library('actor_graph', sources: ['ActorGraph.hpp', 'ActorGraph.cpp'], dependencies: [actor_dep, movie_dep]) 

actor_graph_dep = declare_dependency(include_directories: inc, link_with: actor_graph)
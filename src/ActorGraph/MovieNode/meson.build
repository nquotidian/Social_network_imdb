# Define movie using function library()

inc = include_directories('.')

# movie = library('movie', sources: ['movie.hpp', 'movie.cpp'], dependencies: [actor_dep])
movie = library('movie', sources: ['movie.hpp', 'movie.cpp'])

movie_dep = declare_dependency(include_directories: inc, link_with: movie)
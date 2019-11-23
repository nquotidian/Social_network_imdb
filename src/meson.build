subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable', 
    sources: ['pathfinder.cpp', 'FileUtils.hpp'],
    dependencies : [actor_graph_dep, cxxopts_dep],
#    include_directories : inc,
    install : true)
subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable', 
    sources: ['pathfinder.cpp', 'FileUtils.hpp'],
    dependencies : [actor_graph_dep, cxxopts_dep],
#    include_directories : inc,
    install : true)

pathfinder_exe = executable('linkpredictor.cpp.executable', 
    sources: ['linkpredictor.cpp', 'FileUtils.hpp'],
    dependencies : [actor_graph_dep, cxxopts_dep],
#    include_directories : inc,
    install : true)
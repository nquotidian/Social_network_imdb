/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include "ActorNode/actor.hpp"
#include "MovieNode/movie.hpp"
// #include "actor.hpp"
// #include "movie.hpp"

// Maybe include some data structures here

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // Maybe add class data structure(s) here
    // Actor* root = nullptr;
    // Graph for actors and graph for movies
    // vector<Actor*> actors_graph;
    unordered_map<string, Actor*> actors_list;
    unordered_map<string, Movie*> movies_list;
    // vector<Movie*> movies_graph;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    // Maybe add some more methods here
    void build_weighted_actor_graph(string actor_name, string movie_title,
                                    int year);
    void build_unweighted_actor_graph(string actor_name, string movie_title,
                                      int year);

    void traverse_actor_list();
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
};

#endif  // ACTORGRAPH_HPP

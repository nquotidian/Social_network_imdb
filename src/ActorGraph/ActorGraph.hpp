/*
 * ActorGraph.hpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
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

// Maybe include some data structures here

using namespace std;

/**
 * class to store the actors' list and movies' list
 */
class ActorGraph {
  protected:
    // Maybe add class data structure(s) here
    // Hash list for actors and movies
    unordered_map<string, Actor*> actors_list;
    unordered_map<string, Movie*> movies_list;

  public:
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);

    // Maybe add some more methods here
    // Add actor node and movie node
    void add_actor_movie_node(string actor_name, string movie_and_year);
    // Build unweighted actor movie connection graph
    void build_unweighted_actor_graph(string actor_name, string movie_title,
                                      int year);
    // Build weighted actor movie connection graph
    void build_weighted_actor_graph(string actor_name, string movie_title,
                                    int year);
    // For test
    // void traverse_actor_list();
    long number_of_movies();
    long number_of_actors();
    long number_of_connections();
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

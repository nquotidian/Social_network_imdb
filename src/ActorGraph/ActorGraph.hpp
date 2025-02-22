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
#include <unordered_set>
#include "ActorNode/actor.hpp"
#include "DisjointSet/disjoint.hpp"
#include "MovieNode/movie.hpp"

// Maybe include some data structures here

using namespace std;

/**
 * class to store the actors' list and movies' list
 */
class Link {
  public:
    Actor* actor;
    int weight;
    Link(Actor* a, int w) : actor(a), weight(w) {}
};

struct LinkComp {
    /* Comparator */
    bool operator()(Link*& l, Link*& r) const {
        if (l->weight != r->weight) {
            return l->weight < r->weight;
        } else {
            return l->actor->get_actor_name() > r->actor->get_actor_name();
        }
    }
};

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
    ~ActorGraph(void);

    // Maybe add some more methods here
    // Add actor node and movie node
    void add_actor_movie_node(string actor_name, string movie_and_year,
                              int weight);
    // Build unweighted actor movie connection graph
    void build_unweighted_actor_graph(string actor_name, string movie_title,
                                      int year);
    // Build weighted actor movie connection graph
    void build_weighted_actor_graph(string actor_name, string movie_title,
                                    int year);
    // Load the pairs file
    bool load_pairs_file(string pairsFile, string outputFile, bool weighted);
    // Find the shorest path between source actor and the target actor
    void find_path_between_actors(ofstream& fs, string source, string target);
    // Find the shortest path using dijkstra algorithm
    void find_path_dijkstra(ofstream& fs, string source, string target);
    /* Get all of the connections of the actor, return to a vector*/
    vector<Actor*> get_connection_list(Actor* actor);
    /* Linke predictor part */
    // Load the predict file
    bool load_predict_file(string predictFile, string coledFile,
                           string uncoledFile);
    /* Predict link of the actor */
    void predict_link(string source, ofstream& ofs_col, ofstream& ofs_uncol);
    /* Partial BFS of the graph */
    void BFS(string source);
    /* Calculate priority */
    string coled_actors(Actor* actor, vector<Actor*> list);
    string uncoled_actors(Actor* actor, vector<Actor*> list);
    // int connection_between_coled_casts(Actor* s_actor, Actor* t_actor);
    int connection_between_casts(Actor* s_actor, Actor* t_actor);

    // MST part
    // Initialize the disjoint set which storing all of the actor nodes
    void disjoint_set_init(string outputFile);

    // BFS traverse
    // void  BSTTraverse(string actor, )
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

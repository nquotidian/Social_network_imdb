/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

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
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship, now what?
        if (use_weighted_edges)
            build_weighted_actor_graph(actor, movie_title, year);
        else
            build_unweighted_actor_graph(actor, movie_title, year);
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

void ActorGraph::build_unweighted_actor_graph(string actor_name,
                                              string movie_title, int year) {
    // The graph of actors is empty or the actor is not in the graph
    if (actors_graph.empty() ||
        ((*actors_graph.rbegin())->get_actor_name() != actor_name)) {
        Actor* act = new Actor(actor_name);
        actors_graph.push_back(act);
    }

    string movie_year = movie_title + "#@" + std::to_string(year);
    // Movie list is empty or movie not in the movies_list
    if (movies_list.empty() ||
        movies_list.find(movie_year) == movies_list.end()) {
        Movie* mv = new Movie(movie_year);
        movies_list[movie_year] = mv;
        // actor points to movie
    } else {
        // the movie already exists
        // movie points to the movie
    }
}

void ActorGraph::build_weighted_actor_graph(string actor_name,
                                            string movie_title, int year) {}
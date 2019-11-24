/*
 * ActorGraph.cpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
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

void ActorGraph::add_actor_movie_node(string actor_name, string movie_and_year,
                                      int weight) {
    // The graph of actors is empty or the actor is not in the graph
    if (actors_list.empty() ||
        actors_list.find(actor_name) == actors_list.end()) {
        Actor* act = new Actor(actor_name);
        actors_list[actor_name] = act;
    }
    // Movie list is empty or movie is not in the movies_list
    if (movies_list.empty() ||
        movies_list.find(movie_and_year) == movies_list.end()) {
        Movie* mv = new Movie(movie_and_year, weight);
        movies_list[movie_and_year] = mv;
    }
}

void ActorGraph::build_unweighted_actor_graph(string actor_name,
                                              string movie_title, int year) {
    string movie_year = movie_title + "#@" + std::to_string(year);
    add_actor_movie_node(actor_name, movie_year, 1);
    auto actor = actors_list[actor_name];
    auto movie = movies_list[movie_year];
    // actor points to movie
    actor->points_to_movie(movie);
    // movie points to the actor
    movie->points_to_actor(actor);
}

void ActorGraph::build_weighted_actor_graph(string actor_name,
                                            string movie_title, int year) {
    string movie_year = movie_title + "#@" + std::to_string(year);
    add_actor_movie_node(actor_name, movie_year, 2020 - year);
    auto actor = actors_list[actor_name];
    auto movie = movies_list[movie_year];
    // actor points to movie
    actor->points_to_movie(movie);
    // movie points to the actor
    movie->points_to_actor(actor);
}

// Load the pairs file
bool ActorGraph::load_pairs_file(string pairsFile, string outputFile) {
    // keep reading the file, if it's not the end of the file
    // just like the load file function, get he source actor's name
    // and the target actor's name
    // Then call the function, find teh shorest path between the two actors
    // the function output the results.

    // Initialize the file stream
    ifstream infile(pairsFile);
    ofstream ofs(outputFile);
    bool have_header = false;

    // Output the header of the output file
    ofs << "(actor)--[movie#@year]-->(actor)--..." << endl;
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
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 2) {
            // we should have exactly 3 columns
            continue;
        }

        string source(record[0]);
        string target(record[1]);

        // find the path and output
        cout << "  " << source << "    " << target << endl;
        find_path_between_actors(ofs, source, target);
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << pairsFile << "!\n";
        return false;
    }
    infile.close();
    ofs.close();
    return true;
}

// Find the shorest path between source actor and the target actor
void ActorGraph::find_path_between_actors(ofstream& fs, string source,
                                          string target) {
    // Find the source actor
    // auto src_actor = actors_list[source];
    // // auto tgt_actor = actors_list[target];
    // queue<Actor*> que;
    // int dist = 0;
    // que.push(src_actor);
    // while (!que.empty()) {
    //     auto next = que.front();
    //     vector<Actor*> con_list = get_connection_list(next);
    //     que.pop();
    //     vector<Actor*>::iterator it = con_list.begin();
    //     for (; it != con_list.end(); it++) {
    //         //
    //     }
    // }
}

/* Get all of the connections of the actor, return to a vector*/
vector<Actor*> ActorGraph::get_connection_list(Actor* actor) {
    // vector<Movie*> movies = actor->get_movie_lists();
    // vector<Actor*> connection_list;
    // vector<Actor*>::iterator it = movies.begin();
    // for (; it != movies.end(); it++) {
    // }
}

long ActorGraph::number_of_actors() {
    long actor_num = 0;
    for (auto it = actors_list.begin(); it != actors_list.end(); it++) {
        actor_num++;
    }
    return actor_num;
}

long ActorGraph::number_of_movies() {
    long movie_num = 0;
    for (auto i = movies_list.begin(); i != movies_list.end(); i++) {
        movie_num++;
    }
    return movie_num;
}

long ActorGraph::number_of_connections() {
    long connec_num = 0;
    for (auto i = movies_list.begin(); i != movies_list.end(); i++) {
        connec_num += i->second->num_of_edges();
    }
    return connec_num;
}

/* Function for test */
// void ActorGraph::traverse_actor_list() {
//     // auto it = actors_list.begin();
//     long actor_num = 0;
//     for (auto it = actors_list.begin(); it != actors_list.end(); it++) {
//         // cout << (*it).first << endl;
//         // (*it).second->traverse_movies();
//         actor_num++;
//     }
//     cout << "actors: " << actor_num << endl;
//     long movie_num = 0;
//     long edge_num = 0;
//     for (auto i = movies_list.begin(); i != movies_list.end(); i++) {
//         // cout << (*i).first << endl;
//         // (*i).second->traverse_actors();
//         movie_num++;
//         edge_num += (*i).second->num_of_edges();
//     }
//     cout << "movies: " << movie_num << endl;
//     cout << "edges: " << edge_num << endl;
// }
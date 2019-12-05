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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <climits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}
ActorGraph::~ActorGraph(void) {
    for (auto i = movies_list.begin(); i != movies_list.end(); i++) {
        delete i->second;
    }
    for (auto j = actors_list.begin(); j != actors_list.end(); j++) {
        delete j->second;
    }
}

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
    // weight of the movie = 1+(2019-Y)
    add_actor_movie_node(actor_name, movie_year, 2020 - year);
    auto actor = actors_list[actor_name];
    auto movie = movies_list[movie_year];
    // actor points to movie
    actor->points_to_movie(movie);
    // movie points to the actor
    movie->points_to_actor(actor);
}

// Load the pairs file
bool ActorGraph::load_pairs_file(string pairsFile, string outputFile,
                                 bool weighted) {
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
            // we should have exactly 2 columns
            continue;
        }

        string source(record[0]);
        string target(record[1]);

        // find the path and output
        if (weighted) {
            find_path_dijkstra(ofs, source, target);
        } else {
            find_path_between_actors(ofs, source, target);
        }
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
    // auto tgt_actor = actors_list[target];
    if (actors_list.find(source) == actors_list.end() ||
        actors_list.find(target) == actors_list.end()) {
        fs << endl;
        return;
    }
    // Initialize
    auto map_it = actors_list.begin();
    for (; map_it != actors_list.end(); map_it++) {
        map_it->second->set_dist(INT8_MAX);
        map_it->second->set_prev(nullptr, nullptr);
    }
    // Set the source distance
    // Find the source actor
    auto src_actor = actors_list[source];
    src_actor->set_dist(0);
    queue<Actor*> que;
    que.push(src_actor);
    bool flag = false;
    Actor* neighbor = nullptr;
    while (!que.empty() && !flag) {
        auto next = que.front();
        que.pop();
        vector<Movie*> m_list = next->get_movie_lists();
        vector<Movie*>::iterator m_it = m_list.begin();
        for (; m_it != m_list.end() && !flag; m_it++) {
            vector<Actor*> a_list = (*m_it)->get_actor_lists();
            vector<Actor*>::iterator a_it = a_list.begin();
            for (; a_it != a_list.end() && !flag; a_it++) {
                neighbor = *a_it;
                string name = neighbor->get_actor_name();
                if (name != next->get_actor_name()) {
                    // if not visted, visit
                    if (neighbor->get_dist() == INT8_MAX) {
                        neighbor->set_dist(next->get_dist() + 1);
                        neighbor->set_prev(next, *m_it);
                        que.push(neighbor);
                        if (name == target) {
                            flag = true;
                        }
                    }
                }
            }
        }
    }
    if (flag) {
        string result = "";
        if (neighbor->get_prev().first) {
            result += "(" + neighbor->get_actor_name() + ")";
            auto ptr = neighbor->get_prev();
            while (ptr.first && ptr.second) {
                result.insert(0,
                              "[" + ptr.second->get_movie_name_year() + "]-->");
                result.insert(0, "(" + ptr.first->get_actor_name() + ")--");
                ptr = ptr.first->get_prev();
            }
            fs << result << endl;
        }
    } else {
        fs << endl;
    }
}

// Find the shortest path using dijkstra algorithm
void ActorGraph::find_path_dijkstra(ofstream& fs, string source,
                                    string target) {
    // auto tgt_actor = actors_list[target];
    if (actors_list.find(source) == actors_list.end() ||
        actors_list.find(target) == actors_list.end()) {
        fs << endl;
        return;
    }
    // Initialize weighted graph
    auto map_it = actors_list.begin();
    for (; map_it != actors_list.end(); map_it++) {
        map_it->second->set_dist(INT_MAX);
        map_it->second->set_prev(nullptr, nullptr);
        map_it->second->set_done(false);
    }
    // Set the source distance
    // Find the source actor
    Actor* src_actor = actors_list[source];
    src_actor->set_dist(0);
    priority_queue<Actor*, vector<Actor*>, DijkComp> dijk_que;
    dijk_que.push(src_actor);
    while (!dijk_que.empty()) {
        Actor* next = dijk_que.top();
        dijk_que.pop();
        if (!next->get_done()) {
            next->set_done(true);
            vector<Movie*> m_list = next->get_movie_lists();
            vector<Movie*>::iterator m_it = m_list.begin();
            for (; m_it != m_list.end(); m_it++) {
                vector<Actor*> a_list = (*m_it)->get_actor_lists();
                vector<Actor*>::iterator a_it = a_list.begin();
                for (; a_it != a_list.end(); a_it++) {
                    Actor* neighbor = *a_it;
                    if (neighbor != next) {
                        int distance = next->get_dist() + (*m_it)->get_weight();
                        string name = neighbor->get_actor_name();
                        if (distance < neighbor->get_dist()) {
                            neighbor->set_dist(distance);
                            neighbor->set_prev(next, *m_it);
                            dijk_que.push(neighbor);
                        }
                    }
                }
            }
        }
    }
    // if (actors_list.find(target) != actors_list.end()) {
    Actor* tar = actors_list[target];
    // if (tar->get_prev().first != nullptr) {
    string result = "";
    result += "(" + tar->get_actor_name() + ")";
    auto ptr = tar->get_prev();
    while (ptr.first && ptr.second) {
        result.insert(0, "[" + ptr.second->get_movie_name_year() + "]-->");
        result.insert(0, "(" + ptr.first->get_actor_name() + ")--");
        ptr = ptr.first->get_prev();
    }
    fs << result << endl;
    //} else {
    //   fs << endl;
    //}
    // }
}
// Load predict file
bool ActorGraph::load_predict_file(string predictFile, string coledFile,
                                   string uncoledFile) {
    // Initialize the file stream
    ifstream infile(predictFile);
    ofstream ofs_col(coledFile);
    ofstream ofs_uncol(uncoledFile);
    bool have_header = false;
    string line;
    // Output the header of the output file
    ofs_col << "Actor1,Actor2,Actor3,Actor4" << endl;
    ofs_uncol << "Actor1,Actor2,Actor3,Actor4" << endl;
    // keep reading lines until the end of file is reached

    for (; getline(infile, line);) {
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        predict_link(line, ofs_col, ofs_uncol);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << predictFile << "!\n";
        return false;
    }
    infile.close();
    ofs_col.close();
    ofs_uncol.close();
    return true;
}

/* Predict link of the actor */
void ActorGraph::predict_link(string source, ofstream& ofs_col,
                              ofstream& ofs_uncol) {
    if (actors_list.find(source) == actors_list.end()) {
        return;
    }
    // BFS the graph, find the collabrated actors and uncollaborated actors set
    BFS(source);
    vector<Actor*> col_list;
    vector<Actor*> uncol_list;
    for (auto it = actors_list.begin(); it != actors_list.end(); it++) {
        if ((*it).second->get_dist() == 1) {
            col_list.push_back((*it).second);
        } else if ((*it).second->get_dist() == 2) {
            uncol_list.push_back((*it).second);
        }
    }
    if (!col_list.empty()) {
        string s = coled_actors(actors_list[source], col_list);
        ofs_col << s << endl;
    } else {
        ofs_col << endl;
    }
    if (!uncol_list.empty()) {
        string str = uncoled_actors(actors_list[source], uncol_list);
        ofs_uncol << str << endl;
    } else {
        ofs_uncol << endl;
    }
}

/* Partial BFS of the graph */
void ActorGraph::BFS(string source) {
    // auto tgt_actor = actors_list[target];
    if (actors_list.find(source) == actors_list.end()) {
        return;
    }
    // Initialize
    auto map_it = actors_list.begin();
    for (; map_it != actors_list.end(); map_it++) {
        map_it->second->set_dist(INT8_MAX);
        map_it->second->set_prev(nullptr, nullptr);
    }
    // Set the source distance
    // Find the source actor
    auto src_actor = actors_list[source];
    src_actor->set_dist(0);
    queue<Actor*> que;
    que.push(src_actor);
    bool flag = false;
    Actor* neighbor = nullptr;
    while (!que.empty() && !flag) {
        auto next = que.front();
        que.pop();
        vector<Movie*> m_list = next->get_movie_lists();
        vector<Movie*>::iterator m_it = m_list.begin();
        for (; m_it != m_list.end() && !flag; m_it++) {
            vector<Actor*> a_list = (*m_it)->get_actor_lists();
            vector<Actor*>::iterator a_it = a_list.begin();
            for (; a_it != a_list.end() && !flag; a_it++) {
                neighbor = *a_it;
                string name = neighbor->get_actor_name();
                if (name != next->get_actor_name()) {
                    // if not visted, visit
                    if (neighbor->get_dist() == INT8_MAX) {
                        neighbor->set_dist(next->get_dist() + 1);
                        neighbor->set_prev(next, *m_it);
                        que.push(neighbor);
                        if (next->get_dist() > 2) {
                            flag = true;
                        }
                    }
                }
            }
        }
    }
}

/* Calculate priority */
string ActorGraph::coled_actors(Actor* actor, vector<Actor*> list) {
    // for all of movies of A, if A is not C,
    //      for all of actors of this movie
    priority_queue<Link*, std::vector<Link*>, LinkComp> my_pq;
    int priority = 0;
    for (auto i = list.begin(); i != list.end(); i++) {
        priority = 0;
        priority += connection_between_casts(actor, (*i));
        Link* lk = new Link((*i), priority);
        my_pq.push(lk);
    }
    // Decide the output size
    string result;
    Link* ptr = nullptr;
    unsigned size = my_pq.size();
    unsigned n = size > 4 ? 4 : size;
    for (unsigned i = 0; i < n - 1; i++) {
        ptr = my_pq.top();
        string name = ptr->actor->get_actor_name();
        result += name;
        result += "\t";
        my_pq.pop();
    }
    ptr = my_pq.top();
    result += ptr->actor->get_actor_name();
    return result;
}

string ActorGraph::uncoled_actors(Actor* actor, vector<Actor*> list) {
    priority_queue<Link*, std::vector<Link*>, LinkComp> my_pq;
    int priority = 0;
    for (auto i = list.begin(); i != list.end(); i++) {
        priority = 0;
        priority += connection_between_casts(actor, (*i));
        Link* lk = new Link((*i), priority);
        my_pq.push(lk);
    }

    // Decide the output size
    string result;
    Link* ptr = nullptr;
    unsigned size = my_pq.size();
    unsigned n = size > 4 ? 4 : size;
    for (unsigned i = 0; i < n - 1; i++) {
        ptr = my_pq.top();
        string name = ptr->actor->get_actor_name();
        result += name;
        result += "\t";
        my_pq.pop();
    }
    ptr = my_pq.top();
    result += ptr->actor->get_actor_name();
    return result;
}

int ActorGraph::connection_between_casts(Actor* s_actor, Actor* t_actor) {
    // Return the number of connections between two actors
    int i = 0;
    std::vector<Movie*> m_list = s_actor->get_movie_lists();
    auto m_it = m_list.begin();
    for (; m_it != m_list.end(); m_it++) {
        std::vector<Actor*> a_list = (*m_it)->get_actor_lists();
        auto a_it = a_list.begin();
        for (; a_it != a_list.end(); a_it++) {
            if ((*a_it) != s_actor) {
                std::vector<Movie*> m_list_2 = (*a_it)->get_movie_lists();
                auto m_it_2 = m_list_2.begin();
                for (; m_it_2 != m_list_2.end(); m_it_2++) {
                    std::vector<Actor*> a_list_2 = (*m_it_2)->get_actor_lists();
                    auto a_it_2 = a_list_2.begin();
                    for (; a_it_2 != a_list_2.end(); a_it_2++) {
                        if ((*a_it_2) != (*a_it)) {
                            if ((*a_it_2) == t_actor) {
                                i++;
                            }
                        }
                    }
                }
            }
        }
    }
    return i;
}

// MST part
// Initialize the disjoint set and generate MST
void ActorGraph::disjoint_set_init(string outputFile) {
    ofstream ofs(outputFile);
    unordered_map<string, string> actors_set;
    for (auto i = actors_list.begin(); i != actors_list.end(); i++) {
        actors_set[(*i).second->get_actor_name()] = "-1";
    }
    Set d_set(actors_set);
    // build a heap for all of the movies
    vector<Movie*> heap;
    for (auto it = movies_list.begin(); it != movies_list.end(); it++) {
        heap.push_back(it->second);
    }
    // generate MST
    std::sort(heap.begin(), heap.end(), MSTcompare);
    d_set.generate_mst(heap, actors_list.size(), ofs);
    ofs.close();
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
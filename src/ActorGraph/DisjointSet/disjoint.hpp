/**
 * movie.hpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 * With the reference of the discussion session on week 9,
 * Python code showed by Sander Valstar
 * Movie class hearder file
 */

#ifndef SET_HPP
#define SET_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// #include "actor.hpp"

using namespace std;

class Set;

/* Set node class
 *
 * */
class Set {
  private:
    unordered_map<string, string> actors;
    unordered_map<string, int> size;
    // vector<string> movies;
    void path_compression(vector<string> vec, string sentinel) {
        for (string i : vec) {
            actors[i] = sentinel;
        }
    }

  public:
    /* Constructor of movie */
    Set(unordered_map<string, string>& a) {
        actors = a;
        // movies = m;
        for (auto i = a.begin(); i != a.end(); i++) {
            size[i->first] = 1;
        }
    }
    string find(string name) {
        vector<string> path;
        while (actors[name] != "-1") {
            path.push_back(name);
            name = actors[name];
        }
        path_compression(path, name);
        return name;
    }

    bool union_nodes(string i, string j) {
        string senti_i = find(i);
        string senti_j = find(j);
        int size_i = size[senti_i];
        int size_j = size[senti_j];
        if (senti_i != senti_j) {
            if (size_i < size_j) {
                // size of j equals to size of i plus j
                size[senti_j] = size[senti_j] + size[senti_i];
                actors[senti_i] = senti_j;
            } else {
                // size of i equals to size of j plus i
                size[senti_i] = size[senti_i] + size[senti_j];
                actors[senti_j] = senti_i;
            }
            return true;
        } else {
            return false;
        }
    }

    void generate_mst(vector<Movie*> heap, unsigned n, ofstream& ofs) {
        bool done = false;
        bool inner = false;
        unsigned nodes = 0, edges = 0, total_weight = 0;
        unordered_set<string> visited;
        string name_1;
        string name_2;
        // cout << "heap size " << heap.size() << endl;
        ofs << "(actor)<--[movie#@year]-->(actor)" << endl;
        for (auto i = heap.begin(); i != heap.end() && !done; i++) {
            auto list = (*i)->get_actor_lists();
            inner = false;
            // Find the actor node that was not connected
            for (unsigned j = 0; j < list.size() - 1 && !inner;) {
                name_1 = list[j]->get_actor_name();
                name_2 = list[j + 1]->get_actor_name();
                if (union_nodes(name_1, name_2)) {
                    visited.insert(name_1);
                    visited.insert(name_2);
                    ofs << "(" << name_1 << ")<--["
                        << (*i)->get_movie_name_year() << "]-->(" << name_2
                        << ")" << endl;
                    // cout << " weight  " << (*i)->get_weight() << endl;
                    total_weight += (*i)->get_weight();
                    edges++;
                    // inner = true;
                } else {
                    j++;
                }
            }
            if (visited.size() == n) {
                done = true;
            }
        }
        nodes = edges + 1;
        ofs << "#NODE CONNECTED: " << nodes << endl;
        ofs << "#EDGE CHOSEN: " << edges << endl;
        ofs << "TOTAL EDGE WEIGHTS: " << total_weight << endl;
    }
};

#endif  // MOVIE_HPP
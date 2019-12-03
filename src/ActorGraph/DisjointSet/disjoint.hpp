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

    void union_nodes(string i, string j) {
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
        }
    }
};

#endif  // MOVIE_HPP
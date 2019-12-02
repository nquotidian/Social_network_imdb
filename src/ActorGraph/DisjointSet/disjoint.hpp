/**
 * movie.hpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
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
    unordered_map<string, int> actors;
    vector<string> movies;

  public:
    /* Constructor of movie */
    Set(unordered_map<string, int>& a, vector<string>& m) {
        actors = a;
        movies = m;
    }
    int find(string name) {
        // if(actors[name] == -1)
    }
    void union_nodes(int i, int j) {
        //
    }
};

#endif  // MOVIE_HPP
/**
 * Movie class hearder file
 *
 * Author: Qing Niu
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>
// #include "actor.hpp"

using namespace std;

class Actor;

struct Edge {
    int wei;
    Actor* act;
};

/* Movie class */
class Movie {
  private:
    string name_year;     // the name#@year of the movie
    vector<Edge> actors;  // the actors perform in the movie
  public:
    Movie(string name_and_year) : name_year(name_and_year) {}
    void points_to_actor(int weight, Actor* act_ptr) {
        struct Edge e;
        e.wei = weight;
        e.act = act_ptr;
        actors.push_back(e);
    }
};

#endif  // MOVIE_HPP
/**
 * movie.hpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 * Movie class hearder file
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

/* Movie node class
 *  name_year: movie's name + movie's year
 *  movies: list the weight and the actor's name
 *
 * */
class Movie {
  private:
    string name_year;     // the name#@year of the movie
    vector<Edge> actors;  // the actors perform in the movie
  public:
    /* Constructor of movie */
    Movie(string name_and_year) : name_year(name_and_year) {}
    /* Get the movie's name */
    string get_movie_name_year() { return name_year; }
    /* Points the movie to the actor */
    void points_to_actor(int weight, Actor* act_ptr) {
        struct Edge e;
        e.wei = weight;
        e.act = act_ptr;
        actors.push_back(e);
    }
    /* The number of connections of a single movie */
    long num_of_edges() {
        long n = actors.size();
        if (!n)
            return 0;
        else
            return n * (n + 1);
    }
};

#endif  // MOVIE_HPP
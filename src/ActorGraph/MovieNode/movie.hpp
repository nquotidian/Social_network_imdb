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

/* Movie node class
 *  name_year: movie's name + movie's year
 *  movies: list the weight and the actor's name
 *
 * */
class Movie {
  private:
    string name_year;       // the name#@year of the movie
    int weight;             // the weight of the movie
    vector<Actor*> actors;  // the actors perform in the movie
  public:
    /* Constructor of movie */
    Movie(string name_and_year, int wei)
        : name_year(name_and_year), weight(wei) {}
    /* Get the movie's name */
    string get_movie_name_year() { return name_year; }
    /* Points the movie to the actor */
    void points_to_actor(Actor* act_ptr) { actors.push_back(act_ptr); }
    /* The number of connections of a single movie */
    long num_of_edges() {
        long n = actors.size();
        if (n <= 1)
            return 0;
        else
            return n * (n - 1);
    }
    /* Get the weight of the movie */
    int get_weight() { return weight; }
    /* Get the list of movies of the actor*/
    vector<Actor*> get_actor_lists() { return actors; }
};

// Comparator for the the heap when generating MST

/* Comparator */
bool MSTcompare(Movie*& l, Movie*& r) {
    if (l->get_weight() != r->get_weight()) {
        return l->get_weight() > r->get_weight();
    } else {
        return l->get_movie_name_year() > r->get_movie_name_year();
    }
}

#endif  // MOVIE_HPP
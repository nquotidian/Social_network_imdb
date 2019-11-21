/**
 * Actor class hearder file
 *
 * Author: Qing Niu
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <unordered_set>
#include <vector>
#include "movie.hpp"

using namespace std;

/* Actor node class */
class Actor {
  private:
    string name;            // the name of the actor
    vector<Movie*> movies;  // the movies of the actor performed

  public:
    /* Constructor of actor, add first movie */
    Actor(string actor_name) : name(actor_name) {}
    string get_actor_name() { return name; }
    // void add_movie(string movie, int year) {
    //     Movie* mv = new Movie(movie, year);
    //     movies.push_back(mv);
    // }
    void points_to_movie(Movie* mv_ptr) { movies.push_back(mv_ptr); }
};

#endif  // ACTOR_HPP
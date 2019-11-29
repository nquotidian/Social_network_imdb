/**
 * actor.hpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 * Actor class hearder file
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "MovieNode/movie.hpp"

using namespace std;

/* Actor node class
 *  name: actor's name
 *  movies: list of the actor's movies
 *
 * */
class Actor {
  private:
    string name;
    int dist;
    std::pair<Actor*, Movie*> prev;
    vector<Movie*> movies;
    bool done;

  public:
    /* Constructor of actor, add first movie */
    Actor(string actor_name)
        : name(actor_name),
          dist(INT8_MAX),
          prev(make_pair(nullptr, nullptr)),
          done(false) {}
    /* Get actor's name */
    string get_actor_name() { return name; }
    /* Created a new movie and points the actor to the movie*/
    void points_to_movie(Movie* mv_ptr) { movies.push_back(mv_ptr); }
    /* Traverse all of the movies in the actor node, for test */
    void traverse_movies() {
        for (unsigned i = 0; i < movies.size(); i++) {
            cout << "  " << movies[i]->get_movie_name_year() << endl;
        }
    }
    /* Set the distance to the actor */
    void set_dist(int d) { dist = d; }
    /* Get the distance of the actor */
    int get_dist() { return dist; }
    /* Set the prev pointer */
    void set_prev(Actor* a_ptr, Movie* m_ptr) {
        prev.first = a_ptr;
        prev.second = m_ptr;
    }
    /* Set the done flag to be true */
    void set_done(bool d) { done = d; }
    /* Get the done flag */
    int get_done() { return done; }
    /* Get the prev pointer */
    std::pair<Actor*, Movie*> get_prev() { return prev; }
    /* Get the list of movies of the actor*/
    vector<Movie*> get_movie_lists() { return movies; }
};

// Comparator for the priority queue when doing the dijkstra algorithm
struct DijkComp {
    /* Comparator */
    bool operator()(Actor*& l, Actor*& r) const {
        if (l->get_dist() != r->get_dist()) {
            return l->get_dist() > r->get_dist();
        } else {
            return l->get_actor_name() > r->get_actor_name();
        }
    }
};

#endif  // ACTOR_HPP
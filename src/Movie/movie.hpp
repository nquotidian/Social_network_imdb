/**
 * Movie class hearder file
 *
 * Author: Qing Niu
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>
#include "actor.hpp"

using namespace std;

/* Movie class */
class Movie {
  private:
    string name;            // the name of the movie
    int year;               // the year of the movie
    vector<Actor*> actors;  // the actors perform in the movie
};

#endif  // MOVIE_HPP
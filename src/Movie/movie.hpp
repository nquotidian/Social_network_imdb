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
    string name_year;            // the name#@year of the movie
    vector<int, Actor*> actors;  // the actors perform in the movie
  public:
    Movie(string name_and_year) : name_year(name_and_year) {}
};

#endif  // MOVIE_HPP
/**
 * Actor class hearder file
 *
 * Author: Qing Niu
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <vector>
#include "movie.hpp"

using namespace std;

/* Actor node class */
class Actor {
  private:
    string name;            // the name of the actor
    vector<Movie*> movies;  // the movie of the actor performed
};

#endif  // ACTOR_HPP
/**
 * Place.hpp
 * Author: Qing Niu
 * Date:   Dec 2, 2019
 *
 * Actor class hearder file
 */

#ifndef PLACE_HPP
#define PLACE_HPP

#include <cmath>
#include <map>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Navi/Navi.hpp"

using namespace std;

/* Actor node class
 *  name: actor's name
 *  movies: list of the actor's movies
 *
 * */

class Place {
  private:
    string name;
    // Coordinates
    int x;
    int y;
    double dist;
    double h_dist;
    bool done;
    std::map<Place*, double> edges;

  public:
    /* Constructor of actor, add first movie */
    Place(string place_name, int x_cor, int y_cor)
        : name(place_name), x(x_cor), y(y_cor), done(false) {}
    void point_out(Place* plc) {
        double dist =
            sqrt(pow(x - plc->get_x(), 2) + pow(y - plc->get_y(), 2) * 1.0);
        edges[plc] = dist;
    }
    int get_x() { return x; }
    int get_y() { return y; }
    double get_dist() { return dist; }
    double get_h_dist() { return h_dist; }
    string get_name() { return name; }
    bool get_done() { return done; }
    std::map<Place*, double>* get_map() { return &edges; }
    void set_dist(double d) { dist = d; }
    void set_h_dist(double h_d) { h_dist = h_d; }
    void set_done(bool don) { done = don; }
};

// Comparator for the priority queue when doing the dijkstra algorithm
struct plcComp {
    /* Comparator */
    bool operator()(Place*& l, Place*& r) const {
        if (l->get_h_dist() != r->get_h_dist()) {
            return l->get_h_dist() > r->get_h_dist();
        } else {
            return l->get_name() > r->get_name();
        }
    }
};

#endif  // ACTOR_HPP
/*
 * Navi.hpp
 * Author: Qing Niu
 * Date:   Dec 2, 2019
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef NAVIGRAPH_HPP
#define NAVIGRAPH_HPP

#include <cstddef>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <unordered_map>
#include "Place.hpp"

using namespace std;

/**
 * class to store the places' graph
 */
class NaviGraph {
  protected:
    unordered_map<string, Place*> places_list;

  public:
    /**
     * Constuctor of the Actor graph
     */
    NaviGraph() {}
    ~NaviGraph() {
        for (auto i = places_list.begin(); i != places_list.end(); i++) {
            delete i->second;
        }
    }
    bool loadFromFile(const char* in_filename) {
        // Initialize the file stream
        ifstream infile(in_filename);

        // keep reading lines until the end of file is reached
        while (infile) {
            string s;
            // get the next line
            if (!getline(infile, s)) break;
            istringstream ss(s);
            vector<string> record;

            while (ss) {
                string str;
                // get the next string before hitting a tab character and put it
                // in 'str'
                if (!getline(ss, str, ' ')) break;
                record.push_back(str);
            }

            if (record.size() != 3) {
                // we should have exactly 3 columns
                continue;
            }

            string place_name(record[0]);
            int x_cor = stoi(record[1]);
            int y_cor = stoi(record[2]);

            build_graph(place_name, x_cor, y_cor);
        }
        if (!infile.eof()) {
            cerr << "Failed to read " << in_filename << "!\n";
            return false;
        }
        infile.close();
        return true;
    }

    void build_graph(string place, int x, int y) {
        if (places_list.empty() ||
            places_list.find(place) == places_list.end()) {
            Place* plc = new Place(place, x, y);
            places_list[place] = plc;
        }
    }

    bool load_pairs_file(const char* in_filename) {
        // Initialize the file stream
        ifstream infile(in_filename);

        // keep reading lines until the end of file is reached
        while (infile) {
            string s;
            // get the next line
            if (!getline(infile, s)) break;
            istringstream ss(s);
            vector<string> record;
            while (ss) {
                string str;
                // get the next string before hitting a tab character and put it
                // in 'str'
                if (!getline(ss, str, ' ')) break;
                record.push_back(str);
            }
            if (record.size() != 2) {
                continue;
            }

            string place_1(record[0]);
            string place_2(record[1]);

            connect_graph(place_1, place_2);
            // build_weighted_actor_graph(actor, movie_title, year);
            // build_graph(place_name, x_cor, y_cor);
        }
        if (!infile.eof()) {
            cerr << "Failed to read " << in_filename << "!\n";
            return false;
        }
        infile.close();
        return true;
    }

    void connect_graph(string place_1, string place_2) {
        Place* p1 = nullptr;
        Place* p2 = nullptr;
        if (places_list.find(place_1) != places_list.end())
            p1 = places_list[place_1];
        if (places_list.find(place_2) != places_list.end())
            p2 = places_list[place_2];
        p1->point_out(p2);
        p2->point_out(p1);
    }

    bool astar(string queryFile, string outputFile) {
        // Initialize the file stream
        ifstream infile(queryFile);
        ofstream ofs(outputFile);
        // keep reading lines until the end of file is reached
        while (infile) {
            string s;
            // get the next line
            if (!getline(infile, s)) break;
            istringstream ss(s);
            vector<string> record;
            while (ss) {
                string str;
                // get the next string before hitting a tab character and put it
                // in 'str'
                if (!getline(ss, str, ' ')) break;
                record.push_back(str);
            }
            if (record.size() != 2) {
                continue;
            }

            string place_1(record[0]);
            string place_2(record[1]);

            string path = generate_path(place_1, place_2);
            cout << "--  " << path << endl;
        }
        if (!infile.eof()) {
            cerr << "Failed to read " << queryFile << "!\n";
            return false;
        }
        infile.close();
        ofs.close();
        return true;
    }

    string generate_path(string place_1, string place_2) {
        Place* p1 = nullptr;
        Place* p2 = nullptr;
        if (places_list.find(place_1) != places_list.end())
            p1 = places_list[place_1];
        if (places_list.find(place_2) != places_list.end())
            p2 = places_list[place_2];
        cout << "p1  " << p1->get_name() << endl;
        cout << "p2  " << p2->get_name() << endl;

        string path;
        priority_queue<Place*, vector<Place*>, plcComp> pri_que;
        for (auto i = places_list.begin(); i != places_list.end(); i++) {
            i->second->set_done(false);
            i->second->set_dist(INT8_MAX);
            i->second->set_h_dist(INT8_MAX);
        }
        p1->set_dist(0);
        p1->set_h_dist(0);
        pri_que.push(p1);

        while (!pri_que.empty()) {
            Place* v = pri_que.top();
            pri_que.pop();
            if (!v->get_done()) {
                // path += v->get_name();
                // path += "  ";
                v->set_done(true);
                for (auto p = (v->get_map())->begin(); p != v->get_map()->end();
                     p++) {
                    if (p->first != nullptr) {
                        double c = v->get_dist() + p->second;
                        if (c < p->first->get_dist()) {
                            p->first->set_dist(c);
                            double h = herustic(p->first, p2);
                            p->first->set_h_dist(c + h);
                            pri_que.push(p->first);
                            path += p->first->get_name();
                        }
                    }
                }
            }
        }
        cout << "path -- " << endl << path << endl;
        return path;
    }

    double herustic(Place* p1, Place* p2) {
        double dist = sqrt(pow(p1->get_x() - p2->get_x(), 2) +
                           pow(p1->get_y() - p2->get_y(), 2));
        return dist;
    }
};

#endif  // NAVIGRAPH_HPP

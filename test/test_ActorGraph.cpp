/**
 * Unit test to test ActorGraph class
 *
 * Author: Qing Niu
 */

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

/** Build a unweighted graph of actors
 *    Storing the list of actors and movies,
 *    connect actors with movies
 */
class ActorUnweiGraphFixture : public ::testing::Test {
  protected:
    ActorGraph graph_unwei;

  public:
    ActorUnweiGraphFixture() {
        // initialization code here
        graph_unwei.loadFromFile("/Code/cse100_pa4/data/imdb_small_sample.tsv",
                                 false);
    }
};

/* Test the number of actors in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_NUM_ACTOR) {
    long a_num = graph_unwei.number_of_actors();
    ASSERT_EQ(a_num, 7);
}

/* Test the number of movies in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_NUM_MOVIE) {
    long m_num = graph_unwei.number_of_movies();
    ASSERT_EQ(m_num, 7);
}

/* Test the number of connections in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_NUM_CONNECTIONS) {
    long c_num = graph_unwei.number_of_connections();
    ASSERT_EQ(c_num, 18);
}

/* Test the path between actors in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_ACTOR_NAME) {
    string source = "James McAvoy";
    string target = "Michael Fassbender";
    ofstream ofs;
    ofs.open("/Code/cse100_pa4/data/test.txt", std::ofstream::out);
    graph_unwei.find_path_between_actors(ofs, source, target);
    ofs.close();
}

/* Test the path between actors in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_LOAD_PAIRS_FILE) {
    string input = "/Code/cse100_pa4/data/test_pairs.tsv";
    string output = "/Code/cse100_pa4/data/output.txt";
    bool load = graph_unwei.load_pairs_file(input, output);
    ASSERT_TRUE(load);
}

/* Test the path between actors in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_LOAD_PREDICT_FILE) {
    string input = "/Code/cse100_pa4/data/test_actors.tsv";
    string output_1 = "/Code/cse100_pa4/data/col_output.txt";
    string output_2 = "/Code/cse100_pa4/data/uncol_output.txt";
    string source = "James McAvoy";
    ofstream ofs_1(output_1, std::ofstream::out);
    ofstream ofs_2(output_2, std::ofstream::out);
    bool load = graph_unwei.load_predict_file(input, output_1, output_2);
    graph_unwei.predict_link(source, ofs_1, ofs_2);
    ASSERT_TRUE(load);
}

/* Test the path between actors in the graph */
TEST_F(ActorUnweiGraphFixture, TEST_BFS) {
    string source = "James McAvoy";
    graph_unwei.BFS(source);
}

/** Build a weighted graph of actors
 *    Storing the list of actors and movies,
 *    connect actors with movies
 */
class ActorWeiGraphFixture : public ::testing::Test {
  protected:
    ActorGraph graph_wei;

  public:
    ActorWeiGraphFixture() {
        // initialization code here
        graph_wei.loadFromFile("/Code/cse100_pa4/data/imdb_small_sample.tsv",
                               true);
    }
};

/* Test the number of actors in the graph */
TEST_F(ActorWeiGraphFixture, TEST_NUM_WEI_ACTOR) {
    long a_num = graph_wei.number_of_actors();
    ASSERT_EQ(a_num, 7);
}

/* Test the number of movies in the graph */
TEST_F(ActorWeiGraphFixture, TEST_NUM_WEI_MOVIE) {
    long m_num = graph_wei.number_of_movies();
    ASSERT_EQ(m_num, 7);
}

/* Test the number of connections in the graph */
TEST_F(ActorWeiGraphFixture, TEST_NUM_WEI_CONNECTIONS) {
    long c_num = graph_wei.number_of_connections();
    ASSERT_EQ(c_num, 18);
}
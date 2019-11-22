/**
 * Unit test to test ActorGraph class
 *
 * Author: Qing Niu
 */

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
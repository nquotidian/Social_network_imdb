/*
 * linkpredictor.cpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 */

#include <fstream>
#include <iostream>
#include "FileUtils.hpp"
#include "cxxopts.hpp"

/* add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void navigationsystem(string coordinateFile, string inputFile, string coledFile,
                      string uncoledFile);

/* Main program that runs the link_predictor */
int main(int argc, char* argv[]) {
    // define options object with program description and help messages
    cxxopts::Options options("./navigationsystem",
                             "Find the distance using A*");
    options.positional_help(
        "./path_to_movie_xy_file -./path_to_pairs_file "
        "./query_pairs_file "
        "./output_file");

    // define variables in which to store the parsed options
    // unweighted or weighted grpah option
    string graph_option;
    string xyFile, pairsFile, queryPairs, outputFile;

    // define which options exist, in which variable they should be stored,
    // and their corresponding help messages
    options.allow_unrecognised_options().add_options()(
        "xy", "The file contains the x, y coordinate of the locations",
        cxxopts::value<string>(xyFile))(
        "pairs", "The input file contains the connections of the locations",
        cxxopts::value<string>(pairsFile))(
        "query", "The file contains the query pairs of locations",
        cxxopts::value<string>(queryPairs))("output", "Output file",
                                            cxxopts::value<string>(outputFile))

        ("h,help", "Print help and exit");

    // define which options are required positional arguments
    options.parse_positional({"xy", "pairs", "query", "output"});
    // parse the command line options the user passed into the program
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(xyFile) ||
        FileUtils::isEmptyFile(xyFile)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (!FileUtils::isValidFile(pairsFile) ||
               FileUtils::isEmptyFile(pairsFile)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (!outputFile.empty()) {
        // Build unweighted graph
        /// link_predictor(xyFile, pairsFile, queryPairs, outputFile);
    } else {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
}

void link_predictor(string coordinateFile, string pairsFile, string query,
                    string outputFile) {
    // Create a file stream and read file in binary mode
    FileUtils fu;

    // If the input file is empty, output an empty file
    if (fu.isEmptyFile(coordinateFile) || fu.isEmptyFile(pairsFile)) {
        std::ofstream output(outputFile);
        return;
    }

    // ActorGraph actor_graph;
    // if (actor_graph.loadFromFile(coordinateFile.c_str(), true)) {
    //     // actor_graph.
    //     actor_graph.load_predict_file(pairsFile, query, outputFile);
    // }
}
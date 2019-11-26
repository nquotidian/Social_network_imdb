/*
 * pathfinder.cpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 */

#include <fstream>
#include <iostream>
#include "ActorGraph.hpp"
#include "FileUtils.hpp"
#include "cxxopts.hpp"

/* path finder function, find the shorest path between two actors */
void path_finder(string castsFile, string pairsFile, string outputFile,
                 bool weighted);

/* Main program that runs the pathfinder */
int main(int argc, char* argv[]) {
    // define options object with program description and help messages
    cxxopts::Options options("./pathfinder",
                             "Find the shortest path from one actor to another "
                             "actor through shared movies");
    options.positional_help(
        "./path_to_movie_casts_file -u/w ./path_to_pairs_file "
        "./path_to_output_file");

    // define variables in which to store the parsed options
    // unweighted or weighted grpah option
    string graph_option;
    string castsFileName, pairsFileName, outFileName;

    // define which options exist, in which variable they should be stored,
    // and their corresponding help messages
    options.allow_unrecognised_options().add_options()(
        "casts", "Movie casts file", cxxopts::value<string>(castsFileName))(
        "uORw", "Build up unweighted/weighted graph",
        cxxopts::value<string>(graph_option))(
        "pairs", "Pairs of actors", cxxopts::value<string>(pairsFileName))(
        "output", "File to store the results",
        cxxopts::value<string>(outFileName))("h,help", "Print help and exit");

    // define which options are required positional arguments
    options.parse_positional({"casts", "uORw", "pairs", "output"});
    // parse the command line options the user passed into the program
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(castsFileName) ||
        FileUtils::isEmptyFile(castsFileName)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (!FileUtils::isValidFile(pairsFileName) ||
               FileUtils::isEmptyFile(pairsFileName)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (graph_option == "u") {
        // Build unweighted graph
        path_finder(castsFileName, pairsFileName, outFileName, false);
    } else if (graph_option == "w") {
        // Build weighted graph
        path_finder(castsFileName, pairsFileName, outFileName, true);
    } else {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
}

void path_finder(string castsFile, string pairsFile, string outputFile,
                 bool weighted) {
    // Create a file stream and read file in binary mode
    FileUtils fu;

    // If the input file is empty, output an empty file
    if (fu.isEmptyFile(castsFile) || fu.isEmptyFile(pairsFile)) {
        // If the output file exists, remove it
        if (fu.isValidFile(outputFile)) {
            const char* filePath = outputFile.c_str();
            remove(filePath);
        }
        std::ofstream output(outputFile);
        return;
    }

    ActorGraph actor_graph;
    if (weighted) {
        if (actor_graph.loadFromFile(castsFile.c_str(), true)) {
            actor_graph.load_pairs_file(pairsFile, outputFile);
        }
    } else {
        if (actor_graph.loadFromFile(castsFile.c_str(), false)) {
            actor_graph.load_pairs_file(pairsFile, outputFile);
        }
    }
}
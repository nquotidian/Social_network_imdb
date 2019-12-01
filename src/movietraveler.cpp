/*
 * linkpredictor.cpp
 * Author: Qing Niu
 * Date:   Nov 22, 2019
 *
 */

#include <fstream>
#include <iostream>
#include "ActorGraph.hpp"
#include "FileUtils.hpp"
#include "cxxopts.hpp"

/* add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void movie_traveler(string castsFile, string outputFile);

/* Main program that runs the link_predictor */
int main(int argc, char* argv[]) {
    // define options object with program description and help messages
    cxxopts::Options options("./movie_traveler", "Generate the MST");
    options.positional_help(
        "./path_to_movie_casts_file"
        "./path_to_output_file");

    // define variables in which to store the parsed options
    // unweighted or weighted grpah option
    string castsFileName, outputFile;

    // define which options exist, in which variable they should be stored,
    // and their corresponding help messages
    options.allow_unrecognised_options().add_options()(
        "casts", "Movie casts file", cxxopts::value<string>(castsFileName))(
        "output", "The MST for the actors", cxxopts::value<string>(outputFile))(
        "h,help", "Print help and exit");

    // define which options are required positional arguments
    options.parse_positional({"casts", "output"});
    // parse the command line options the user passed into the program
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(castsFileName) ||
        FileUtils::isEmptyFile(castsFileName)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (!FileUtils::isValidFile(castsFileName)) {
        cout << options.help({""}) << std::endl;
        exit(0);
    } else if (!outputFile.empty())
        cout << "Call the movietraveler function " << endl;
    else {
        cout << options.help({""}) << std::endl;
        exit(0);
    }
}

void link_predictor(string castsFile, string inputFile, string coledFile,
                    string uncoledFile) {
    // Create a file stream and read file in binary mode
    FileUtils fu;

    // If the input file is empty, output an empty file
    if (fu.isEmptyFile(castsFile) || fu.isEmptyFile(inputFile)) {
        std::ofstream output(coledFile);
        std::ofstream output_2(uncoledFile);
        return;
    }

    ActorGraph actor_graph;
    if (actor_graph.loadFromFile(castsFile.c_str(), true)) {
        // actor_graph.
        actor_graph.load_predict_file(inputFile, coledFile, uncoledFile);
    }
}
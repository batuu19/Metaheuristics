#include "Controller.h"


Controller::Controller() {

}

void Controller::run() {
    std::string filename = "berlin11_modified.tsp";
    std::string configFilename = "config.cfg";

    auto problem = Loader::loadData(TSP_DIRECTORY + filename);
    auto configs = Loader::loadConfigs(configFilename);

//    Algorithm algorithm(configs[0]);

}

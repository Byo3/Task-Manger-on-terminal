# pragma once
#include "include.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

struct Task_Manager{
    using json         = nlohmann::json;

    int task_position = 0;

    int Task_Id        = 0;
    
    using informations = std::map<std::string, std::string>; //It is used any to accept any kind of input
    std::vector<informations> info_list;

    void pull_apart(const char text)
    {std::cout << '\n' << std::string(100, text) << '\n';} // It divides the user actions

    static void print_task(const std::string& command){ // I used a reference to not be copied by the compiler
    std::cout << command << std::endl;
    }

    // Setting up the JSON function
    void JsonSet(int type_action){
        static const std::string task_file = "Tasks.json";
        std::fstream checking_file("Tasks.json");

        if (!checking_file){ 
            std::cerr << "Unfortunately, Your file Was not found.";
        }
        checking_file.close(); // Always close the reader file before reopening  it.

        switch (type_action) {
            case 1: {
                // Creates a new Task
            json json_array = json::array();
            
            for (size_t i = 0; i < info_list.size(); i++) {
                json taskEntry = {
                    {"ID", i},
                    {"Task Name", info_list[i]["taskName"]},
                    {"Task", info_list[i]["Task"]}
                };  
                json_array.push_back(taskEntry);
            }
                std::ofstream output(task_file);
                if (output.is_open()){
                output << json_array.dump(4);
                }
                break;
            } case 2: {
                // It shows The existant Tasks.
                std::ifstream input(task_file);
                json Loaded_file;
                input.close();

                input >> Loaded_file;
                std::cout << "========== YOUR TASKS ==========" << "\n";
                for (const auto& stuff : Loaded_file){
                    std::cout << "[" << stuff["ID"] << "]" << stuff["Task Name"] << "\n";
                    std::cout << "    |___Details: " << stuff["Task"] << "\n";
                break;
                } // for
            }// cases
        } // switch cases
    }// JsonSet

    void creating_task();
    void delete_task();
    void manage_task();
};

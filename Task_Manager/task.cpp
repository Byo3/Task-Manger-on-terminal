#include "task.hpp"
#include "include.hpp"

namespace ERRORS {
    constexpr const char* not_found    = "[ERROR] This file does not exist.\n";
    constexpr const char* empty_input  = "[Error] Your task name cannot be empty.\n";
    constexpr const char* invalid_task = "[Invalid] Select a valid Task.\n";
    constexpr const char* out_range    = "[Invalid] To delete a task it is necessary select an existant task first.\n";
} // namespace ERRORS

void Task_Manager::creating_task(){

    bool validating_actions = false;
    informations              inputs;
    /** Para usar o dicionário é necéssario criar um apelido,
     *  já que informations é como um tipo de dado e nao uma variavél.
    */
    do {
        try {
            // * Defing a name for the task.
                std::cout << "Define a name: ";
                std::cin >> inputs["taskName"];

            // * Setting up the informations of the task.
                std::cout << "Set your task: ";
                std::cin >> inputs["Task"];

                info_list.push_back(inputs);

                if (std::cin.fail()) {
                    throw std::invalid_argument(ERRORS::empty_input);
                }// if cin.fail

                print_task(paint("Your task was saved successfully.", Term::GREEN));

                //  From this line onward, the JSON file will be processed.
                JsonSet(1);
                validating_actions = true;
            
        } catch(std::invalid_argument& e) {
            std::cout << paint(e.what(), Term::RED) << "\n";
        } // try & catch

    } while(!(validating_actions)); // do & while(validating)
} // Create a task

void Task_Manager::delete_task(){
    bool validating_actions = false;
    task_position           = 0;

    if (info_list.empty()) {
        print_task(paint("There's no any task yet, you should add one.", Term::YELLOW));
        
    } else { 
        for (size_t i = 0; i < info_list.size(); i++) {
            std::cout << "[" << i << "] " << info_list[i]["taskName"] << "\n";
        }

        do {
            try {
                std::cout << "Select a Task to be delete it: ";
                std::cin >> task_position;

                if (std::cin.fail()) { 
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    pull_apart('-');
                    throw std::invalid_argument(ERRORS::invalid_task);
                } // if cin fail

                if (task_position >= 0 && task_position < info_list.size()){
                    std::string erased_task = info_list[task_position]["taskName"];
                    info_list.erase(info_list.begin() + task_position);
                    // It wipes out a task from task_list based on its index like pop() method, from python
                    // but it is necessary sum up when statt the list and an index

                    print_task(paint("Task Deleted successfully.", Term::RED)); 
                    validating_actions = true;

                    } else {
                        throw std::invalid_argument(ERRORS::out_range);
                    } // if & else 0 <= position <= length info list
            } catch (std::invalid_argument& e) {
                std::cout << paint(e.what(), Term::RED) << "\n";
            } // try & catch

        } while (!(validating_actions));
    } // else info_list is not empty
}// Delete a tasks

void Task_Manager::manage_task(){
    bool validating_actions = false;
    std::string               input;
    task_position           = 0;

    for (size_t i = 0; i < info_list.size(); ++i){
        std::cout << "[" << i << "]" << info_list[i]["taskName"] << "\n";
    } // for const auto& task : info_list 
    do {
        try {
            print_task(paint("- Select of these actions: ", Term::GRAY)); 
            std::cout << "  |----Are you want to get out? [y/n]: ";
            std::cin >> input;
            if (input == "y" || input == "Y") {
                validating_actions = true;
            } else {
                throw std::invalid_argument("My fellow, there is nothing to do. Did want to stay?");
            }
            
            // Developing a state manager, which works as an interface (UI), it is moved by the keybord arrows.  
        } catch (std::invalid_argument& e) {
            std::cout << paint(e.what(), Term::YELLOW) << "\n";
        }
    } while (!(validating_actions));
}

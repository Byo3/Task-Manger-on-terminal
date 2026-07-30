#include "include.hpp"
#include "task.hpp"

// Necessário para capturar o std::invalid_argument


namespace ERRORS {
    constexpr const char* not_found     = "[ERROR] This file does not exist.\n";
    constexpr const char* Invalid_input = "[Invalid] Please enter a number\n";
    constexpr const char* out_range     = "[Invalid] Your input needs to be between 1 and 4.\n";
} // namespace ERRORS

int main(){
    
    Task_Manager    manager;
    auto       print = manager.print_task;
    int    usr_input = 0;
    do { 
        print(paint("\n==Task Manager==", Term::GRAY));
        print("   [1] Create a Task:");
        print("   [2] Delete a Task:");
        print("   [3] Manage a Tasks:");
        print("   [4] Exit:");

        try {
            manager.pull_apart('=');
            std::cout << "Select of these options: ";
            std::cin >> usr_input;
            manager.pull_apart('=');

            if (std::cin.fail()) {

                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument(ERRORS::Invalid_input);
             // ! Bug, It throws an invalid input that didn't was written.

            } else if (usr_input > 4 || usr_input < 1) {    
                throw std::invalid_argument(ERRORS::out_range); 

            } else { 
            switch (usr_input) {
                    case 1:
                        manager.creating_task();
                        break;
                    case 2:
                        manager.delete_task();
                        break;
                    case 3:
                        manager.manage_task();
                        break;
                    case 4:
                        manager.pull_apart('=');
                        print("Program end. Have a good day :)");
                }// swictch cases
            }// if input >=1 && input <=4
        } catch (std::invalid_argument& e) {
            manager.pull_apart('=');
            std::cout << paint(e.what(), Term::RED) << "\n";
        } // try & catch 
    } while (usr_input != 4);
} // main func

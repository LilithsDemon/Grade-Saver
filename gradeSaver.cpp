#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <map>

void clearTerminal()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void outputMenu()
{
    std::cout << "\n+---====--Grade Menu--====---+\n";
    std::cout << "1. List Students\n";
    std::cout << "2. Add a student\n";
    std::cout << "3. List Tests\n";
    std::cout << "4. Add a test\n";
    std::cout << "5. Edit test results\n";
    std::cout << "6. Get info from Tests\n";
    std::cout << "7. Clear terminal\n";
    std::cout << "8. Quit\n";
    std::cout << "Run function: ";
}

std::vector<std::string> splitText(std::string command, std::string seperator)
{
    std::vector<std::string> commands;
    int last_stop = 0;
    std::string current_text = "";
    int current_command = 0;

    for (int i = 0; i < (command.length() - seperator.length()); i++)
    {
        current_text = command.substr(i, seperator.length());
        if(current_text == seperator)
        {
            commands.push_back(command.substr(last_stop, i - last_stop));
            current_command++;
            last_stop = i+seperator.length();
        }
    }
    commands.push_back(command.substr(last_stop));
    if (commands.size() == 0)
    {
        commands.push_back(command);
    }
    
    return commands;
}

void readFromFile(std::map<std::string, std::map<std::string, int>> &student_data, std::vector<std::string> &tests)
{
    std::ifstream file("data.grades");
    std::vector<std::string> students;
    std::string current_text;
    while (getline(file, current_text))
    {
        students.push_back(current_text);
    }
    std::vector<std::vector<std::string>> file_lines;
    std::vector<std::string> broken_down_student;
    for (int i = 0; i < students.size(); i++) 
    {
        broken_down_student = splitText(students[i], ",");
        file_lines.push_back(broken_down_student);
    }
    std::map<std::string, int> test_data;
    for (int i = 0; i < file_lines.size(); i++)
    {
        for(int j = 1;  j < file_lines[0].size(); j++)
        {
            if(file_lines[i][j] != "")
            {
                
                test_data.insert({splitText(file_lines[i][j], ":")[0], std::stoi(splitText(file_lines[i][j], ":")[1])});
                if (i == 0) {tests.push_back(splitText(file_lines[i][j], ":")[0]);}
            }
            student_data.insert({file_lines[i][0], test_data});
            test_data.clear();
        }
    }
    file.close();
}

void writeToFile(std::map<std::string, std::map<std::string, int>> &student_data)
{
    std::string text_to_save = "";
    std::ofstream file("data.grades");
    
    for(auto student : student_data)
    {
        text_to_save += student.first + ",";
        for(auto test : student.second)
        {  
            text_to_save += test.first + ":" + std::to_string(test.second) + ",";
        }
        text_to_save += "\n";
    }

    file << text_to_save;
    file.close();
}


int main()
{
    std::map<std::string, std::map<std::string, int>> student_data;
    std::vector<std::string> tests;
    readFromFile(student_data, tests);

    int user_input = 0;
    
    while(true)
    {
        outputMenu();
        std::cin >> user_input;

        switch (user_input)
        {
            case 1:
            {
                int count = 0;
                for(auto student : student_data)
                {
                    std::cout << count+1 << ": " << student.first;
                    if (student.second.size() > 0)
                    {
                        float average_score = 0;
                        int total_score = 0;

                        for (auto test : student.second)
                        {
                            total_score += test.second;
                        }
                        average_score = total_score / student.second.size();
                        std:: cout << ": Average score: " << average_score << "%";
                    }
                    count++;
                    std::cout << "\n";
                }
                break;
            }
            case 2:
            {
                std::string student_name = "";
                std::cout << "\nEnter new Students name: ";
                std::cin.ignore();
                std::getline(std::cin, student_name);
                std::map<std::string, int> test_data;
                if (tests.size() > 0)
                {
                    for (int i = 0; i < tests.size(); i++)
                    {
                        test_data.insert({tests[i], 0});
                    }
                }
                student_data.insert({student_name, test_data});
                break;
            }
            case 3:
            {
                int count = 0;
                for (auto test : tests)
                {
                    count += 1;
                    std::cout << "\n" << count << ": " << test;
                }
                if (count == 0)
                {
                    std::cout << "\nThere are no tests initialized yet\n";
                }
                break;
            }
            case 4:
            {
                std::string test_name;
                std::cout << "\nTest name to add: ";
                std::cin.ignore();
                std::getline(std::cin, test_name);
                tests.push_back(test_name);
                for (auto student:student_data)
                {
                    student.second.insert({test_name, 0});
                }
                break;
            }
            case 5:
            { 
                if(tests.size() == 0)
                {
                    std::cout << "\nThere are no tests initialized yet\n";
                    break;
                }
                if(student_data.size() == 0)
                {
                    std::cout << "\nThere are no students initialized yet\n";
                    break;
                }
                std::cout << "\n__Test Names__\n";
                for (auto test : tests)
                {
                    std::cout << test << "\n";
                }
                while (true)
                {
                    std::cout << "Enter name of test you want to get result from: ";
                    std::string name_of_test = "";
                    std::cin.ignore();
                    std::getline(std::cin, name_of_test);
                    bool test_found = false;
                    for (auto test : tests)
                    {
                        if(name_of_test == test)
                        {
                            test_found = true;
                        }
                    }
                    if (test_found == true)
                    {          
                        while(true)
                        {
                            std::string test_change;
                            std::cout << "\n";
                            for (auto student : student_data)
                            {
                                std::cout << student.first << ": : " << student.second[name_of_test] << "%\n";
                            }
                            std::cout << "\nEnter students name to edit score or q to quit: ";
                            std::getline(std::cin, test_change);
                            if (test_change == "q" || test_change == "quit")
                            {
                                break;
                            }
                            else 
                            {
                                bool valid_student = false;
                                for (auto student : student_data)
                                {
                                    if (test_change == student.first)
                                    {
                                        valid_student=true;
                                    }
                                }
                                if (valid_student == false)
                                {
                                    std::cout << "\nThat is not a valid student\n";
                                }
                                else
                                {
                                    std::cout << "What was " << test_change << "'s score: ";
                                    std::string new_val = "0";
                                    std::getline(std::cin, new_val);
                                    student_data[test_change][name_of_test] = stoi(new_val);                               }
                            }
                        }
                    }
                    else
                    {
                        std::cout << "\nThat test does not exist ... please re-enter\n";
                    }
                    break;
                }
                break;
            }
            case 6:
            {
                if(tests.size() == 0)
                {
                    std::cout << "\nThere are no tests initialized yet\n";
                    break;
                }
                if(student_data.size() == 0)
                {
                    std::cout << "\nThere are no students initialized yet\n";
                    break;
                }
                std::cout << "\n__Test Names__\n";
                for (auto test : tests)
                {
                    std::cout << test << "\n";
                }
                while (true)
                {
                    std::cout << "Enter name of test you want to get result from: ";
                    std::string name_of_test = "";
                    std::cin.ignore();
                    std::getline(std::cin, name_of_test);
                    bool found_test = false;
                    for (auto test : tests)
                    {
                        if(name_of_test == test)
                        {
                            found_test = true;
                        }
                    }
                    if (found_test == true)
                    {
                        std::cout << "\n";
                        int total_score = 0;
                        int best_score = 0;
                        int worst_score = 100;
                        for (auto student : student_data)
                        {
                            std::cout << student.first << ": : " << student.second[name_of_test] << "%\n";
                            total_score += student.second[name_of_test];
                            if (student.second[name_of_test] > best_score)
                            {
                                best_score = student.second[name_of_test];
                            }
                            if (student.second[name_of_test] < worst_score)
                            {
                                worst_score = student.second[name_of_test];
                            }
                        }
                        std::cout << "\nAverage Score is " << total_score/student_data.size() << "%";
                        std::cout << "\nTop Score is " << best_score << "%";
                        std::cout << "\nWort Score is " << worst_score << "%";
                    }
                    else
                    {
                        std::cout << "\nThat test does not exist ... please re-enter\n";
                    }
                    break;
                }
                break;
            }
            case 7:
            {
                clearTerminal();
                break;
            }
            case 8:
            {
                clearTerminal(); 
                writeToFile(student_data);
                exit(0);
            }
        }
    }
}

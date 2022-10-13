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

void readFromFile()
{
    //This will be reading from from the file
    std::ifstream file("data.grades");
    std::vector<std::string> student_data;
    std::string currentText;
    while (getline(file, currentText))
    {
        student_data.pushback(currentText);
    }
    file.close();
}

void writeToFile()
{
    //This will be exporting to file
}


int main()
{
	std::vector<std::string> students;
    std::vector<std::map<std::string, int>> test_scores;
    std::map<std::string, int> test_names;
   
    int user_input = 0;
    
    while(true)
    {
        outputMenu();
        std::cin >> user_input;

        switch (user_input)
        {
            case 1:
                {
                    for(int i=0; i < students.size(); i++)
                    {
                        if (test_scores.size() > 0)
                        {
                            int overall_score = 0;
                            for (int j = 0; j < test_scores.size(); j++)
                            {
                                overall_score += test_scores[j][students[i]];
                            }
                            int average_score = overall_score / test_scores.size();
                            std::cout << "\n" << i+1 << ": " << students[i] << ": Average Score: " << average_score << "%\n";
                        }
                        else
                        {
                            std::cout << "\n" << i+1 << ": " << students[i] << "\n"; 
                        }
                    }
                    if (students.size() == 0)
                    {
                        std::cout << "\nThere are no students initialized yet\n";
                    }
                    break;
                }
            case 2:
                {
                    std::string student_name = "";
                    std::cout << "\nEnter new Students name: ";
                    std::cin.ignore();
                    std::getline(std::cin, student_name);
                    students.push_back(student_name);
                    for (int i = 0; i < test_scores.size(); i++)
                    {
                        test_scores[i].insert({student_name, 0});
                    }
                    break;
                }
            case 3:
                {
                    int count = 0;
                    for (auto test : test_names)
                    {
                        count += 1;
                        std::cout << "\n" << count << ": " << test.first;
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
                    test_names.insert({test_name, test_scores.size()});
                    std::map<std::string, int> students_blank;
                    for (int i = 0; i < students.size(); i++)
                    {
                        students_blank.insert({students[i], 0});
                    }
                    test_scores.push_back(students_blank);
                    break;
                }
            case 5:
                {
                    if(test_scores.size() == 0)
                    {
                        std::cout << "\nThere are no tests initialized yet\n";
                        break;
                    }
                    if(students.size() == 0)
                    {
                        std::cout << "\nThere are no students initialized yet\n";
                        break;
                    }
                    std::cout << "\n__Test Names__\n";
                    for (auto test : test_names)
                    {
                        std::cout << test.first << "\n";
                    }
                    while (true)
                    {
                        std::cout << "Enter name of test you want to get result from: ";
                        std::string name_of_test = "";
                        std::cin.ignore();
                        std::getline(std::cin, name_of_test);
                        int test_num = INT_MAX;
                        for (auto test : test_names)
                        {
                            if(name_of_test == test.first)
                            {
                                test_num = test.second;
                            }
                        }
                        if (test_num != INT_MAX)
                        {          
                            while(true)
                            {
                                std::string test_change;
                                std::cout << "\n";
                                for (auto test : test_scores[test_num])
                                {
                                    std::cout << test.first << ": : " << test.second << "%\n";
                                }
                                std::cout << "\nEnter students name to edit score or q to quit: ";
                                std::getline(std::cin, test_change);;
                                if (test_change == "q" || test_change == "quit")
                                {
                                    break;
                                }
                                else 
                                {
                                    bool valid_student = false;
                                    for (auto student : test_scores[test_num])
                                    {
                                        if (test_change == student.first)
                                        {
                                            int score = 0;
                                            std::cout << "\nWhat is their score: ";
                                            std::cin >> score;
                                            test_scores[test_num][test_change] = score;
                                            valid_student=true;
                                        }
                                    }
                                    if (valid_student == false)
                                    {
                                        std::cout << "\nThat is not a valid student\n";
                                    }
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
                    if(test_scores.size() == 0)
                    {
                        std::cout << "\nThere are no tests initialized yet\n";
                        break;
                    }
                    if(students.size() == 0)
                    {
                        std::cout << "\nThere are no students initialized yet\n";
                        break;
                    }
                    std::cout << "\n__Test Names__\n";
                    for (auto test : test_names)
                    {
                        std::cout << test.first << "\n";
                    }
                    while (true)
                    {
                        std::cout << "Enter name of test you want to get result from: ";
                        std::string name_of_test = "";
                        std::cin.ignore();
                        std::getline(std::cin, name_of_test);
                        int test_num = INT_MAX;
                        for (auto test : test_names)
                        {
                            if(name_of_test == test.first)
                            {
                                test_num = test.second;
                            }
                        }
                        if (test_num != INT_MAX)
                        {
                            std::cout << "\n";
                            for (auto test : test_scores[test_num])
                            {
                                std::cout << test.first << ": : " << test.second << "%\n";
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
            case 7:
                {
                    clearTerminal();
                    break;
                }
            case 8:
                {
                    clearTerminal();                    
                    exit(0);
                }
        }

    }
}

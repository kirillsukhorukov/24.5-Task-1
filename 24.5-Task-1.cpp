#include <iostream>
#include <string>
#include <ctime>

//Функция вывода приветствия
void hello()
{
std::cout << "----- Hello! Welcome to the 'Time tracking' program. -----" << std::endl << std::endl;
std::cout << " - Enter 'begin' to start tracking a new task." << std::endl;
std::cout << " - Enter 'end' to end tracking of the current task." << std::endl;
std::cout << " - Enter 'status' to display completed tasks." << std::endl;
std::cout << " - Enter 'exit' to exit the program." << std::endl << std::endl;
return;
}

//Функция ввода запроса и определение его типа
int req_input()
{
    std::string str;
    bool error = false;
    do
    {
        //Сброс ошибки
        error = false;

        //Ввод строки с запросом
        std::cout << "Please enter your request: ";
        std::getline(std::cin, str);

        //Проверка запроса на отслеживание новой задачи
        if (str == "begin") return 1;
        
        //Проверка запроса на окончание отслеживания текущей задачи
        else if (str == "end") return 2;

        //Проверка запроса на вывод на экран информации о всех законченных задачах и времени, которое было на них потрачено.
        else if (str == "status") return 3;        
        
        //Проверка запроса на выход из программы
        if (str == "exit") return 4;
       
        else
        {
            error = true;
            std::cerr << "Invalid reqest! Reenter your request." << std::endl;
        }
    } while (error);

    return 0;
}

//Функция начала отслеживания новой задачи
std::time_t begin(std::string &taskName)
{
    //Ввод строки с запросом
    std::cout << "Please enter a task name: ";
    std::getline(std::cin, taskName);

    std::time_t curTime=std::time(nullptr);
    std::cout << curTime << " " << taskName << std::endl;
    return curTime;
}

//Функция окончания отслеживания текущей задачи
void end(const std::time_t &tBegin, const std::string &taskName)
{
    std::cout << "OK" << std::endl;
    std::cout << tBegin << " " << taskName << std::endl;
}

//Функция вывода на экран информации о всех законченных задачах и времени, которое было на них потрачено.
void status(const std::string &taskName)
{
    std::cout << "Current task: " << taskName << std::endl;
}

int main()
{
    hello();

    int reqType = 0; //Переменная с кодом запроса
    std::string taskName; //Строка с именем задания
    bool taskStart = false; //Флаг наличия текущей задачи
    std::time_t tBegin;

    do
    {
        reqType = req_input();
        if (reqType == 1)
        {
            if (taskStart)
            {
                end(tBegin,taskName);
                taskStart = false;
            } 
            tBegin = begin(taskName);
            taskStart = true;
        } 
        if (reqType == 2 && taskStart) 
        {
            end(tBegin,taskName);
            taskStart = false;
        }
        if (reqType == 3) 
        {
            (taskStart)? status(taskName): status("NO TASKS");
        }
    } while (reqType!=4);
    
    std::cout << std::endl << "Program completed. Press any key...";
    std::cin.get();

    return 0;
}
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
std::string begin()
{

}

//Функция окончания отслеживания текущей задачи
void end()
{

}

//Функция вывода на экран информации о всех законченных задачах и времени, которое было на них потрачено.
void status()
{

}

int main()
{
    hello();

    int reqType = 0; //Переменная с кодом запроса
    std::string taskName; //Строка с именем задания
    bool taskStart = false;

    do
    {
        reqType = req_input();
        if (reqType == 1)
        {
            if (taskStart)
            {
                end();
                taskStart = false;
            } 
            taskName = begin();
        } 
        if (reqType == 2 && taskStart) 
        {
            end();
            taskStart = false;
        }
        if (reqType == 3) status ();
    } while (reqType!=4);
    
    std::cout << std::endl << "Program completed. Press any key...";
    std::cin.get();

    return 0;
}
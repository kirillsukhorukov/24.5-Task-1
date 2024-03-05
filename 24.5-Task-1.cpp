#include <iostream>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

//Имя файла для сохранения данных
const std::string FILE_NAME = "TimeTracking.bin";

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

//Функция создания файла с данными
void createFile()
{
    std::ifstream file(FILE_NAME, std::ios::binary);
    if (!file.is_open())
    {
        std::ofstream file(FILE_NAME, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error create file\n";
            exit(1);
        }
        file.close();
    }
    file.close();

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
    //Взятие времени начала задачи
    std::time_t curTime=std::time(nullptr);
    return curTime;
}

//Функция окончания отслеживания текущей задачи
void end(const std::time_t &tBegin, const std::string &taskName)
{
    //Взятие времени окнчания задачи и определение разницы
    std::time_t tEnd=std::time(nullptr);
    double taskTime = difftime(tEnd, tBegin);

    //Находим количество часов минут и секунд потраченных на задание
    int HH = (int)taskTime/3600;
    int MM = (int)(taskTime-HH*3600)/60;
    int SS = taskTime-HH*3600-MM*60;

    //Открытие файла для записи
    std::ofstream file(FILE_NAME, std::ios::binary | std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "File " << FILE_NAME << " is not open!\n" << std::endl;
        return;
    }
    //Запись в файл
    int len = taskName.length();
    file.write((char*)&len, sizeof(len));
    file.write(taskName.c_str(), len);
    file.write((char*)&HH, sizeof(int));
    file.write((char*)&MM, sizeof(int));
    file.write((char*)&SS, sizeof(int));
    //Закрытие файла
    file.close();
}

//Функция вывода на экран информации о всех законченных задачах и времени, которое было на них потрачено.
void status(const std::string &taskName)
{
    
    std::cout << "----------------------------" << std::endl;
    //Открытие файла
    std::ifstream file(FILE_NAME, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "File " << FILE_NAME << " is not open!\n" << std::endl;
        return;
    }
    
    //Заплатка для корректной работы чтения из файла
    file.seekg(0, std::ios::end);
    int fsize = file.tellg();
    file.seekg(0);
    //Чтение и вывод информации из файла
    while (file.tellg()<fsize)
    {
        std::string name;
        int len, HH, MM, SS;
        file.read((char*)&len, sizeof(int));
        name.resize(len);
        file.read((char*)name.c_str(), len);
        file.read((char*)&HH, sizeof(int));
        file.read((char*)&MM, sizeof(int));
        file.read((char*)&SS, sizeof(int));
        std::cout << name << ":-> " << HH << " hour " << MM << " min "<< SS << " sec " << std::endl;
    }
    
    //Закрытие файла    
    file.close();
    
    std::cout << "----------------------------" << std::endl;
    
    //Вывод названия текущей задачи
    std::cout << "Current task: " << taskName << std::endl;
    
    std::cout << "----------------------------" << std::endl;
}

int main()
{
    //Вывод приветствия
    hello();

    //Создание или проверка наличия файла для сохранения данных
    createFile();

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
            (taskStart)? status(taskName): status("- NO TASKS -");
        }
    } while (reqType!=4);
    
    std::cout << std::endl << "Program completed. Press any key...";
    std::cin.get();

    return 0;
}
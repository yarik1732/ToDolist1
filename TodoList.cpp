#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Task {
    string title;
    string date;
    int priority;
    bool completed;
    bool favorite;
    string description;
};
// Функция для сортировки задач по приоритету
void sortTasksPriority(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task& task1, const Task& task2) {
        return task1.priority < task2.priority;
        });
    cout << "Задачи отсортированы по приоритету!" << endl;
}

// Функция для сортировки задач по дате
void sortTasksDate(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), [](const Task& task1, const Task& task2) {
        return task1.date < task2.date;
        });
    cout << "Задачи отсортированы по дате!" << endl;
}
// Функция для разделения строки по разделителю
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Функция для сохранения списка задач в файл
// Функция для сохранения списка задач в файл
void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream myfile;
    myfile.open("tasks.csv");
    for (const Task& task : tasks) {
        myfile << task.title << ", " << task.date << ", " << task.priority << ", " << task.completed << ", " << task.favorite << ", " << task.description << '\n';
    }
    cout << "всё кайф: " << filename << endl;
}

// Функция для загрузки списка задач из файла
vector<Task> loadTasksFromFile(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> taskData = splitString(line, ', ');
            if (taskData.size() == 6) {
                Task task;
                task.title = taskData[0];
                task.date = taskData[1];
                task.priority = std::stoi(taskData[2]);
                task.completed = (taskData[3] == "1");
                task.favorite = (taskData[4] == "1");
                task.description = taskData[5];
                tasks.push_back(task);
            }
        }
        file.close();
        cout << "Список задач загружен из файла: " << filename << endl;
    }
    else {
        cout << "Не удалось загрузить список задач из файла: " << filename << endl;
    }
    return tasks;
}

// Функция для добавления новой задачи
void addTask(vector<Task>& tasks) {
    Task task;
    cout << "Введите название задачи: ";
    getline(cin, task.title);
    cout << "Введите дату задачи: ";
    getline(cin, task.date);
    cout << "Введите приоритет задачи (от 1 до 5): ";
    cin >> task.priority;
    cin.ignore();
    cout << "Задача выполнена (1 - да, 0 - нет): ";
    cin >> task.completed;
    cin.ignore();
    cout << "Задача избранная (1 - да, 0 - нет): ";
    cin >> task.favorite;
    cin.ignore();
    cout << "Введите информацию о задаче: ";
    getline(std::cin, task.description);
    tasks.push_back(task);
    cout << "Задача добавлена!" << endl;
}

// Функция для вывода списка задач
void printTasks(const vector<Task>& tasks) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        cout << "[" << (i + 1) << "] ";
        cout << "Название: " << task.title << " | ";
        cout << "Дата: " << task.date << " | ";
        cout << "Приоритет: " << task.priority << " | ";
        cout << "Выполнена: " << (task.completed ? "Да" : "Нет") << " | ";
        cout << "Избранная: " << (task.favorite ? "Да" : "Нет") << " | ";
        cout << "Описание: " << task.description << endl;
    }
}

// Функция для отметки задачи как выполненной
void markTaskAsCompleted(vector<Task>& tasks) {
    int taskId;
    cout << "Введите номер задачи, которую хотите отметить как выполненную: ";
    cin >> taskId;
    cin.ignore();
    if (taskId >= 1 && taskId <= tasks.size()) {
        Task& task = tasks[taskId - 1];
        task.completed = true;
        cout << "Задача отмечена как выполненная!" << endl;
    }
    else {
        cout << "Задача с указанным номером не найдена." << endl;
    }
}

// Функция для отображения выполненных задач
void printCompletedTasks(const vector<Task>& tasks) {
    for (const Task& task : tasks) {
        if (task.completed) {
            cout << "Название: " << task.title << " | ";
            cout << "Дата: " << task.date << " | ";
            cout << "Приоритет: " << task.priority << " | ";
            cout << "Избранная: " << (task.favorite ? "Да" : "Нет") << " | ";
            cout << "Описание: " << task.description << std::endl;
        }
    }
}

// Функция для отображения невыполненных задач
void printIncompleteTasks(const vector<Task>& tasks) {
    for (const Task& task : tasks) {
        if (!task.completed) {
            cout << "Название: " << task.title << " | ";
            cout << "Дата: " << task.date << " | ";
            cout << "Приоритет: " << task.priority << " | ";
            cout << "Избранная: " << (task.favorite ? "Да" : "Нет") << " | ";
            cout << "Описание: " << task.description << endl;
        }
    }
}
// Функция для отображения избранных задач
void printFavoriteTasks(const vector<Task>& tasks) {
    for (const Task& task : tasks) {
        if (task.favorite) {
            cout << "Название: " << task.title << " | ";
            cout << "Дата: " << task.date << " | ";
            cout << "Приоритет: " << task.priority << " | ";
            cout << "Избранная: " << (task.favorite ? "Да" : "Нет") << " | ";
            cout << "Описание: " << task.description << endl;
        }
    }
}
int main() {
    setlocale(LC_ALL, "rus");
    vector<Task> tasks;
    string filename = "tasks.csv";
    tasks = loadTasksFromFile(filename);
    while (true) {
        cout << "\n===== Microsoft To-Do =====" << endl;
        cout << "1. Добавить задачу" << endl;
        cout << "2. Показать список задач" << endl;
        cout << "3. Отметить задачу как выполненную" << endl;
        cout << "4. Показать выполненные задачи" << endl;
        cout << "5. Показать невыполненные задачи" << endl;
        cout << "6. Отсортировать задачи по дате" << endl;
        cout << "7. Отсортировать задачи по приоритету" << endl;
        cout << "8. Показать избранные задачи" << endl;
        cout << "0. Выйти" << endl;
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 0:
            saveTasksToFile(tasks, filename);
            return 0;
        case 1:
            addTask(tasks);
            saveTasksToFile(tasks, filename);
            break;
        case 2:
            printTasks(tasks);
            break;
        case 3:
            markTaskAsCompleted(tasks);
            saveTasksToFile(tasks, filename);
            break;

        case 4:
            printCompletedTasks(tasks);
            break;
        case 5:
            printIncompleteTasks(tasks);
            break;
        case 6:
            sortTasksDate(tasks);
            saveTasksToFile(tasks, filename);
            break;
        case 7:
            sortTasksPriority(tasks);
            saveTasksToFile(tasks, filename);
            break;
        case 8:
            printFavoriteTasks(tasks);
            break;
        default:
            cout << "Некорректный выбор. Пожалуйста, выберите существующую опцию." << endl;
            break;
        }
    }
}
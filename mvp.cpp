#include <iostream>
#include <vector>
#include <string>
#include <limits> 

struct Set {
    int weight; // его надо в double
    int reps;
};

struct Exercise {
    std::string name;
    std::vector<Set> sets;
    std::string comment;
};

struct Workout {
    std::string date;
    std::string type;
    std::vector<Exercise> exercises;
    std::string comment;
};

void showMenu() {
    std::cout << "\n================================\n";
    std::cout << "       ТРЕКЕР ТРЕНИРОВОК\n";
    std::cout << "================================\n";
    std::cout << "\n1. Создать тренировку\n2. Показать тренировки\n3. Посмотреть тренировку\n4. Удалить тренировку\n5. Выход\n";
    std::cout << "\nВыберите опцию (введите число):\n> ";
}

void showWorkouts(std::vector<Workout>& workouts) {

    std::cout << "\nСписок тренировок:\n";
    std::cout << "Дата         |   Тип тренировки\n"; // табуирование красивое сделать
    
    for (int i = 0; i < workouts.size(); ++i) {
        std::cout << i + 1 << ". " << workouts[i].date << " | " << workouts[i].type << '\n';
    }
}


int check(int beginV, int endV) {
    
    int input;

    while (true) {
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Это не число. Попробуйте еще раз: ";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input >= beginV && input <= endV) {
            return input; 
        }

        std::cout << "\nВведено значение за пределами диапазона! Попробуйте ещё раз\n > ";
    }
}


Exercise addExersise() { // вот тут тоже вдруг не int вводятся
    Exercise ex;

    std::cout << "================================\n";
    std::cout << "НОВОЕ УПРАЖНЕНИЕ\n";

    std::string name;
    std::cout << "\nВведите название упражнения:\n> "; // выберите
    std::getline(std::cin, ex.name);

    
    std::cout << "\nВведите количество подходов (от 1 до 100):\n> ";
    int n_sets = check(1, 100);

    std::vector<Set> sets;

    for (int i = 0; i < n_sets; ++i) {
        Set set;

        std::cout << "\n" << i + 1 << " подход: введите вес (кг) (от 0 до 100) \n> ";
        int weight = check(0, 100);
        set.weight = weight;

        std::cout << "\n" << i + 1 << " подход: введите кол-во повторов (от 1 до 100) \n> ";
        int reps = check(1, 100);
        set.reps = reps;

        sets.push_back(set);
    }
    ex.sets = sets;

    std::string comment;
    std::cout << "\nКомментарий к упражнению:\n> ";
    std::getline(std::cin, ex.comment);

    return ex;
}

Workout addWorkout() {
    Workout w;
    std::cout << "\n================================\n";
    std::cout << "НОВАЯ ТРЕНИРОВКА\n";

    std::string date;
    std::cout << "\nВведите дату тренировки (DD.MM.YYYY):\n> "; //формат
    std::getline(std::cin, w.date);

    std::string type;
    std::cout << "\nВведите тип тренировки:\n> "; // выберите
    std::getline(std::cin, w.type);

    std::vector<Exercise> exercises;

    std::cout << "\nДобавления упражнений в этой тренировке:\n"; 

    while (true) {
        Exercise ex = addExersise();
        exercises.push_back(ex);

        std::cout << "\nДобавить ещё одно упражнение? 1 - да, 0 - нет:\n> ";
        int choice2 = check(0, 1);

        if (choice2 == 0) {
            break;
        }
    }
    w.exercises = exercises;

    std::string comment;
    std::cout << "\nКомментарий к тренировке:\n> ";
    std::getline(std::cin, w.comment);

    return w;
}

int main() {

    std::vector<Workout> workouts;

    showMenu();

    int choice = check(1, 5);

    while (choice != 5) {
        switch (choice) {
        case 1: { // create workout
            Workout w = addWorkout();
            workouts.push_back(w);
            std::cout << "\nТренировка записана!\n";
            break;
        } 
            
        case 2: { // посмотреть список тренировок

            if (!workouts.empty()) {
                showWorkouts(workouts);
            } else {
                std::cout << "\nПока тренировок нет.\n";
            }
            
            break;
        } 

        case 3: { // открыть конуретную тренировку

            if (!workouts.empty()) {
                showWorkouts(workouts);

                std::cout << "\nВведите номер тренировки для просмотра:\n> ";
                int ind = check(1, workouts.size());

                std::cout << workouts[ind - 1].date << " | " << workouts[ind - 1].type << '\n';
                std::cout << "Упражнения в этой тренировке:\n";
                std::cout << "Название     |  Комментарий:\n";
                for (Exercise ex: workouts[ind - 1].exercises) {
                    std::cout << ex.name << " | " << ex.comment << '\n';
                    for (Set s: ex.sets) {
                        std::cout << "Вес: " << s.weight << " кг, Повторов: " << s.reps << '\n';
                    }
                }    
            } else {
                std::cout << "\nПока тренировок нет.\n";
            }
    
            break;
        } 

        case 4: { // удалить тренировку
            if (!workouts.empty()) {
                showWorkouts(workouts);
                std::cout << "\nВведите номер тренировки для удаления:\n> ";
                int ind = check(1, workouts.size());

                workouts.erase(workouts.begin() + ind - 1);
                std::cout << "\nТренировка удалена!\n";
                
            } else {
                std::cout << "\nПока тренировок нет.\n";
            }
            break;
        }

        }
        showMenu();
        choice = check(1, 5);
    }

    std::cout << "Выход из программы...";

    return 0;
}
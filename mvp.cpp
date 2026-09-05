#include <iostream>
#include <vector>
#include <string>
#include <limits> 


// MODEL

struct Set {
    int weight; // его надо в double
    int reps;
};
// нужна ли ваще эта функция
Set addSet(int weight, int reps) {
    Set s;
    s.weight = weight;
    s.reps = reps;
    return s;
}

class Exercise {
public:
    Exercise(const std::string& name, const std::string& comment = "")
        : m_name(name), m_comment(comment) {}

    void addSet(const Set& set) {
        m_sets.push_back(set);
    }
    
    const std::string& getName() const { return m_name; }
    const std::vector<Set>& getSets() const { return m_sets; }
    const std::string& getComm() const { return m_comment; }

private:
    std::string m_name;
    std::vector<Set> m_sets;
    std::string m_comment;

};

class Workout {
public:
    Workout(const std::string& date, const std::string& type, const std::string& comment = "") 
        : m_date(date), m_type(type), m_comment(comment) {}

    void addExersice(const Exercise& ex) {
        m_exercises.push_back(ex);
    }

    const std::string& getDate() const { return m_date; }
    const std::string& getType() const { return m_type; }
    const std::vector<Exercise>& getExersices() const { return m_exercises; }
    const std::string& getComm() const { return m_comment; }

private:
    std::string m_date;
    std::string m_type;
    std::vector<Exercise> m_exercises;
    std::string m_comment;

};

class WorkoutManager {
public:
    WorkoutManager() {}

    void addWorkout(const Workout& w) {
        m_workouts.push_back(w);
    }

    bool deleteWorkout(size_t ind) { 
        if (ind >= m_workouts.size()) {
            return false;
        }
        m_workouts.erase(m_workouts.begin() + ind);
        return true;
    }

    const std::vector<Workout>& getWorkouts() const { return m_workouts; }
    const size_t getCount() const { return m_workouts.size(); }
    // методы подгрузки базы данных

private:
    std::vector<Workout> m_workouts;

};

// VIEW

void showMenu() {
    std::cout << "\n================================\n";
    std::cout << "       ТРЕКЕР ТРЕНИРОВОК\n";
    std::cout << "================================\n";
    std::cout << "\n1. Создать тренировку\n2. Показать тренировки\n3. Посмотреть тренировку\n4. Удалить тренировку\n5. Выход\n";
    std::cout << "\nВыберите опцию (введите число):\n> ";
}

void showWorkouts(WorkoutManager& manager) {
    const auto& workouts = manager.getWorkouts();
    std::cout << "\nСписок тренировок:\n";
    std::cout << "Дата         |   Тип тренировки\n"; // табуирование красивое сделать
    
    for (int i = 0; i < workouts.size(); ++i) {
        std::cout << i + 1 << ". " << workouts[i].getDate() << " | " << workouts[i].getType() << '\n';
    }
}

// CONTROLLER

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

Set promptSet() {
    std::cout << "\nВведите вес (кг) (от 0 до 100) \n> ";
    int weight = check(0, 100);
    std::cout << "\nВведите кол-во повторов (от 1 до 100) \n> ";
    int reps = check(1, 100);
    return Set({weight, reps});
}

Exercise promptExercise() { // вот тут тоже вдруг не int вводятся
    std::cout << "================================\n";
    std::cout << "НОВОЕ УПРАЖНЕНИЕ\n";

    std::string name;
    std::cout << "\nВведите название упражнения:\n> "; // выберите
    std::getline(std::cin, name);

    std::string comment; // как его добавить!
    std::cout << "\nКомментарий к упражнению:\n> ";
    std::getline(std::cin, comment);

    Exercise ex(name, comment); // мб лучше потом добавлять коммент
    
    std::cout << "\nВведите количество подходов (от 1 до 100):\n> ";
    int n_sets = check(1, 100);

    for (int i = 0; i < n_sets; ++i) {
        std::cout << "\n" << i + 1 << " подход:";
        ex.addSet(promptSet());
    }

    return ex;
}

Workout promptWorkout() {
    std::cout << "\n================================\n";
    std::cout << "НОВАЯ ТРЕНИРОВКА\n";

    std::string date;
    std::cout << "\nВведите дату тренировки (DD.MM.YYYY):\n> "; //формат
    std::getline(std::cin, date);

    std::string type;
    std::cout << "\nВведите тип тренировки:\n> "; // выберите
    std::getline(std::cin, type);

    std::string comment;
    std::cout << "\nКомментарий к тренировке:\n> ";
    std::getline(std::cin, comment);

    Workout w(date, type, comment);

    std::cout << "\nДобавления упражнений в этой тренировке:\n"; 

    while (true) {
        w.addExersice(promptExercise());
        std::cout << "\nДобавить ещё одно упражнение? 1 - да, 0 - нет:\n> ";
        int choice2 = check(0, 1);

        if (choice2 == 0) {
            break;
        }
    }

    return w;
}

int main() {

    WorkoutManager manager;

    showMenu();

    int choice = check(1, 5);

    while (choice != 5) {
        switch (choice) {
        case 1: { // create workout
            manager.addWorkout(promptWorkout());
            std::cout << "\nТренировка записана!\n";
            break;
        } 
            
        case 2: { // посмотреть список тренировок

            if (manager.getCount() != 0) {
                showWorkouts(manager);
            } else {
                std::cout << "\nПока тренировок нет.\n";
            }
            break;
        } 

        case 3: { // открыть конуретную тренировку
            if (manager.getCount() != 0) {
                showWorkouts(manager);

                std::cout << "\nВведите номер тренировки для просмотра:\n> ";
                int ind = check(1, manager.getCount());
                Workout w = manager.getWorkouts()[ind - 1];
                std::cout << w.getDate() << " | " << w.getType() << '\n';
                std::cout << "Упражнения в этой тренировке:\n";
                std::cout << "Название     |  Комментарий:\n";
                for (Exercise ex: w.getExersices()) {
                    std::cout << ex.getName() << " | " << ex.getComm() << '\n';
                    for (Set s: ex.getSets()) {
                        std::cout << "Вес: " << s.weight << " кг, Повторов: " << s.reps << '\n';
                    }
                }    
            } else {
                std::cout << "\nПока тренировок нет.\n";
            }
    
            break;
        } 

        case 4: { // удалить тренировку
            if (manager.getCount() != 0) {
                showWorkouts(manager);
                std::cout << "\nВведите номер тренировки для удаления:\n> ";
                int ind = check(1, manager.getCount());
                manager.deleteWorkout(ind - 1);
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
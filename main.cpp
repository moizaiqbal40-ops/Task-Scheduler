#include "Task.h"
#include "UrgentTask.h"
#include "PersonalTask.h"
#include "Scheduler.h"
#include <iostream>
#include <limits>

const std::string SAVE_FILE = "tasks.txt";

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int askInt(const std::string& prompt, int lo, int hi) {
    int val;
    while (true) {
        std::cout << prompt;
        std::cin >> val;
        if (std::cin.fail() || val < lo || val > hi) {
            std::cout << "Please enter a number between " << lo << " and " << hi << ".\n";
            clearInput();
            continue;
        }
        return val;
    }
}

void addUrgentTask(Scheduler& scheduler) {
    clearInput();
    std::cout << "Task title: ";
    std::string title;
    std::getline(std::cin, title);

    int deadline = askInt("Deadline hour (0-23): ", 0, 23);
    int difficulty = askInt("Difficulty (1=Easy 2=Medium 3=Hard): ", 1, 3);
    int urgency = askInt("Urgency level (1-10): ", 1, 10);

    scheduler.addTask(new UrgentTask(title, deadline, static_cast<Difficulty>(difficulty), urgency));
    std::cout << "Urgent task added.\n";
}

void addPersonalTask(Scheduler& scheduler) {
    clearInput();
    std::cout << "Task title: ";
    std::string title;
    std::getline(std::cin, title);

    int deadline = askInt("Deadline hour (0-23): ", 0, 23);
    int difficulty = askInt("Difficulty (1=Easy 2=Medium 3=Hard): ", 1, 3);
    int pref = askInt("Best time of day (0=Morning 1=Afternoon 2=Evening): ", 0, 2);

    scheduler.addTask(new PersonalTask(title, deadline, static_cast<Difficulty>(difficulty), static_cast<TimePreference>(pref)));
    std::cout << "Personal task added.\n";
}

void printMenu() {
    std::cout << "\n========== SMART TASK SCHEDULER ==========\n";
    std::cout << "1. Add Urgent Task\n";
    std::cout << "2. Add Personal Task\n";
    std::cout << "3. View Scheduled Queue\n";
    std::cout << "4. Complete Top Priority Task\n";
    std::cout << "5. Remove Completed Tasks\n";
    std::cout << "6. Save & Exit\n";
    std::cout << "===========================================\n";
}

int main() {
    Scheduler scheduler;
    scheduler.loadFromFile(SAVE_FILE);

    bool running = true;
    while (running) {
        printMenu();
        int choice = askInt("Choose an option: ", 1, 6);

        switch (choice) {
            case 1: addUrgentTask(scheduler); break;
            case 2: addPersonalTask(scheduler); break;
            case 3: scheduler.displayQueue(); break;
            case 4: scheduler.completeTopTask(); break;
            case 5: scheduler.removeCompletedTasks(); break;
            case 6:
                scheduler.saveToFile(SAVE_FILE);
                running = false;
                break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}

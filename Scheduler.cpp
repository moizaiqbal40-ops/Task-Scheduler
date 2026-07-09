#include "Scheduler.h"
#include "UrgentTask.h"
#include "PersonalTask.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

Scheduler::~Scheduler() {
    for (Task* t : tasks) delete t;
}

void Scheduler::resortByPriority() {
    // Highest priority score first. Works for ANY Task subtype because
    // getPriorityScore() is virtual -> POLYMORPHISM in action.
    std::sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
        return a->getPriorityScore() > b->getPriorityScore();
    });
}

void Scheduler::addTask(Task* task) {
    tasks.push_back(task);
    resortByPriority();
}

void Scheduler::displayQueue() const {
    if (tasks.empty()) {
        std::cout << "No tasks scheduled.\n";
        return;
    }
    std::cout << "\n----- Scheduled Tasks (highest priority first) -----\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". ";
        tasks[i]->display();
    }
    std::cout << "------------------------------------------------------\n";
}

bool Scheduler::completeTopTask() {
    for (Task* t : tasks) {
        if (!t->getIsCompleted()) {
            t->markCompleted();
            std::cout << "Completed: " << t->getTitle() << "\n";
            return true;
        }
    }
    std::cout << "Nothing left to complete.\n";
    return false;
}

void Scheduler::removeCompletedTasks() {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [](Task* t) {
        if (t->getIsCompleted()) {
            delete t;
            return true;
        }
        return false;
    }), tasks.end());
}

int Scheduler::pendingCount() const {
    int count = 0;
    for (Task* t : tasks) if (!t->getIsCompleted()) count++;
    return count;
}

void Scheduler::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Could not open file for saving.\n";
        return;
    }
    for (Task* t : tasks) {
        out << t->serialize() << "\n";
    }
    out.close();
    std::cout << "Saved " << tasks.size() << " task(s) to " << filename << "\n";
}

void Scheduler::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "No existing save file found. Starting fresh.\n";
        return;
    }

    for (Task* t : tasks) delete t;
    tasks.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, title, deadlineStr, difficultyStr, completedStr, extra;

        std::getline(ss, type, '|');
        std::getline(ss, title, '|');
        std::getline(ss, deadlineStr, '|');
        std::getline(ss, difficultyStr, '|');
        std::getline(ss, completedStr, '|');
        std::getline(ss, extra, '|');

        int deadline = std::stoi(deadlineStr);
        Difficulty diff = static_cast<Difficulty>(std::stoi(difficultyStr));
        bool completed = std::stoi(completedStr);

        Task* t = nullptr;
        if (type == "URGENT") {
            int urgency = std::stoi(extra);
            t = new UrgentTask(title, deadline, diff, urgency);
        } else if (type == "PERSONAL") {
            TimePreference pref = static_cast<TimePreference>(std::stoi(extra));
            t = new PersonalTask(title, deadline, diff, pref);
        }

        if (t) {
            if (completed) t->markCompleted();
            tasks.push_back(t);
        }
    }
    resortByPriority();
    std::cout << "Loaded " << tasks.size() << " task(s) from " << filename << "\n";
}

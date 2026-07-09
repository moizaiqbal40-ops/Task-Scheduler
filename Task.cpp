#include "Task.h"

Task::Task(const std::string& title, int deadlineHour, Difficulty difficulty)
    : title(title), deadlineHour(deadlineHour), difficulty(difficulty), isCompleted(false) {}

void Task::markCompleted() {
    isCompleted = true;
}

bool Task::getIsCompleted() const {
    return isCompleted;
}

std::string Task::getTitle() const {
    return title;
}

int Task::getDeadlineHour() const {
    return deadlineHour;
}

Difficulty Task::getDifficulty() const {
    return difficulty;
}

std::string Task::serialize() const {
    // Base format: type|title|deadlineHour|difficulty|completed
    return getType() + "|" + title + "|" + std::to_string(deadlineHour) + "|" +
           std::to_string(static_cast<int>(difficulty)) + "|" + std::to_string(isCompleted);
}

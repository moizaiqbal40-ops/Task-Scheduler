#include "UrgentTask.h"
#include <iostream>

UrgentTask::UrgentTask(const std::string& title, int deadlineHour, Difficulty difficulty, int urgencyLevel)
    : Task(title, deadlineHour, difficulty), urgencyLevel(urgencyLevel) {}

int UrgentTask::getPriorityScore() const {
    // Closer deadline + higher urgency + harder task = higher score
    int deadlineFactor = 24 - deadlineHour;              // sooner deadline -> bigger number
    int difficultyFactor = static_cast<int>(difficulty);
    return (urgencyLevel * 10) + (deadlineFactor * 3) + (difficultyFactor * 2);
}

void UrgentTask::display() const {
    std::cout << "[URGENT]  " << title
              << " | Deadline: " << deadlineHour << ":00"
              << " | Urgency: " << urgencyLevel << "/10"
              << " | Score: " << getPriorityScore()
              << (isCompleted ? "  [DONE]" : "") << "\n";
}

std::string UrgentTask::getType() const {
    return "URGENT";
}

std::string UrgentTask::serialize() const {
    return Task::serialize() + "|" + std::to_string(urgencyLevel);
}

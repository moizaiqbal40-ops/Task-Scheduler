#include "PersonalTask.h"
#include <iostream>

PersonalTask::PersonalTask(const std::string& title, int deadlineHour, Difficulty difficulty, TimePreference preference)
    : Task(title, deadlineHour, difficulty), preference(preference) {}

int PersonalTask::getPriorityScore() const {
    int difficultyFactor = static_cast<int>(difficulty);
    int base = difficultyFactor * 4;

    // "Humanized" bonus: hard tasks matched to morning score highest,
    // easy tasks matched to evening score decently too.
    int bonus = 5; // default, mismatched preference
    if (difficulty == Difficulty::HARD && preference == TimePreference::MORNING) {
        bonus = 15;
    } else if (difficulty == Difficulty::MEDIUM && preference == TimePreference::AFTERNOON) {
        bonus = 10;
    } else if (difficulty == Difficulty::EASY && preference == TimePreference::EVENING) {
        bonus = 8;
    }

    int deadlineFactor = 24 - deadlineHour;
    return base + bonus + deadlineFactor;
}

void PersonalTask::display() const {
    std::cout << "[PERSONAL]" << title
              << " | Best time: " << preferenceToString(preference)
              << " | Deadline: " << deadlineHour << ":00"
              << " | Score: " << getPriorityScore()
              << (isCompleted ? "  [DONE]" : "") << "\n";
}

std::string PersonalTask::getType() const {
    return "PERSONAL";
}

TimePreference PersonalTask::getPreference() const {
    return preference;
}

std::string PersonalTask::preferenceToString(TimePreference p) {
    switch (p) {
        case TimePreference::MORNING: return "Morning";
        case TimePreference::AFTERNOON: return "Afternoon";
        case TimePreference::EVENING: return "Evening";
    }
    return "Unknown";
}

std::string PersonalTask::serialize() const {
    return Task::serialize() + "|" + std::to_string(static_cast<int>(preference));
}

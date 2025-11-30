#include "TaskManager.hpp"

#include <filesystem>
#include <iostream>
#include <limits>

namespace fs = std::filesystem;

void showMenu() {
    std::cout << "\nStudy Task Tracker\n"
              << "1) List tasks\n"
              << "2) Add task\n"
              << "3) Mark task complete\n"
              << "4) Save now\n"
              << "0) Exit\n"
              << "Choose: ";
}

void listTasks(const TaskManager& manager) {
    const auto& tasks = manager.getTasks();
    if (tasks.empty()) {
        std::cout << "No tasks yet. Add one!\n";
        return;
    }

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        const auto& task = tasks[i];
        std::cout << i + 1 << ") [" << (task.completed ? 'x' : ' ') << "] "
                  << task.title << " (due: " << task.dueDate << ")\n";
    }
}

void addTask(TaskManager& manager) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string title;
    std::string due;

    std::cout << "Task title: ";
    std::getline(std::cin, title);
    std::cout << "Due date/label (e.g., 2024-08-31 or 'next lab'): ";
    std::getline(std::cin, due);
    manager.addTask(title, due);
}

void markComplete(TaskManager& manager) {
    std::cout << "Task number to complete: ";
    std::size_t idx{};
    std::cin >> idx;
    if (manager.markTaskComplete(idx - 1)) {
        std::cout << "Great job! Task marked complete.\n";
    } else {
        std::cout << "Could not find that task.\n";
    }
}

int main() {
    const fs::path dataPath = fs::path("data") / "tasks.txt";
    std::error_code ec;
    fs::create_directories(dataPath.parent_path(), ec);

    TaskManager manager(dataPath.string());
    if (manager.loadFromDisk()) {
        std::cout << "Loaded existing tasks.\n";
    } else {
        std::cout << "Starting fresh task list.\n";
    }

    bool running = true;
    while (running) {
        showMenu();
        int choice{};
        std::cin >> choice;

        switch (choice) {
            case 1:
                listTasks(manager);
                break;
            case 2:
                addTask(manager);
                break;
            case 3:
                markComplete(manager);
                break;
            case 4:
                if (manager.saveToDisk()) {
                    std::cout << "Saved tasks.\n";
                } else {
                    std::cout << "Unable to save tasks.\n";
                }
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Unknown option.\n";
        }
    }

    if (manager.saveToDisk()) {
        std::cout << "Good luck! Tasks saved in " << dataPath << '\n';
    } else {
        std::cout << "Finished, but saving failed. Check permissions.\n";
    }
    return 0;
}

#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    // Constructor
    GameDecisionTree() : root(nullptr) {}

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        std::unordered_map<int, Node<T>*> nodes;
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        std::string line;
        // Read file line by line.
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            // Tokenize the line using the provided delimiter.
            while (std::getline(iss, token, delimiter)) {
                size_t start = token.find_first_not_of(" \t");
                size_t end = token.find_last_not_of(" \t");
                if (start != std::string::npos && end != std::string::npos)
                    token = token.substr(start, end - start + 1);
                tokens.push_back(token);
            }
            // Expecting four tokens: eventNumber, description, leftEventNumber, rightEventNumber.
            if (tokens.size() < 4) continue;
            int eventNumber = std::stoi(tokens[0]);
            std::string description = tokens[1];
            int leftEventNumber = std::stoi(tokens[2]);
            int rightEventNumber = std::stoi(tokens[3]);
            // Create the Story object and corresponding Node.
            T story(description, eventNumber, leftEventNumber, rightEventNumber);
            Node<T>* newNode = new Node<T>(story);
            nodes[eventNumber] = newNode;
        }
        inFile.close();

        // Link nodes together based on left and right event numbers.
        for (auto& pair : nodes) {
            T s = pair.second->data;
            if (s.leftEventNumber != -1 && nodes.find(s.leftEventNumber) != nodes.end())
                pair.second->left = nodes[s.leftEventNumber];
            if (s.rightEventNumber != -1 && nodes.find(s.rightEventNumber) != nodes.end())
                pair.second->right = nodes[s.rightEventNumber];
        }

        // Determine the root node:
        // The root is defined as a node that is not referenced as a child by any other node.
        std::unordered_set<int> childSet;
        for (auto& pair : nodes) {
            T s = pair.second->data;
            if (s.leftEventNumber != -1)
                childSet.insert(s.leftEventNumber);
            if (s.rightEventNumber != -1)
                childSet.insert(s.rightEventNumber);
        }
        for (auto& pair : nodes) {
            if (childSet.find(pair.first) == childSet.end()) {
                root = pair.second;
                break;
            }
        }
    }

    // Function to start the game and traverse the decision tree based on user input
    void playGame() {
        if (!root) {
            std::cout << "No game loaded." << std::endl;
            return;
        }
        Node<T>* current = root;
        while (true) {
            // Display the current event's description.
            std::cout << "\n" << current->data.description << "\n" << std::endl;

            // If the node is a leaf (no further paths), end the game.
            if (current->left == nullptr && current->right == nullptr) {
                std::cout << "The story ends here. Game over." << std::endl;
                break;
            }

            // Determine available paths
            bool hasLeft = (current->left != nullptr);
            bool hasRight = (current->right != nullptr);

            // If both options exist, prompt normally.
            if (hasLeft && hasRight) {
                std::cout << "Enter choice (1 for left, 2 for right): ";
                int choice;
                std::cin >> choice;
                if (std::cin.fail() || (choice != 1 && choice != 2)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    continue;
                }
                if (choice == 1) {
                    current = current->left;
                } else { // choice == 2
                    current = current->right;
                }
            }
            // Only left option is available.
            else if (hasLeft && !hasRight) {
                std::cout << "Only left path is available. Enter 1 to continue: ";
                int choice;
                std::cin >> choice;
                if (std::cin.fail() || choice != 1) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    continue;
                }
                current = current->left;
            }
            // Only right option is available.
            else if (!hasLeft && hasRight) {
                std::cout << "Only right path is available. Enter 2 to continue: ";
                int choice;
                std::cin >> choice;
                if (std::cin.fail() || choice != 2) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    continue;
                }
                current = current->right;
            }
        }
    }
};

#endif // GAMEDECISIONTREE_H

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jIKk4bke)
# CS210 Data Structures SP25
## Programming Assignment 2: Text-Based RPG Using Decision Trees

### **Student Name:** `Dino Mrakovic`
### **Student ID:** `5550136813`

---

## **1. Project Overview**
(Provide a brief summary of your RPG game. Describe how it uses a decision tree and how the player interacts with it.)

This game covers multiple choices in some of its paths. I wanted to implement a particular moment that requires 3 choices rather than 2, so I made a loop using the binary trees to cycle through the decisions. Other than that loop, the rest of the decisions are either presented as 2 choices. For its structure, I have alternating pages between a story description and a dialogue or action page for the choices. The code reads through the story document, then translates each line to the console. The player input decides which available action will be committed and where the player will be sent next. To initiate an ending, both ends of the node have to be marked with "-1" representing no available choice.

Example:
> This project implements a text-based RPG using a **binary decision tree**. Each game event is represented as a node, and the player progresses by choosing between two paths at each stage. The storyline is loaded from an external text file (`story.txt`), which is parsed to construct the decision tree. The game ends when a leaf node (with `-1` as left and right children) is reached.

---

## **2. Folder & File Structure**
(Explain the role of each file in your project.)

- **`main.cpp`** → This file contains the entry point for the program. It creates an instance of the decision tree, reads the story data from the text file, and starts the game by making the appropriate function calls.
- **`GameDecisionTree.h`** → This file defines the templated GameDecisionTree class. It includes functions to read the story events from a file in order to construct the binary decision tree and traverse the tree according to user responses during the gameplay.
- **`Node.h`** → This header file has the definition of the templated Node class. Each Node has a data item (here, a Story object) and a pointer to its left and right child nodes, which are utilized as building blocks for the decision tree.
- **`Story.h`** → This header file contains the declaration of the Story class which contains the details of every event (i.e., the event description, event number, and the left and right event numbers of the event). Its constructors are implemented in Story.cpp.
- **`story.txt`** → A text file containing the story events of the game. Each line contains a story event in the form of an event number, a description, and left and right event pointers. The GameDecisionTree reads and parses this file to build the decision tree for the game.

---

## **3. Decision Tree Construction**

The story is structured so that the events each operate on their own numbered line descending in order. The event can be called on by choices either binary, or singular (using a -1 to mark a null choice). Making the console paste the text in the event. If a -1 is present, for the left or right line character "|" that choice (1 and 2 respectively) is considered null, meaning it cannot be called. In the event of 2 null choices, the event is a game ending.

(Explain how the decision tree is built from the `story.txt` file.)

- How are `Story` objects created from the text file?
- How are nodes linked based on left and right event numbers?
- What happens if an event has `-1` as left or right children?

---

## **4. Game Traversal**

The player can only input 1 or 2 on events that have both options available. If one or both options are null, said options cannot be inputted. Inputting 1 or 2 will take the player to the corresponding numbered event for the left or right path respectively.

(Describe how the game moves through the decision tree.)

- How does user input determine the path taken?
- What happens when the player reaches a leaf node?
- Explain the special case where multiple events lead to the same outcome.

---

## **5. File Parsing & Data Loading**
The program reads the text document line by line. It uses our delimeter " | " to know when to read the values for the event number, the event description, the left event number, and the right event number. This is stored as a Story object in a node of our tree with a key. The root node is the one not referenced as a child and leaf nodes are recognized when their left and right childs point to null.
- How is the file read and parsed using a delimiter?
- How do you ensure nodes are properly linked?
- Any challenges faced while handling file input?

---

## **6. Debugging Process (Errors & Fixes)**

Most of my debugging involved human error on the story.txt file, typing the incorrect number, missing numbers, or accidentally leaving null values for paths intended to have an available choice. ---

(Describe one or more debugging challenges you faced and how you fixed them.)

Example:
> Initially, my program was crashing when trying to access an uninitialized node. I realized it was because I was not properly checking for `nullptr` before accessing child nodes, so I added a check to prevent accessing uninitialized memory.

---

## **7. Sample Output & Walkthrough**

The game begins with an introductory paragraph explaining the player's situation and allows for a single input to proceed to the available actions. Once on the next input, the player can cycle through 3 available options for how to proceed. Each actions/dialogue page has 2 possible inputs, either an input that will move onto another story page or an input that leads to another action page. This gameplay loop continues until one of the story endings is achieved.

(Provide an example of how the game runs, including player input.)

---

## **8. Big-O Analysis of Core Methods**
(Analyze the complexity of key methods.)

Loading the tree from the file requires reading over each line of the story.txt file which has an O(n) runtime. Tokenizing each line and assigning values each take their own O(1) runtimes, and searching an event from the tree also takes O(n) as a worst case because we search through that same txt document. During the game, the program travels down one step of the tree every event, so the travel efficiency through the whole tree will always be height n of the tree for a O(n) runtime.

- **Loading the tree from the file** → `O(?)`
- **Searching for an event in the tree** → `O(?)`
- **Game traversal efficiency** → `O(?)`

---

## **9. Edge Cases & Testing**

I ran through several of the possible endings, ensuring that all the paths I checked lead to the proper events as I intended. I tested so that all of my endings are achievable and none of the options lead to the wrong event.

(Describe at least one edge case you tested and its outcome.)

Example:
> I tested a scenario where the player reaches a dead-end (leaf node) and ensured the program correctly ends the game.

---

## **10. Justification of Additional Features (If Any)**

I only added a simple feature of a 3 option loop, allowing the player to cycle through 3 action pages that each have a possible choice to progress the story while the 2nd option is to cycle.

(If you added extra features, describe them and explain why.)

Example:
> I added a **save/load feature** so players can resume the game later. This was done by writing the current node’s event number to a file and reading it when restarting.

---

## **Final Notes**
- **README is mandatory** → `(-10 points deduction if missing).`
- **Code must compile and run** → `(Code that does not run will receive a 0).`
- **Do not modify provided skeleton code** → `(You may only add to it).`

---
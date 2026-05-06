# Word Frequency Analyzer Using AVL Trees and Hash Tables

## 1. Project Overview

This project is a menu-driven C program that reads a text from an input file, extracts words from it, and counts how many times each word appears. The words are first stored in an **AVL tree** (which keeps them sorted and balanced), and then transferred to a **hash table** to allow faster searching, insertion, and deletion.

The user can use the menu to load the file, edit the AVL tree, build the hash table, insert and delete words, search for a word's frequency, and print word statistics.

## 2. Course Information

- **Course:** Data Structures and Algorithms
- **Course Code:** COMP2421
- **Project:** Trees + Hash
- **Language:** C

## 3. Main Idea

The program reads a text file, removes any non-alphabetical characters, and treats each remaining word as an item to be stored.

The same words are stored in two different data structures, each one for a specific purpose:

- An **AVL Tree** is used to keep the words sorted alphabetically and balanced. Every time the same word is inserted again, its frequency is increased instead of adding a new node.
- A **Hash Table** is built from the AVL tree to allow faster access to each word and its frequency. **Double hashing** is used to handle collisions, and the table is **rehashed** automatically when it gets too full.

This way the project combines two important data structures and shows how the same data can be organized in different ways for different goals.

## 4. Data Structures Used

The program uses the following data structures:

- **AVL Tree node**, which contains:
  - The word (a string).
  - Pointer to the left child.
  - Pointer to the right child.
  - Height of the node (used for balancing).
  - Frequency counter (how many times the word appeared).
- **Hash Table**, which is an array of records, where each record contains:
  - The word.
  - Its frequency.
- **Dynamic memory allocation** using `malloc` and `free` for both the tree nodes and the hash table.

## 5. Program Features

The program supports the following operations through its menu:

1. Load words from the input file `input.txt`.
2. Create the AVL tree.
3. Insert a word into the AVL tree.
4. Delete a word from the AVL tree.
5. Print the words in sorted order using in-order traversal.
6. Create the hash table from the AVL tree.
7. Insert a word into the hash table.
8. Delete a word from the hash table.
9. Search for a word in the hash table and print its frequency.
10. Print word statistics (number of unique words, most frequent word, words above a given threshold).
11. Exit the application.

The program also automatically:

- Removes non-alphabetical characters from the text before inserting words.
- Rehashes the table when the load factor reaches 0.7.

The project covers AVL trees, hash tables, double hashing, rehashing, file handling, insertion, deletion, searching, and frequency counting.

## 6. Input File Format

The input file is named `input.txt` and must be placed in the same folder as the executable.

The file contains plain text. The program reads it line by line, removes any character that is not a letter (such as numbers, dots, commas, brackets), and treats the remaining text as a list of words separated by spaces.

Example input:

```
The quick brown fox jumps over the lazy dog.
The dog was not amused, but the fox was happy!
```

After cleaning the text, the program will treat the words as:

```
The quick brown fox jumps over the lazy dog
The dog was not amused but the fox was happy
```

Each word is then inserted into the AVL tree, and repeated words increase their frequency instead of creating a new node.

## 7. AVL Tree Implementation

The AVL tree stores each unique word as a single node and keeps a counter for how many times the word appeared.

Main operations:

- **Insert:** If the word is new, a new node is created. If the word is already in the tree, only the frequency is increased.
- **Delete:** A normal AVL delete is performed. If the node has two children, it is replaced by the smallest node in its right subtree.
- **Balancing:** After each insertion or deletion, the tree checks the height difference between the left and right subtrees. If the difference is bigger than 1, the tree is rebalanced using one of the four rotations:
  - Single rotation with left.
  - Single rotation with right.
  - Double rotation with left.
  - Double rotation with right.
- **In-order traversal:** Used to print the words in alphabetical order along with their frequencies.

Word comparison is done using `strcasecmp`, so words are compared in a case-insensitive way (for example, "The" and "the" are treated as the same word).

## 8. Hash Table Implementation

The hash table is implemented as an array of records. Each record holds a word and its frequency.

Key points:

- The initial table size is **17** (a prime number).
- The table is built from the AVL tree by visiting the tree in order and inserting each word with its frequency into the hash table.
- **Double hashing** is used to handle collisions. The probing formula is:

  ```
  index = (hash1(word) + i * hash2(word)) % tableSize
  ```

  Where:
  - `hash1` is based on the sum of the ASCII values of the characters modulo the table size.
  - `hash2` uses a prime number smaller than the table size to ensure a different step.
  - `i` is the probe number (0, 1, 2, …) until an empty slot is found.

- If the same word is found during probing, only its frequency is increased.
- Searching and deletion follow the same probing sequence to find the word.

## 9. Rehashing Strategy

To keep the hash table efficient, the program checks the load factor before each insertion:

```
load factor = number of inserted elements / table size
```

When the load factor reaches **0.7**, the table is rehashed:

1. A new size is calculated as the next prime number after `2 * currentSize`.
2. A new, larger hash table is allocated.
3. All existing words from the old table are inserted again into the new table using double hashing.
4. The new table replaces the old one.

This makes sure the hash table never gets too crowded, which keeps the search operations fast.

## 10. Word Statistics

The "Print word statistics" option allows the user to see useful information about the text, such as:

- The number of **unique words** (words that appeared only once).
- The **most frequent word** in the hash table.
- All the words that appeared more than a given **threshold**, which the user enters.

This is helpful for analyzing the text and understanding which words are common and which ones are rare.

## 11. Example Menu

When the program runs, the following menu is displayed:

```
Menu of my application
Please select an operation
1-Load data from the file
2-Create the AVL tree
3-Insert a word to the AVL tree
4-Delete a word from the AVL tree
5-Print the words as sorted in the AVL tree
6-Create the Hash Table
7-Insert a word to the Hash table
8-Delete a word from the hash table
9-Search for a word in the hash table and print its frequency
10-Print words statistics
11-Exit the application
```

The user types the number of the operation, and the program performs it. The menu keeps appearing until the user chooses option 11 to exit.

**Note:** The user must first **create the AVL tree** (option 2) and then **load the file** (option 1) before using the other options. The program checks for this and shows a message if the order is wrong.

## 12. Notes about the Implementation

- The AVL tree uses the standard rotation operations explained in class. The height of each node is updated after every insertion and deletion.
- The same word with different cases is treated as one word (for example "Word" and "word"), because `strcasecmp` is used for comparisons.
- Before inserting a word into the hash table, the first letter is converted to upper case and the rest to lower case to make all words have the same form.
- The function `RemoveNonAlphabetical` cleans the text by keeping only letters and spaces, so symbols like commas, dots, and digits do not affect the words.
- The hash table size always remains a prime number after rehashing, which helps reduce collisions.
- Two pointers are used in the program: one for the original hash table and one for the rehashed table. A `rehash` flag tells the program which one is currently active.
- Memory is freed when the AVL tree is emptied through the `MakeEmpty` function.


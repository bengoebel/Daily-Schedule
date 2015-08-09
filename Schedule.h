//
//  Schedule.h
//  Schedule
//
//  Created by Ben Goebel on 6/9/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//
//  This is the header file for the Schedule class.
//

#ifndef __Schedule__Schedule__
#define __Schedule__Schedule__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <string>

using namespace std;

struct event_node
{
    string name;
    double start_time;        // Army time
    double end_time;
    string description;
    event_node *right;       // Right node has a later time than current node
    event_node *left;        // Left node has an earlier time than current node
};

class Schedule
{
public:
    Schedule();     // The constructor
    ~Schedule();    // The destructor
    bool insert_event(string n, double st, double et, string desc);
    // Inserts an event into the schedule
    bool remove_event(string n, double st, double et);
    // Removes an event from the schedule
    bool edit_name(string n, double st, double et, string nn);
    // Edits an event's name
    bool edit_start_time(string n, double st, double et, double nst);
    // Edits an event's start time
    bool edit_end_time(string n, double st, double et, double net);
    // Edits an event's end time
    bool edit_description(string n, double st, double et, string desc);
    // Edits an event's description
    void print();   // Prints the schedule
    void delete_schedule(); // Deletes the schedule
private:
    event_node *root;
    bool insert_event(event_node *temp, string n, double st, double et,
                      string desc); // Inserts an event into the schedule
    void create_event(event_node *&node, string dir, string n, double st,
                      double et, string desc);
    // Creates a new node
    void initialize_event(event_node *node, string n, double st, double et,
                          string desc);
    // Initializes each of the event's member variables
    bool remove_event(event_node *node, string n, double st, double et);
    // Removes an event from the schedule
    int get_height(event_node *node); // Gets the height of the node
    void find_imbalance(stack<event_node*> s, event_node *curr);
    // Checks to see if the tree is balanced. If it is not, it balances it
    void balance_tree(stack<event_node*> s);
    // Balances the tree to maintain the AVL tree invariant
    void left_rotation(event_node *prev, event_node *node);
    // Performs a left rotation rooted at the event_node passed to the function
    void right_rotation(event_node *prev, event_node *node);
    // Performs a right rotation rooted at the event_node passed to the function
    void left_right_rotation(event_node *prev, event_node *node);
    // Performs a left-right rotation rooted at the second event_node passed to
    // the function
    void right_left_rotation(event_node *prev, event_node *node);
    // Performs a right-left rotation rooted at the second event_node passed to
    // the function
    void remove_replace_left(event_node *prev, event_node *curr);
    // Removes the current node and replaces it with the rightmost node in the
    // current node's left subtree
    void remove_replace_right(event_node *prev, event_node *curr);
    // Removes the current node and replaces it with the leftmost node in the
    // current node's right subtree
    bool find_prev_node(event_node *&node, string n, double st, double et);
    // Gets the node whose event is the last to occur before the node being
    // searched for occurs
    bool find_node(stack<event_node*> &s, event_node *&node, string n,
                   double st, double et);
    // Finds an event
    bool find_next_node(event_node *&node, string n, double st, double et);
    // Gets the node whose event is the next to occur after the node being
    // searched for occurs
    void traverse_left(event_node *&prev, event_node *&curr);
    // Traverses to the leftmost node
    void traverse_right(event_node *&prev, event_node *&curr);
    // Traverses to the rightmost node
    void not_prev_left(stack<event_node*> s, event_node *&prev);
    // Looks for the previous node if node->left is NULL
    void not_next_right(stack<event_node*> s, event_node *&next);
    // Looks for the next node if node->right is NULL
    void print(event_node *node);   // Prints the schedule
    void delete_all(event_node *node);   // Deletes every node
};

#endif /* defined(__Schedule__Schedule__) */

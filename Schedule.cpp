//
//  Schedule.cpp
//  Schedule
//
//  Created by Ben Goebel on 6/9/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//
//  This is the implementation for the Schedule class.
//

#include "Schedule.h"


// The constructor
Schedule::Schedule()
{
    root = NULL;
}

// The destructor
Schedule::~Schedule()
{
    delete_all(root);
    root = NULL;        // Even if node is deleted, root will point to it
}

// Purpose: Inserts an event into the schedule if it is not already there and
//          it fits into the schedule.
// Arguments: Two strings: the name of the event and the description. Two
//            doubles: the start time and the end time of the event.
// Returns: A bool: true if the event is inserted into the schedule and false
//          if the event is already in the schedule or does not fit into the
//          the scedule.
bool Schedule::insert_event(string n, double st, double et, string desc)
{
    if( st >= et )                  // Conflicting time check
        return false;
    if( root != NULL )          // Insert event if root is not NULL
        return insert_event(root, n, st, et, desc);
    root = new event_node();
    initialize_event(root, n, st, et, desc);
    // Otherwise, create a new node and point the root at the new node
    return true;
}

// Purpose: Removes an event from the schedule if it is in the schedule.
// Arguments: A string: the name of the event. Two doubles: the start time and
//            end times of the event.
// Returns: A bool: true if the event is removed from the schedule and false
//          if the event is not in the schedule.
bool Schedule::remove_event(string n, double st, double et)
{
    return remove_event(root, n, st, et);
}

// Purpose: Edits an event's name if the event is in the schedule.
// Arguments: A string: the event's current name. 2 doubles: the event's start
//            and end times. And another string: the event's new name.
// Returns: A bool: true if the event's name is changed and false if the event
//          is not in the schedule.
bool Schedule::edit_name(string n, double st, double et, string nn)
{
    stack<event_node*> s;                   // Used to find the node
    event_node *node = root;
    if( find_node(s, node, n, st, et) )     // Find the node if it exists
    {
        if( node->name == nn )              // unchanged check
            return false;
        node->name = nn;                    // and edit its name
        return true;
    }
    return false;       // If it does not exist, return false
}

// Purpose: Edits an event's start time if the event is in the schedule and if
//          the time is not conflicting.
// Arguments: A string: the event's name and 3 doubles: the event's start,
//            end and new start times.
// Returns: A bool: true if the event's start time is changed, and false if the
//          time is conflicting, or the event is not in the schedule.
bool Schedule::edit_start_time(string n, double st, double et, double nst)
{
    if( nst >= et || nst == st )    // Invalid input check
        return false;
    event_node *prev = root;
    if( find_prev_node(prev, n, st, et) )   // Gets the previos node (timewise)
    {                                       // if the current node exists
        stack<event_node*> s;   // Create stack to call find_node
        event_node *curr = root;    // Stack is otherwise useless
        find_node(s, curr, n, st, et);
        if( prev == NULL || nst > prev->end_time )  // prev = NULL means it
        {                                           // does not exist
            curr->start_time = nst;
            return true;
        }
    }
    return false;
}

// Purpose: Edits an event's end time if the event is in the schedule and the
//          time is not conflicting.
// Arguments: A string: the event's name and 3 doubles: the event's start, end
//            and new end times.
// Returns: A bool: true if the event's end time is changed, and false if the
//          time is conflicting, or the event is not in the schedule.
bool Schedule::edit_end_time(string n, double st, double et, double net)
{
    if( net <= st || net == et )                        // Invalid input check
        return false;
    event_node *next = root;
    if( find_next_node(next, n, st, et) )
    {
        stack<event_node*> s;                           // Used to find node
        event_node *curr = root;
        find_node(s, curr, n, st, et);
        if( next == NULL || net < next->start_time )    // next = NULL means it
        {                                               // does not exist
            curr->end_time = net;
            return true;
        }
    }
    return false;
}

// Purpose: Edits an event's description if the event is in the schedule.
// Arguments: 2 strings: The event's name and its new description and 2 doubles:
//            the event's start and end times.
// Returns: A bool: true if the event's description is changed and false if
//          the event is not in the schedule.
bool Schedule::edit_description(string n, double st, double et, string desc)
{
    stack<event_node*> s;                   // Used to find node
    event_node *node = root;
    if( find_node(s, node, n, st, et) )
    {
        if( node->description == desc )     // unchanged check
            return false;
        node->description = desc;
        return true;
    }
    return false;
}

// Purpose: Prints the schedule.
// Arguments: None.
// Returns: Nothing.
void Schedule::print()
{
    if( root == NULL )
        cout << "Schedule is empty" << endl;
    else
    {
        cout << "Schedule: " << endl;
        print(root);
    }
}

// Purpose: Deletes the schedule.
// Arguments: None.
// Returns: Nothing.
void Schedule::delete_schedule()
{
    delete_all(root);
    root = NULL;    // Even if node is deleted, root will point to it
}

// Purpose: Inserts an event into the schedule if it is not already there and
//          if it does not have a conflicting time.
// Arguments: An event_node: the schedule being examined. Two strings: the name
//            of the event and the description. Two doubles: the start and end
//            times of the event.
bool Schedule::insert_event(event_node *temp, string n, double st, double et,
                            string desc)
{
    event_node *prev = NULL;        // Node will point to temp
    string dir = "";    // The direction a node points
    while( temp != NULL )
    {
        if( temp->end_time < st )
        {
            prev = temp;            // Later time
            temp = temp->right;
            dir = "R";
        }
        else if( temp->start_time > et )
        {
            prev = temp;            // Earlier time
            temp = temp->left;
            dir = "L";
        }
        else
            return false;   // Conflicting time
    }
    create_event(prev, dir, n, st, et, desc);
    stack <event_node*> s;  // Stack created to find an imbalance
    find_imbalance(s, root);
    return true;
}

// Purpose: Creates a new node.
// Arguments: An event_node: the node that will point to the new node being
//            created. 3 strings: the direction the node will point, the event's
//            name and its description. 2 doubles: the start and end times.
// Returns: Nothing.
void Schedule::create_event(event_node *&node, string dir, string n, double st,
                            double et, string desc)
{
    if( dir == "R" )                            // Checking direction
    {
        node->right = new event_node();
        node = node->right;
    }
    else                                        // Making the new node
    {
        node->left = new event_node();
        node = node->left;
    }
    initialize_event(node, n, st, et, desc);
}

// Purpose: Initializes each of the event's member variables.
// Arguments: An event_node: the node to be initialized. 2 strings: the event's
//            name and description. 2 doubles: the event's start and end times.
// Returns: Nothing.
void Schedule::initialize_event(event_node *node, string n, double st,
                                double et, string desc)
{
    node->name = n;
    node->start_time = st;
    node->end_time = et;                        // Editing the new node's
    node->description = desc;                   // member variables
    node->right = NULL;
    node->left = NULL;
}

// Purpose: Removes an event from the schedule if it is in the schedule.
// Arguments: An event_node: the schedule the event is being deleted from. A
//            string: the name of the event. Two doubles: the start and end
//            times of the event.
// Returns: A bool: true if the event is removed from the schedule and false
//          if the event is not in the schedule.
bool Schedule::remove_event(event_node *node, string n, double st, double et)
{
    event_node *prev = NULL;        // Will point to the pointer node
    stack<event_node*> traversed;   // Traversed nodes
    if( find_node(traversed, node, n, st, et) )
    {
        if( !traversed.empty() )
            prev = traversed.top();
        if( get_height(node->left) >= get_height(node->right) )
            remove_replace_left(prev, node);
        else                                    // Remove node
            remove_replace_right(prev, node);
        stack<event_node*> s;   // Stack used to find imbalance in tree
        find_imbalance(s, root);
        return true;
    }
    return false;
}

// Purpose: Gets the height of the node.
// Arguments: An event_node: the node to get the height of.
// Returns: An int: the height of the node.
int Schedule::get_height(event_node *node)
{
    if( node == NULL )
        return 0;
    int height_right = 0;
    int height_left = 0;
    height_right = 1 + get_height(node->right);
    height_left = 1 + get_height(node->left);
    if( height_right >= height_left )
        return height_right;
    else                        // Different subtrees have different heights
        return height_left;
}

// Purpose: Checks to see if the tree is balanced. If it is not, it balances it.
// Arguments: A stack: this helps to track the path traversed through the AVL
//            tree. An event_node: the AVL tree being examined.
// Returns: Nothing.
void Schedule::find_imbalance(stack<event_node*> s, event_node *curr)
{
    if( curr == NULL )
        return;
    if( !s.empty() &&     // Find imbalance closest to leaf
        abs( get_height(s.top()->left) - get_height(s.top()->right) ) > 1 &&
        abs( get_height(curr->left) - get_height(curr->right) ) <= 1 )
        balance_tree(s);
    else
    {
        s.push(curr);
        find_imbalance(s, curr->right);  // Keep checking right and left
        find_imbalance(s, curr->left);
    }
}

// Purpose: Balances the tree to maintain the AVL tree invariant.
// Arguments: A stack: the nodes in the AVL tree that have been traversed.
// Returns: Nothing.
void Schedule::balance_tree(stack<event_node*> s)
{
    event_node *node = s.top();     // The node that is imbalanced
    event_node *copy_node = node;   // A copy of the node
    s.pop();
    event_node *prev = NULL; // The node that points to the imbalanced node
    if( !s.empty() )
        prev = s.top();
    if( get_height(node->right) > get_height(node->left) )
    { // Checking the type of rotation needed
        node = node->right;
        if( get_height(node->right) > get_height(node->left) )
            left_rotation(prev, copy_node);
        else
            left_right_rotation(prev, copy_node);
    }
    else
    {
        node = node->left;
        if( get_height(node->left) > get_height(node->right) )
            right_rotation(prev, copy_node);
        else
            right_left_rotation(prev, copy_node);
    }
}

// Purpose: Performs a left rotation rooted at the second event_node passed to
//          the function.
// Arguments: 2 event_nodes: the node to be rotated left and the node that
//            points to that node to help facilitate the rotation.
// Returns: Nothing.
void Schedule::left_rotation(event_node *prev, event_node *node)
{
    if( prev == NULL )
        root = node->right;     // Rotating root
    else
    {
        if( prev->right == node )
            prev->right = node->right;  // What will point to the rotated
        else                            // subtree
            prev->left = node->right;
    }
    prev = node;
    node = node->right;
    prev->right = node->left;   // Must be done because node->left will be
    node->left = prev;          // prev and we don't want to lose a pointer
                                // to anything node->left points to currently
}

// Purpose: Performs a right rotation rooted at the second event_node passed to
//          the function.
// Arguments: 2 event_nodes: the node to be rotated right and the node that
//            points to that node to help facilitate the rotation.
// Returns: Nothing.
void Schedule::right_rotation(event_node *prev, event_node *node)
{
    if( prev == NULL )
        root = node->left;  // Rotating root
    else
    {
        if( prev->right == node )
            prev->right = node->left;   // What will point to the rotated
        else                            // subtree
            prev->left = node->left;
    }
    prev = node;
    node = node->left;
    prev->left = node->right;   // Must be done because node->right will be
    node->right = prev;         // prev and we don't want to lose a pointer
                                // to anything node->right points to currently
}

// Purpose: Performs a left-right rotation rooted at the second event_node
//          passed to the function.
// Arguments: 2 event_nodes: the node to be rotated, and the
//            node that points to that node to help facilitate the
//            rotation.
// Returns: Nothing.
void Schedule::left_right_rotation(event_node *prev, event_node *node)
{
    event_node *prev_temp = node->right;     // Points to temp
    event_node *temp = prev_temp->left;      // Set up for left rotation
    node->right = temp;
    prev_temp->left = temp->right;  // Done so that we don't lose what
    temp->right = prev_temp;        // temp->right points to currently
    left_rotation(prev, node);
}

// Purpose: Performs a right-left rotation rooted at the second event_node
//          passed to the function.
// Arguments: 2 event_nodes: the node to be rotated, and the
//            node that points to that node to help facilitate the
//            rotation.
// Returns: Nothing.
void Schedule::right_left_rotation(event_node *prev, event_node *node)
{
    event_node *prev_temp = node->left;     // Points to temp
    event_node *temp = prev_temp->right;    // Set up for right rotation
    node->left = temp;
    prev_temp->right = temp->left;  // Done so that we don't lose what
    temp->left = prev_temp;         // temp->left points to currently
    right_rotation(prev, node);
}

// Purpose: Removes the current node and replaces it with the rightmost node in
//          the current node's left subtree.
// Arguments: 2 event_nodes: the one being deleted and the one that points to
//            it.
// Returns: Nothing.
void Schedule::remove_replace_left(event_node *prev, event_node *curr)
{
    event_node *prev_replace = NULL; // the node that points to the replacement
    event_node *replace = curr->left;     // the replacement node
    if( replace != NULL )
    {
        traverse_right(prev_replace, replace);
        replace->right = curr->right;       // Where replace->right points
    }
    if( prev == NULL )
        root = replace;             // Curr is root changing root to replace
    else
    {
        if( prev->right == curr )
            prev->right = replace;
        else                                // Prev pointing to replacement
            prev->left = replace;
    }
    if( prev_replace != NULL )
    {
        prev_replace->right = replace->left; // Where prev_replace points to
        replace->left = curr->left;          // Where replace->left points
    }
    delete curr;
}

// Purpose: Removes the current node and replaces it with the leftmost node in
//          the current node's right subtree.
// Arguments: 2 event_nodes: the one being deleted and the one that points to
//            it.
// Returns: Nothing.
void Schedule::remove_replace_right(event_node *prev, event_node *curr)
{
    event_node *prev_replace = NULL; // the node that points to the replacement
    event_node *replace = curr->right;     // the replacement node
    if( replace != NULL )
    {
        traverse_left( prev_replace, replace);
        replace->left = curr->left;     // Where replace->left points
    }
    if( prev == NULL )
        root = replace;                 // Curr is root changing root to replace
    else
    {
        if( prev->right == curr )
            prev->right = replace;
        else                                // Prev pointing to replacement
            prev->left = replace;
    }
    if( prev_replace != NULL )
    {
        prev_replace->left = replace->right; // Where prev_replace points to
        replace->right = curr->right;         // Where replace->right points
    }
    delete curr;
}

// Purpose: Gets the node whose event is the last to occur before the node being
//          searched for occurs.
// Arguments: An event_node: the schedule being examined. A string: the event's
//            name and 2 doubles: the event's start and end times.
// Returns: A bool: true if the event being searched for exists and false if
//          it does not exist.
// Note: This function gets the previous node if it exists, and if it does not
//       the event_node will be set to NULL. However, this function searches
//       for the event specified by the arguments.
bool Schedule::find_prev_node(event_node *&node, string n, double st, double et)
{
    stack<event_node*> s;
    if( find_node(s, node, n, st, et) )
    {
        event_node *copy_node = node;   // Used to see if node changes
        if( node->left != NULL )
        {                           // Go left and traverse right
            node = node->left;
            event_node *null_pointer = NULL;
            traverse_right(null_pointer, node); // Can't pass NULL, so use
        }                                       // variable
        else
            not_prev_left(s, node);
        if( node == copy_node ) // If node didn't change prev node doesn't exist
            node = NULL;            // If no prev node, set node to NULL
        return true;
    }
    return false;
}

// Purpose: Finds an event in the schedule.
// Arguments: A stack: this helps to track the path traversed through the AVL
//            tree. An event_node: the schedule being examined.
//            A string: the event's name and 2 doubles: the event's start and
//            end times.
// Returns: A bool: true if the event being searched for exists and false if
//          it does not exist.
bool Schedule::find_node(stack<event_node*> &s, event_node *&node, string n,
                         double st, double et)
{
    while( node != NULL )
    {
        if( node->name == n && node->start_time == st && node->end_time == et)
            return true;            // Event found
        else if( node->start_time < st && node->end_time < et )
        {
            s.push(node);           // Later time
            node = node->right;
        }
        else if( node->start_time > st && node->end_time > et )
        {
            s.push(node);           // Earlier time
            node = node->left;
        }
        else
            return false;           // Event not in schedule
    }
    return false;
}

// Purpose: Gets the node whose event is the next to occur after the node being
//          searched for occurs.
// Arguments: An event_node: the schedule being examined. A string: the event's
//            name and 2 doubles: the event's start and end times.
// Returns: A bool: true if the event being searched for exists and false if
//          it does not exist.
// Note: This function gets the next node if it exists, and if it does not
//       the event_node will be set to NULL. However, this function searches
//       for the event specified by the arguments.
bool Schedule::find_next_node(event_node *&node, string n, double st, double et)
{
    stack<event_node*> s;
    if( find_node(s, node, n, st, et) )
    {
        event_node *copy_node = node;   // Used to see if node changes
        if( node->right != NULL )
        {                           // Go right and traverse left
            node = node->right;
            event_node *null_pointer = NULL;    // Can't pass NULL, so use
            traverse_left(null_pointer, node);  // variable
        }
        else
            not_next_right(s, node);
        if( node == copy_node ) // If node didn't change next node doesn't exist
            node = NULL;        // If no next node, set node to NULL
        return true;
    }
    return false;
}

// Purpose: Traverses to the leftmost node.
// Arguments: 2 event_nodes: the leftmost node and the one that points to it.
// Returns: Nothing.
void Schedule::traverse_left(event_node *&prev, event_node *&curr)
{
    while( curr->left != NULL )
    {
        prev = curr;         // Traversing to the leftmost node
        curr = curr->left;
    }
}

// Purpose: Traverses to the rightmost node.
// Arguments: 2 event_nodes: the rightmost node and the one that points to it.
// Returns: Nothing.
void Schedule::traverse_right(event_node *&prev, event_node *&curr)
{
    while( curr->right != NULL )
    {
        prev = curr;         // Traversing to the rightmost node
        curr = curr->right;
    }
}

// Purpose: Looks for the previous node if node->left is NULL.
// Arguments: A stack: the traversed nodes. An event_node: the previous node.
// Returns: Nothing.
void Schedule::not_prev_left(stack<event_node *> s, event_node *&prev)
{
    if( s.empty() )
        prev = NULL;    // The prev node does not exist
    while( !s.empty() )
    {
        if( s.top()->start_time < prev->start_time )
        {                       // Look for previous node in stack
            prev = s.top();
            break;
        }
        else
            s.pop();
    }
}

// Purpose: Looks for the next node if node->right is NULL.
// Arguments: A stack: the traversed nodes. An event_node: the next node.
// Returns: Nothing.
void Schedule::not_next_right(stack<event_node *> s, event_node *&next)
{
    if( s.empty() )
        next = NULL;    // The next node does not exist
    while( !s.empty() )
    {
        if( s.top()->start_time > next->start_time )
        {                       // Look for next node in stack
            next = s.top();
            break;
        }
        else
            s.pop();
    }
}

// Purpose: Prints the schedule.
// Arguments: An event_node: The schedule to be printed.
// Returns: Nothing.
void Schedule::print(event_node *node)
{
    double min = 0.00;    // minutes in time
    if( node == NULL )
        return;
    print(node->left);  // Print leftmost node
    cout << "Name: " << node->name << endl; // Then print node
    cout << "Start Time: " << (int)floor(node->start_time) << ":";
    min = (node->start_time - floor(node->start_time)) * 100;
    if( min < 10 )
        cout << 0 << min << endl;   // Put a zero in front of minutes digit
    else
        cout << min << endl;
    cout << "End Time: " << (int)floor(node->end_time) << ":";
    min = (node->end_time - floor(node->end_time)) * 100;
    if( min < 10 )
        cout << 0 << min << endl;
    else
        cout << min << endl;
    cout << "Description: " << node->description << endl;
    cout << endl;
    print(node->right); // Then print rightmost node
}

// Purpose: Deletes every node.
// Arguments: An event_node: The schedule to be deleted.
// Returns: Nothing.
void Schedule::delete_all(event_node *node)
{
    if( node == NULL )
        return;
    delete_all(node->left);     // Delete leftmost node
    node->left = NULL;          // Set the pointer to that node to NULL
    delete_all(node->right);    // Delete rightmost node
    node->right = NULL;         // Set the pointer to that node to NULL
    delete node;                // Delete the node
    node = NULL;                // Set the node to NULL
}






//
//  main.cpp
//  Schedule
//
//  Created by Ben Goebel on 6/9/15.
//  Copyright (c) 2015 Ben Goebel. All rights reserved.
//

#include "Schedule.h"

void run_insert(Schedule *s);
void run_remove(Schedule *s);
void run_edit_name(Schedule *s);
void run_edit_start_time(Schedule *s);
void run_edit_end_time(Schedule *s);
void run_edit_description(Schedule *s);
void run_print(Schedule *s);
void run_delete(Schedule *s);
void main_prompt();
void insert_prompt();
void remove_prompt();
void edit_name_prompt();
void edit_start_time_prompt();
void edit_end_time_prompt();
void edit_description_prompt();
void input_n(string *n, bool edit);
bool input_start_time(double *start_time, bool edit);
bool input_end_time(double *end_time, bool edit);
void input_d(string *d, bool edit);

int main()
{
    Schedule s;
    string input = "list";  // To list the commands first
    while( input != "end" )
    {
        cout << endl;                           // Spacing
        if( input == "insert" )
            run_insert(&s);
        else if( input == "remove" )
            run_remove(&s);
        else if( input == "edit_name" )
            run_edit_name(&s);
        else if( input == "edit_start_time" )
            run_edit_start_time(&s);
        else if( input == "edit_end_time" )
            run_edit_end_time(&s);
        else if( input == "edit_description" )
            run_edit_description(&s);
        else if( input == "print" )
            run_print(&s);
        else if( input == "delete" )
            run_delete(&s);
        else if( input == "list" )
            main_prompt();
        else
            cout << "Invalid input." << endl;
        cout << endl;                           // Spacing
        cout << "Main Command: ";
        cin >> input;
    }
    return 0;
}

// Purpose: Runs the insert function.
// Arguments: A pointer to a Schedule: the schedule events are being inserted
//            into.
// Returns: Nothing.
void run_insert(Schedule *s)
{
    cout << endl;                           // Spacing
    insert_prompt();
    string input = "";
    string name, description;
    double start_time, end_time;
    bool invalid_input = false;             // For invalid input
    cout << "Insert Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "insert" )
        {
            input_n(&name, false);
            invalid_input = input_start_time(&start_time, false);
            if( invalid_input )
                input_end_time(&end_time, false);
            else
                invalid_input = input_end_time(&end_time, false);
            input_d(&description, false);
            if( !invalid_input &&
               s->insert_event(name, start_time, end_time, description) )
                cout << "Event inputed into schedule." << endl;
            else
            {
                cout << "Event not inputed into schedule due to a conflicting ";
                cout << "or invalid time." << endl;
            }
        }
        cout << endl;                   // Spacing
        cout << "Insert Command: ";
        cin >> input;
    }
}

// Purpose: Runs the remove function.
// Arguments: A pointer to a Schedule: the schedule events are being removed
//            from.
// Returns: Nothing.
void run_remove(Schedule *s)
{
    cout << endl;                       // Spacing
    remove_prompt();
    string input = "";
    string name;
    double start_time, end_time;
    cout << "Remove Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "remove" )
        {
            input_n(&name, false);
            input_start_time(&start_time, false);
            input_end_time(&end_time, false);
            if( s->remove_event(name, start_time, end_time) )
                cout << "Event removed from schedule." << endl;
            else
                cout << "Event not found in schedule." << endl;
        }
        cout << endl;                   // Spacing
        cout << "Remove Command: ";
        cin >> input;
    }
}

// Purpose: Runs the edit_name function.
// Arguments: A pointer to a Schedule: the schedule event names are
//            being edited from.
// Returns: Nothing.
void run_edit_name(Schedule *s)
{
    cout << endl;                   // Spacing
    edit_name_prompt();
    string input = "";
    string name, new_name;
    double start_time, end_time;
    cout << "Edit Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "edit" )
        {
            input_n(&name, false);
            input_start_time(&start_time, false);
            input_end_time(&end_time, false);
            input_n(&new_name, true);
            if( s->edit_name(name, start_time, end_time, new_name) )
                cout << "Event name edited." << endl;
            else
                cout << "Event not found or unmodified in schedule." << endl;
        }
        cout << endl;               // Spacing
        cout << "Edit Command: ";
        cin >> input;
    }
}

// Purpose: Runs the edit_start_time function.
// Arguments: A pointer to a Schedule: the schedule event start times are
//            being edited from.
// Returns: Nothing.
void run_edit_start_time(Schedule *s)
{
    cout << endl;                                   // Spacing
    edit_start_time_prompt();
    string input = "";
    string name;
    double start_time, end_time, new_start_time;
    cout << "Edit Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "edit" )
        {
            input_n(&name, false);
            input_start_time(&start_time, false);
            input_end_time(&end_time, false);
            input_start_time(&new_start_time, true);
            if( s->edit_start_time(name, start_time, end_time, new_start_time) )
                cout << "Event start time edited." << endl;
            else
                cout << "Event not found or unmodified in schedule." << endl;
        }
        cout << endl;                               // Spacing
        cout << "Edit Command: ";
        cin >> input;
    }
}

// Purpose: Runs the edit_end_time function.
// Arguments: A pointer to a Schedule: the schedule event end times are
//            being edited from.
// Returns: Nothing.
void run_edit_end_time(Schedule *s)
{
    cout << endl;                                   // Spacing
    edit_end_time_prompt();
    string input = "";
    string name;
    double start_time, end_time, new_end_time;
    cout << "Edit Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "edit" )
        {
            input_n(&name, false);
            input_start_time(&start_time, false);
            input_end_time(&end_time, false);
            input_end_time(&new_end_time, true);
            if( s->edit_end_time(name, start_time, end_time, new_end_time) )
                cout << "Event end time edited." << endl;
            else
                cout << "Event not found or unmodified in schedule." << endl;
        }
        cout << endl;                               // Spacing
        cout << "Edit Command: ";
        cin >> input;
    }
}

// Purpose: Runs the edit_description function.
// Arguments: A pointer to a Schedule: the schedule event descriptions are
//            being edited from.
// Returns: Nothing.
void run_edit_description(Schedule *s)
{
    cout << endl;                               // Spacing
    edit_description_prompt();
    string input = "";
    string name, new_desc;
    double start_time, end_time;
    cout << "Edit Command: ";
    cin >> input;
    while( input != "end" )
    {
        cout << endl;
        if( input == "edit" )
        {
            input_n(&name, false);
            input_start_time(&start_time, false);
            input_end_time(&end_time, false);
            input_d(&new_desc, true);
            if( s->edit_description(name, start_time, end_time, new_desc) )
                cout << "Event description edited." << endl;
            else
                cout << "Event not found or unmodified in schedule." << endl;
        }
        cout << endl;                           // Spacing
        cout << "Edit Command: ";
        cin >> input;
    }
}

// Purpose: Runs the print function.
// Arguments: A pointer to a Schedule: the schedule being printed.
// Returns: Nothing.
void run_print(Schedule *s)
{
    s->print();
}

// Purpose: Runs the delete function.
// Arguments: A pointer to a Schedule: the schedule being deleted.
// Returns: Nothing.
void run_delete(Schedule *s)
{
    s->delete_schedule();
    cout << "Schedule deleted." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          program.
// Arguments: None.
// Returns: Nothing.
void main_prompt()
{
    cout << "Please type a command: 'insert' to insert an event into the ";
    cout << "schedule, 'remove' to remove an event from the schedule, ";
    cout << "'edit_name' to edit an event's name, 'edit_start_time' to edit ";
    cout << "an event's start time, 'edit_end_time' to edit an event's end ";
    cout << "time, 'edit_description' to edit an event's description, 'print' ";
    cout << "to print the schedule, 'delete' to delete the schedule, 'end' to ";
    cout << "end the program, or list to list the commands and descriptions ";
    cout << "again. Input is case and space sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          insert function.
// Arguments: None.
// Returns: Nothing.
void insert_prompt()
{
    cout << "Please enter 'insert' to insert an event into the schedule.";
    cout << " Enter 'end' when done inserting events into the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          remove function.
// Arguments: None.
// Returns: Nothing.
void remove_prompt()
{
    cout << "Please enter 'remove' to remove an event from the schedule.";
    cout << " Enter 'end' when done removing events from the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          edit_name function.
// Arguments: None.
// Returns: Nothing.
void edit_name_prompt()
{
    cout << "Please enter 'edit' to edit an event's name in the schedule.";
    cout << " Enter 'end' when done editing event names in the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          edit_start_time function.
// Arguments: None.
// Returns: Nothing.
void edit_start_time_prompt()
{
    cout << "Please enter 'edit' to edit an event's start time in the schedule.";
    cout << " Enter 'end' when done editing event start times in the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          edit_end_time function.
// Arguments: None.
// Returns: Nothing.
void edit_end_time_prompt()
{
    cout << "Please enter 'edit' to edit an event's end time in the schedule.";
    cout << " Enter 'end' when done editing event end times in the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Lists and describes all the commands that can be inputed into the
//          edit_description function.
// Arguments: None.
// Returns: Nothing.
void edit_description_prompt()
{
    cout << "Please enter 'edit' to edit an event's description in the schedule.";
    cout << " Enter 'end' when done editing event descriptions in the schedule.";
    cout << " Input is case sensitive." << endl;
}

// Purpose: Allows the user to input an event name.
// Arguments: A string: the event name. A bool: true if the name is being
//            edited and false if otherwise.
// Returns: Nothing.
void input_n(string *n, bool edit)
{
    string name;
    if( edit )
        cout << "New Event Name (No Spaces): ";
    else
        cout << "Event Name (No Spaces): ";
    cin >> name;
    cout << endl;
    *n = name;
}

// Purpose: Allows the user to input an event start time.
// Arguments: A double: the start time. A bool: true if the time is being
//            edited and false if otherwise.
// Returns: A bool: true if the time is invalid and false otherwise.
bool input_start_time(double *start_time, bool edit)
{
    double hour, min;
    if( edit )
        cout << "New Event Start Time (Army Time)" << endl;
    else
        cout << "Event Start Time (Army Time)" << endl;
    cout << "Start Hour: ";
    cin >> hour;
    if( hour < 0 || hour >= 24 )    // Invalid input check
        return true;
    cout << endl;
    cout << "Start Minute: ";
    cin >> min;
    if( min < 0 || min >= 60 )      // Invalid input check
        return true;
    cout << endl;
    *start_time = hour + min/100;
    return false;
}

// Purpose: Allows the user to input an event end time.
// Arguments: A double: the end time. A bool: true if the time is being
//            edited and false if otherwise.
// Returns: A bool: true if the time is invalid and false otherwise.
bool input_end_time(double *end_time, bool edit)
{
    double hour, min;
    if( edit )
        cout << "New Event End Time (Army Time)" << endl;
    else
        cout << "Event End Time (Army Time)" << endl;
    cout << "End Hour: ";
    cin >> hour;
    if( hour < 0 || hour >= 24 )    // Invalid input check
        return true;
    cout << endl;
    cout << "End Minute: ";
    cin >> min;
    if( min < 0 || min >= 60 )      // Invalid input check
        return true;
    cout << endl;
    *end_time = hour + min/100;
    return false;
}

// Purpose: Allows the user to input an event description.
// Arguments: A string: the event description. A bool: true if the description
//            is being edited and false if otherwise.
// Returns: Nothing.
void input_d(string *d, bool edit)
{
    *d = "";
    int num_words;
    string desc;
    cout << "Number of Words in Description: ";
    cin >> num_words;
    cout << endl;
    if( edit )
        cout << "New Event Description: ";
    else
        cout << "Event Description: ";
    for( int i = 0; i < num_words; i++)
    {
        cin >> desc;
        *d += " " + desc;
    }
    cout << endl;
}

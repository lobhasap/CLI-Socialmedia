#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// Define a structure for the post
typedef struct Post_Stack {
    char username[15];
    string post;
    int up_down_vote = 0;
    int index;
    struct Post_Stack* next;
} Post;

Post* TOP = nullptr;
int counter = 0;
char username[15]; // Add a global variable for the currently logged-in user

// Function to sign up a new user
bool SignUp() {
    char newUsername[15], password[15];
    cout << "Enter a username: ";
    cin >> newUsername;

    ifstream usersFile("users.txt");
    if (usersFile) {
        while (usersFile >> username >> password) {
            if (strcmp(newUsername, username) == 0) {
                cout << "Username is already taken. Please choose a different username." << endl;
                usersFile.close();
                return false;
            }
        }
        usersFile.close();
    }

    ofstream userFile("users.txt", ios::app);
    cout << "Enter a password: ";
    cin >> password;
    userFile << newUsername << " " << password << endl;
    userFile.close();
    cout << "Account created successfully!" << endl;
    return true;
}

// Function to log in a user
bool LogIn() {
    char inputUsername[15], inputPassword[15];
    cout << "Enter your username: ";
    cin >> inputUsername;
    cout << "Enter your password: ";
    cin >> inputPassword;

    ifstream usersFile("users.txt");
    if (!usersFile) {
        cout << "No users found. Please sign up first." << endl;
        return false;
    }

    char fileUsername[15], filePassword[15];

    while (usersFile >> fileUsername >> filePassword) {
        if (strcmp(inputUsername, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0) {
            strcpy(username, inputUsername); // Set the currently logged-in username
            cout << "Login successful!" << endl;
            usersFile.close();
            return true;
        }
    }

    usersFile.close();
    cout << "Incorrect username or password. Please try again." << endl;
    return false;
}

Post* New_Post() {
    Post* temp = new Post;
    if (temp == nullptr) {
        cout << "Memory not Allocated!!" << endl;
        exit(1);
    } else {
        counter++;
        strcpy(temp->username, username); // Set the username for the new post
        cout << "Enter Post - ";
        cin.ignore();
        getline(cin, temp->post);
        temp->next = nullptr;
        temp->index = counter;
        return temp;
    }
}

void Add_Post() {
    Post* new1, *p;
    new1 = New_Post();
    if (TOP == nullptr) {
        TOP = new1;
    } else {
        p = TOP;
        new1->next = p;
        TOP = new1;
    }
}

int Del_Post() {
    int index;
    char confirm;
    Post* p;
    Post* q, *r;
    cout << "Total no. of Posts are " << counter << endl;
    cout << "Enter Index of the Post to Delete: ";
    cin >> index;
    p = TOP;
    while (p->index != index) {
        r = p;
        p = p->next;
    }

    cout << p->index << ". Username - " << p->username << ", Post - " << p->post << " Votes - " << p->up_down_vote << endl;

    cout << "Please Confirm if you want to delete the Post (y/n) - ";
    cin >> confirm;
    if (confirm == 'n') {
        return 0;
    } else {
        if (index == counter) {
            q = p->next;
            p->next = nullptr;
            delete p;
            TOP = q;
        } else if (index == 1) {
            r->next = nullptr;
            delete p;
        } else {
            r->next = p->next;
            p->next = nullptr;
            delete p;
        }
    }
    return 0;
}

void Up_Down_Vote() {
    int choice;
    Post* p;
    cout << "Options:" << endl;
    cout << "1. Upvote" << endl;
    cout << "2. Downvote" << endl;
    cout << "Select from the above Options: ";
    cin >> choice;
    int index;
    cout << "Total no. of Posts are " << counter << endl;
    cout << "Enter Index of the Post to Vote: ";
    cin >> index;
    p = TOP;
    while (p->index != index) {
        p = p->next;
    }

    cout << p->index << ". Username - " << p->username << ", Post - " << p->post << ", Votes - " << p->up_down_vote << endl;

    switch (choice) {
        case 1:
            p->up_down_vote++;
            cout << "Post has been Upvoted" << endl;
            break;
        case 2:
            p->up_down_vote--;
            cout << "Post has been Downvoted" << endl;
            break;
    }
}

int Display_All_Posts() {
    Post* p;
    p = TOP;
    if(TOP == nullptr){
        cout<<"No Posts Entered Yet!!"<<endl;
        return 0;
    }
    while (p->next != nullptr) {
        cout << p->index << ". Username - " << p->username << ", Post - " << p->post << ", Votes - " << p->up_down_vote << endl;
        p = p->next;
    }
    cout << p->index << ". Username - " << p->username << ", Post - " << p->post << ", Votes - " << p->up_down_vote << endl;

    return 0;
}

int Display_User_Posts() {
    Post* p;
    p = TOP;
    char user[15];
    cout << "Enter Username to display its Posts: ";
    cin >> user;

    if(TOP == nullptr){
        cout<<"No Posts Entered Yet!!"<<endl;
        return 0;
    }
    while (p->next != nullptr) {
        if (strcmp(p->username, user) == 0) {
            cout << p->index << ". Username - " << p->username << ", Post - " << p->post << ", Votes - " << p->up_down_vote << endl;
        }
        p = p->next;
    }
    if (strcmp(p->username, user) == 0) {
        cout << p->index << ". Username - " << p->username << ", Post - " << p->post << ", Votes - " << p->up_down_vote << endl;
    }

    return 0;
}

int main() {
    ABOVE:
    int choice;

    cout << "Press 1 to Sign up" << endl;
    cout << "Press 2 to Log in" << endl;
    cout << "Press 3 to Exit" << endl;
    cout << "Select form the above choice - ";
    cin >> choice;

    switch (choice) {
        case 1:
            if (SignUp()) {
                break;
            } else {
                cout<<"Error Occurred, Try signing up again!!"<<endl;
                goto ABOVE;
            }
        case 2:
            if (LogIn()) {
                break;
            } else {
                goto ABOVE;
            }
        case 3:
            cout<<"Exiting the Program..."<<endl;
            exit(1);
        default:
            cout << "Invalid selection! Exiting the program..." << endl;
            exit(1);
    }

    do {
        cout << " " << endl;
        cout << "Press 1 to Enter post" << endl;
        cout << "Press 2 to Delete post" << endl;
        cout << "Press 3 to upvote or downvote a post" << endl;
        cout << "Press 4 to show posts of a particular user" << endl;
        cout << "Press 5 to display all posts" << endl;
        cout << "Press 6 to LogOut" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                Add_Post();
                break;
            case 2:
                Del_Post();
                break;
            case 3:
                Up_Down_Vote();
                break;
            case 4:
                Display_User_Posts();
                break;
            case 5:
                Display_All_Posts();
                break;
            case 6:
                cout << "Logged Out" << endl;
                goto ABOVE; 
            default:
                cout << "Invalid selection! Enter a Valid Choice!!" << endl;
        }
    } while (choice != 6);
}
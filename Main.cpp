#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Defining the student class
class Student {
    public:

    int rollNo;
    string name;
    float marks;

    void input();
    void display();
};

void Student::input(){
    cout<<"Enter Roll No: ";
    cin>>rollNo;

    cout<<"Enter Name:";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, name);
    cout<<"Enter Marks: ";
    cin>>marks;
}

void Student::display(){
    cout<<"Roll No: "<<rollNo<< ", Name: "<< name <<" , Marks: "<<marks<<endl;
}

//Adding a student to file
void addStudent(){
    Student s;
    s.input();
    ofstream outFile("students.txt", ios::binary | ios::app);
    outFile.write((char*)&s, sizeof(s));
    outFile.close();
    cout << "Student added successfully!" << endl;
}

//Viewing all students from file
void viewStude1nts(){
    Student s;
    ifstream in("students.txt", ios::binary);
    while(in.read((char*)&s, sizeof(s))){
        s.display();
    }
    in.close();
}

//Search Student by Roll No
void searchStudent(int rollNo) {
    Student s;
    bool found = false;
    ifstream in("students.txt", ios::binary);
    while (in.read((char*)&s, sizeof(s))) {
        if (s.rollNo == rollNo) {
            s.display();
            found = true;
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    in.close();
}

// Delete Student
void deleteStudent(int rollNo) {
    Student s;
    ifstream in("students.txt", ios::binary);
    ofstream out("temp.txt", ios::binary);
    while (in.read((char*)&s, sizeof(s))) {
        if (s.rollNo != rollNo) {
            out.write((char*)&s, sizeof(s));
        }
    }
    in.close();
    out.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    cout << "Student deleted if existed.\n";
}

// Update Student
void updateStudent(int rollNo) {
    fstream file("students.txt", ios::binary | ios::in | ios::out);
    Student s;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == rollNo) {
            cout << "Enter new details:\n";
            s.input();
            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            cout << "Updated successfully.\n";
            file.close();
            return;
        }
    }
    cout << "Student not found.\n";
    file.close();
}

int main() {
    int choice, rollNo;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Student\n2. View All\n3. Search\n4. Delete\n5. Update\n6. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3:
                cout << "Enter Roll: "; cin >> rollNo;
                searchStudent(rollNo); break;
            case 4:
                cout << "Enter Roll: "; cin >> rollNo;
                deleteStudent(rollNo); break;
            case 5:
                cout << "Enter Roll: "; cin >> rollNo;
                updateStudent(rollNo); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}



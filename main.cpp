#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <sstream>

using namespace std;



// creating class to define the structure of a node in doubly
class node{
public:
    int deptNo;
    int staffId;
    string deptName;
    string staffName;
    int salary;
    node* prev;
    node* next;

    // default constructor

    node(){

        this->deptNo = 0;
        this->staffId = 0;
        this->deptName = "";
        this->staffName = "";
        this->salary = 0;
        this->prev = NULL;
        this->next = NULL;

    }

    // constructor to add data to the node

    node(int a,int d,string b,string c,int k){

        this->deptNo = a;
        this->staffId = d;
        this->deptName = b;
        this->staffName = c;
        this->salary = k;
        this->prev = NULL;
        this->next = NULL;
    }
};

//global node array declaration

node* root[3];

/*
departments for now - CSE, IT, ECE
depNo for the same -  1, 2 , 3
 */

// declaring functions

void menu();
void showDeptList();
void insert(node* root[]);
void sort();
// void sort(); ---> parameters yet to decide

// A list of departments

void showDeptList(){
    cout<<endl<<endl;
    cout<<"1 -> CSE"<<endl;
    cout<<"2. -> IT"<<endl;
    cout<<"3. -> ECE"<<endl;
}
/*

using insert creating doubly linked list for each department
root[0] --> CSE
root[1] --> IT
root[2] --> ECE

writing inputted data in common file "StaffData.txt"
simultaneously entering in department specific files "StaffCSE.txt", "StaffIT.txt", "StaffECE.txt"

 */

void insert(node* root[]){
    int deNo;
    string facName;
    int sal;

    // creating an ofstream object for writing in the file

    ofstream fout;

    //append mode

    fout.open("StaffData.txt",ios::app);

    // ask user to input data

    cout<<"Enter the department number:";
    showDeptList();
    cin>>deNo;

    cout<<"Enter Faculty name:";
    cin>>facName;

    srand((unsigned int)time(NULL));

    int staffId = rand() % 500;

    cout<<"Enter Faculty's salary : ";
    cin>>sal;

// for CSE

    if(deNo==1){
        node *temp = new node(deNo,staffId,"CSE",facName,sal);

        // writing data in the file

        fout<<deNo<<" "<<staffId<<" CSE "<<facName<<" "<<sal<<endl;

        ofstream cse;
        cse.open("StaffCSE.txt",ios::app);

        cse<<deNo<<" "<<staffId<<" CSE "<<facName<<" "<<sal<<endl;


        // check if the list is empty
        if(root[0]== NULL){
            root[0] = temp;
        }

        else{
            node* curr = root[0];
            while(curr!=NULL){
                curr = curr->next;
            }
            curr->next= temp;
            temp->prev = curr;
        }

        cse.close();
        cout<<endl<<endl;
        menu();
    }

    // for IT

    else if(deNo==2){
        node *temp = new node(deNo,staffId,"IT",facName,sal);

        fout<<deNo<<" "<<staffId<<" IT "<<facName<<" "<<sal<<endl;

        ofstream it;
        it.open("StaffIT.txt",ios::app);

        it<<deNo<<" "<<staffId<<" IT "<<facName<<" "<<sal<<endl;


        // check if the list is empty
        if(root[1]== NULL){
            root[1] = temp;
        }

        else{
            node* curr = root[1];
            while(curr!=NULL){
                curr = curr->next;
            }
            curr->next= temp;
            temp->prev = curr;
        }

        it.close();
        cout<<endl<<endl;
        menu();
    }

    // for ECE

    else if(deNo==3){
        node *temp = new node(deNo,staffId,"ECE",facName,sal);
        fout<<deNo<<" "<<staffId<<" ECE "<<facName<<" "<<sal<<endl;

        ofstream ece;
        ece.open("StaffECE.txt",ios::app);

        ece<<deNo<<" "<<staffId<<" ECE "<<facName<<" "<<sal<<endl;


        // check if the list is empty
        if(root[2]== NULL){
            root[2] = temp;
        }

        else{
            node* curr = root[2];
            while(curr!=NULL){
                curr = curr->next;
            }
            curr->next= temp;
            temp->prev = curr;
        }

        ece.close();
        cout<<endl<<endl;
        menu();
    }

    // incorrect choice

    else{
        cout<<"Incorrect Department number. Please enter a valid number"<<endl;
        cout<<endl<<endl;
        menu();
    }
    
    fout.close();
}

// Menu for the user interface
//Declaring display function

//declaring functions for sorting the linked list
// split() to find the middle node address by slow fast method

// merge() similar to that used in array, to merge two linked lists

node* mergesort(node* head);

node* split(node* head);

node* merge(node* &head,node* first,node* second);

void search();

void display();

void calldel();

void del(int id);

void deleteline();

void editSalary();

void editName();


void modify(){
    int choice;
    cout<<"1.Modify name "<<endl;
    cout<<"2.Modify Salary "<<endl;
    cout<<"Enter your chocie (1/2):";
    cin>>choice;

    switch (choice){
        case 1:
            editName();
            menu();
            break;
        case 2:
            editSalary();
            menu();
            break;
        default:
            cout<<"Invalid choice"<<endl;
            menu();
            break;
    }
}

void menu(){

    int choice;
    cout<<endl;
    cout<<"1.Add new Staff Member "<<endl;
    cout<<"2.Delete a Staff Member"<<endl;
    cout<<"3.Display desired details "<<endl;
    cout<<"4.Search for a staff  "<<endl;
    cout<<"5.Modify Staff Data "<<endl;
    cout<<"6.exit "<<endl;

    // ask user to chose from above operations

    cout<<"Please enter your choice: (1/2/3/4/5/6):";
    cin>>choice;

    if(choice == 1){
        insert(root);
    }

    else if (choice==2){
        deleteline();
    }
    else if(choice==3){
        display();
    }

    else if(choice==4){
        search();
    }
    else if(choice==5){
        modify();
    }
    else if(choice==6){
        exit(0);
    }
}

// declare global array of node* type
// head[0] => ALL STAFF'S DETAILS
// HEAD[1] => CSE STAFF'S DETAILS
// HEAD[2] => ECE STAFF'S DETAILS
// HEAD[3] => IT STAFF'S DETAILS

node *head[4];

void extract(node* &head,string filename){

    ifstream fin;
    fin.open(filename,ios::in);
    int a,d,e;
    string b,c;

    if(fin.is_open()){
    // reads data if entered...eof() not used to avoid to reading of an empty line and causing anomoly
    while(fin>>a>>d>>b>>c>>e){
        node *temp = new node(a,d,b,c,e);

        if(head == NULL){
            head = temp;
        }

        else{

            node *curr = head;

            while(curr->next != NULL){
                curr=curr->next;
            }

            curr->next=temp;
            temp->prev = curr;
        }
    }
}
}

//To print linked list
void print(node* head){
    node *curr = head;
    cout<<"\tDepartment No. \t |staffId\t| Department name\t |Staff Name\t|Salary \t\t"<<endl;
    while(curr!=NULL){
        if(curr->deptName!="NULL" && curr->staffName!="NULL"){
        cout<<"\t\t"<<curr->deptNo<<"\t\t"<<curr->staffId<<"\t\t"<<curr->deptName<<"\t\t\t"<<curr->staffName<<"\t\t"<<curr->salary<<"\t\t"<<endl;
        }
        curr = curr->next;

    }
}
node* LinearSearch(node* head,int x);
void display(){

    int k;
    int z;

    cout<<"1. Sorted Display "<<endl;
    cout<<"2. Unsorted Display "<<endl<<endl;
    cout<<"ENTER YOUR CHOICE : ";
    cin>>z;

    if(z==2){

    cout<<"Choose the department you want to see data of: "<<endl;
    cout<<"1. CSE"<<endl;
    cout<<"2. IT"<<endl;
    cout<<"3. ECE"<<endl;
    cout<<"4. ALL DEPARTMEMTS"<<endl<<endl;
    cout<<"ENTER YOUR CHOICE : ";

    cin>>k;

    switch(k){

        case 1:
            extract(head[0],"StaffCSE.txt");
            print(head[0]);
            head[0]=NULL;
            menu();
            break;

        case 2:
            extract(head[1],"StaffIT.txt");
            print(head[1]);
            head[1]=NULL;
            menu();
            break;

        case 3:
            extract(head[2],"StaffECE.txt");
            print(head[2]);
            head[2]=NULL;

            menu();
            break;

        case 4:
            extract(head[3],"StaffData.txt");
            print(head[3]);
            head[3]=NULL;
            menu();
            break;

        default:
            cout<<"Invalid choice"<<endl;
            menu();
            break;

        }
    }

    else if(z==1){

    cout<<"Choose the department you want to see data of: "<<endl;
    cout<<"1. CSE"<<endl;
    cout<<"2. IT"<<endl;
    cout<<"3. ECE"<<endl;
    cout<<"4. ALL DEPARTMEMTS"<<endl<<endl;
    cout<<"ENTER YOUR CHOICE : ";

    cin>>k;

    switch(k){

        case 1:
            extract(head[0],"StaffCSE.txt");
            head[0] = mergesort(head[0]);
            print(head[0]);
            head[0]=NULL;
            menu();
            break;

        case 2:
            extract(head[1],"StaffIT.txt");
            head[1] = mergesort(head[1]);
            print(head[1]);
            head[1]=NULL;
            menu();
            break;

        case 3:
            extract(head[2],"StaffECE.txt");
            head[2] = mergesort(head[2]);
            print(head[2]);
            head[2]=NULL;

            menu();
            break;

        case 4:
            extract(head[3],"StaffData.txt");
            head[3] = mergesort(head[3]);
            print(head[3]);
            head[3]=NULL;
            menu();
            break;

        default:
            cout<<"Invalid choice"<<endl;
            menu();
            break;

        }
    }
}

// void displayLL(node head[]){
//     cout<<root->deptNo<<"  "<<root->deptName<<"  "<<root->staffName;
// }

node* merge(node* first,node* second){

    if(!first){
        return second;
    }
    if(!second){
        return first;
    }
    if(first->staffId < second->staffId){
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else{
        second->next = merge(second->next,first);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
    }


node* mergesort(node* head){

    if(head==NULL || head->next==NULL)
        return head;

    node* second = split(head);

    head = mergesort(head);
    second = mergesort(second);

    return merge(head,second);
}

node* split(node* head){

    node* second;
    node* slow = head;
    node* fast = head->next;

    while(fast!=NULL){

        fast = fast->next;

        if(fast!=NULL){

            slow = slow->next;
            fast = fast->next;

        }
    }

    second = slow->next;
    slow->next = NULL;

    return second;

}

node* middle(node* start,node *last){

    if(start == NULL){
        return NULL;
    }
    node* slow = start;
    node* fast = start->next;

    while(fast!=last){
        fast = fast->next;
        if(fast!=last){
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

node* BinarySearch(node* head,int value){
    node* start = head;
    node* last = NULL;

    do{
        node* mid = middle(start,last);

        if(mid == NULL){
            return NULL;
        }
        if(mid->staffId == value ){
            return mid;
        }

        // if mid value less than required value.....start value = next of mid/ right side of mid
        else if(mid->staffId < value){
            start = mid->next;
        }

        // if mid value greater than required value.....last value =  mid/ left side of mid

        else if(mid->staffId > value){
            last = mid;
        }

    }while(last==NULL|| last!=start);

    // if value not found then null

    return NULL;

}

node* searchname(string name);

void search(){

    int requestId;
    node* searched;
    int choice;

    cout<<"1. Search by ID"<<endl;
    cout<<"2. Search by staff name"<<endl<<endl;
    cout<<"ENTER YOUR CHOICE :";
    cin>>choice;
    //asl for input from the user

    if(choice==1){
    cout<<"Enter the ID of the required Staff member : ";
    cin>>requestId;

    extract(head[0],"StaffData.txt");
    // mergesort(head[0]);

    searched = LinearSearch(head[0],requestId);

    if(searched==NULL){
        cout<<"Your requested staff with the entered staff ID does not exist"<<endl;
    }

    else{
        cout<<"\tDepartment No. \t |staffId\t| Department name\t |Staff Name\t |Salary\t\t"<<endl;
        cout<<"\t\t"<<searched->deptNo<<"\t\t"<<searched->staffId<<"\t\t"<<searched->deptName<<"\t\t\t"<<searched->staffName<<"\t\t"<<searched->salary<<"\t\t"<<endl;
    }


    head[0] = NULL;

}

    if(choice == 2){
        string search;
        cout<<"Enter the name of the member whom you want to search : ";
        cin>>search;

        searched = searchname(search);

        if(searched==NULL){
        cout<<"Your requested staff with the entered staff ID does not exist"<<endl;
    }

    else{
        cout<<"\tDepartment No. \t |staffId\t| Department name\t |Staff Name\t |Salary\t\t"<<endl;
        cout<<"\t\t"<<searched->deptNo<<"\t\t"<<searched->staffId<<"\t\t"<<searched->deptName<<"\t\t\t"<<searched->staffName<<"\t\t"<<searched->salary<<"\t\t"<<endl;
    }


    }

    menu();

    }

node* searchname(string name){

    node* searched;
    extract(head[0],"StaffData.txt");
    node *curr = head[0];
    head[0] = NULL;
    while(curr->next!=NULL){

        if(curr->staffName==name){
            return curr;
        }

        curr = curr->next;

    }

    // no such entry exists
    return NULL;

}

// void calldel(){

//     int ask;
//     cout<<"Enter the id of the staff member you want to delete data of: ";
//     cin>>ask;

//     del(ask);

// }

// void del(int id){

//     node* curr;
//     extract(curr,"StaffData.txt");
//     node* find;
//     find = BinarySearch(curr,id);
//     fstream file;
//     fstream prev;
//     if(find!=NULL)
//     {

//     file.open("temp.txt",ios::out);
//     prev.open("StaffData.txt",ios::in);

//     int a,b,e;
//     string c,d;

//     while(prev>>a>>b>>c>>d>>e){
//         node* temp = new node(a,b,c,d,e);

//         if(temp->staffId!=find->staffId){
//             file<<temp->deptNo<<" "<<temp->staffId<<" "<<temp->deptName<<" "<<temp->staffName<<" "<<temp->salary<<endl;
//         }
//         else{
//             continue;
//         }
//     }

//     file.close();
//     prev.close();

//     remove("StaffData.txt");
//     rename("temp.txt","StaffData.txt");


//     if(find->deptNo == 1){
//         file.open("StaffCSE.txt",ios::in);
//         prev.open("temp.txt",ios::out);

//         int a,b,e;
//         string c,d;

//         while(file>>a>>b>>c>>d>>e){
//             node* temp = new node(a,b,c,d,e);

//         if(temp->staffId!=find->staffId){
//             prev<<temp->deptNo<<" "<<temp->staffId<<" "<<temp->deptName<<" "<<temp->staffName<<" "<<temp->salary<<endl;
//         }
//         else{
//             continue;
//         }
//         }

//         file.close();
//         prev.close();

//         remove("StaffCSE.txt");
//         rename("temp.txt","StaffCSE.txt");

//     }

//     else if(find->deptNo == 2){

//         file.open("StaffIT.txt",ios::in);
//         prev.open("temp1.txt",ios::out);
//         int a,b,e;
//         string c,d;

//         while(file>>a>>b>>c>>d>>e){
//             node* temp = new node(a,b,c,d,e);

//         if(temp->staffId!=find->staffId){
//             prev<<temp->deptNo<<" "<<temp->staffId<<" "<<temp->deptName<<" "<<temp->staffName<<" "<<temp->salary<<endl;
//         }
//         else{
//             continue;
//         }
//         }

//         file.close();
//         prev.close();

//         remove("StaffIT.txt");
//         rename("temp.txt","StaffIT.txt");

//     }

//     else if(find->deptNo == 3){
//         file.open("StaffECE.txt",ios::in);
//         prev.open("temp1.txt",ios::out);

//         int a,b,e;
//         string c,d;

//         while(file>>a>>b>>c>>d>>e){
//             node* temp = new node(a,b,c,d,e);

//         if(temp->staffId!=find->staffId){
//             prev<<temp->deptNo<<" "<<temp->staffId<<" "<<temp->deptName<<" "<<temp->staffName<<" "<<temp->salary<<endl;
//         }
//         else{
//             continue;
//         }
//         }

//         file.close();
//         prev.close();

//         remove("StaffIT.txt");
//         rename("temp.txt","StaffECE.txt");

//     }
// }
//     else{
//         cout<<"No Staff member with requested id exists."<<endl;
//     }

//     menu();

// }

void deletelineIT(string staffid);
void deletelineCSE(string staffid);
void deletelineECE(string staffid);

 void deleteline(){

    string StaffID;
    string line;

    ifstream fin;
    fin.open("StaffData.txt");
    ofstream temp;
    temp.open("temp.txt");
    cout << "Input id to remove: "; //input line to remove
    cin >> StaffID;
    string nth;
    while (getline(fin, line))
    {
        if (line.find(StaffID) != string::npos)
        {
            std::istringstream ss(line);
            for (int i = 0; i < 1; ++i)
                ss >> nth;
            continue;
        }
        temp << line << endl;
    }

    temp.close();
    fin.close();
    remove("StaffData.txt");
    rename("temp.txt", "StaffData.txt");

    if(nth == "1"){
        deletelineCSE(StaffID);
    }

    else if(nth == "2"){
        deletelineIT(StaffID);
    }

    else if(nth == "3"){
        deletelineECE(StaffID);
    }
 }

  void deletelineCSE(string staffid){

    // string StaffID;
    string line1;

    ifstream fin1;
    fin1.open("StaffCSE.txt");
    ofstream temp1;
    temp1.open("temp1.txt");
    // cout << "Input id to remove: "; //input line to remove
    // cin >> StaffID;
    string nth;
    while (getline(fin1, line1))
    {
        if (line1.find(staffid) != string::npos)
        {
            // std::istringstream ss(line1);
            // for (int i = 0; i < 1; ++i)
            //     ss >> nth;
            continue;
        }
        temp1 << line1 << endl;
    }

    temp1.close();
    fin1.close();
    remove("StaffCSE.txt");
    rename("temp1.txt", "StaffCSE.txt");

 }

   void deletelineIT(string staffid){

    // string StaffID;
    string line1;

    ifstream fin1;
    fin1.open("StaffIT.txt");
    ofstream temp1;
    temp1.open("temp1.txt");
    // cout << "Input id to remove: "; //input line to remove
    // cin >> StaffID;
    string nth;
    while (getline(fin1, line1))
    {
        if (line1.find(staffid) != string::npos)
        {
            // std::istringstream ss(line1);
            // for (int i = 0; i < 1; ++i)
            //     ss >> nth;
            continue;
        }
        temp1 << line1 << endl;
    }

    temp1.close();
    fin1.close();
    remove("StaffIT.txt");
    rename("temp1.txt", "StaffIT.txt");

 }

   void deletelineECE(string staffid){

    // string StaffID;
    string line1;

    ifstream fin1;
    fin1.open("StaffECE.txt");
    ofstream temp1;
    temp1.open("temp1.txt");
    // cout << "Input id to remove: "; //input line to remove
    // cin >> StaffID;
    string nth;
    while (getline(fin1, line1))
    {
        if (line1.find(staffid) != string::npos)
        {
            // std::istringstream ss(line);
            // for (int i = 0; i < 1; ++i)
            //     ss >> nth;
            continue;
        }
        temp1 << line1 << endl;
    }

    temp1.close();
    fin1.close();
    remove("StaffECE.txt");
    rename("temp1.txt", "StaffECE.txt");

 }
/*
int x = 0;
    string choice = "staffName";

    if (choice == "deptNo") {
        x=1;
    }
    else if (choice == "staffId") {
        x=2;
    }
    else if (choice == "deptName") {
        x=3;
    }
    else if (choice == "staffName") {
        x=4;
    }
    else if (choice == "salary") {
        x=5;
    }

    ifstream fin;
    fin.open("StaffData.txt");
    string line;
    string nth;
    getline(fin, line);
    std::istringstream ss(line);
    for (int i = 0; i < x; ++i)
        ss >> nth;
    cout<< "||" << nth << "||" << endl;
    fin.close();
*/

void editSalaryCSE(int sal,int deno,int id);
void editSalaryECE(int sal,int deno,int id);
void editSalaryIT(int sal,int deno,int id);
void editNameCSE(int id,int deno,string name);
void editNameIT(int id,int deno,string name);
void editNameECE(int id,int deno,string name);

void editSalary() {

    int id;
    cout << "Enter the id of the staff member you want to edit salary of: ";
    cin >> id;
    node* curr;
    extract(curr, "StaffData.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    int sal;
    int deno;
    if (find != NULL)
    {

        file.open("temp.txt", ios::out);
        prev.open("StaffData.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != find->staffId) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                cout << "Enter the new salary: ";
                cin >> temp->salary;
                sal = temp->salary;
                deno = temp->deptNo;
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffData.txt");
        rename("temp.txt", "StaffData.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }

    if(deno == 1){
        editSalaryCSE(sal,deno,id);
    }

    else if(deno==2){
        editSalaryIT(sal,deno,id);
    }
    else if(deno==3){
        editSalaryECE(sal,deno,id);
    }
}


void editName() {

    int id;
    cout << "Enter the id of the staff member you want to edit name of: ";
    cin >> id;
    node* curr;
    extract(curr, "StaffData.txt");
    node* find;
    find = LinearSearch(curr, id);
    int deno;
    string name;
    fstream file;
    fstream prev;
    if (find != NULL)
    {
        file.open("temp.txt", ios::out);
        prev.open("StaffData.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != find->staffId) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                cout << "Enter the new name: ";
                cin >> temp->staffName;
                name = temp->staffName;
                deno = temp->deptNo;
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffData.txt");
        rename("temp.txt", "StaffData.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }

    if(deno==1){
        editNameCSE(id,deno,name);
    }

    else if(deno==2){
        editNameIT(id,deno,name);
    }

    else if(deno==3){
        editNameECE(id,deno,name);
    }
}

node* LinearSearch(node* head, int x)
{
    node* current = head;
    while (current != NULL)
    {
        if (current->staffId == x)
            return current;
        current = current->next;
    }
    return NULL;
}

void editNameIT(int id,int deno,string name) {
    //int id;
   // cout << "Enter the id of the staff member you want to edit name of: ";
    //cin >> id;
    node* curr;
    extract(curr, "StaffIT.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffIT.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                //cout << "Enter the new name: ";
                //cin >> temp->staffName;
                file << deno<< " " << id << " " << temp->deptName << " " << name << " " << temp->salary << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffIT.txt");
        rename("temp1.txt", "StaffIT.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

void editNameECE(int id,int deno,string name) {
    //int id;
   // cout << "Enter the id of the staff member you want to edit name of: ";
    //cin >> id;
    node* curr;
    extract(curr, "StaffECE.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffECE.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                //cout << "Enter the new name: ";
                //cin >> temp->staffName;
                file << deno<< " " << id << " " << temp->deptName << " " << name << " " << temp->salary << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffECE.txt");
        rename("temp1.txt", "StaffECE.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

void editNameCSE(int id,int deno,string name) {
    //int id;
   // cout << "Enter the id of the staff member you want to edit name of: ";
    //cin >> id;
    node* curr;
    extract(curr, "StaffCSE.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffCSE.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                //cout << "Enter the new name: ";
                //cin >> temp->staffName;
                file << deno<< " " << id << " " << temp->deptName << " " << name << " " << temp->salary << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffCSE.txt");
        rename("temp1.txt", "StaffCSE.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

void editSalaryCSE(int sal,int deno,int id) {
    // int id;
    // cout << "Enter the id of the staff member you want to edit salary of: ";
    // cin >> id;
    node* curr;
    extract(curr, "StaffCSE.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffCSE.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                // cout << "Enter the new salary: ";
                // cin >> temp->salary;
                file << deno << " " << id << " " << temp->deptName << " " << temp->staffName << " " << sal << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffCSE.txt");
        rename("temp1.txt", "StaffCSE.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

void editSalaryIT(int sal,int deno,int id) {
    // int id;
    // cout << "Enter the id of the staff member you want to edit salary of: ";
    // cin >> id;
    node* curr;
    extract(curr, "StaffIT.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffIT.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                // cout << "Enter the new salary: ";
                // cin >> temp->salary;
                file << deno << " " << id << " " << temp->deptName << " " << temp->staffName << " " << sal << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffIT.txt");
        rename("temp1.txt", "StaffIT.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

void editSalaryECE(int sal,int deno,int id) {
    // int id;
    // cout << "Enter the id of the staff member you want to edit salary of: ";
    // cin >> id;
    node* curr;
    extract(curr, "StaffECE.txt");
    node* find;
    find = LinearSearch(curr, id);
    fstream file;
    fstream prev;
    if (find != NULL)
    {

        file.open("temp1.txt", ios::out);
        prev.open("StaffECE.txt", ios::in);

        int a, b, e;
        string c, d;

        while (prev >> a >> b >> c >> d >> e) {
            node* temp = new node(a, b, c, d, e);

            if (temp->staffId != id) {
                file << temp->deptNo << " " << temp->staffId << " " << temp->deptName << " " << temp->staffName << " " << temp->salary << endl;
            }
            else {
                // cout << "Enter the new salary: ";
                // cin >> temp->salary;
                file << deno << " " << id << " " << temp->deptName << " " << temp->staffName << " " << sal << endl;
            }
        }

        file.close();
        prev.close();

        remove("StaffECE.txt");
        rename("temp1.txt", "StaffECE.txt");
    }

    else {
        cout << "No Staff member with requested id exists." << endl;
    }
}

int main(){

    // node* li[3];
    menu();
    return 0;

}

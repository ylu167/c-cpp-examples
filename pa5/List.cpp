/********************************************************************************* 
* List.cpp
* Implementation file for List ADT
*********************************************************************************/
#include "List.h"
#include <iostream>
#include <string>

using namespace std;

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = NULL;
    prev = NULL;
}

// Creates new List in the empty state.
List::List(){
    List::Node *frontDummy = (Node*)malloc(sizeof(Node));
    List::Node *backDummy = (Node*)malloc(sizeof(Node));
    *frontDummy = Node(-1);
    *backDummy = Node(-2);
    this -> frontDummy = frontDummy;
    this -> backDummy = backDummy;
    this -> frontDummy -> next = this -> backDummy;
    this -> backDummy -> prev = this -> frontDummy;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> backDummy;
    this -> pos_cursor = 0;
    this -> num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
    List::Node *frontDummy = (Node*)malloc(sizeof(Node));
    List::Node *backDummy = (Node*)malloc(sizeof(Node));
    *frontDummy = Node(-1);
    *backDummy = Node(-2);
    
    this -> frontDummy = frontDummy;
    this -> backDummy = backDummy;
    this -> frontDummy -> next = this -> backDummy;
    this -> backDummy -> prev = this -> frontDummy;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> backDummy;
    this -> pos_cursor = 0;
    this -> num_elements = 0;
    
    List::Node *element = L.frontDummy -> next;
    for (int i = 1; i <= L.num_elements; i++){
        insertAfter(element -> data);
        moveNext();
        element = element -> next;
    }
    this -> pos_cursor = 0;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> beforeCursor -> next;
    this -> num_elements = L.length();
    
}

// Destructor
List::~List(){
    clear();
    free (this -> frontDummy);
    free (this -> backDummy);
    this -> beforeCursor = NULL;
    this -> afterCursor = NULL;
    this -> frontDummy = NULL;
    this -> backDummy = NULL;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return this -> num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(this -> num_elements != 0){
        return this -> frontDummy -> next -> data;
    }else{
        throw std::length_error("No data exist!");
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(this -> num_elements != 0){
        return this -> backDummy -> prev -> data;
    }else{
        throw std::length_error("No data exist!");
    }
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return this -> pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("No Data Next!");
        return -1;
    }
    return this -> afterCursor -> data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (this -> pos_cursor == 0){
        throw std::range_error("No Data Prev!");
        return -1;
    }
    return this -> beforeCursor -> data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    for (int i = 1; i <= this -> num_elements; i++){
        eraseAfter();
    }
    this -> pos_cursor = 0;
    this -> num_elements = 0;
    return;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    this -> pos_cursor = 0;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> frontDummy -> next;
    return;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    this -> pos_cursor = this -> num_elements;
    this -> beforeCursor = this -> backDummy -> prev;
    this -> afterCursor = this -> backDummy;
    return;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext(){
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("No Node Next!");
        return -1;
    }
    ListElement val = this -> afterCursor -> data;
    this -> pos_cursor++;
    this -> beforeCursor = this -> beforeCursor -> next;
    this -> afterCursor = this -> afterCursor -> next;
    return val;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev(){
    if(this -> pos_cursor == 0){
        throw std::range_error("No Node Prev!");
        return -1;
    }
    ListElement val = this -> beforeCursor -> data;
    this -> pos_cursor--;
    this -> afterCursor = this -> afterCursor -> prev;
    this -> beforeCursor = this -> beforeCursor -> prev;
    return val;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    List::Node *element = (Node*)malloc(sizeof(Node));
    *element = Node(x);
    this -> beforeCursor -> next = element;
    this -> afterCursor -> prev = element;
    element -> next = this -> afterCursor;
    element -> prev = this -> beforeCursor;
    
    this -> num_elements++;
    this -> afterCursor = element;
    
    
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    List::Node *element = (Node*)malloc(sizeof(Node));
    *element = Node(x);
    this -> beforeCursor -> next = element;
    this -> afterCursor -> prev = element;
    element -> next = this -> afterCursor;
    element -> prev = this -> beforeCursor;
    this -> num_elements++;
    this -> pos_cursor++;
    this -> beforeCursor = element;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("No Node Next!");
        return;
    }
    this -> afterCursor -> data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(this -> pos_cursor == 0){
        throw std::range_error("No Node Prev!");
        return;
    }
    this -> beforeCursor -> data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("No Node Next!");
        return;
    }
    Node* element = this -> afterCursor;
    this -> beforeCursor -> next = this -> afterCursor -> next;
    this -> afterCursor -> next -> prev = this -> beforeCursor;
    this -> afterCursor = this -> afterCursor -> next;
    this -> num_elements--;
    free(element);
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(this -> pos_cursor == 0){
        throw std::range_error("No Node Prev!");
        return;
    }
    Node* element = this -> beforeCursor;
    this -> beforeCursor -> prev -> next = this -> afterCursor;
    this -> afterCursor -> prev = this -> beforeCursor -> prev;
    this -> beforeCursor = this -> beforeCursor -> prev;
    this -> num_elements--;
    this -> pos_cursor--;
    free(element);
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x){
    while(this -> pos_cursor < this -> num_elements){
        if (moveNext() == x){
            return position();
        }
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x){
    while(this -> pos_cursor > 0){
        cout << "peek Prev = " << peekPrev() << endl;
        cout << "position = " << position() << endl;
        if (movePrev() == x){
            return position();
        }
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    int* data = (int*) malloc(sizeof(int) * (this -> num_elements + 1));
    for (int i = 0; i <= this -> num_elements; i++){
        data[i] = 0;
    }
    int count = 1;
    Node* element = this -> frontDummy -> next;
    
    int length = this -> num_elements;
    int pos = position();
    while(count <= length){
        data[count] = element -> data;
        for (int i = 1; i < count; i++){
            if(data[count] == data[i]){
                element -> prev -> next = element -> next;
                element -> next -> prev = element -> prev;
                if(count <= pos){
                    this -> pos_cursor--;
                }
                this -> num_elements--;
                break;
            }
        }
        element = element -> next;
        count++;
    }
    pos = position();
    moveFront();
    while(position() != pos){
        moveNext();
    }
    
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List Result = List();
    Node *element = this -> frontDummy -> next;
    for (int i = 0; i < this -> num_elements; i++){
        Result.insertAfter(element -> data);
        Result.moveNext();
        element = element -> next;
    }
    element = L.frontDummy -> next;
    for (int i = 0; i < L.num_elements; i++){
        Result.insertAfter(element -> data);
        Result.moveNext();
        element = element -> next;
    }
    Result.pos_cursor = 0;
    Result.beforeCursor = Result.frontDummy;
    Result.afterCursor = Result.frontDummy -> next;
    Result.num_elements = this -> num_elements + L.num_elements;
    return Result;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    if (this -> num_elements == 0){
        return "()";
    }
    string result;
    result.append("(");
    Node* element = this -> frontDummy -> next;
    for (int i = 1; i < this -> num_elements; i++){
        result.append(std::to_string(element -> data));
        result.append(",");
        element = element -> next;
    }
    result.append(std::to_string(element -> data));
    result.append(")");
    return result;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (this -> num_elements != R.num_elements){
        return false;
    }
    Node* element_L = this -> frontDummy -> next;
    Node* element_R = R.frontDummy -> next;
    for (int i = 1; i <= this -> num_elements; i++){
        if (element_L -> data != element_R -> data){
            return false;
        }else{
            element_L = element_L -> next;
            element_R = element_R -> next;
        }
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    stream << L.to_string();
    return stream;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    List::Node *frontDummy = (Node*)malloc(sizeof(Node));
    List::Node *backDummy = (Node*)malloc(sizeof(Node));
    *frontDummy = Node(-1);
    *backDummy = Node(-2);
    
    this -> frontDummy = frontDummy;
    this -> backDummy = backDummy;
    this -> frontDummy -> next = this -> backDummy;
    this -> backDummy -> prev = this -> frontDummy;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> backDummy;
    this -> pos_cursor = 0;
    this -> num_elements = 0;
    
    List::Node *element = L.frontDummy -> next;
    for (int i = 1; i <= L.num_elements; i++){
        insertAfter(element -> data);
        moveNext();
        element = element -> next;
    }
    this -> pos_cursor = 0;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> beforeCursor -> next;
    this -> num_elements = L.length();
    
    return *this;
}

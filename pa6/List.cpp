/********************************************************************************* 
* List.cpp
* Implementation of performing arithmetic operations on arbitrarily 
* large signed integers by using BigInterger ADT
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
    // List::Node *frontDummy = (Node*)malloc(sizeof(Node));
    // List::Node *backDummy = (Node*)malloc(sizeof(Node));
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
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
    // List::Node *frontDummy = (Node*)malloc(sizeof(Node));
    // List::Node *backDummy = (Node*)malloc(sizeof(Node));
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    
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
    // free (this -> frontDummy);
    // free (this -> backDummy);
    // this -> beforeCursor = NULL;
    // this -> afterCursor = NULL;
    // this -> frontDummy = NULL;
    // this -> backDummy = NULL;
    delete frontDummy;
    delete backDummy;
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
        throw std::length_error("List: front(): no data exist");
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(this -> num_elements != 0){
        return this -> backDummy -> prev -> data;
    }else{
        throw std::length_error("List: back(): no data exist");
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
        throw std::range_error("List: peakNext(): no next cursor");
    }
    return this -> afterCursor -> data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (this -> pos_cursor == 0){
        throw std::range_error("List: peakPrev(): no prev cursor");
    }
    return this -> beforeCursor -> data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
    this -> pos_cursor = 0;
    this -> num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    this -> pos_cursor = 0;
    this -> beforeCursor = this -> frontDummy;
    this -> afterCursor = this -> frontDummy -> next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    this -> pos_cursor = this -> num_elements;
    this -> beforeCursor = this -> backDummy -> prev;
    this -> afterCursor = this -> backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext(){
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("List: moveNext(): no next cursor");
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
        throw std::range_error("List: movePrev(): no prev cursor");
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
    // List::Node *element = (Node*)malloc(sizeof(Node));
    Node *element = new Node(x);
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
    // List::Node *element = (Node*)malloc(sizeof(Node));
    Node *element = new Node(x);
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
        throw std::range_error("List: setAfter(): no next cursor");
    }
    this -> afterCursor -> data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(this -> pos_cursor == 0){
        throw std::range_error("List: setBefore(): no prev cursor");
    }
    this -> beforeCursor -> data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if (this -> pos_cursor == this -> num_elements){
        throw std::range_error("List: eraseAfter(): no next cursor");
    }
    Node* element = this -> afterCursor;
    this -> beforeCursor -> next = this -> afterCursor -> next;
    this -> afterCursor -> next -> prev = this -> beforeCursor;
    this -> afterCursor = this -> afterCursor -> next;
    this -> num_elements--;
    // free(element);
    delete element;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(this -> pos_cursor == 0){
        throw std::range_error("List: eraseBefore(): no prev cursor");
    }
    Node* element = this -> beforeCursor;
    this -> beforeCursor -> prev -> next = this -> afterCursor;
    this -> afterCursor -> prev = this -> beforeCursor -> prev;
    this -> beforeCursor = this -> beforeCursor -> prev;
    this -> num_elements--;
    this -> pos_cursor--;
    // free(element);
    delete element;
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
        // cout << "peek Prev = " << peekPrev() << endl;
        movePrev();
        if (afterCursor -> data == x){
            // cout << "return position = " << position() << endl;
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
    // int* data = (int*) malloc(sizeof(int) * (this -> num_elements + 1));
    // for (int i = 0; i <= this -> num_elements; i++){
    //     data[i] = 0;
    // }
    int start = 1;
    Node* element = this -> frontDummy -> next;
    // int pos = position();
    // Node* temp = new Node(0);
    while (element != backDummy) {
        int count = start;
        Node* next_element = element -> next;
        // for (int j = 1; j < this -> num_elements; j++) {
        while (next_element != backDummy) {
            // cout << "position() = " << position() << endl;
            if(element -> data == next_element -> data){
                Node *temp = next_element;
                temp -> prev -> next = temp -> next;
                temp -> next -> prev = temp -> prev;
                next_element = next_element->next;
                delete temp;
                if (count < position()) {
                    this -> pos_cursor --;
                } else if (count == position()) {
                    beforeCursor = next_element -> prev;
                    this -> pos_cursor --;
                } else if (count == position() + 1) {
                    afterCursor = next_element;
                }
                num_elements --;
                count ++;
                continue;
            }
            count ++;
            next_element = next_element->next;
        }
        // this -> num_elements -= count;
        // count = 0;
        element = element -> next;
        start++;
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
    std::string result = "(";
    Node* element = this -> frontDummy -> next;
    for (int i = 1; i < this -> num_elements; i++){
        result += std::to_string(element -> data) + ", ";
        element = element -> next;
    }
    result += std::to_string(element -> data);
    result += ")";
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
    // stream << L.to_string();
    // return stream;
    return stream << L.List::to_string();
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
    // from example of the professor
    if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }

   // return this with the new data installed
   return *this;
}

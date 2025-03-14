/********************************************************************************* 
* Dictionary.cpp
* Implementation file for Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

// Node constructor
Dictionary::Node::Node(keyType x, valType y){
    key = x;
    val = y;
    left = NULL;
    right = NULL;
    parent = NULL;
    color = 1;  // red = 0; black = 1
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = new Node("", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete nil;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        // s += R->key + " : " + std::to_string(R->val) + "\n";
        s+=R->key;
		s+=" : ";
		s+=std::to_string(R->val);
		s+="\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        if (R != nil) {
            setValue(R->key, R->val);
            preOrderCopy(R->left, N);
            preOrderCopy(R->right, N);
        }
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil) {
        return nil;
    }
    if (R->key == k) {
        return R;
    }
    if (R->key < k) {
        return search(R->right, k);
    } else {
        return search(R->left, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (this->num_pairs != 0) {
        while (R != nil && R->left != nil) {
            R = R->left;
        }
        return R;
    }
    return nil;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    if (this->num_pairs != 0) {
        while (R != nil && R->right != nil) {
            R = R->right;
        }
        return R;
    }
    return nil;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    // N is nil or rightmost
    if (N == nil || findMax(root) == N) {
        return nil;
    }
    if (N->right != nil) {
        return findMin(N->right);
    }
    // follow the pseudocode
    Node* y = N->parent;
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    // N is nil or leftmost
    if (N == nil || findMin(root) == N){
        return nil;
    }
    if (N->left != nil) {
        return findMax(N->left);
    }
    // follow the pseudocode
    Node* y = N->parent;
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

// transplant()
// Follow professor's pseudocode
void Dictionary::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    if (v != nil) {
      v->parent = u->parent;
    }
}


// RBT Helper Functions (Optional) -----------------------------------------

// All follow the pseudocode

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    // set y
    Node* y = N->right;
    
    // turn y's left subtree into x's right subtree
    N->right = y->left;
    if (y->left != nil) {    // not necessary if using sentinal nil node
        y->left->parent = N;
    }
    
    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    // put x on y's left
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y
    Node* y = N->left;
    
    // turn y's right subtree into x's left subtree
    N->left = y->right;
    if (y->right != nil) {  // not necessary if using sentinal nil node
        y->right->parent = N;
    }
    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }
    // put x on y's right
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == 0) {
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right;
            if (y->color == 0) {
                N->parent->color = 1;             // case 1
                y->color = 1;                     // case 1
                N->parent->parent->color = 0;     // case 1
                N = N->parent->parent;            // case 1
            } else {
                if (N == N->parent->right) {
                  N = N->parent;                  // case 2
                  LeftRotate(N);                  // case 2
                }
                N->parent->color = 1;             // case 3
                N->parent->parent->color = 0;     // case 3
                RightRotate(N->parent->parent);   // case 3
            }
        } else {
            Node* y = N->parent->parent->left;
            if (y->color == 0) {
                N->parent->color = 1;             // case 4
                y->color = 1;                     // case 4
                N->parent->parent->color = 0;     // case 4
                N = N->parent->parent;            // case 4
            } else {
                if (N == N->parent->left) {
                  N = N->parent;                  // case 5
                  RightRotate(N);                 // case 5
                }
                N->parent->color = 1;             // case 6
                N->parent->parent->color = 0;     // case 6
                LeftRotate(N->parent->parent);    // case 6
            }
        }
    }
    root->color = 1;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else 
      u->parent->right = v;
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root and N->color == 1) {
      if (N == N->parent->left) {
          Node* w = N->parent->right;
          if (w->color == 0) {
              w->color = 1;                         // case 1
              N->parent->color = 0;                 // case 1
              LeftRotate(N->parent);                // case 1
              w = N->parent->right;                 // case 1
          }
          if (w->left->color == 1 and w->right->color == 1) {
              w->color = 0;                         // case 2
              N = N->parent;                        // case 2
          } else {
              if (w->right->color == 1) {
                w->left->color = 1;                 // case 3
                w->color = 0;                       // case 3
                RightRotate(w);                     // case 3
                w = N->parent->right;               // case 3
              }
              w->color = N->parent->color;          // case 4
              N->parent->color = 1;                 // case 4
              w->right->color = 1;                  // case 4
              LeftRotate(N->parent);                // case 4
              N = root;                             // case 4
          }
      } else {
          Node* w = N->parent->left;
          if (w->color == 0) {
              w->color = 1;                         // case 5
              N->parent->color = 0;                 // case 5
              RightRotate(N->parent);               // case 5
              w = N->parent->left;                  // case 5
          }
          if (w->right->color == 1 and w->left->color == 1) {
              w->color = 0;                         // case 6
              N = N->parent;                        // case 6
          } else {
              if (w->left->color == 1) {
                w->right->color = 1;                // case 7
                w->color = 0;                       // case 7
                LeftRotate(w);                      // case 7
                w = N->parent->left;                // case 7
              }
              w->color = N->parent->color;          // case 8
              N->parent->color = 1;                 // case 8
              w->left->color = 1;                   // case 8
              RightRotate(N->parent);               // case 8
              N = root;                             // case 8
          }
      }
    }
    N->color = 1;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node* y = N;
    Node* x;
    int y_original_color = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
          x->parent = y;
        } else {
          RB_Transplant(y, y->right);
          y->right = N->right;
          y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == 1) {
        RB_DeleteFixUp(x);
    }
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (contains(k)) {
        Node* N = search(root, k);
        return N -> val;
    }
    throw std::logic_error("Dictionary: getValue(): key doesn't exist");
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if(hasCurrent()) {
        return current->key;
    }
    throw std::logic_error("Dictionary: currentKey(): current doesn't exist");
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if(hasCurrent()) {
        return current->val;
    }
    throw std::logic_error("Dictionary: currentVal(): current doesn't exist");
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // Node* find = search(root, k);
    // // overwrite
    // if (find != nil) {
    //     find->val = v;
    // } else {
    Node* newN = new Node(k, v);
    Node* start = root;
    Node* temp = nil;
    if (this->num_pairs == 0) {
        root = newN;
        newN->parent = nil;
    } else {
        while(start != nil) {
            temp = start;
            if (k == start->key) {
                start->val = v;
                return;
            } else if(k < start->key) {
                newN->parent = start;
                start = start->left;
            } else {
                newN->parent = start;
                start = start->right;
            }
        }
        // newN->parent = temp;
        if (k < temp->key) {
            temp->left = newN;
        } else {
            temp->right = newN;
        }
    }
    newN->left = nil;
    newN->right = nil;
    newN->color = 0;
    RB_InsertFixUp(newN);
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    // follow the pseudocode
    if (contains(k)) {
        Node* z = search(root, k);
        if (current == z) current = nil;
        // if (z->left == nil) {
        //     transplant(z, z->right);
        // } else if (z->right == nil) {
        //     transplant(z, z->left);
        // } else {
        //     Node* y = findMin(z->right);
        //     if (y->parent != z) {
        //         transplant(y, y->right);
        //         y->right = z->right;
        //         y->right->parent = y;
        //     }
        //     transplant(z, y);
        //     y->left = z->left;
        //     y->left->parent = y;
        // }
        // delete z;
        RB_Delete(z);
        num_pairs--;
    } else {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (this->num_pairs > 0) {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (this->num_pairs > 0) {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if(hasCurrent()) {
        if(current == findMax(root)) {
            current = nil;
        } else {
            current = findNext(current);
        }
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if(hasCurrent()) {
        if(current == findMin(root)) {
            current = nil;
        } else {
            current = findPrev(current);
        }
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s,root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s,root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    bool eq = false;
    std::string s = D.to_string();
    std::string s_this = (*this).to_string();
    eq = (this->num_pairs == D.num_pairs);
    if (eq && s == s_this) {
        return true;
    }
    return false;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    // from example of the professor
    if( this != &D ){ // not self assignment
      // make a copy of Q
      Dictionary temp = D;

      // then swap the copy's fields with fields of this
      std::swap(nil, temp.nil);
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
   }

   // return this with the new data installed
   return *this;
}
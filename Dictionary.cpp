

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>
//#include <ftream>
const keyType NIL = "XXXXD";
const valType NIL2 = 2147483646;
const int black = 0;
const int red = 1;
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = black;
}

void Dictionary::inOrderString(std::string &s, Node *R) const {
  // static std::string s1;
  static std::string s2;
  static std::string s3 = "\n";
  static std::string s4 = " : ";

  if (R->key != nil->key) {
    inOrderString(s, R->left);
    // s1=R->key;
    s2 = std::to_string(R->val);
    s.append(R->key + s4 + s2 + s3);
    inOrderString(s, R->right);
  }

  // printf("here\n");
}
void Dictionary::preOrderString(std::string &s, Node *R) const {
  // static std::string s1;
  static std::string s2 = "\n";
  if (R->key != nil->key) {
    // s1=R->key;
    s.append(R->key + s2);
    preOrderString(s, R->left);
    // s.append(R->key+s2);
    preOrderString(s, R->right);
    // s.append(R->key+s2);
  }
}
void Dictionary::preOrderCopy(Node *R, Node *N) {
  // static int x=0;

  // static Node* tempx;
  if (root->key == nil->key) {
    // root=new Node(R->key,R->val);
    // printf("how many here\n");
    // root->key=R->key;
    // root->val=R->val;
    root->left = nil;
    root->right = nil;
    root->color = red;
    root->parent = nil;
    current = root;
  }

  // x+=1;
  if ((R->key) != (nil->key)) {
    if (root->key != nil->key) {
      Node *x = new Node(R->key, R->val);
      // printf("number of times here\n");

      x->parent = current;
      // tempx=x->parent;
      if (R->parent->left->key == R->key) {
        current->left = x;
      } else {
        current->right = x;
      }
      x->left = nil;
      x->right = nil;
      x->color = R->color;
      // tempx=current;
      current = x;
      // tempx=x->parent;
    }
    if (root->key == nil->key) {
      root->key = R->key;
      root->val = R->val;
      root->color = R->color;
    }
    preOrderCopy(R->left, nil);
    // current=tempx;
    preOrderCopy(R->right, nil);
    current = current->parent;
  }
}
// current=current->parent;

void Dictionary::postOrderDelete(Node *R) {
  if (R->key != nil->key) {
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
    // disconnect?
  }
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  // printf("not even here\n");
  if ((R->key == nil->key) || (R->key == k)) {
    // std::cout<<R->key<<std::endl;
    return R;

  } else if (k < R->key) {
    return search(R->left, k);

  } else {
    return search(R->right, k);
  }
}

Dictionary::Node *Dictionary::findMin(Node *R) {
  while (R->left->key != nil->key) {
    R = R->left;
  }
  return R;
}

Dictionary::Node *Dictionary::findMax(Node *R) {

  while (R->right->key != nil->key) {
    R = R->right;
  }
  return R;
}

Dictionary::Node *Dictionary::findNext(Node *N) {
  Node *y;

  if (N->right->key != nil->key) {
    return findMin(N->right);
  }

  y = N->parent;
  while ((y->key != nil->key) && (N->key == y->right->key)) {
    N = y;
    y = y->parent;
  }
  // std::cout<<y->key<<std::endl;
  return y;
}

// prob not working
Dictionary::Node *Dictionary::findPrev(Node *N) {
  Node *y;
  if (N->left->key != nil->key) {
    return findMax(N->left);
  }
  y = N->parent;
  while ((y->key != nil->key) && (N->key == y->left->key)) {
    N = y;
    y = y->parent;
  }
  return y;
}
void Dictionary::LeftRotate(Node *N) {
  // set y
  Node *y;
  y = N->right;
  // printf("starts left\n");
  // turn y's left subtree into x's right subtree
  N->right = y->left;
  if (y->left->key != nil->key) { // not necessary if using sentinal nil node
    y->left->parent = N;
  }
  // link y's parent to x
  y->parent = N->parent;
  if (N->parent->key == nil->key) {
    root = y;
  } else if (N->key == N->parent->left->key) {
    N->parent->left = y;
  } else {
    N->parent->right = y;
  }
  // put x on y's left
  y->left = N;
  N->parent = y;
  // printf("ends left\n");
}
void Dictionary::RightRotate(Node *N) {
  // set y
  Node *y;
  y = N->left;
  // printf("starts right\n");
  // turn y's right subtree into x's left subtree
  N->left = y->right;
  // if (y->right->key != nil->key){  // not necessary if using sentinal nil
  // node
  y->right->parent = N;
  //}
  // link y's parent to x
  y->parent = N->parent;
  if (N->parent->key == nil->key) {
    root = y;
  } else if (N->key == N->parent->right->key) {
    N->parent->right = y;
  } else {
    N->parent->left = y;
  }
  // put x on y's right
  y->right = N;
  N->parent = y;
  // printf("ends right\n");
}
void Dictionary::RB_InsertFixUp(Node *N) {
  Node *y;
  while (N->parent->color == red) {
    if (N->parent->key == N->parent->parent->left->key) {
      y = N->parent->parent->right;
      if (y->color == red) {
        N->parent->color = black;       // case 1
        y->color = black;               // case 1
        N->parent->parent->color = red; // case 1
        N = N->parent->parent;
      } // case 1
      else {
        if (N->key == N->parent->right->key) {
          N = N->parent; // case 2
          LeftRotate(N);
        }                               // case 2
        N->parent->color = black;       // case 3
        N->parent->parent->color = red; // case 3
        RightRotate(N->parent->parent);
      } // case 3
    } else {
      y = N->parent->parent->left;
      if (y->color == red) {
        N->parent->color = black;       // case 4
        y->color = black;               // case 4
        N->parent->parent->color = red; // case 4
        N = N->parent->parent;
      } else {
        if ((N->key == N->parent->left->key)) {
          N = N->parent;
          RightRotate(N);
        }
        N->parent->color = black;
        N->parent->parent->color = red;
        LeftRotate(N->parent->parent);
      }
    }
  }
  root->color = black;
}
void Dictionary::RB_Transplant(Node *u, Node *v) {
  if (u->parent->key == nil->key) {
    root = v;
  } else if (u->key == u->parent->left->key) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}
void Dictionary::RB_DeleteFixUp(Node *N) {
  Node *w;
  while (N->key != root->key and N->color == black) {
    if (N->key == N->parent->left->key) {
      w = N->parent->right;
      if (w->color == red) {
        w->color = black;       // case 1
        N->parent->color = red; // case 1
        LeftRotate(N->parent);  // case 1
        w = N->parent->right;
      } // case 1
      if (w->left->color == black and w->right->color == black) {
        w->color = red; // case 2
        N = N->parent;
      } // case 2
      else {
        if (w->right->color == black) {
          w->left->color = black; // case 3
          w->color = red;         // case 3
          RightRotate(w);         // case 3
          w = N->parent->right;
        }                            // case 3
        w->color = N->parent->color; // case 4
        N->parent->color = black;    // case 4
        w->right->color = black;     // case 4
        LeftRotate(N->parent);       // case 4
        N = root;
      }
    } // case 4
    else {
      w = N->parent->left;
      if (w->color == red) {
        w->color = black;       // case 5
        N->parent->color = red; // case 5
        RightRotate(N->parent); // case 5
        w = N->parent->left;    // case 5
      }
      if (w->right->color == black and w->left->color == black) {
        w->color = red; // case 6
        N = N->parent;
      } // case 6
      else {
        if (w->left->color == black) {
          w->right->color = black; // case 7
          w->color = red;          // case 7
          LeftRotate(w);           // case 7
          w = N->parent->left;
        }                            // case 7
        w->color = N->parent->color; // case 8
        N->parent->color = black;    // case 8
        w->left->color = black;      // case 8
        RightRotate(N->parent);      // case 8
        N = root;
      }
    }
    //N->color = black;
  }
  N->color=black; // case 8
}

void Dictionary::RB_Delete(Node *N) {
  Node *y;
  Node *x;
  int org_color;
  y = N;
  org_color = y->color;
  if (N->left->key == nil->key) {
    x = N->right;
    RB_Transplant(N, N->right);
  } else if (N->right->key == nil->key) {
    x = N->left;
    RB_Transplant(N, N->left);
  } else {
    y = findMin(N->right); //**
    org_color = y->color;
    x = y->right;
    if (y->parent->key == N->key) {
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
  if (org_color == black) {
    RB_DeleteFixUp(x);
  }
  // printf("crash here END of RB delete\n");
}
Dictionary::Dictionary() {
  nil = new Node(NIL, NIL2);
  root = nil;
  current = nil;
  num_pairs = 0;
  nil->color = black;
  // printf("called upon\n");
}

Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node(NIL, NIL2);
  nil->color = black;
  root = new Node(NIL, NIL2);
  // root->parent=nil;
  // current=root;
  // printf("hey!");
  // Node *temp = D.root;
  // Node *temp2=D.nil;
  // printf("error2`\n");
  // Node* temp2=//findMax(D.root);
  // printf("can't be here!!!!\n");

  preOrderCopy(D.root, D.nil);
  num_pairs = D.num_pairs;
  current = root;

  // idk fill in a tree
}
Dictionary::~Dictionary() {
  clear();
  // if(nil==root){
  delete nil;
  // delete current;
  //}
  // else{
  //	delete nil;
  //	delete root;
  //}
}
int Dictionary::size() const { return num_pairs; }

bool Dictionary::contains(keyType k) const {
  // printf("contains isue\n");
  if (((search(root, k))->key) != (nil->key)) {
    return true;
  }
  return false;
}

valType &Dictionary::getValue(keyType k) const {
  if ((contains(k)) == false) {
    throw std::logic_error("Dictionary: getValue(): 'key blah' does not exist");
  }
  // printf("search error\n");
  return ((search(root, k))->val);
}

bool Dictionary::hasCurrent() const {
  if (((current)->key != (nil)->key)) {
    return true;
  }
  return false;
}

keyType Dictionary::currentKey() const {
  if (current->key != ((nil)->key)) {
    return current->key;
  }
  /*
  if(current->key!=nil->key)
return current->key;
  if((hasCurrent()==false)){
  0
  */
  throw std::logic_error("Dictionary: currentKey(): current undefined");

  //}

  // return current->key;
}

valType &Dictionary::currentVal() const {

  if (current->key != ((nil)->key)) {
    return current->val;
  }
  throw std::logic_error("Dictionary: currentVal(): current undefined");
}

void Dictionary::clear() {
  begin();
  // Node* temp;
  /*
  for(int x=0; x<(size()); x++){
          temp=findMin(root);
          remove(temp->key);

  }
  */
  postOrderDelete(root);
  nil->key = "XXXXD";
  num_pairs = 0;
  current = nil;
  root = nil;
}
// def speed up rewrite later
void Dictionary::setValue(keyType k, valType v) {
  Node *y;
  Node *x;
  x = root;
  y = nil;
  Node *z = new Node(k, v);
  while (x->key != nil->key) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else if (z->key > x->key) {
      x = x->right;
    } else {
      valType &z1 = getValue(k);
      z1 = v;
      delete z;
      return;
    }
  }
  z->parent = y;
  if (y->key == nil->key) {
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = nil;
  z->right = nil;
  z->color = red;
  RB_InsertFixUp(z);
  num_pairs += 1;
}

void Dictionary::remove(keyType k) {
  if ((contains(k)) == false) {
    throw std::logic_error("Dictionary: remove(): key 'blah' does not exist");
  }

  Node *z = search(root, k);
  // Node *y;
  Node *remv = z;
  bool truth = false;
  if (current->key == z->key) {
    truth = true;
  }
  // printf("HEY\n");
  RB_Delete(z);
  // printf("YO\n");
  num_pairs -= 1;
  delete remv;

  // deal with memory leak later
  if (truth == true) {
    current = nil;
  }
}

void Dictionary::begin() {
  if (size() != 0) {
    current = findMin(root);
  }
}

void Dictionary::end() {
  if (size() != 0) {
    current = findMax(root);
  }
}

void Dictionary::next() {

  if ((hasCurrent()) == false) {
    throw std::logic_error("Dictionary: next(): current not defined");
  }

  if (current != (findMax(root))) {
    current = findNext(current);

  } else {
    current = nil;
  }
}
void Dictionary::prev() {
  if ((hasCurrent()) == false) {
    throw std::logic_error("Dictionary: prev(): current not defined");
  }

  if (current->key != (findMin(root)->key)) {
    current = findPrev(current);

  } else {
    current = nil;
  }
}

std::string Dictionary::to_string() const {
  std::string s;
  Node *roots = root;
  inOrderString(s, roots);

  return s;
}

std::string Dictionary::pre_string() const {
  Node *roots = root;
  std::string s;
  preOrderString(s, roots);
  return s;
}

bool Dictionary::equals(const Dictionary &D) const {
  if ((this->num_pairs) != D.num_pairs) {
    return false;
  }

  std::string s;
  std::string s1;
  inOrderString(s, this->root);
  inOrderString(s1, D.root);
  // std::cout<<s<<std::endl;
  // std::cout<<s1<<std::endl;
  if ((s1) != (s)) {
    return false;
  }
  return true;
}

std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary &A, const Dictionary &B) {
  return A.Dictionary::equals(B);
}

Dictionary &Dictionary::operator=(const Dictionary &D) {
  if (this != &D) {

    Dictionary D1 = D;
    std::swap(nil, D1.nil);
    std::swap(root, D1.root);
    std::swap(current, D1.current);
    std::swap(num_pairs, D1.num_pairs);
  }
  return *this;
}

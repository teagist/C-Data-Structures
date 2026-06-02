# Linked List Tests

This repository contains the implementation and a **comprehensive test suite** for a templated singly‑linked list. 
---

## Features of the Linked List
* Templated Singly Linked List.
*  Insertion, Deletion, Retrieval, Sorting, and Traversal of the List.

## ✅ Automated Test Checklist  

> **How to use:**  
> - Open `tests/slist_test.cpp`.  
> - Each bullet below corresponds to one (or a group of) `TEST`/`TEST_F` cases.  
> - Mark the checkbox when the test passes in your CI pipeline.  

### 1️⃣ Construction & Destruction  

- [ ] **DefaultConstructor** – empty list, size 0, head nullptr.  
- [ ] **DestructorNoLeak** – run under ASAN/Valgrind, no leaks.  
- [ ] **CopyConstructor** – deep copy, independent modifications.  
- [ ] **MoveConstructor** – source emptied, destination owns nodes.  
- [ ] **CopyAssignment** – self‑assignment safe, deep copy semantics.  
- [ ] **MoveAssignment** – self‑assignment safe, source emptied, no double‑free.  

### 2️⃣ Insertion Operations  

- [ ] **PushFrontSingle** – head holds element, size 1.  
- [ ] **PushFrontMultiple** – elements appear in reverse order of insertion.  
- [ ] **PushBackSingle** – tail holds element, size 1.  
- [ ] **PushBackMultiple** – elements appear in insertion order.  
- [ ] **InsertAtBeginning** – equivalent to `push_front`.  
- [ ] **InsertAtMiddle** – node appears at correct index, others shift.  
- [ ] **InsertAtEnd** – equivalent to `push_back`.  
- [ ] **InsertInvalidIndex** – throws `std::out_of_range` (or returns error).  
- [ ] **InsertLargeCount** – insert ≥ 10 000 elements, no overflow.  

### 3️⃣ Removal Operations  

- [ ] **PopFrontSingle** – list becomes empty, returned value matches head.  
- [ ] **PopFrontMultiple** – FIFO removal, size decrements correctly.  
- [ ] **PopBackSingle** – list becomes empty, tail removed correctly.  
- [ ] **PopBackMultiple** – removal from tail, head unchanged until empty.  
- [ ] **EraseAtBeginning** – equivalent to `pop_front`.  
- [ ] **EraseAtMiddle** – correct link bypass, size updates.  
- [ ] **EraseAtEnd** – equivalent to `pop_back`.  
- [ ] **EraseInvalidIndex** – throws / returns error for out‑of‑range index.  
- [ ] **Clear** – all nodes freed, `empty()` true, size 0.  

### 4️⃣ Element Access  

- [ ] **OperatorBracketValid** – returns correct element for every valid index.  
- [ ] **OperatorBracketOutOfRange** – throws `std::out_of_range`.  
- [ ] **Front/Back** – return first/last element, handle empty case appropriately.  
- [ ] **At** (if implemented) – bounds‑checked access, throws on invalid index.  
- [ ] **ConstAccess** – read‑only access works on `const SList<T>`.  

### 5️⃣ Iterator Correctness  

- [ ] **BeginEndEmpty** – `begin() == end()` on an empty list.  
- [ ] **ForwardIteration** – range‑for yields elements in insertion order.  
- [ ] **PrePostIncrement** – both `++it` and `it++` behave correctly.  
- [ ] **EqualityInequality** – iterator comparisons work as expected.  
- [ ] **ConstIterator** – `cbegin()/cend()` return `const T&`.  
- [ ] **MultiPass** – two independent iterators can traverse simultaneously.  
- [ ] **EraseDuringIteration** – erasing the current node invalidates only that iterator.  
- [ ] **IteratorInvalidationRules** – after `push_front`/`push_back` only `begin()`ated; after `erase` only the erased iterator is invalid.  

### 6️⃣ Algorithms & STL Compatibility  

- [ ] **std::find works** – `std::find(begin, end, value)` locates element.  
- [ ] **std::copy works** – copy list elements into a `std::vector`.  
- [ ] **std::distance correct** – returns number of elements between iterators.  
- [ ] **Other forward‑iterator algorithms** – e.g., `std::any_of`, `std::all_of`.  

### 7️⃣ Edge‑Case / Stress Tests  

- [ ] **VeryLargeList** – ≥ 1 000 000 inserts, no overflow, reasonable runtime.  
- [ ] **RepeatedPushPop** – alternating push/pop many times, no leaks or corruption.  
- [ ] **SelfAssignment (copy & move)** – `lst = lst;` leaves list unchanged.  
- [ ] **ExceptionSafety** – inserting a type that throws on copy leaves list unchanged (strong guarantee).  
- [ ] **POD vs Non‑POD** – test with `int`, `std::string`, and a custom class with side‑effects.  
- [ ] **MultiThreadReadOnly** – multiple threads iterate over a `const` list simultaneously (no data races).  
- [ ] **SanitizerChecks** – compile with ASAN/UBSAN; no address or undefined‑behavior violations.  

---

## 🛠️ Building & Running the Tests  

```bash
# Clone the repository
git clone <repo-url>
cd <repo-directory>

# Create a build directory
mkdir build && cd build

# Configure (enable sanitizers if desired)
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON ..

# Build
make -j$(nproc)

# Run the test suite
ctest   # or ./tests/slist_test

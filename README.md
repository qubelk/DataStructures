# DataStructures

Writing Data Structures In C++ For Learning

To better understand the topic of data structures, in this repository I will implement my own versions of collections and smart pointers from the C++ STL, Rust, Java, and other languages ​​and resources.

## Roadmap

### Collections

- [x] `Array<T, N>` - wrapper around a static array from C++ STL.

- [ ] `Vector<T>` - dynamic array from C++ STL.

- [ ] `List<T>` - ordered list of elements from C++ STL.

### Smart Pointers

- [x] `Unique<T>` - pointer with automatic release and unique ownership from C++ STL.

- [ ] `Rc<T>` - pointer with reference count for owners from Rust.

- [ ] `Arc<T>` - thread safe analog for `Rc<T>` uses atomic from Rust.

- [x] `Cow<T>` - pointer with copying data on write from Rust.

- [x] `Lazy<T>` - pointer to function whose value calculated once and then cached from 'Thunk' concepts.

- [ ] `ConcurrentLazy<T>` - thread safe analog of `Lazy<T>`.

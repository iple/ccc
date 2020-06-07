#include <cstdio>
#include <utility>

template <typename T>
struct SimpleUniquePointer {
  SimpleUniquePointer() = default;
  SimpleUniquePointer(T* pointer)
      : pointer{ pointer } {}
  ~SimpleUniquePointer() {
    if(pointer)
      delete pointer;
  }
  SimpleUniquePointer(const SimpleUniquePointer&) = delete;
  SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
  SimpleUniquePointer(SimpleUniquePointer&& other) noexcept
      : pointer{ other.pointer } {
    other.pointer = nullptr;
  }
  SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
    if(pointer)
      delete pointer;
    pointer = other.pointer;
    other.pointer = nullptr;
    return *this;
  }
  T* get() const {
    return pointer;
  }

  private:
  T* pointer;
};

struct Tracer {
  Tracer(const char* name)
      : name{ name } {
    printf("%s constructed.\n", name);
  }
  ~Tracer() {
    printf("%s destructed.\n", name);
  }

  private:
  const char* const name;
};

// if param is const &, no move takes place and Tracer object lives till end of main
void consumer(SimpleUniquePointer<Tracer> consumer_ptr) {
//void consumer(const SimpleUniquePointer<Tracer>& consumer_ptr) {
  printf("(cons) consumer_ptr: %p\n", consumer_ptr.get());
}

// Listing 6-34
// pass arguments to the constructor of template parameter T, for non-default constructors
// using std::forward is more efficient, detects if arguments are rvalue or lvalue to perform move or copy
template <typename T, typename... Arguments>
SimpleUniquePointer<T> make_simple_unique(Arguments... arguments) {
  //return SimpleUniquePointer<T>{new T{arguments...}};
  return SimpleUniquePointer<T>{new T{std::forward<Arguments>(arguments)...}};

}

int main() {
  //auto ptr_a = SimpleUniquePointer<Tracer>(new Tracer{ "ptr_a" });
  auto ptr_a = make_simple_unique<Tracer>("ptr_A");
  printf("(main) ptr_a: %p\n", ptr_a.get());
  consumer(std::move(ptr_a));
  printf("(main) ptr_a: %p\n", ptr_a.get());
}

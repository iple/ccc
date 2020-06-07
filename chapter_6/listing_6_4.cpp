#include <cstdio>

void carbon_thaw(const int& solo)
{
  //solo++; //error
  printf("%s: %d is the mark_of_the_solo. %p\n", __FUNCTION__, solo, &solo);
  auto& sick_solo = const_cast<int&>(solo);
  sick_solo++;
  printf("%s: %d is the mark_of_the_solo. %p\n", __FUNCTION__, solo, &sick_solo);

}

short increment_as_short(void* target) {
  auto as_short = static_cast<short*>(target);
  *as_short = *as_short + 1;
  return *as_short;
}

int main() {
  short beast{ 665 };
  auto mark_of_the_beast = increment_as_short(&beast);
  printf("%s: %d is the mark_of_the_beast.\n", __FUNCTION__, mark_of_the_beast);
  const int solo{15};
  carbon_thaw(solo);
  printf("%s: %d is the mark_of_the_solo. %p\n", __FUNCTION__, solo, &solo);
}

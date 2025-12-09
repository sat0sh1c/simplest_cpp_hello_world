#include "functions/functions.hpp"
#include "headers/classes.hpp"
#include <future>
#include <thread>

int main()
{
  const base b{std::string{"ak;hladf"}, 3};
  b.basic();

  const derived<static_cast<std::uint32_t>(';') + 42> d;
  d.basic();

  num_base dd(std::bitset<8>{"00110110"});
  dd.hex(std::string{"6C"});

  io_stuff obj{' ' + '!' + ':' - (sizeof(int) * 3)};
  {
    std::vector<std::jthread> workers;
    std::size_t thread_amount = std::thread::hardware_concurrency();
    workers.reserve(thread_amount);
    std::once_flag guarantor{};
    for (std::size_t i = 0; i < thread_amount; ++i)
    {
      workers.emplace_back(print_smb, 32, std::ref(guarantor));
    }
  }

  std::function<void(std::int8_t)> w_print = [](std::int8_t value)
  { std::cout << static_cast<char>(~value); };

  fn_taker<-120>(w_print);

  std::uint16_t iter{};
  while (!std::async(std::launch::async, runtime_template_fucntion_call, iter++)
              .get())
  {
  }

  try_guess(1337);

  int* ptr = new int[1];
  delete[] ptr;

  asm_block lol(41);
}

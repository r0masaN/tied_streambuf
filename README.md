# tied_streambuf
Simple class for teeing multiple streambuf objects so you can write in one streambuf/ostream as you were writing in every tied streambuf of any ostream

## Usage example

```cpp
std::ostringstream oss1;
std::ostringstream oss2;
std::ofstream file("test_log.txt");

tied_streambuf t_buf{oss1.rdbuf(), oss2.rdbuf(), file.rdbuf(), std::cout.rdbuf()};
std::ostream multi_os{&t_buf};

multi_os << "Test 1: Hello Multi-world!" << std::endl;
multi_os << "Test 2: Number " << 42 << " and hex " << std::hex << 0xff << std::dec << std::endl;
```

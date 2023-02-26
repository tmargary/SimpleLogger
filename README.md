# SimpleLogger
Level based and thread-safe logger implementation in C++

### Installation
1. `git clone https://github.com/tmargary/SimpleLogger`
2. `cd SimpleLogger`
3. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`
4. `cmake --build ./build`
5. `./build/tests/LoggerTest`

### Usage
```
std::string freq = "day";
std::string path = get_cwd();
std::string config_path = path + "/config.json";
LogLevel level = get_level(config_path);

Logger logger(path, freq, level);
logger.log(DEBUG, "Debug message");
```

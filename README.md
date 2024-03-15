# iceTest
### Dependencies
- MinGW (Window) / GCC (Linux)
- Msys (Windows)
- Cmake
- SFML
---
### How build from source
1. Clone source 
    - `git clone ...`
2. Configure project
    - `cd iceTest && mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release`
3. Build project
    - `cmake --build . --config release --parallel`
5. Execute 
    - Run file 'iceTest'
---
### API Keys
 - ключи пусть будут 
 - v-напряжение 
 - i-ток
 - h-уровень топлива
 - V-скорость траты топлива
 - x-широта
 - y-долгота
 - o-показания с магнитометра 
 - a-показания с аксилерометра 
 - H-высота
--- 
### Connect
 - Server address
    - 192.168.0.1
 - Server port
    - 80

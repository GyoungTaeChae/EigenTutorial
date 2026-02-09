# CMake 외부 라이브러리 사용 가이드

## Header-Only 라이브러리 (예: Eigen)

소스를 컴파일할 필요 없이 **include 경로만 지정**하면 된다.

```cmake
add_library(Eigen3::Eigen INTERFACE IMPORTED)
set_target_properties(Eigen3::Eigen PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/thirdparty/eigen"
)

target_link_libraries(my_target Eigen3::Eigen)
```

- `INTERFACE IMPORTED` — 빌드할 코드가 없는 라이브러리 (헤더만 제공)
- `INTERFACE_INCLUDE_DIRECTORIES` — 컴파일러에게 헤더 탐색 경로를 전달
- 내부적으로 컴파일러에 `-I thirdparty/eigen` 플래그를 넘기는 것과 동일

## 일반 라이브러리 (예: OpenCV, Ceres)

소스를 컴파일하여 `.so`(동적) 또는 `.a`(정적) 파일을 생성한 뒤 **링크**해야 한다.

### 방법 A: add_subdirectory

소스를 내 프로젝트 빌드에 포함시킨다. 내 프로젝트 빌드 시 라이브러리도 같이 빌드된다.

```bash
# 소스를 thirdparty에 배치
git submodule add <url> thirdparty/some_library
```

```cmake
add_subdirectory(thirdparty/some_library)
target_link_libraries(my_target some_library::some_library)
```

### 방법 B: find_package

시스템에 미리 설치된 라이브러리를 찾아서 링크한다.

```bash
# 라이브러리를 별도로 빌드 & 설치
cd thirdparty/some_library
cmake -B build
cmake --build build
sudo cmake --install build
```

```cmake
find_package(SomeLibrary REQUIRED)
target_link_libraries(my_target SomeLibrary::SomeLibrary)
```

## 비교

| | Header-Only (Eigen) | 일반 라이브러리 (OpenCV 등) |
|---|---|---|
| 라이브러리 빌드 | 불필요 | 필요 (`.so`/`.a` 생성) |
| 필요한 설정 | include 경로만 | include 경로 + 라이브러리 파일 링크 |
| 내 프로젝트 컴파일 속도 | 느림 (매번 헤더 파싱) | 빠름 (미리 컴파일됨) |
| 대표 예시 | Eigen, nlohmann/json, spdlog | OpenCV, Ceres, g2o, PCL |

## clangd에서 "use of undeclared identifier" 오류 해결

thirdparty 라이브러리를 CMake에 추가해도, clangd(VSCode의 C++ 언어 서버)는 include 경로를 모른다.
`compile_commands.json`을 생성하면 clangd가 각 파일의 컴파일 플래그(`-I` 경로 포함)를 인식하게 된다.

```bash
# 1. compile_commands.json 생성
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# 2. 프로젝트 루트에 심볼릭 링크 (clangd는 루트에서 이 파일을 찾음)
ln -sf build/compile_commands.json compile_commands.json
```

VSCode에서 `Ctrl+Shift+P` → **"clangd: Restart language server"** 로 반영한다.

cmake_minimum_required(VERSION 3.10)

project(
    CppProject
    VERSION 0.1
    DESCRIPTION "crossy-road-clone"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

# SFML 찾기
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 모든 cpp 파일 자동 수집
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 실행 파일 생성
add_executable(main ${SOURCES})

# SFML 라이브러리 연결
target_link_libraries(main sfml-graphics sfml-window sfml-system)

# 헤더 디렉토리 추가 (include/ 내부의 헤더들을 경로 없이 사용)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)
# xv6-SSU

> **2025-1 숭실대학교 운영체제 과목 실습**  

## 실행 환경 구성
- Docker를 이용해 실습 환경을 격리하여 구성

```text
[Host OS]
   ↓
[Docker (Ubuntu 18.04)]
   ↓
[QEMU Emulator]
   ↓
[xv6 Operating System]
```

## 실습 진행 루틴

1. **Docker 이미지 빌드**
   - `make build`
   - Ubuntu 18.04 베이스의 Docker 이미지 생성

2. **컨테이너 실행 (bash 진입)**
   - `make run`
   - 컨테이너 내부 bash 환경 진입

4. **xv6 실행**
   - `/root/xv6-ssu/templates/<subject>` 위치에 접근해서 xv6 실행 (`make qemu-nox`)
   - QEMU 에뮬레이터로 xv6 실행

5. **반복 실습 시**
   - 컨테이너는 계속 켜둔 채,
   - 코드 수정 → `make qemu-nox` 반복 실행
   - 도커 내부에서 vim 사용하기 (sudo 문제)

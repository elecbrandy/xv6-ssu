# xv6-SSU

> **2025-1 숭실대학교 운영체제 과목 실습**  
> `xv6` 운영체제를 활용한 커널 실습 및 이해

## 실행 환경 구성

> **권장 사양**  
- x86 기반 **Intel CPU** 사용 (호환성 문제 방지 차원에서 권장)

> **환경 구성 흐름**  
Docker를 이용해 실습 환경을 격리하여 구성

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

3. **코드 수정 (VSCode 등에서)**
   - 소스코드를 컨테이너에 **볼륨 마운트** 해두었음
   - 호스트에서 코드 수정 시, 컨테이너에 **자동 반영**

4. **xv6 실행**
   - `/root/xv6-ssu/templates/[과제]` 위치에 접근해서 xv6 실행 (`make qemu-nox`)
   - QEMU 에뮬레이터로 xv6 실행

5. **반복 실습 시**
   - 컨테이너는 계속 켜둔 채,
   - 코드 수정 → `make qemu-nox` 반복 실행

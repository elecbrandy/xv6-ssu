## `int setnice(int pid, int nice)`
- set the process priority
- argument: process ID, nice value
- return value: failure -1 / success 0

## `int getnice(int pid)`
- get the process priority
- argument: process ID
- return value: failure -1 / success 0

## `ps`
- pid
- state: RUNNING, RUNNABLE, SLEEPING
- priority: nice value
- runtime: 0

```text
user: kill() → syscall → int 64
↓
CPU: idt[64] 참조 → vector64 실행 (진입 지점)
↓
커널 모드 전환 → trap() 호출
↓
syscall() → sys_kill()
```

1. syscall.h → 번호 부여
2. usys.S → SYSCALL 매크로 등록
3. user.h → 유저 함수 선언
4. syscall.c → syscalls[]에 함수 연결
5. sysproc.c → sys_hello() 함수 구현
6. Makefile → 새 파일 o파일 추가
7. user/test.c → 테스트용 유저 프로그램
8. Makefile → 테스트 프로그램 등록
9. make qemu → 실행 & 확인!

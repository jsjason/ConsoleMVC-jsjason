> **이 파일은 [CLAUDE.md](./CLAUDE.md)와 동일한 내용입니다.**

# ConsoleMVC-jsjason

생산주문관리 시스템 개발 전, C++ 콘솔 환경에서 MVC 패턴을 검증하는 PoC 프로젝트.

## 개발 환경

- **IDE**: Visual Studio 18 (2022)
- **빌드**: MSBuild
- **언어 표준**: C++20
- **플랫폼**: x64 (Debug / Release)

### 빌드 명령

```
MSBuild.exe ConsoleMVC-jsjason\ConsoleMVC-jsjason.vcxproj /p:Configuration=Debug /p:Platform=x64
```

## 프로젝트 구조

```
ConsoleMVC-jsjason/          ← 프로젝트 루트
├── main.cpp                 ← 진입점. 의존성 조립 및 콘솔 인코딩 초기화
├── Model/
│   ├── ProductionOrder.h    ← OrderStatus enum, ProductionOrder 구조체, Repository 선언
│   └── ProductionOrder.cpp  ← ProductionOrderRepository CRUD 구현
├── View/
│   ├── ProductionOrderView.h
│   └── ProductionOrderView.cpp  ← 콘솔 출력(메뉴, 목록 테이블, 상세) 및 입력 프롬프트
└── Controller/
    ├── ProductionOrderController.h
    └── ProductionOrderController.cpp  ← 메뉴 루프, 사용자 입력 → Model/View 연결
```

## MVC 레이어 역할

### Model (`Model/ProductionOrder`)

데이터 구조와 저장소 로직만 담당. View/Controller를 전혀 참조하지 않는다.

- `OrderStatus` — `Pending | InProgress | Completed | Cancelled`
- `ProductionOrder` — `{ id, productName, quantity, status }`
- `ProductionOrderRepository` — 인메모리 CRUD (`Add`, `UpdateStatus`, `Remove`, `FindById`, `GetAll`)

### View (`View/ProductionOrderView`)

콘솔 렌더링과 사용자 입력 수집만 담당. 비즈니스 로직을 포함하지 않는다.

- `ShowMenu()` / `ShowOrderList()` / `ShowOrder()` — 출력
- `PromptInt()` / `PromptString()` — 입력

### Controller (`Controller/ProductionOrderController`)

Model과 View를 연결하는 메뉴 루프. 입력을 받아 Model을 조작하고 View로 결과를 표시한다.

- `Run()` — 메인 루프
- `HandleList()` / `HandleCreate()` / `HandleUpdateStatus()` / `HandleDelete()`

### main.cpp

세 레이어를 조립하고 실행한다. 의존성은 생성자 주입(참조)으로 전달한다.

```cpp
ProductionOrderRepository repo;
ProductionOrderView       view;
ProductionOrderController controller(repo, view);
controller.Run();
```

## 한글 인코딩

소스 파일은 UTF-8로 저장되며, 두 가지 설정이 맞물려 한글이 정상 출력된다.

| 설정 | 위치 | 역할 |
|---|---|---|
| `/utf-8` 컴파일러 플래그 | `.vcxproj` 모든 Configuration | 소스·실행 파일 인코딩을 UTF-8로 통일 |
| `SetConsoleCP(65001)` / `SetConsoleOutputCP(65001)` | `main.cpp` 시작 | 콘솔 입출력 코드 페이지를 UTF-8로 변경 |

## MCP 설정 (`.mcp.json`)

로컬에 `.mcp.json`이 존재하며 Claude Code의 MCP 서버 설정(GitHub 등)을 담고 있다.
개인 인증 토큰이 포함되어 있어 `.gitignore`에 등록되어 있으며 **커밋에서 제외**한다.

## 확장 방향 (생산주문관리 시스템)

이 PoC를 실제 시스템으로 확장할 때 레이어별 변경 범위는 다음과 같다.

- **Model** — DB 연결, 비즈니스 규칙 추가 (납기일, 담당자, 자재 연동 등)
- **View** — TUI 라이브러리 교체 또는 GUI/Web 레이어로 교체 가능 (Controller는 무변경)
- **Controller** — 메뉴 항목 추가, 입력 유효성 강화

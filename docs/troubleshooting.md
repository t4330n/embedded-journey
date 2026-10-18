# 🔍 트러블슈팅 기록

실습 중 막혔던 문제와 해결 과정을 모아 둡니다.
비슷한 문제를 다시 만났을 때 빠르게 찾아볼 수 있도록 **증상 → 원인 → 해결** 순서로 적습니다.

<br>

## 목차

| # | 실습 | 문제 요약 |
| :---: | --- | --- |
| 1 | [01_led_blink](../01_gpio/01_led_blink) | [Board Selector로 만든 프로젝트에서 PA5 설정이 변경되지 않음](#1-board-selector로-만든-프로젝트에서-pa5-설정이-변경되지-않음) |
| 2 | [01_led_blink](../01_gpio/01_led_blink) | [MCU 선택 시 부품 번호가 여러 개라 무엇을 골라야 할지 모름](#2-mcu-선택-시-부품-번호가-여러-개라-무엇을-골라야-할지-모름) |
| 3 | [01_led_blink](../01_gpio/01_led_blink) | [SYS 메뉴에서 Debug(Serial Wire) 설정 항목을 찾을 수 없음](#3-sys-메뉴에서-debugserial-wire-설정-항목을-찾을-수-없음) |
| 4 | [01_led_blink](../01_gpio/01_led_blink) | [코드 생성 시 프로젝트 폴더가 이중으로 생성될 뻔함](#4-코드-생성-시-프로젝트-폴더가-이중으로-생성될-뻔함) |

<br>

---

## 1. Board Selector로 만든 프로젝트에서 PA5 설정이 변경되지 않음

- **실습**: [01_led_blink](../01_gpio/01_led_blink)
- **증상**
  - STM32CubeMX의 **Board Selector**에서 `NUCLEO-C031C6`을 선택해 프로젝트를 생성함
  - PA5(LD4)를 `GPIO_Output`으로 바꾸려고 클릭해도 반응이 없고, `Pin PA5 is under BSP control` 툴팁만 표시됨
  - PA5, PC13, PA2, PA3 핀이 일반적인 회색·초록색이 아닌 **다홍색**으로 표시됨
- **원인**
  - 보드 단위로 프로젝트를 만들면 ST가 제공하는 **BSP(Board Support Package)** 가 보드의 LED·버튼·통신 핀을 미리 점유함
  - BSP가 관리하는 핀은 사용자가 Pinout 화면에서 직접 모드를 바꿀 수 없음
- **해결**
  - **MCU/MPU Selector**에서 칩(`STM32C031C6T6`)을 직접 선택해 프로젝트를 새로 생성
  - 빈 상태의 칩에서 PA5를 `GPIO_Output`으로 직접 설정하고 User Label `LD4`를 지정
- **배운 점**
  - Board Selector는 개발 보드로 빠르게 데모를 만들 때 편리하지만, 핀 설정을 BSP에 맡기게 된다.
  - 실무에서는 회사가 직접 설계한 보드를 사용하는 경우가 많으므로, **칩 단위로 핀을 직접 설정하는 방법**을 익혀 두는 것이 중요하다.

<br>

## 2. MCU 선택 시 부품 번호가 여러 개라 무엇을 골라야 할지 모름

- **실습**: [01_led_blink](../01_gpio/01_led_blink)
- **증상**
  - MCU/MPU Selector에서 `STM32C031C6`을 검색하자 `C6T3`, `C6T6`, `C6U6`, `C6T6TR` 등 여러 부품 번호가 표시됨
  - 보드에 실장된 칩이 어떤 것인지 구분하기 어려웠음
- **원인**
  - STM32 부품 번호는 **접미사마다 핀 수, 메모리 크기, 패키지, 동작 온도 범위**를 나타내며, 같은 칩이라도 조합에 따라 번호가 달라짐
- **해결**
  - 보드에 표기된 `LQFP48`과 보드 이름(`NUCLEO-C031C6`)을 근거로 **`STM32C031C6T6`** 선택
  - 부품 번호 `STM32C031C6T6` 해석

    | 글자 | 의미 |
    | :---: | --- |
    | `C` | 핀 수 48개 |
    | `6` | Flash 메모리 32KB |
    | `T` | LQFP 패키지 (칩 둘레로 핀이 나온 형태, `U`는 UFQFPN) |
    | `6` | 동작 온도 -40~85℃ (`7`: -40~105℃, `3`: -40~125℃) |
    | `TR` | 칩은 동일하며, 생산용 테이프 & 릴 포장을 의미 |
- **배운 점**
  - 부품 번호의 각 글자에는 의미가 있으며, 이를 읽으면 **실제 하드웨어와 일치하는 칩**을 정확히 고를 수 있다.
  - 칩 선택은 이후 핀 배치와 설정 전체의 기준이 되므로, 보드 표기와 문서를 근거로 확인하는 습관이 필요하다.

<br>

## 3. SYS 메뉴에서 Debug(Serial Wire) 설정 항목을 찾을 수 없음

- **실습**: [01_led_blink](../01_gpio/01_led_blink)
- **증상**
  - 디버그 인터페이스를 켜기 위해 `System Core → SYS`를 열었으나 `Debug` 항목이 없고 `Timebase Source`만 표시됨
- **원인**
  - 참고한 안내는 다른 STM32 시리즈 기준이었고, **STM32C0 시리즈는 Debug 설정이 별도 메뉴에 있음**
  - STM32 시리즈마다 CubeMX의 메뉴 구성이 다를 수 있음
- **해결**
  - `Trace and Debug → DEBUG`에서 `Serial Wire` 활성화
  - PA13이 `SWDIO`, PA14가 `SWCLK`로 할당된 것을 Pinout 화면에서 확인
- **배운 점**
  - **SWD(Serial Wire Debug)** 는 디버거(보드의 ST-LINK)가 두 개의 선(SWDIO, SWCLK)으로 MCU에 코드를 쓰고 디버깅하는 방식이다. PC는 USB로 ST-LINK와 연결된다.
  - PA13, PA14는 리셋 직후 기본적으로 SWD로 동작한다. 하지만 CubeMX에서 Serial Wire로 명시해 두면 핀이 예약되어, 이후 다른 기능에 잘못 할당해 **디버그 연결이 끊기는 상황을 예방**할 수 있다.
  - 설정 위치가 안내와 다를 때는 시리즈별 차이를 의심하고 메뉴를 직접 확인해야 한다.

<br>

## 4. 코드 생성 시 프로젝트 폴더가 이중으로 생성될 뻔함

- **실습**: [01_led_blink](../01_gpio/01_led_blink)
- **증상**
  - Project Manager에서 `Project Location`을 `.../01_gpio/01_led_blink`로 지정하자
    `Toolchain Folder Location`이 `.../01_led_blink/01_led_blink/`로 표시됨
- **원인**
  - CubeMX는 **`Project Location` + `Project Name`** 경로에 프로젝트 폴더를 새로 생성함
  - 위치에 프로젝트 이름까지 포함하면 같은 이름의 폴더가 한 번 더 만들어짐
- **해결**
  - `Project Location`을 상위 폴더인 `.../embedded-journey/01_gpio`로 변경
  - `Toolchain Folder Location`이 `.../01_gpio/01_led_blink/`로 바뀐 것을 확인한 뒤 코드 생성
- **배운 점**
  - 코드 생성 전 **최종 생성 경로(Toolchain Folder Location)를 확인**하는 습관이 필요하다.
  - 레포 폴더 구조를 일정하게 유지해야 실습 기록과 프로젝트 파일을 함께 관리하기 쉽다.

<br>

---

<!--
## N. 문제 제목

- **실습**:
- **증상**:
- **원인**:
- **해결**:
- **배운 점**:
-->

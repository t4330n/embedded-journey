# 🔧 Embedded Journey

> NUCLEO-C031C6 보드로 임베디드 개발을 처음부터 차근차근 익혀 나가는 학습 기록입니다.
> LED 하나 켜는 것부터 시작해, 센서·통신·RTOS를 거쳐 직접 만든 프로젝트까지 단계별로 쌓아 갑니다.

<br>

## 🎯 목표

- 마이크로컨트롤러의 동작 원리를 **직접 코드로 확인하며** 이해하기
- 실습마다 **목표 → 구현 → 결과 → 배운 점 → 문제 해결 과정**을 기록하기
- 배운 내용을 조합해 **동작하는 임베디드 프로젝트** 완성하기

<br>

## ✨ 이 레포의 특징

- **같은 기능, 세 가지 구현** — 각 실습을 **HAL · LL · 레지스터 직접 접근**으로 구현하고, HAL 내부 코드를 열어 실제로 어떤 레지스터가 움직이는지 비교합니다.
- **디버거로 확인한 동작** — STM32CubeIDE의 **SFRs 창**으로 레지스터 값이 바뀌는 순간을 캡처해, 코드와 하드웨어 동작을 함께 기록합니다.
- **막힌 과정까지 기록** — 실습 중 막혔던 문제를 **증상 → 원인 → 해결 → 배운 점** 순서로 [트러블슈팅 문서](./docs/troubleshooting.md)에 정리합니다.

<br>

## 🛠 개발 환경

| 항목 | 내용 |
| --- | --- |
| Board | NUCLEO-C031C6 |
| MCU | STM32C031C6T6 (Arm Cortex-M0+, Flash 32KB) |
| Tool | STM32CubeMX (핀·클럭 설정, 코드 생성) |
| IDE | STM32CubeIDE |
| Debugger | ST-LINK (보드 내장) + CubeIDE 디버거 (SFRs 창) |
| Library | STM32 HAL / LL, 레지스터 직접 접근 |
| Language | C |

<br>

## 🗺 로드맵 & 진행 상황

| 단계 | 주제 | 실습 | 핵심 키워드 | 상태 |
| :---: | --- | --- | --- | :---: |
| 1 | GPIO | [LED 깜빡이기](./01_gpio/01_led_blink) | `GPIO 출력` `ODR` `BSRR` `HAL·LL·레지스터 비교` `SFRs 디버깅` | ✅ |
| 1 | GPIO | [버튼으로 LED 제어](./01_gpio/02_button_led) | `GPIO 입력` `IDR` `BRR` `풀업·풀다운` `액티브 로우` | ✅ |
| 0 | 기초 | [전압·전류·저항](./docs/basics/01_voltage_current_resistance.md) | `전압` `전류` `저항` `GND` `옴의 법칙` | ✅ |
| 0 | 기초 | [디지털 0/1과 플로팅](./docs/basics/02_digital_floating.md) · [실험](./00_basics/02_floating_input) | `플로팅` `PUPDR` `내부 풀업·풀다운` | ✅ |
| 0 | 기초 | [회로도 기호 읽기](./docs/basics/03_schematic_symbols.md) | `회로도 기호` `연결점` `넷 라벨` `부품 이름` | ✅ |
| 0 | 기초 | [보드 회로도 확인](./docs/basics/04_board_schematic.md) | `보드 회로도` `B1 풀업 저항` `LD4` `트랜지스터` | ✅ |
| 1 | GPIO | [버튼 토글 & 디바운싱](./01_gpio/03_button_toggle) | `엣지 검출` `바운싱` `디바운싱` `HAL_GetTick` `Live Expressions` | ✅ |
| 2 | Timer / Interrupt | 타이머로 LED 주기 제어, 외부 인터럽트(EXTI) | | ⬜ |
| 3 | UART | PC와 시리얼 통신, printf 디버깅 | | ⬜ |
| 4 | I2C / SPI | 온도 센서 읽기, 디스플레이 출력 | | ⬜ |
| 5 | ADC / PWM | 가변저항 읽기, LED 밝기 제어 | | ⬜ |
| 6 | RTOS | FreeRTOS 태스크 분리 | | ⬜ |
| 7 | Project | 배운 내용을 조합한 개인 프로젝트 | | ⬜ |

✅ 완료 · 🔄 진행 중 · ⬜ 예정

> 전기 기초는 GPIO 입력 실습 중 풀업·플로팅 개념을 깊이 이해할 필요를 느껴, 다음 실습 전에 보강하기로 했습니다.

<br>

## 📁 폴더 구조

```
embedded-journey/
├── README.md                    # 지금 보고 있는 문서
├── .gitignore
├── docs/
│   ├── practice-template.md     # 실습 기록 템플릿
│   ├── troubleshooting.md       # 문제 해결 기록 모음
│   └── basics/                  # 전기 기초 노트
│       └── sim/                 #   학습용 시뮬레이션 (GitHub Pages로 실행)
├── 00_basics/                   # 전기 기초 실험
│   └── 02_floating_input/       #   플로팅·풀업·풀다운 실험
├── 01_gpio/
│   ├── 01_led_blink/            # 각 폴더 = STM32CubeIDE 프로젝트 1개
│   │   ├── Core/                #   소스 코드 (main.c 등)
│   │   ├── images/              #   결과 GIF, 디버거 캡처
│   │   ├── 01_led_blink.ioc     #   CubeMX 설정 파일
│   │   └── README.md            #   실습 기록
│   ├── 02_button_led/
│   └── 03_button_toggle/
├── 02_timer_interrupt/
├── 03_uart/
├── 04_i2c_spi/
├── 05_adc_pwm/
├── 06_rtos/
└── projects/                    # 최종 프로젝트
```

각 실습 폴더에는 CubeIDE 프로젝트와 함께 해당 실습을 정리한 `README.md`, 결과 이미지가 들어 있습니다.

<br>

## 📝 실습 기록 방식

모든 실습은 [`docs/practice-template.md`](./docs/practice-template.md) 형식으로 정리합니다.

1. **목표** — 이 실습으로 무엇을 확인하려 했는지
2. **사용한 핀 / 설정** — 어떤 핀을 어떻게 설정했는지
3. **핵심 코드** — 동작의 중심이 되는 코드와 설명 (HAL · LL · 레지스터 구현 비교 포함)
4. **결과** — 동작 GIF와 디버거(SFRs 창) 캡처
5. **배운 점** — 새로 이해하게 된 개념
6. **트러블슈팅** — 막혔던 부분과 해결 과정

<br>

## 💡 주요 배운 점

> 실습이 쌓일수록 핵심 내용을 여기에 요약합니다. 자세한 내용은 각 실습의 README에 있습니다.

**레지스터**
- **레지스터**는 칩 내부의 고정된 주소에 연결된 하드웨어 제어용 칸으로, 값을 쓰면 실제 핀 동작이 바뀐다. `GPIO_TypeDef` 구조체는 이 주소들에 이름을 붙인 지도 역할을 한다.
- **ODR**은 출력 상태를 담는 레지스터, **IDR**은 핀으로 들어오는 실제 입력을 기록하는 읽기 전용 레지스터다.
- **BSRR**은 1을 쓴 비트의 핀만 켜고(n번) 끄는(n+16번) 레지스터로, 값을 저장하지 않는다. ODR을 직접 수정할 때 생길 수 있는 읽기-수정-쓰기 문제 없이 다른 핀에 영향을 주지 않는다. **BRR**은 끄기 전용 레지스터다.

**드라이버 선택**
- HAL은 쉽고 안전하지만 무겁고, LL은 파라미터 검사 없이 인라인으로 동작해 가볍고 빠르며, 레지스터 직접 접근은 가장 가볍지만 레지스터 이해가 필요하다.
- 실무에서는 HAL로 빠르게 구현한 뒤, 속도나 코드 크기가 중요한 부분만 LL이나 레지스터로 바꾸는 방식이 일반적이다.

**하드웨어와 입력 회로**
- 입력 핀은 아무 데도 연결되지 않으면 값이 흔들리는 **플로팅** 상태가 되므로, **풀업·풀다운** 저항으로 기본값을 정한다.
- 보드의 사용자 버튼 B1은 외부 풀업 회로라 누르면 0이 되는 **액티브 로우**이며, 외부 저항이 있으면 소프트웨어에서는 No pull로 설정해야 한다.
- 입력 값의 의미는 회로 설계에 따라 정해지므로, 코드 작성 전에 회로도나 디버거로 실제 값을 확인해야 한다.
- 기계식 버튼은 누르는 순간 접점이 떨리는 **바운싱**이 있어 한 번의 입력이 여러 번 읽힌다. 회로(B1의 C16·R26)나 코드(일정 시간 유지될 때만 인정하는 **디바운싱**)로 걸러야 한다.
- 칩은 입력을 읽는 코드가 실행될 때만 핀 값을 안다(**폴링**). 눌리는 순간을 찾으려면 이전 값과 현재 값을 비교한다.
- 보드 회로도(MB1717)에서 LD4는 PA5가 트랜지스터(T2)를 켜고 끄는 구조로, LED 전류는 칩이 아닌 3V3에서 공급된다.

**개발 도구**
- 보드(Board Selector)가 아닌 칩(MCU Selector) 단위로 프로젝트를 만들어야 BSP의 점유 없이 핀을 직접 설정할 수 있다.
- 디버거의 **SFRs 창**으로 레지스터 값을 직접 관찰하면, 코드만 읽어서는 이해하기 어려운 동작도 빠르게 확인할 수 있다.
- **Live Expressions**는 프로그램을 멈추지 않고 변수 값을 실시간으로 보여 주므로, 바운싱처럼 빠른 현상의 횟수를 측정할 수 있다. (Debug로 시작 후 Resume으로 실행)

<br>

## 🔍 트러블슈팅

막혔던 문제와 해결 과정은 [`docs/troubleshooting.md`](./docs/troubleshooting.md)에 모아 둡니다.

| # | 실습 | 문제 |
| :---: | --- | --- |
| 1 | 01_led_blink | [Board Selector로 만든 프로젝트에서 PA5 설정이 변경되지 않음](./docs/troubleshooting.md#1-board-selector로-만든-프로젝트에서-pa5-설정이-변경되지-않음) |
| 2 | 01_led_blink | [MCU 선택 시 부품 번호가 여러 개라 무엇을 골라야 할지 모름](./docs/troubleshooting.md#2-mcu-선택-시-부품-번호가-여러-개라-무엇을-골라야-할지-모름) |
| 3 | 01_led_blink | [SYS 메뉴에서 Debug(Serial Wire) 설정 항목을 찾을 수 없음](./docs/troubleshooting.md#3-sys-메뉴에서-debugserial-wire-설정-항목을-찾을-수-없음) |
| 4 | 01_led_blink | [코드 생성 시 프로젝트 폴더가 이중으로 생성될 뻔함](./docs/troubleshooting.md#4-코드-생성-시-프로젝트-폴더가-이중으로-생성될-뻔함) |
| 5 | 01_led_blink | [HAL 내부의 비트 연산이 왜 필요한지 이해되지 않음](./docs/troubleshooting.md#5-hal-내부의-비트-연산이-왜-필요한지-이해되지-않음) |
| 6 | 01_led_blink | [BSRR에 쓴 비트 값이 계속 유지된다고 오해함](./docs/troubleshooting.md#6-bsrr에-쓴-비트-값이-계속-유지된다고-오해함) |
| 7 | 02_button_led | [버튼을 눌렀을 때 LED가 예상과 반대로 동작함](./docs/troubleshooting.md#7-버튼을-눌렀을-때-led가-예상과-반대로-동작함) |
| 8 | 기초 02 | [실험에 사용할 A0 핀의 위치를 찾지 못함](./docs/troubleshooting.md#8-실험에-사용할-a0-핀의-위치를-찾지-못함) |
| 9 | 03_button_toggle | [버튼을 누르면 입력 변수 값이 저절로 바뀐다고 오해함](./docs/troubleshooting.md#9-버튼을-누르면-입력-변수-값이-저절로-바뀐다고-오해함) |
| 10 | 03_button_toggle | [점퍼선으로 한 번 연결해도 눌림 횟수가 10 이상 증가함](./docs/troubleshooting.md#10-점퍼선으로-한-번-연결해도-눌림-횟수가-10-이상-증가함) |
| 11 | 03_button_toggle | [Run으로 실행하면 Live Expressions에서 변수 값을 볼 수 없음](./docs/troubleshooting.md#11-run으로-실행하면-live-expressions에서-변수-값을-볼-수-없음) |

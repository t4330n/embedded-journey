# 🔧 Embedded Journey

> NUCLEO-C031C6 보드로 임베디드 개발을 처음부터 차근차근 익혀 나가는 학습 기록입니다.
> LED 하나 켜는 것부터 시작해, 센서·통신·RTOS를 거쳐 직접 만든 프로젝트까지 단계별로 쌓아 갑니다.

<br>

## 🎯 목표

- 마이크로컨트롤러의 동작 원리를 **직접 코드로 확인하며** 이해하기
- 실습마다 **목표 → 구현 → 결과 → 배운 점 → 문제 해결 과정**을 기록하기
- 배운 내용을 조합해 **동작하는 임베디드 프로젝트** 완성하기

<br>

## 🛠 개발 환경

| 항목 | 내용 |
| --- | --- |
| Board | NUCLEO-C031C6 |
| MCU | STM32C031C6 (Arm Cortex-M0+) |
| IDE | STM32CubeIDE |
| Library | STM32 HAL |
| Language | C |

<br>

## 🗺 로드맵 & 진행 상황

| 단계 | 주제 | 실습 | 상태 |
| :---: | --- | --- | :---: |
| 1 | GPIO | [LED 깜빡이기](./01_gpio/01_led_blink) | ✅ |
| 1 | GPIO | [버튼으로 LED 제어](./01_gpio/02_button_led) | 🔄 |
| 1 | GPIO | 버튼 토글 & 디바운싱 | ⬜ |
| 2 | Timer / Interrupt | 타이머로 LED 주기 제어, 외부 인터럽트(EXTI) | ⬜ |
| 3 | UART | PC와 시리얼 통신, printf 디버깅 | ⬜ |
| 4 | I2C / SPI | 온도 센서 읽기, 디스플레이 출력 | ⬜ |
| 5 | ADC / PWM | 가변저항 읽기, LED 밝기 제어 | ⬜ |
| 6 | RTOS | FreeRTOS 태스크 분리 | ⬜ |
| 7 | Project | 배운 내용을 조합한 개인 프로젝트 | ⬜ |

✅ 완료 · 🔄 진행 중 · ⬜ 예정

<br>

## 📁 폴더 구조

```
embedded-journey/
├── README.md                 # 지금 보고 있는 문서
├── .gitignore
├── docs/
│   ├── practice-template.md  # 실습 기록 템플릿
│   └── troubleshooting.md    # 문제 해결 기록 모음
├── 01_gpio/
│   ├── 01_led_blink/         # 각 폴더 = STM32CubeIDE 프로젝트 1개
│   └── 02_button_led/
├── 02_timer_interrupt/
├── 03_uart/
├── 04_i2c_spi/
├── 05_adc_pwm/
├── 06_rtos/
└── projects/                 # 최종 프로젝트
```

각 실습 폴더에는 CubeIDE 프로젝트와 함께 해당 실습을 정리한 `README.md`가 들어 있습니다.

<br>

## 📝 실습 기록 방식

모든 실습은 [`docs/practice-template.md`](./docs/practice-template.md) 형식으로 정리합니다.

1. **목표** — 이 실습으로 무엇을 확인하려 했는지
2. **사용한 핀 / 설정** — 어떤 핀을 어떻게 설정했는지
3. **핵심 코드** — 동작의 중심이 되는 코드와 설명
4. **결과** — 동작 사진 또는 GIF
5. **배운 점** — 새로 이해하게 된 개념
6. **트러블슈팅** — 막혔던 부분과 해결 과정

<br>

## 💡 주요 배운 점

> 실습이 쌓일수록 핵심 내용을 여기에 요약합니다.

- **GPIO 출력**: `HAL_GPIO_WritePin`으로 핀 상태를 바꿔 LED를 제어할 수 있다.
- **GPIO 입력**: 보드의 사용자 버튼은 풀업 구조라 누르지 않으면 `1`, 누르면 `0`이 읽힌다.

<br>

## 🔍 트러블슈팅

막혔던 문제와 해결 과정은 [`docs/troubleshooting.md`](./docs/troubleshooting.md)에 모아 둡니다.

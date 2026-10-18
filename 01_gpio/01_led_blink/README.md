# 01. LED 깜빡이기

> 보드의 사용자 LED를 일정한 간격으로 켰다 끄며 GPIO 출력의 기본을 익힌 첫 실습

## 🎯 목표
- STM32CubeIDE로 프로젝트를 만들고 보드에 코드를 올리는 과정 익히기
- GPIO 출력 핀으로 LED 제어하기

## 📌 사용한 핀 / 설정
| 핀 | 모드 | 역할 |
| --- | --- | --- |
| PA5 | GPIO_Output | 사용자 LED (LD4, 초록) |

## 💻 핵심 코드
```c
while (1)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // LED 상태 뒤집기
    HAL_Delay(500);                        // 500ms 기다리기
}
```
- `HAL_GPIO_TogglePin`: 핀이 켜져 있으면 끄고, 꺼져 있으면 켠다.
- `HAL_Delay`: 지정한 시간(ms)만큼 기다린다.

## 🎬 결과
<!-- 동작 사진 또는 GIF -->

## 💡 배운 점
- CubeIDE에서 핀 설정(.ioc) → 코드 생성 → 빌드 → 보드 업로드까지의 흐름
- `/* USER CODE BEGIN */` ~ `/* USER CODE END */` 사이에 작성해야 코드 재생성 시 지워지지 않는다.

## 🔍 트러블슈팅
| 문제 | 원인 | 해결 |
| --- | --- | --- |
|  |  |  |

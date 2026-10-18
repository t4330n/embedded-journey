# 02. 버튼으로 LED 제어

> 사용자 버튼을 누르고 있는 동안만 LED가 켜지도록 만들며 GPIO 입력을 익힌 실습

## 🎯 목표
- GPIO 입력 핀으로 버튼 상태 읽기
- 읽은 입력에 따라 GPIO 출력(LED) 제어하기

## 📌 사용한 핀 / 설정
| 핀 | 모드 | 역할 |
| --- | --- | --- |
| PC13 | GPIO_Input | 사용자 버튼 (B1) |
| PA5 | GPIO_Output | 사용자 LED (LD4, 초록) |

## 💻 핵심 코드
```c
while (1)
{
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);   // 버튼 눌림 → LED 켜기
    } else {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // 버튼 뗌 → LED 끄기
    }
}
```
- `HAL_GPIO_ReadPin`: 입력 핀의 현재 상태(SET/RESET)를 읽는다.
- `HAL_GPIO_WritePin`: 출력 핀을 원하는 상태로 바꾼다.

## 🎬 결과
<!-- 동작 사진 또는 GIF -->

## 💡 배운 점
- 사용자 버튼은 풀업 구조라 **누르지 않으면 1, 누르면 0**이 읽힌다.
- 그래서 "눌렸다"는 조건을 `GPIO_PIN_RESET`으로 판단해야 한다.

## 🔍 트러블슈팅
| 문제 | 원인 | 해결 |
| --- | --- | --- |
|  |  |  |

## ➡️ 다음 도전
- 한 번 누르면 켜지고, 다시 누르면 꺼지는 **토글** 만들기
- 버튼이 여러 번 눌린 것처럼 동작하는 **채터링** 문제와 **디바운싱** 해결

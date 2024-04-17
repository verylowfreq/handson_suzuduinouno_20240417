extern "C" {
  // ArduinoはC++だが公式SDKはC言語なので、externでシンボル名を合わせる
  void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
}

// タイマー2で割り込みが発生すると"TIM2_IRQHandler"が呼び出される
void TIM2_IRQHandler(void) {
  static int delta = 1;
  static uint8_t ratio = 1;
  static uint8_t count = 0;

  if (count == 20) {
    if (ratio == 0 || ratio == 255) {
      delta *= -1;
    }
    ratio += delta;
  }

  if (count == 0) {
    digitalWrite(PA5, HIGH);
  }
  if (count >= ratio) {
    digitalWrite(PA5, LOW);
  }

  count += 1;

  // 次の割り込みを許可する
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void setup() {
  pinMode(PA5, OUTPUT);

  // タイマー2の割り込みを受け付ける
  NVIC_InitTypeDef NVICInit = { 0 };
  NVICInit.NVIC_IRQChannel = TIM2_IRQn;
  NVICInit.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVICInit);

  // タイマー2 にクロックの供給を開始する
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  // タイマー2の初期化
  TIM_TimeBaseInitTypeDef TIM_TimeInit = { 0 };
  TIM_TimeInit.TIM_Prescaler = 144 - 1;  // 144MHzを14分周し、1MHzにする
  TIM_TimeInit.TIM_Period = 10 - 1;  // 100KHzごとに割り込みを発生させる
  TIM_TimeInit.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeInit);
  TIM_Cmd(TIM2, ENABLE);

  // タイマー2で割り込みの発生を有効にする
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void loop() {
  // 次の割り込みまでCPUを停止する
  __WFI();
}

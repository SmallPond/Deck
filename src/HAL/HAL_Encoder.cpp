#include "HAL/HAL.h"
#include "App/Utils/ButtonEvent/ButtonEvent.h"
#include "App/Accounts/Account_Master.h"

static ButtonEvent EncoderPush(5000); // long press time
static ButtonEvent EncoderNext(5000);
static ButtonEvent EncoderPrev(5000);


static bool EncoderEnable = true;
static volatile int16_t EncoderDiff = 0;
static bool EncoderDiffDisable = false;

Account* actEncoder;

// static void Encoder_IrqHandler()
// {
//     if (!EncoderEnable || EncoderDiffDisable)
//     {
//         return;
//     }

//     static volatile int count, countLast;
//     static volatile uint8_t a0, b0;
//     static volatile uint8_t ab0;
//     uint8_t a = digitalRead(CONFIG_ENCODER_A_PIN);
//     uint8_t b = digitalRead(CONFIG_ENCODER_B_PIN);
//     if (a != a0)
//     {
//         a0 = a;
//         if (b != b0)
//         {
//             b0 = b;
//             count += ((a == b) ? 1 : -1);
//             if ((a == b) != ab0)
//             {
//                 count += ((a == b) ? 1 : -1);
//             }
//             ab0 = (a == b);
//         }
//     }

//     if (count != countLast)
//     {
//         EncoderDiff += (count - countLast) > 0 ? 1 : -1;
//         countLast = count;
//     }
// }

static void Encoder_NextHandler(ButtonEvent* btn, int event)
{
    Serial.print("Encoder_Next event:");
    Serial.println(event);
    if (event == ButtonEvent::EVENT_PRESSED)
    {
        Serial.println("Encoder_Next");
        EncoderDiff += 1;
    } 
}
static void Encoder_PrevHandler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED)
    {
        Serial.println("Encoder_Prev");
        EncoderDiff -= 1;
    } 
}

static void Encoder_PushHandler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED)
    {
        HAL::Buzz_Tone(500, 20);
        EncoderDiffDisable = true;
    } else if (event == ButtonEvent::EVENT_RELEASED)
    {
        HAL::Buzz_Tone(700, 20);
        EncoderDiffDisable = false;
    } else if (event == ButtonEvent::EVENT_LONG_PRESSED)
    {
        HAL::Audio_PlayMusic("Shutdown");
        HAL::Power_Shutdown();
    }
}

static void Encoder_RotateHandler(int16_t diff)
{
    HAL::Buzz_Tone(300, 5);

    actEncoder->Commit((const void*) &diff, sizeof(int16_t));
    actEncoder->Publish();
}

void HAL::Encoder_Init()
{
    pinMode(CONFIG_ENCODER_A_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_B_PIN, INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_PULLUP);
    //attachInterrupt(CONFIG_ENCODER_A_PIN, Encoder_A_IrqHandler, CHANGE);
    EncoderPush.EventAttach(Encoder_PushHandler);
    EncoderNext.EventAttach(Encoder_NextHandler);
    EncoderPrev.EventAttach(Encoder_PrevHandler);

    actEncoder = new Account("Encoder", AccountSystem::Broker(), sizeof(int16_t), nullptr);

}

void HAL::Encoder_Update()
{
    EncoderPush.EventMonitor(Encoder_GetIsPush());
    EncoderNext.EventMonitor(Encoder_NextIsPush());
    EncoderPrev.EventMonitor(Encoder_PrevIsPush());
}

int16_t HAL::Encoder_GetDiff()
{
    int16_t diff = EncoderDiff;
    if (diff != 0)
    {
        // EncoderDiff是实际的脉冲数；把本次变量用掉了，需要重新置0
        EncoderDiff = 0;
        Encoder_RotateHandler(diff);
    }

    return diff;
}

bool HAL::Encoder_GetIsPush()
{
    if (!EncoderEnable)
    {
        return false;
    }
    return (digitalRead(CONFIG_ENCODER_PUSH_PIN) == LOW);
}
bool HAL::Encoder_NextIsPush()
{
    if (!EncoderEnable)
    {
        return false;
    }

    return (digitalRead(CONFIG_ENCODER_A_PIN) == LOW);
}
bool HAL::Encoder_PrevIsPush()
{
    if (!EncoderEnable)
    {
        return false;
    }

    return (digitalRead(CONFIG_ENCODER_B_PIN) == LOW);
}

void HAL::Encoder_SetEnable(bool en)
{
    EncoderEnable = en;
}

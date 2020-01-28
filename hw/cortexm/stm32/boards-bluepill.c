/*
 * STM32 Bluepill board emulation.
 *
 * Copyright (c) 2020 Javier Alvarez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <hw/cortexm/board.h>
#include <hw/cortexm/stm32/mcus.h>
#include <hw/cortexm/gpio-led.h>
#include <hw/cortexm/button-gpio.h>
#include <hw/cortexm/button-reset.h>
#include <hw/cortexm/helper.h>

// ----- STM32F103C8T6 Bluepill -----------------------------------------------------
static GPIOLEDInfo bluepill_leds_info[] = {
    {
        .name = "led:red",
        .active_low = false,
        .colour_name = "red",
        .x = 545,
        .y = 200,
        .w = 14,
        .h = 22,
        .gpio_path = DEVICE_PATH_STM32_GPIO_C,
        .irq_name = STM32_IRQ_GPIO_ODR_OUT,
        .gpio_bit = 13,
    /**/
    },
    { },
/**/
};

static ButtonResetInfo bluepill_button_reset_info = {
    .x = 202,
    .y = 188,
    .w = 56,
    .h = 56,
/**/
};

static void bluepill_board_init_callback(MachineState *machine)
{
    CortexMBoardState *board = CORTEXM_BOARD_STATE(machine);

    cortexm_board_greeting(board);
    BoardGraphicContext *board_graphic_context =
            cortexm_board_init_graphic_image(board, "STM32-Bluepill.jpg");

    {
        // Create the MCU
        Object *mcu = cm_object_new_mcu(machine, TYPE_STM32F103RB);

        cm_object_property_set_int(mcu, 8000000, "hse-freq-hz"); // 8.0 MHz
        cm_object_property_set_int(mcu, 0, "lse-freq-hz"); // N/A

        cm_object_realize(mcu);
    }

    Object *peripheral = cm_container_get_peripheral();
    // Create board LEDs.
    gpio_led_create_from_info(peripheral, bluepill_leds_info,
            board_graphic_context);
    if (board_graphic_context != NULL) {
        // Create board buttons.
        button_reset_create_from_info(peripheral,
                &bluepill_button_reset_info, board_graphic_context);
    }
}

static void bluepill_board_class_init_callback(ObjectClass *oc, void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "STM32F103C8T6 Bluepill";
    mc->init = bluepill_board_init_callback;
}

static const TypeInfo bluepill_machine = {
    .name = BOARD_TYPE_NAME("BLUEPILL"),
    .parent = TYPE_CORTEXM_BOARD,
    .class_init = bluepill_board_class_init_callback
/**/
};

// ----- Boards inits ---------------------------------------------------------

static void stm32_machines_init(void)
{
    type_register_static(&bluepill_machine);
}

type_init(stm32_machines_init);

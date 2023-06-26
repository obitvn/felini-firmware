/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __CONFIG_H
#define __CONFIG_H

/*=========================
   Application configuration
 *=========================*/

#define CONFIG_LIVE_MAP_DEBUG_ENABLE          0
#if CONFIG_LIVE_MAP_DEBUG_ENABLE
#  define CONFIG_LIVE_MAP_VIEW_WIDTH          240
#  define CONFIG_LIVE_MAP_VIEW_HEIGHT         240
#else
#  define CONFIG_LIVE_MAP_VIEW_WIDTH          LV_HOR_RES
#  define CONFIG_LIVE_MAP_VIEW_HEIGHT         LV_VER_RES
#endif

#define CONFIG_MONKEY_TEST_ENABLE             0
#if CONFIG_MONKEY_TEST_ENABLE
#  define CONFIG_MONKEY_INDEV_TYPE            LV_INDEV_TYPE_ENCODER
#  define CONFIG_MONKEY_TIME_MIN              10
#  define CONFIG_MONKEY_TIME_MAX              300
#  define CONFIG_MONKEY_INPUT_RANGE_MIN       -5
#  define CONFIG_MONKEY_INPUT_RANGE_MAX       5
#endif

#endif

#include <cstdio>
#include "HAL.h"

// #include <string.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include "esp_system.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_log.h"
// #include "nvs_flash.h"

// #include "lwip/err.h"
// #include "lwip/sys.h"

/* FreeRTOS event group to signal when we are connected*/
// static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
// #define WIFI_CONNECTED_BIT BIT0
// #define WIFI_FAIL_BIT      BIT1

// static const char *TAG = "HAL::WiFi";

// static int s_retry_num = 0;
// static bool wifi_connected_status = false;
// static char sta_ip[32];

// static void event_handler(void *arg, esp_event_base_t event_base,
//                           int32_t event_id, void *event_data)
// {
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
//         esp_wifi_connect();
//     } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
//         if (s_retry_num < CONFIG_MAXIMUM_RETRY) {
//             esp_wifi_connect();
//             s_retry_num++;
//             ESP_LOGI(TAG, "retry %d to connect to the AP", s_retry_num);
//         } else {
//             wifi_connected_status = false;
//             xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
//         }
//         ESP_LOGI(TAG, "connect to the AP fail");
//     } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
//         ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
//         ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
//         sprintf(sta_ip, IPSTR, IP2STR(&event->ip_info.ip));
//         s_retry_num = 0;
//         wifi_connected_status = true;
//         xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
//     }
// }

void HAL::WiFi_Init()
{
    // s_wifi_event_group = xEventGroupCreate();

    // ESP_ERROR_CHECK(esp_netif_init());

    // ESP_ERROR_CHECK(esp_event_loop_create_default());
    // esp_netif_create_default_wifi_sta();

    // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // esp_event_handler_instance_t instance_any_id;
    // esp_event_handler_instance_t instance_got_ip;
    // ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
    //                 ESP_EVENT_ANY_ID,
    //                 &event_handler,
    //                 NULL,
    //                 &instance_any_id));
    // ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
    //                 IP_EVENT_STA_GOT_IP,
    //                 &event_handler,
    //                 NULL,
    //                 &instance_got_ip));

    // wifi_config_t wifi_config = {};
    // MEMCPY(wifi_config.sta.ssid, (char *)CONFIG_WIFI_SSID, sizeof(CONFIG_WIFI_SSID));
    // MEMCPY(wifi_config.sta.password, (char *)CONFIG_WIFI_PASSWORD, sizeof(CONFIG_WIFI_PASSWORD));
    // wifi_config.sta.pmf_cfg.capable = true;
    // wifi_config.sta.pmf_cfg.required = false;
    // wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA_WPA2_PSK;

    // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    // ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    // ESP_ERROR_CHECK(esp_wifi_start() );

    // ESP_LOGI(TAG, "wifi_init_sta finished.");

    // /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
    //  * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    // EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
    //         WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
    //         pdFALSE,
    //         pdFALSE,
    //         portMAX_DELAY);

    // /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
    //  * happened. */
    // if (bits & WIFI_CONNECTED_BIT) {
    //     ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
    //              CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
    // } else if (bits & WIFI_FAIL_BIT) {
    //     ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
    //              CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);
    // } else {
    //     ESP_LOGE(TAG, "UNEXPECTED EVENT");
    // }
}

void HAL::WiFi_GetInfo(WiFi_Info_t *info)
{
    // info->isConnected = wifi_connected_status;
    // sprintf(info->ip_str, "%s", sta_ip);
}

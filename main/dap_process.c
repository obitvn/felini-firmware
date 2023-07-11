#include "usbd_core.h"
#include "DAP_config.h"
#include "DAP.h"

uint8_t USB_Request[DAP_PACKET_SIZE];         // Request  Buffer
static uint8_t USB_Response[DAP_PACKET_SIZE]; // Response Buffer
volatile uint8_t dealing_data = 0;
volatile uint8_t dap_send_busy = 0;

void usb_dap_recv_callback(uint8_t ep, uint32_t nbytes)
{
    if (USB_Request[0] == ID_DAP_TransferAbort)
    {
        usbd_ep_start_read(ep, USB_Request, DAP_PACKET_SIZE);
        DAP_TransferAbort = 1;
        return;
    }

    if (dealing_data)
    {
        // TODO:
        usbd_ep_start_read(ep, USB_Request, DAP_PACKET_SIZE);
        return; // Discard packet when buffer is full
    }
    dealing_data = 1;
    usbd_ep_start_read(ep, USB_Request, DAP_PACKET_SIZE);
}

void usb_dap_send_callback(uint8_t ep, uint32_t nbytes)
{
    if (dap_send_busy == 1)
    {
        dap_send_busy = 0;
    }
}

void dap_process(void)
{
    static uint8_t res_len = 0;
    if (dealing_data)
    {
        res_len = DAP_ProcessCommand(USB_Request, USB_Response);
        usbd_ep_start_write(0x82, USB_Response, res_len);
        dap_send_busy = 1;
        while (dap_send_busy)
        {
            /*!< wait */
        }
        dealing_data = 0;
    }
}


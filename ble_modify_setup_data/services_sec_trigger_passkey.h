/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
*
* The information contained herein is property of Nordic Semiconductor ASA.
* Terms and conditions of usage are described in detail in NORDIC
* SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
*
* Licensees are granted free, non-transferable use of the information. NO
* WARRANTY of ANY KIND is provided. This heading must NOT be removed from
* the file.
*/

/**
* This file is autogenerated by nRFgo Studio 1.15.0.2677 
*/

#ifndef SETUP_MESSAGES_H__
#define SETUP_MESSAGES_H__

#include "hal_platform.h" 
#include "aci.h"

#define ACI_DYNAMIC_DATA_SIZE 251
#define PIPE_FBTRACKER_TXPIPE_TX 1
#define PIPE_FBTRACKER_TXPIPE_TX_MAX_SIZE 20

#define PIPE_FBTRACKER_RXPIPE_RX 2
#define PIPE_FBTRACKER_RXPIPE_RX_MAX_SIZE 20

#define PIPE_FBACTIVITY_FBACTIVITYVALUE_TX 3
#define PIPE_FBACTIVITY_FBACTIVITYVALUE_TX_MAX_SIZE 16

#define PIPE_FBACTIVITY_SECURITYTRIGGER_RX_ACK_AUTO 4
#define PIPE_FBACTIVITY_SECURITYTRIGGER_RX_ACK_AUTO_MAX_SIZE 6

#define PIPE_DEVICE_INFORMATION_FITBIT_DATA_BROADCAST 5
#define PIPE_DEVICE_INFORMATION_FITBIT_DATA_BROADCAST_MAX_SIZE 2

#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET 6
#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET_MAX_SIZE 15

#define PIPE_BATTERY_BATTERY_LEVEL_TX 7
#define PIPE_BATTERY_BATTERY_LEVEL_TX_MAX_SIZE 1

#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_CONTROL_POINT_TX_ACK 8
#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_CONTROL_POINT_TX_ACK_MAX_SIZE 20

#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_NOTIFICATION_SOURCE_RX 9
#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_NOTIFICATION_SOURCE_RX_MAX_SIZE 1

#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_DATA_SOURCE_RX 10
#define PIPE_APPLE_NOTIFICATION_CENTER_ANC_DATA_SOURCE_RX_MAX_SIZE 20


#define NUMBER_OF_PIPES 10

#define SERVICES_PIPE_TYPE_MAPPING_CONTENT {\
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_RX},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_RX_ACK_AUTO},   \
  {ACI_STORE_LOCAL, ACI_TX_BROADCAST},   \
  {ACI_STORE_LOCAL, ACI_SET},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_REMOTE, ACI_TX_ACK},   \
  {ACI_STORE_REMOTE, ACI_RX},   \
  {ACI_STORE_REMOTE, ACI_RX},   \
}

#define GAP_PPCP_MAX_CONN_INT 0x6 /**< Maximum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_MIN_CONN_INT  0x6 /**< Minimum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific maximum*/
#define GAP_PPCP_SLAVE_LATENCY 0
#define GAP_PPCP_CONN_TIMEOUT 0xc8 /** Connection Supervision timeout multiplier as a multiple of 10msec, 0xFFFF means no specific value requested */

#define NB_SETUP_MESSAGES 38
#define SETUP_MESSAGES_CONTENT {\
    {0x00,\
        {\
            0x07,0x06,0x00,0x00,0x03,0x02,0x41,0xd7,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0x07,0x04,0x0b,0x01,0x01,0x00,0x00,0x05,0x00,0x01,\
            0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfb,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x1c,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x10,0x08,0x00,0x00,0x10,0x08,0x10,0x90,0x06,0xff,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x38,0xff,0xff,0x00,0x78,0x0a,0x05,0x00,0x00,0x00,0x50,0x00,0x00,0x00,0x50,0x00,0x00,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x05,0x06,0x10,0x54,0x01,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x00,0x04,0x04,0x02,0x02,0x00,0x01,0x28,0x00,0x01,0x00,0x18,0x04,0x04,0x05,0x05,0x00,\
            0x02,0x28,0x03,0x01,0x02,0x03,0x00,0x00,0x2a,0x04,0x04,0x14,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x1c,0x07,0x00,0x03,0x2a,0x00,0x01,0x41,0x6a,0x61,0x79,0x73,0x6f,0x6e,0x65,0x6d,0x69,\
            0x2e,0x63,0x6f,0x6d,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x38,0x05,0x05,0x00,0x04,0x28,0x03,0x01,0x02,0x05,0x00,0x01,0x2a,0x06,0x04,0x03,0x02,\
            0x00,0x05,0x2a,0x01,0x01,0x00,0x00,0x04,0x04,0x05,0x05,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x54,0x06,0x28,0x03,0x01,0x02,0x07,0x00,0x04,0x2a,0x06,0x04,0x09,0x08,0x00,0x07,0x2a,\
            0x04,0x01,0x06,0x00,0x06,0x00,0x00,0x00,0xc8,0x00,0x04,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x70,0x02,0x02,0x00,0x08,0x28,0x00,0x01,0x01,0x18,0x04,0x04,0x10,0x10,0x00,0x09,0x28,\
            0x00,0x01,0xba,0x56,0x89,0xa6,0xfa,0xbf,0xa2,0xbd,0x01,0x46,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x8c,0x7d,0x6e,0x00,0xfb,0xab,0xad,0x04,0x04,0x13,0x13,0x00,0x0a,0x28,0x03,0x01,0x12,\
            0x0b,0x00,0xba,0x56,0x89,0xa6,0xfa,0xbf,0xa2,0xbd,0x01,0x46,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xa8,0x7d,0x6e,0x01,0xfb,0xab,0xad,0x14,0x04,0x14,0x01,0x00,0x0b,0xfb,0x01,0x02,0x42,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xc4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x14,0x03,0x02,0x00,0x0c,0x29,0x02,0x01,\
            0x00,0x00,0x04,0x04,0x13,0x13,0x00,0x0d,0x28,0x03,0x01,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xe0,0x0e,0x00,0xba,0x56,0x89,0xa6,0xfa,0xbf,0xa2,0xbd,0x01,0x46,0x7d,0x6e,0x02,0xfb,\
            0xab,0xad,0x44,0x10,0x14,0x00,0x00,0x0e,0xfb,0x02,0x02,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x00,0x04,0x04,0x10,0x10,0x00,0x0f,0x28,0x00,0x01,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x18,0x80,0x29,0xe6,0x93,0xaa,0x4e,0x02,0x9f,0x05,0x41,0xa8,0x4f,0x00,0xfa,0x8d,0x55,\
            0x04,0x04,0x13,0x13,0x00,0x10,0x28,0x03,0x01,0x12,0x11,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x34,0x80,0x29,0xe6,0x93,0xaa,0x4e,0x02,0x9f,0x05,0x41,0xa8,0x4f,0x01,0xfa,0x8d,0x55,\
            0x16,0x04,0x11,0x10,0x00,0x11,0xfa,0x01,0x03,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x14,0x03,\
            0x02,0x00,0x12,0x29,0x02,0x01,0x00,0x00,0x04,0x04,0x13,0x13,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x6c,0x00,0x13,0x28,0x03,0x01,0x0a,0x14,0x00,0xba,0x56,0x89,0xa6,0xfa,0xbf,0xa2,0xbd,\
            0x01,0x46,0x7d,0x6e,0x0a,0x00,0xab,0xad,0x44,0x1C,0x06,0x06,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x88,0x00,0x14,0x00,0x0a,0x02,0x11,0x22,0x33,0x44,0x55,0x66,0x04,0x04,0x02,0x02,0x00,\
            0x15,0x28,0x00,0x01,0x0a,0x18,0x04,0x04,0x05,0x05,0x00,0x16,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xa4,0x28,0x03,0x01,0x02,0x17,0x00,0x29,0x2a,0x06,0x04,0x15,0x14,0x00,0x17,0x2a,0x29,\
            0x01,0x46,0x69,0x74,0x62,0x69,0x74,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x08,0x07,0x00,0x18,0x29,\
            0x04,0x01,0x19,0x00,0x00,0x00,0x01,0x00,0x00,0x04,0x04,0x05,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xdc,0x05,0x00,0x19,0x28,0x03,0x01,0x02,0x1a,0x00,0x00,0xfb,0x04,0x04,0x02,0x02,0x00,\
            0x1a,0xfb,0x00,0x01,0x00,0x00,0x04,0x04,0x05,0x05,0x00,0x1b,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0xf8,0x28,0x03,0x01,0x02,0x1c,0x00,0x27,0x2a,0x04,0x04,0x0f,0x00,0x00,0x1c,0x2a,0x27,\
            0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x22,0x14,0x00,0x00,0x00,0x00,0x04,0x04,0x02,0x02,0x00,0x1d,0x28,0x00,0x01,0x0f,0x18,0x04,\
            0x04,0x05,0x05,0x00,0x1e,0x28,0x03,0x01,0x12,0x1f,0x00,0x19,\
        },\
    },\
    {0x00,\
        {\
            0x1a,0x06,0x22,0x30,0x2a,0x16,0x04,0x02,0x01,0x00,0x1f,0x2a,0x19,0x01,0x00,0x46,0x14,0x03,0x02,0x00,\
            0x20,0x29,0x02,0x01,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x0d,0x06,0x30,0x00,0xf4,0x31,0x04,0x07,0x03,0x18,0x01,0x01,0x0a,0x01,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x00,0xfb,0x01,0x02,0x00,0x02,0x04,0x00,0x0b,0x00,0x0c,0xfb,0x02,0x02,0x00,0x08,0x04,\
            0x00,0x0e,0x00,0x00,0xfa,0x01,0x03,0x00,0x02,0x04,0x00,0x11,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x1c,0x00,0x12,0x00,0x0a,0x02,0x04,0x00,0x04,0x00,0x14,0x00,0x00,0xfb,0x00,0x01,0x00,\
            0x01,0x04,0x00,0x1a,0x00,0x00,0x2a,0x27,0x01,0x00,0x80,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x38,0x00,0x1c,0x00,0x00,0x2a,0x19,0x01,0x00,0x02,0x04,0x00,0x1f,0x00,0x20,0xd8,0xf3,\
            0x05,0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x12,0x0d,0x06,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1d,0x06,0x40,0x54,0x08,0x04,0x00,0x00,0x00,0x00,0xc6,0xe9,0x07,0x00,0x08,0x04,0x00,0x00,0x00,0x00,\
            0x2a,0x05,0x01,0x00,0x10,0x04,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x50,0x00,0xba,0x56,0x89,0xa6,0xfa,0xbf,0xa2,0xbd,0x01,0x46,0x7d,0x6e,0x00,0x00,0xab,0xad,\
            0x80,0x29,0xe6,0x93,0xaa,0x4e,0x02,0x9f,0x05,0x41,0xa8,0x4f,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x50,0x1c,0x00,0x00,0x8d,0x55,0xd0,0x00,0x2d,0x12,0x1e,0x4b,0x0f,0xa4,0x99,0x4e,0xce,0xb5,\
            0x00,0x00,0x05,0x79,0xd9,0xd9,0xaa,0xfd,0xbd,0x9b,0x21,0x98,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x50,0x38,0xa8,0x49,0xe1,0x45,0x00,0x00,0xd1,0x69,0xbd,0x1d,0xa2,0x99,0xe6,0x25,0x58,0x8c,\
            0xd9,0x42,0x01,0x63,0x00,0x00,0xbf,0x9f,0xfb,0x7b,0x7c,0xce,\
        },\
    },\
    {0x00,\
        {\
            0x0f,0x06,0x50,0x54,0x6a,0xb3,0x44,0xbe,0xb5,0x4b,0xd6,0x24,0x00,0x00,0xea,0x22,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x08,0x06,0x60,0x1c,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x06,0x06,0xf0,0x00,0x03,0xCA,0x0E,\
        },\
    },\
}

#endif

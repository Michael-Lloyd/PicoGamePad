/*
 *  Author:     Michael Lloyd (micl.dev)
 *  Version:    1.0.0
 *  Variant:    A
 *  Date:       21/09/22
 *
 *      __   ___.--'_`. 
 *     ( _`.'. -   'o` ) 
 *     _\.'_'      _.-'  
 *     ( `. )    //`    
 *     \_`-'`---'\__,   
 *      \`        \`--    
 *
 */

#include "include/usb.h"

// ================================================================================================
// USB Communication Handling
// ================================================================================================

#define _PID_TABLE(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID (0x4000 | _PID_TABLE(CDC, 0) | _PID_TABLE(MSC, 1) | _PID_TABLE(HID, 2) | \
		_PID_TABLE(MIDI, 3) | _PID_TABLE(VENDOR, 4))

// ========================================================
// h2_Header
void USBDevice::init() { 


} 

void USBDevice::update() { 


} 

void USBDevice::ConnectionPanic(uint16_t e) { 

	this.report.Btn = e; 

	while(1) { 

		this.update(); 

		if(this.state[USB] == CONN_SUSPENDED) { 
			this.remote_wakeup();
		} 


		if(this.state[HID] == DEVICE_READY) { 
			this.hidReport(0x00, 0x01, &this.report, sizeof(this.report)); 
		}
	}
}

// Reference :
// https://github.com/hathach/tinyusb/blob/master/examples/device/hid_generic_inout/src/usb_descriptors.c 

//FIXME const deviceDescriptor = {
	.bLen = sizeof(//FIXME)
	.bDescriptor_t = USB_DESCRIPTOR,
	.bcdUSB = 0x200,
	.bDeviceClass = 0x00, 
	.bDeviceSubClass = 0x00,
	.bDeviceProtocol = 0x00,
	.bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE

	.idVendor		= 0xCafe,
	.idProduct		= USB_PID 
	.iSerialNum		= 0x03 

	.bNumConfigs	= 0x01 

}; 

// * - *

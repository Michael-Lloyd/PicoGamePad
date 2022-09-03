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
 *     \_`-'`---'\\__,   
 *      \\`        \`--    
 *
 */

#ifndef _PICOPAD_SYSTEM_
#define _PICOPAD_SYSTEM_ 

#include "include/picoSystem.h" 
#include "include/storage.h" 

// ================================================================================================
// class System
// ================================================================================================

// ========================================================
// System constructor 

inline System::System() { 

	// Flash init 
	
	// Flash format & crc chk?
	
	// Gamepad composition

	// Layout structures 
	
	// Mask assignment 

	// multicore inits  
	
	// Event queue init 
	
	// Event log init 
	
} 

// ========================================================
// Setup

void System::setup() { 
	
	// Flash 
	
	// CRC sign 
	
	// Gamepad mappings, settings, masks, resultant configurations 
	
	// Mask => Sanity check 
	
	// Core init, thread 
	
	// Event queue population 
	
	// Event log appendages 
	
	// Mask => Sanity check 
	
	// Debug => Telemetry 
	
	// LED init & status blink 

	// Mode specific setups 
	
	switch(this.getMode()) { 
		case():
			break; 
		case(): 
			break; 
		default:
			break; 
	} 
} 

// ========================================================
// System loop, or 'update'

void System::update() { 
	
	// Tick log obj

	// Timer check 

	// Dynamic debouncing thread spawn 
	
	/* 
	 *      <--------------- GLOBAL_DEBOUNCE_WINDOW -------------------->
	 *  c0: <------BTN A------>
	 *  c1: <------BTN START -------->
	 *  c1:                           <------- BTN B -------->
	 *  c0:                    <------- BTN UP -------->
	 *	etc ... 
	 *
	 */
	
	// Thread awaits & log aggregation 
		// 10% margin for timer due to RT lag 
		// while(!queue.isEmpty() && timer < 0.9*window )...
	
	// Report generation 
	
	// report -> log 

	// Log -> Flash 

	// nextRuntime = curr + GLOBAL_DEBOUNCE_WINDOW 

} 

// * - *

#endif

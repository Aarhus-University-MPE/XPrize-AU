/*
  Lake Profiler Command List
  - Sent over Serial (USB)

  Every message is wrapped with start and end mark
    '<COMMAND>'

  Example:
    '<FL>' - Returns a list of all files on the local storage

  Mads Rosenhøj Jepepsen
  Aarhus University
  2022
*/

#pragma once

// Wrappers
#define CMD_START_MARK         '<'
#define CMD_END_MARK           '>'

// File system
#define CMD_FILES              'F'
#define CMD_FILES_LIST         'L'
#define CMD_FILES_SIZE         'S'
#define CMD_FILES_DOWNLOAD     'D'
#define CMD_FILES_CREATE       'C'
#define CMD_FILES_REMOVE       'R'
#define CMD_FILES_WRITE        'W'
#define CMD_FILES_WRITENEWLINE 'N'
#define CMD_FILES_QUIT         'Q'
#define CMD_FILES_BLCKBOX      'B'
#define CMD_FILES_BLCKBOXEMPTY 'E'
#define CMD_FILES_WIPEDATA     'w'

// Power
#define CMD_POWER              'P'
#define CMD_POWER_SET          'S'
#define CMD_POWER_GET          'G'
#define CMD_POWER_PRINT        'P'

// DEBUG
#define CMD_DEBUG              'D'
#define CMD_DEBUG_A            'A'
#define CMD_DEBUG_B            'B'
#define CMD_DEBUG_C            'C'
#define CMD_DEBUG_D            'D'

// ------------------------------------------------------------ //
//                      Example Commands                        //
// ------------------------------------------------------------ //

// Clock setup
// <CY22><CM9><CD28><CH12><Cm25><CP>
// 2022/09/28/12:25

// Local storage Clear
// <FRdata/22072117.csv><FRdata/22072117.log>
// <FRdata/22072123.csv><FRdata/22072123.log><FRdata/22072100.csv><FRdata/2207210o.l0g>
// <FRdata/22072105.csv><FRdata/22072105.log>
// <FRdata/22072106.csv><FRdata/22072106.log>
// <FRdata/22072111.csv><FRdata/22072111.log>
// <FRdata/22072115.csv><FRdata/22072115.log>'
//
// <FRdata/>
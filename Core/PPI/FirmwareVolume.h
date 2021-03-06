/*++

Copyright (c) 2007 - 2009, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  FirmwareVolume.h

Abstract:

  PI 1.0 spec definition.

--*/

#ifndef __FIRMWARE_VOLUME_H__
#define __FIRMWARE_VOLUME_H__

#if defined(PI_SPECIFICATION_VERSION)&&(PI_SPECIFICATION_VERSION>=0x00010000)
#include <Pei.h>

EFI_FORWARD_DECLARATION (EFI_PEI_FIRMWARE_VOLUME_PPI);

typedef UINT32  EFI_FV_FILE_ATTRIBUTES;
typedef VOID  * EFI_PEI_FILE_HANDLE;
typedef VOID  * EFI_PEI_FV_HANDLE;

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FV_PROCESS_FV) (
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI        *This,
  IN  VOID                                    *Buffer,
  IN  UINTN                                   BufferSize,
  OUT EFI_PEI_FV_HANDLE                       *FvHandle
  );


typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FV_FIND_FILE_TYPE) (
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI       *This,
  IN EFI_FV_FILETYPE                         SearchType,
  IN EFI_PEI_FV_HANDLE                       FvHandle,
  IN OUT EFI_PEI_FILE_HANDLE                 *FileHandle
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_PEI_FV_FIND_FILE_NAME) (
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI     *This,
  IN CONST EFI_GUID                        *FileName,
  IN OUT EFI_PEI_FV_HANDLE                 *FvHandle,
  OUT EFI_PEI_FILE_HANDLE                  *FileHandle
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FV_GET_FILE_INFO) (
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI     *This,
  IN EFI_PEI_FILE_HANDLE                   FileHandle,
  OUT EFI_FV_FILE_INFO                     *FileInfo
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FV_GET_INFO)(
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI  *This,
  IN EFI_PEI_FV_HANDLE                  FvHandle,
  OUT EFI_FV_INFO                       *VolumeInfo
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PEI_FV_FIND_SECTION) (
  IN CONST EFI_PEI_FIRMWARE_VOLUME_PPI   *This,
  IN EFI_SECTION_TYPE                    SearchType,
  IN EFI_PEI_FILE_HANDLE                 FileHandle,
  OUT VOID                               **SectionData
  );

typedef struct _EFI_PEI_FIRMWARE_VOLUME_PPI {
  EFI_PEI_FV_PROCESS_FV             ProcessVolume;
  EFI_PEI_FV_FIND_FILE_TYPE         FindFileByType;   
  EFI_PEI_FV_FIND_FILE_NAME         FindFileByName;     
  EFI_PEI_FV_GET_FILE_INFO          GetFileInfo;      
  EFI_PEI_FV_GET_INFO               GetVolumeInfo;
  EFI_PEI_FV_FIND_SECTION           FindSectionByType;
} EFI_PEI_FIRMWARE_VOLUME_PPI;

#endif


#endif
/** @file
  Header file for SMM Access Driver.

@copyright
  Copyright (c) 1999 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains an 'Intel Peripheral Driver' and uniquely
  identified as "Intel Reference Module" and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
**/
#ifndef _SMM_ACCESS_DRIVER_H_
#define _SMM_ACCESS_DRIVER_H_

#include "EdkIIGlueDxe.h"
#include "pci22.h"
#include "EdkIIGlueHobLib.h"
#include "EfiScriptLib.h"
#include "SaAccess.h"

///
/// Driver Consumed Protocol Prototypes
///
#include EFI_PROTOCOL_CONSUMER (PciRootBridgeIo)

///
/// Driver private data
///
#include EFI_GUID_DEFINITION (SmramMemoryReserve)
#include EFI_GUID_DEFINITION (Hob)
#include EFI_PROTOCOL_DEFINITION (SmmAccess)

#define SMM_ACCESS_PRIVATE_DATA_SIGNATURE EFI_SIGNATURE_32 ('4', '5', 's', 'a')

///
/// Private data
///
typedef struct {
  UINTN                           Signature;
  EFI_HANDLE                      Handle;
  EFI_SMM_ACCESS_PROTOCOL         SmmAccess;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo;

  ///
  /// Local Data for SMM Access interface goes here
  ///
  UINTN                           NumberRegions;
  EFI_SMRAM_DESCRIPTOR            *SmramDesc;
} SMM_ACCESS_PRIVATE_DATA;

#define SMM_ACCESS_PRIVATE_DATA_FROM_THIS(a) \
  CR (a, \
      SMM_ACCESS_PRIVATE_DATA, \
      SmmAccess, \
      SMM_ACCESS_PRIVATE_DATA_SIGNATURE \
      )

///
/// Prototypes
/// Driver model protocol interface
///
/**
  This is the standard EFI driver point that
  installs an SMM Access Protocol

  @param[in] ImageHandle     - Handle for the image of this driver
  @param[in] SystemTable     - Pointer to the EFI System Table

  @retval EFI_SUCCESS     - Protocol was installed successfully
  @exception EFI_UNSUPPORTED - Protocol was not installed
**/
EFI_STATUS
SmmAccessDriverEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
;

/**
  This routine accepts a request to "open" a region of SMRAM.  The
  region could be legacy ABSEG, HSEG, or TSEG near top of physical memory.
  The use of "open" means that the memory is visible from all boot-service
  and SMM agents.

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Open.

  @retval EFI_SUCCESS           - The region was successfully opened.
  @retval EFI_DEVICE_ERROR      - The region could not be opened because locked by
                          chipset.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Open (
  IN EFI_SMM_ACCESS_PROTOCOL *This,
  IN UINTN                   DescriptorIndex
  )
;

/**
  This routine accepts a request to "close" a region of SMRAM.  The
  region could be legacy AB or TSEG near top of physical memory.
  The use of "close" means that the memory is only visible from SMM agents,
  not from BS or RT code.

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Close.

  @retval EFI_SUCCESS           - The region was successfully closed.
  @retval EFI_DEVICE_ERROR      - The region could not be closed because locked by
                            chipset.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Close (
  IN EFI_SMM_ACCESS_PROTOCOL *This,
  IN UINTN                   DescriptorIndex
  )
;

/**
  This routine accepts a request to "lock" SMRAM.  The
  region could be legacy AB or TSEG near top of physical memory.
  The use of "lock" means that the memory can no longer be opened
  to BS state..

  @param[in] This                  - Pointer to the SMM Access Interface.
  @param[in] DescriptorIndex       - Region of SMRAM to Lock.

  @retval EFI_SUCCESS           - The region was successfully locked.
  @retval EFI_DEVICE_ERROR      - The region could not be locked because at least
                          one range is still open.
  @retval EFI_INVALID_PARAMETER - The descriptor index was out of bounds.
**/
EFI_STATUS
EFIAPI
Lock (
  IN EFI_SMM_ACCESS_PROTOCOL *This,
  IN UINTN                   DescriptorIndex
  )
;

/**
  This routine services a user request to discover the SMRAM
  capabilities of this platform.  This will report the possible
  ranges that are possible for SMRAM access, based upon the
  memory controller capabilities.

  @param[in] This                  - Pointer to the SMRAM Access Interface.
  @param[in] SmramMapSize          - Pointer to the variable containing size of the
                            buffer to contain the description information.
  @param[in] SmramMap              - Buffer containing the data describing the Smram
                            region descriptors.

  @retval EFI_BUFFER_TOO_SMALL  - The user did not provide a sufficient buffer.
  @retval EFI_SUCCESS           - The user provided a sufficiently-sized buffer.
**/
EFI_STATUS
EFIAPI
GetCapabilities (
  IN EFI_SMM_ACCESS_PROTOCOL     *This,
  IN OUT UINTN                   *SmramMapSize,
  IN OUT EFI_SMRAM_DESCRIPTOR    *SmramMap
  )
;

#endif

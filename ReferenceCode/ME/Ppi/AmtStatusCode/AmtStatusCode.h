/** @file
  Header file for AMT Status Code support at PEI phase

@copyright
  Copyright (c) 2010 - 2012 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
**/
#ifndef _PEI_AMT_STATUS_CODE_PPI_H_
#define _PEI_AMT_STATUS_CODE_PPI_H_

///
/// Intel AMT PEI Status Code PPI GUID
/// This driver produces interface to let PEI Status Code generic driver report status to
/// Intel AMT, so that Intel AMT PET message can be sent out in PEI phase.
///
#define PEI_AMT_STATUS_CODE_PPI_GUID \
  { \
    0x881807d2, 0x98d1, 0x4ec9, 0xaf, 0xa0, 0x77, 0x46, 0xc4, 0x2f, 0x24, 0x49 \
  }

extern EFI_GUID gPeiAmtStatusCodePpiGuid;

EFI_FORWARD_DECLARATION (PEI_AMT_STATUS_CODE_PPI);

/**
  Provides an interface that a software module can call to report an ASF PEI status code.
  The extension to report status code to Intel AMT, so that Intel AMT PET message will
  be sent out in PEI.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] This                 This interface.
  @param[in] Type                 Indicates the type of status code being reported.
  @param[in] Value                Describes the current status of a hardware or software entity.
                                  This included information about the class and subclass that is
                                  used to classify the entity as well as an operation.
  @param[in] Instance             The enumeration of a hardware or software entity within
                                  the system. Valid instance numbers start with 1.
  @param[in] CallerId             This optional parameter may be used to identify the caller.
                                  This parameter allows the status code driver to apply different
                                  rules to different callers.
  @param[in] Data                 This optional parameter may be used to pass additional data.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_DEVICE_ERROR        The function should not be completed due to a device error.
**/
typedef
EFI_STATUS
(EFIAPI *PEI_AMT_STATUS_CODE_PPI_REPORT_STATUS_CODE) (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  PEI_AMT_STATUS_CODE_PPI     *This,
  IN  EFI_STATUS_CODE_TYPE        Type,
  IN  EFI_STATUS_CODE_VALUE       Value,
  IN  UINT32                      Instance,
  IN  EFI_GUID                    *CallerId OPTIONAL,
  IN  EFI_STATUS_CODE_DATA        *Data OPTIONAL
  )
;

///
/// Intel AMT PEI Status Code PPI
/// The PEI platform status code driver should be responsible to use this interface to report
/// status code to Intel AMT. For example, memory init, memory init done, chassis intrusion.
/// So that Intel AMT driver will send corresponding PET message out.
///
struct _PEI_AMT_STATUS_CODE_PPI {
  ///
  /// The extension to report status code to Intel AMT, so that Intel AMT PET message will
  /// be sent out in PEI.
  ///
  PEI_AMT_STATUS_CODE_PPI_REPORT_STATUS_CODE  ReportStatusCode;
};

///
/// Queue Hob.
/// This hob is used by PEI Status Code generic driver before Intel AMT PEI status code driver
/// starts.
/// 1) If AMT driver is not ready yet, StatusCode driver can save information
///    to QueueHob.
/// 2) If after AMT driver start, but ME is not ready, the AMT
///    driver can also save information to QueueHob.
/// Later, when ME is ready, AMT driver will send all the
/// message in the QueueHob.
///
typedef struct {
  EFI_HOB_GUID_TYPE     EfiHobGuidType; ///< The GUID type hob header
  EFI_STATUS_CODE_VALUE Value;          ///< Status code value
  EFI_STATUS_CODE_TYPE  Type;           ///< Status code type
} AMT_PET_QUEUE_HOB;

#define AMT_PET_QUEUE_HOB_GUID \
  { \
    0xca0801d3, 0xafb1, 0x4dec, 0x9b, 0x65, 0x93, 0x65, 0xec, 0xc7, 0x93, 0x6b \
  }

extern EFI_GUID gAmtPetQueueHobGuid;

#define AMT_FORCE_PUSH_PET_HOB_GUID \
  { \
    0x4efa0db6, 0x26dc, 0x4bb1, 0xa7, 0x6f, 0x14, 0xbc, 0x63, 0x0c, 0x7b, 0x3c \
  }

typedef struct {
  EFI_HOB_GUID_TYPE EfiHobGuidType;
  INT32             MessageType;
} AMT_FORCE_PUSH_PET_HOB;

extern EFI_GUID gAmtForcePushPetHobGuid;

#endif

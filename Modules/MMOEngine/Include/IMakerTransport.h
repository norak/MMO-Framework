/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef IMAKERTRANSPORT_H
#define IMAKERTRANSPORT_H

#include "INetTransport.h"

class DllExport IMakerTransport
{
public:
  IMakerTransport();
  virtual ~IMakerTransport();
  
  virtual INetTransport* New() = 0;
  virtual void Delete(INetTransport* pTransport)= 0;
};

#endif
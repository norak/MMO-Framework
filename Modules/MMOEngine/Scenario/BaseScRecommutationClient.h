/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef BASE_SC_RECOMMUTATION_CLIENT_H
#define BASE_SC_RECOMMUTATION_CLIENT_H

#include "IScenario.h"
#include "DescRecvSession.h"
#include "BaseScRecommutationClient_Struct.h"
#include "DescCallBack.h"
#include "MapCallBack.h"

namespace nsMMOEngine
{
  class  TContextScRecommutationClient;
  struct TDescRequestConnectForRecipient;
  class TBaseScRecommutationClient
  {
  protected:
	  IScenario* mScenario;
  public:
	  TBaseScRecommutationClient(IScenario* pSc);
    virtual ~TBaseScRecommutationClient();

    void Recv(TDescRecvSession* pDesc);
    virtual void Work(unsigned int time_ms) = 0;

  protected:
    TContextScRecommutationClient* Context();

    unsigned int GetID_SessionClientSlave();
    void SetID_SessionClientSlave(unsigned int id);
    unsigned int GetID_SessionMasterSlave();
    void SetID_SessionMasterSlave(unsigned int id);
  protected:
    virtual void RecvInherit(TDescRecvSession* pDesc) = 0;
  protected:
    void SetTimeWaitForNow();
  protected:
    // �� Scenario
    bool Begin();
    void End();
  protected:
    void NeedContextByClientKey(unsigned int key);
    void NeedContextByClientSessionForSlave(unsigned int id_session, bool donor);
    void NeedContextByClientKeyForSlave(unsigned int key, bool donor);
    void NeedSessionDonorByClientKey(IScenario* pScenario);
    void EventActivate();
    void EventDisconnectClient(unsigned int key);
    void EventTimeClientElapsed(unsigned int key);// ����� ����� �������� ������ �� ������� �� Slave

    void NeedContextByRequestForRecipient(TDescRequestConnectForRecipient* pDesc);
  };
}
#endif

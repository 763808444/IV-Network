/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CIVPhysical_h
#define CIVPhysical_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVDynamicEntity.h"
#include <IV/CIVScriptEnums.h>
#include "CIVWeaponInfo.h"

class IVPhysical : public IVDynamicEntity
{
public:
        // 000-10C
        // 13C - In Water (BYTE)?
        PAD(IVPhysical, pad0, 0xD8);    // 10C-1E4
        // 0x1BC - IVEntity * m_pAttachedToEntity;
        // 0x140 - BYTE m_byteAttachedToEntity;
        // 0x150 - IVEntity * m_pCollidedEntity;
        // 0x1AA - BYTE m_byteHasDamageEntity;
        // 0x1C0 - CVector3 vecAttachedOffset;
        // 0x1D0 - Quaternion quatAttachedOffset;
        IVEntity * m_pLastDamageEntity; // 1E4-1E8
        PAD(IVPhysical, pad1, 0x4);     // 1E8-1EC
        eWeaponType m_lastDamageWeapon; // 1EC-1F0 // -1: None, eWeaponType: Weapon
        float m_fHealth;                // 1F0-1F4
        PAD(IVPhysical, pad3, 0x1C);    // 1F4-210

        virtual					~IVPhysical();
        virtual bool			Function55(); 
        virtual void			Function56(); // seems get flag
        virtual void			Function57(); // something with bound or so
        virtual void			Function58(); // nullsub
        virtual CVector3*		GetVelocity(CVector3*);
        virtual void			SetHealth(float);
        virtual void			SetHealth(float, int);
        virtual void			AddHealth(float);
        virtual float			GetHealth();
		virtual void			Function64(); // something with network object
		virtual void			Function65(); // return 1;
		virtual void			Function66(); // return 1;
        virtual CVector3*		Function67(CVector3*); // sets something
		virtual void			Function68(); // unregister reference
		virtual void			Function69(); // physics calculation
		virtual void			Function70();
		virtual void			Function71();
};

class CIVPhysical : public CIVDynamicEntity
{
public:
        CIVPhysical();
        CIVPhysical(IVPhysical * pPhysical);
        ~CIVPhysical();

        void         SetPhysical(IVPhysical * pPhysical);
        IVPhysical * GetPhysical();

        void         SetMoveSpeed(const CVector3& vecMoveSpeed);
        void         GetMoveSpeed(CVector3& vecMoveSpeed);
        void         SetTurnSpeed(const CVector3& vecTurnSpeed);
        void         GetTurnSpeed(CVector3& vecTurnSpeed);
        void         SetLastDamageEntity(IVEntity * pLastDamageEntity);
        IVEntity *   GetLastDamageEntity();
        void         SetHealth(float fHealth);
        float        GetHealth();
};

#endif // CIVPhysical_h
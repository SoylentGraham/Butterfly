#pragma once

#include "BPacket.h"


class BEntityRef
{
public:
	BEntityRef(uint32 Ref=0) :
		mRef	( Ref )
	{
	}

	bool		IsValid() const	{	return mRef != 0;	}

public:
	uint32		mRef;	//	unique ref
};


//----------------------------------------
//	generic data
//----------------------------------------
class BEntityInfo
{
public:
	BufferString<50>	mName;
};


//----------------------------------------
//	A thing in the world
//----------------------------------------
class BEntity
{
public:
	explicit BEntity(const BEntityInfo& Info,const BEntityRef& Ref) :
		mInfo	( Info ),
		mRef	( Ref )
	{
	}

	const BEntityRef&	GetRef() const		{	return mRef;	}
	const BEntityInfo&	GetInfo() const		{	return mInfo;	}

protected:
	BEntityInfo			mInfo;

private:
	BEntityRef			mRef;
};

template<class STRING>
inline STRING& operator<<(STRING& str,const BEntity& Value)
{
	str << "E." << Value.GetInfo().mName;
	return str;
}


//----------------------------------------
//	he lives, he learns, he loves.
//----------------------------------------
class BAgent : public BEntity
{
public:
	explicit BAgent(const BEntityInfo& Info,const BEntityRef& Ref);
};

template<class STRING>
inline STRING& operator<<(STRING& str,const BAgent& Value)
{
	str << "A." << Value.GetInfo().mName;
	return str;
}

//----------------------------------------
//	somwhere for humans to be
//----------------------------------------
class BBuilding : public BEntity
{
public:
	explicit BBuilding(const BEntityInfo& Info,const BEntityRef& Ref);
};

template<class STRING>
inline STRING& operator<<(STRING& str,const BBuilding& Value)
{
	str << "B." << Value.GetInfo().mName;
	return str;
}





namespace BLondonCommand
{
	enum Type
	{
		Invalid,

		StepForward,
		StepBackward,

		TestPopulate,
	};

	BufferString<100>	ToString(Type Button);
	Type				ToType(const BufferString<100>& Name);
	void				GetArray(ArrayBridge<Type>& Array);
};
SOY_DECLARE_ENUM(BLondonCommand);



class BPacketCommand : public BPacket
{
public:
	BLondonCommand::Type	mCommand;
};


//------------------------------------
//	world simulator
//------------------------------------
class BLondon
{
public:
	BLondon();
	
	void			Update();
		
	void			SendPacket(const BPacketCommand& Packet)	{	mPackets.PushBack( Packet );	}

	const SoyTime&	GetTime() const								{	return mTime;	}

	BAgent*			AllocAgent(const BEntityInfo& Info);
	BBuilding*		AllocBuilding(const BEntityInfo& Info);

protected:
	void			HandlePackets();
	void			HandlePacket(const BPacketCommand& Packet);

private:
	Array<BPacketCommand>	mPackets;
	SoyTime					mTime;

	uint32					mLastEntityRef;
	Array<BAgent*>			mAgents;
	Array<BBuilding*>		mBuildings;
};


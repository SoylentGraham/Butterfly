#include "BLondon.h"



BufferString<100> BLondonCommand::ToString(BLondonCommand::Type Button)
{
	switch ( Button )
	{
	case BLondonCommand::StepForward:	return "Step Forward";
	case BLondonCommand::StepBackward:	return "Step Backward";
	case BLondonCommand::TestPopulate:	return "Populate";
	default:							return "???";
	};
}

BLondonCommand::Type BLondonCommand::ToType(const BufferString<100>& Name)
{
	if ( Name == ToString(BLondonCommand::StepForward) )	return BLondonCommand::StepForward;
	if ( Name == ToString(BLondonCommand::StepBackward) )	return BLondonCommand::StepBackward;
	if ( Name == ToString(BLondonCommand::TestPopulate) )	return BLondonCommand::TestPopulate;
	return BLondonCommand::Invalid;
}
	

void BLondonCommand::GetArray(ArrayBridge<Type>& Array)
{
	Array.PushBack( BLondonCommand::StepForward );
	Array.PushBack( BLondonCommand::StepBackward );
	Array.PushBack( BLondonCommand::TestPopulate );
}
	


BLondon::BLondon() :
	mLastEntityRef	( 1 )
{
}

void BLondon::Update()
{
	HandlePackets();
}
	
void BLondon::HandlePackets()
{
	//	fifo
	for ( int i=0;	i<mPackets.GetSize();	i++ )
	{
		HandlePacket( mPackets[i] );
	}
	mPackets.Clear(false);
}

void BLondon::HandlePacket(const BPacketCommand& Packet)
{
	switch ( Packet.mCommand )
	{
	case BLondonCommand::StepBackward:
		mTime.mTime -= 1;
		break;

	case BLondonCommand::StepForward:
		mTime.mTime += 1;
		break;
	}
}


#include "BRender.h"





BPanel::BPanel() :
	mGui	( NULL )
{
	float Width = 300;
	float Border = 5;

	mGui = new ofxUIScrollableCanvas( Border, Border, ofGetWidth()-Border-Border, ofGetHeight()-Border-Border );
	mGui->setScrollAreaToScreen();
    mGui->setScrollableDirections(false, true);

	ofAddListener( mGui->newGUIEvent, this, &BPanel::OnGuiEvent );
	mGui->setDrawWidgetPadding(true);

	mGui->autoSizeToFitWidgets();
}

BPanel::~BPanel()
{
	if ( mGui )
	{
		delete mGui; 
		mGui = NULL;
	}
}

void BPanel::OnGuiEvent(ofxUIEventArgs &e)
{
	auto kind = e.widget->getKind(); 
	switch ( kind )
	{
		case OFX_UI_WIDGET_BUTTON:
		{
			ofxUIButton& Button = *static_cast<ofxUIButton*>( e.widget );
			if ( Button.getValue() )
				OnButtonDown( Button.getName().c_str() );
			else
				OnButtonUp( Button.getName().c_str() );
		};
	}
}



BLondonPanel::BLondonPanel(BLondon& London) :
	mLondon			( London ),
	BButtonPanel	( "London" ),
	mTimeLabel		( NULL )
{
    ofAddListener( ofEvents().update, this, &BLondonPanel::OnUpdate );
	mTimeLabel = new ofxUILabel( "", OFX_UI_FONT_SMALL );
	mGui->addWidgetDown( mTimeLabel); 
	mGui->autoSizeToFitWidgets();
}

void BLondonPanel::OnUpdate(ofEventArgs &data)
{
	String TimeLabel;
	TimeLabel << "Time: " << mLondon.GetTime();
	mTimeLabel->setLabel( static_cast<const char*>(TimeLabel) );
}

void BLondonPanel::OnButtonDown(BLondonCommand::Type Button)
{
	BPacketCommand Packet;
	Packet.mCommand = Button;
	mLondon.SendPacket( Packet );
}




BRender::BRender(BLondon& London) :
	mLondon				( London ),
	mBackgroundColour	( 233, 27, 52 )
{
	//	create new panel
	auto* pControlPanel = new BLondonPanel( London );
	mPanels.PushBack( pControlPanel );

}

BRender::~BRender()
{

}

void BRender::Render()
{
	ofBackground( mBackgroundColour ); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}

